# 动态库调用指南（Windows / macOS）

`shared` 压缩包包含完整的 `flashrom` 命令行程序、动态库和公共头文件
`libflashrom.h`。原有静态链接版本仍在单独的发布包中。动态链接版 CLI 的
CH347 读取命令为 `flashrom.exe -p ch347_spi -r backup.bin`（Windows）或
`./flashrom -p ch347_spi -r backup.bin`（macOS）。

下面演示**自己的 C 或 C++ 程序**如何在运行时调用动态库。示例代码仅在本文档
中，仓库没有新增 C++ 源文件。Windows DLL 由 MinGW 构建，但导出 x64 C ABI，
MSVC x64 程序可用 `LoadLibraryA` / `GetProcAddress` 调用；macOS 用
`dlopen` / `dlsym`。两种平台均无须链接 import `.lib` 或 `.a`。

## 准备和运行依赖

1. 解压对应平台的 `shared` 包，保持动态库、依赖库和示例 EXE 在同一目录。
   Windows 包附带构建时识别出的非系统 DLL。macOS 需安装 MacPorts
   `libusb`：`sudo port install libusb`。
2. 用包内原版 `libflashrom.h` 编译，并确保程序和库均为 x64。原版头文件
   不含 `extern "C"`，且使用 GNU `__attribute__`；下方示例在调用方处理
   MSVC 和 C++ 兼容性，不修改库的头文件。
3. 程序运行时传入动态库路径和输出文件路径。macOS 库名固定为
   `libflashrom.1.dylib`；Windows DLL 文件名以解压包中的实际文件为准。

库分配的探测结果必须用 `flashrom_data_free` 释放。示例自己用 `malloc`
分配的读取缓冲区则用自己的 `free` 释放；不要跨 DLL 边界混用内存管理器。

## C / C++ 通用示例：读取 CH347 芯片

把代码保存为解压目录中的 `flashrom_read.c`。同一文件可分别按 C 和 C++
编译。参数为 `程序 动态库路径 输出文件 [芯片名称]`。若探测到多个芯片，
程序会列出名称；再次运行时传入其中一个名称即可。示例只读取，不写入或擦除。

```c
#include <sys/types.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#ifdef _MSC_VER
#define __attribute__(x)
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "libflashrom.h"
#ifdef __cplusplus
}
#endif
#ifdef _MSC_VER
#undef __attribute__
#endif
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
typedef HMODULE library_handle;
#define OPEN(path) LoadLibraryA(path)
#define SYMBOL(lib, name) GetProcAddress(lib, name)
#define CLOSE(lib) FreeLibrary(lib)
#else
#include <dlfcn.h>
typedef void *library_handle;
#define OPEN(path) dlopen(path, RTLD_NOW | RTLD_LOCAL)
#define SYMBOL(lib, name) dlsym(lib, name)
#define CLOSE(lib) dlclose(lib)
#endif

typedef const char *(*version_fn)(void);
typedef int (*init_fn)(int);
typedef int (*shutdown_fn)(void);
typedef int (*context_fn)(struct flashrom_flashctx **);
typedef int (*programmer_fn)(struct flashrom_programmer **, const char *, const char *);
typedef int (*programmer_end_fn)(struct flashrom_programmer *);
typedef int (*probe_fn)(struct flashrom_flashctx *, const char ***,
                        const struct flashrom_programmer *, const char *);
typedef size_t (*size_fn)(const struct flashrom_flashctx *);
typedef int (*read_fn)(struct flashrom_flashctx *, void *, size_t);
typedef int (*free_fn)(void *);
typedef void (*release_fn)(struct flashrom_flashctx *);

int main(int argc, char **argv)
{
    library_handle lib;
    struct flashrom_programmer *programmer = NULL;
    struct flashrom_flashctx *flash = NULL;
    const char **matches = NULL;
    unsigned char *image = NULL;
    FILE *output = NULL;
    size_t image_size = 0;
    int initialized = 0, programmer_started = 0, found = 0, result = 1;
    version_fn version;
    init_fn init;
    shutdown_fn shutdown;
    context_fn create_context;
    programmer_fn programmer_init;
    programmer_end_fn programmer_shutdown;
    probe_fn probe;
    size_fn getsize;
    read_fn read_image;
    free_fn data_free;
    release_fn release;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s LIBRARY OUTPUT.bin [CHIP]\n", argv[0]);
        return 2;
    }
    lib = OPEN(argv[1]);
    if (!lib) {
        fprintf(stderr, "Cannot load library: %s\n", argv[1]);
        return 1;
    }
    version = (version_fn)SYMBOL(lib, "flashrom_version_info");
    init = (init_fn)SYMBOL(lib, "flashrom_init");
    shutdown = (shutdown_fn)SYMBOL(lib, "flashrom_shutdown");
    create_context = (context_fn)SYMBOL(lib, "flashrom_create_context");
    programmer_init = (programmer_fn)SYMBOL(lib, "flashrom_programmer_init");
    programmer_shutdown = (programmer_end_fn)SYMBOL(lib, "flashrom_programmer_shutdown");
    probe = (probe_fn)SYMBOL(lib, "flashrom_flash_probe_v2");
    getsize = (size_fn)SYMBOL(lib, "flashrom_flash_getsize");
    read_image = (read_fn)SYMBOL(lib, "flashrom_image_read");
    data_free = (free_fn)SYMBOL(lib, "flashrom_data_free");
    release = (release_fn)SYMBOL(lib, "flashrom_flash_release");
    if (!version || !init || !shutdown || !create_context ||
        !programmer_init || !programmer_shutdown || !probe || !getsize ||
        !read_image || !data_free || !release) {
        fprintf(stderr, "Required libflashrom symbol is missing\n");
        goto done;
    }
    printf("libflashrom: %s\n", version());
    if (init(1) != 0) { fprintf(stderr, "Initialization failed\n"); goto done; }
    initialized = 1;
    if (create_context(&flash) != 0 || !flash) {
        fprintf(stderr, "Context creation failed\n"); goto done;
    }
    if (programmer_init(&programmer, "ch347_spi", NULL) != 0) {
        fprintf(stderr, "Cannot initialize CH347\n"); goto done;
    }
    programmer_started = 1;
    found = probe(flash, &matches, programmer, argc == 4 ? argv[3] : NULL);
    if (found != 1 || !matches || !matches[0]) {
        int i;
        fprintf(stderr, "Expected one chip; probe returned %d\n", found);
        if (matches)
            for (i = 0; matches[i]; ++i) fprintf(stderr, "  %s\n", matches[i]);
        goto done;
    }
    printf("Chip: %s\n", matches[0]);
    image_size = getsize(flash);
    if (image_size == 0 || !(image = (unsigned char *)malloc(image_size))) {
        fprintf(stderr, "Cannot allocate image buffer\n"); goto done;
    }
    if (read_image(flash, image, image_size) != 0) {
        fprintf(stderr, "Chip read failed\n"); goto done;
    }
    output = fopen(argv[2], "wb");
    if (!output || fwrite(image, 1, image_size, output) != image_size) {
        fprintf(stderr, "Cannot write complete output file\n"); goto done;
    }
    if (fclose(output) != 0) {
        output = NULL;
        fprintf(stderr, "Cannot close output file\n"); goto done;
    }
    output = NULL;
    printf("Saved %zu bytes to %s\n", image_size, argv[2]);
    result = 0;

done:
    if (output) fclose(output);
    free(image);
    if (matches && data_free) data_free((void *)matches);
    if (flash && release) release(flash);
    if (programmer_started && programmer_shutdown(programmer) != 0) result = 1;
    if (initialized && shutdown() != 0) result = 1;
    CLOSE(lib);
    return result;
}
```

读取成功后才会打开输出文件；如果写文件或关闭文件失败，输出路径可能留下
不完整文件，应检查并删除后重试。

### Windows：MSVC 编译与运行

在 **x64 Native Tools Command Prompt for VS** 中进入解压目录。DLL 及其依赖
DLL 要与生成的示例 EXE 放在同一目录。`/TP` 把同一份 `.c` 文件按 C++ 编译：

```bat
cl /nologo /W4 /std:c11 /TC /I. flashrom_read.c /Feread_c.exe
cl /nologo /W4 /EHsc /std:c++17 /TP /I. flashrom_read.c /Feread_cpp.exe
```

例如包内 DLL 名为 `libflashrom-1.dll` 时：

```bat
read_c.exe .\libflashrom-1.dll backup.bin
read_cpp.exe .\libflashrom-1.dll backup.bin
```

把示例中的 DLL 名称替换成解压包中的实际名称。若加载失败，检查 EXE、DLL
及依赖 DLL 均为 x64，并确认依赖 DLL 位于 EXE 所在目录。可用
`dumpbin /exports libflashrom-1.dll` 查看公共函数是否导出。

### macOS：Clang 编译与运行

在解压目录运行以下命令。同一份代码分别按 C 和 C++ 编译；无需 `-ldl`
或链接 `libflashrom`：

```sh
clang -std=c11 -Wall -Wextra -I. flashrom_read.c -o read_c
clang++ -std=c++17 -Wall -Wextra -x c++ -I. flashrom_read.c -o read_cpp
./read_c ./libflashrom.1.dylib backup.bin
./read_cpp ./libflashrom.1.dylib backup.bin
```

如果出现 `Library not loaded`，用 `otool -L libflashrom.1.dylib` 检查
MacPorts `libusb` 依赖，并确认运行机器与 Intel 包的架构一致。

动态链接版 CLI 还需要库的部分内部符号，但这些符号不是稳定的外部接口。
其他程序只调用 `libflashrom.h` 中声明的公共函数。
