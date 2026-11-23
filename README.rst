flashrom CH347 fork
===================

flashrom detects, reads, writes, verifies, and erases flash chips. This fork's
``develop`` branch focuses on programming SPI flash with WCH CH347 adapters.
The local ``main`` branch and the upstream snapshot used for this comparison
both point to ``69aa8f28``.

.. contents::
   :local:
   :depth: 1

English
-------

Differences from upstream
~~~~~~~~~~~~~~~~~~~~~~~~~

* Upstream already supports the CH347T and CH347F through ``ch347_spi`` using
  libusb. This fork uses the WCH driver and loads ``CH347DLLA64.DLL`` at
  runtime on Windows. On Linux and macOS it uses libusb, with changes to
  USB interface claiming and checks for incomplete SPI configuration transfers.
* The default SPI clock changes from 15 MHz to 30 MHz. Set
  ``ch347_spi:spispeed=15M`` to use the upstream baseline's default speed.
* The fork adds a Meson option that links the classic CLI to shared
  ``libflashrom``. The default CLI build still links ``libflashrom``
  statically. Applications should use the public functions declared in
  ``libflashrom.h``.

Downloads and runtime requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `fork's GitHub Releases`_ provide CH347-only builds for Windows x64
(MSYS2 UCRT64) and Intel macOS. The workflow publishes two ZIPs per platform
after both platform jobs succeed on a push to ``develop``. The release's
``SHA256SUMS.txt`` lists the SHA-256 checksums for the four ZIPs.

.. list-table::
   :header-rows: 1

   * - Platform
     - CLI with static ``libflashrom``
     - CLI with shared ``libflashrom``
   * - Windows x64
     - ``flashrom-win-x64-<version>.zip``
     - ``flashrom-win-x64-shared-<version>.zip``
   * - Intel macOS
     - ``flashrom-macos-intel-<version>.zip``
     - ``flashrom-macos-intel-shared-<version>.zip``

The shared ZIPs include the CLI, shared library, ``libflashrom.h``, and the
`shared library guide`_ with C and C++ examples. Either CLI variant may
require third-party runtime libraries.

* **Windows x64** — Keep the packaged DLLs next to the executable. Install the
  WCH driver and obtain ``CH347DLLA64.DLL`` from WCH. Place it beside the
  executable. Both package variants require it for CH347 operations.
* **Intel macOS** — Install MacPorts libusb with
  ``sudo port install libusb``. Both package variants load it from
  ``/opt/local/lib``.

Read a backup
~~~~~~~~~~~~~

From the extracted shared ZIP, run the command for your platform. Keep a
copy of the backup before writing to the flash chip.

.. code-block:: powershell

   .\flashrom.exe -p ch347_spi -r backup.bin

.. code-block:: sh

   ./flashrom -p ch347_spi -r backup.bin

The ZIPs with static ``libflashrom`` use versioned executable names. Use the
filename from the ZIP in the same command. To read at 15 MHz, use
``-p ch347_spi:spispeed=15M``.

Build from source
~~~~~~~~~~~~~~~~~

Use Meson, Ninja, a C compiler, and the libusb development files. Use the
MSYS2 UCRT64 shell on Windows. These configurations match the CH347-only
release builds and use separate build directories.

.. code-block:: sh

   meson setup build-static -Dprogrammer=ch347_spi -Ddefault_library=static \
       -Drpmc=disabled -Dtests=disabled -Ddocumentation=disabled -Dman-pages=disabled
   meson compile -C build-static

   meson setup build-shared -Dprogrammer=ch347_spi -Ddefault_library=shared \
       -Dcli_link_mode=shared -Drpmc=disabled -Dtests=disabled \
       -Ddocumentation=disabled -Dman-pages=disabled
   meson compile -C build-shared

See the `upstream build guide`_ and the `flashrom CLI manual`_ for general
build instructions and command options.

What the release workflow checks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The workflow runs ``--version`` on the packaged CLIs and checks that the
shared libraries load, export the expected public symbols, and can initialize
and shut down. CH347 detection, reading, writing, and erasing require
separate hardware testing. The Windows unit-test suite skips four CH347
lifecycle and fault cases that use libusb mocks.

简体中文
--------

flashrom 可检测、读取、写入、验证和擦除闪存芯片。本 fork 的
``develop`` 分支主要用于通过 WCH CH347 编程器操作 SPI 闪存。本地
``main`` 和本次对比使用的上游快照均指向 ``69aa8f28``。

与上游的区别
~~~~~~~~~~~~

* 上游已经通过 libusb 为 CH347T 和 CH347F 提供 ``ch347_spi`` 支持。
  本 fork 在 Windows 上使用 WCH 驱动，并在运行时加载
  ``CH347DLLA64.DLL``。Linux 和 macOS 使用 libusb，同时调整了 USB
  接口占用的处理，并增加了对 SPI 配置传输长度的检查。
* SPI 默认时钟从 15 MHz 调整为 30 MHz。指定
  ``ch347_spi:spispeed=15M`` 可使用上游基线的默认速率。
* 本 fork 新增 Meson 选项，让经典 CLI 可以链接动态版
  ``libflashrom``。默认构建仍采用静态链接。应用程序应调用
  ``libflashrom.h`` 中声明的公共函数。

下载与运行依赖
~~~~~~~~~~~~~~

`本 fork 的 GitHub Releases`_ 提供仅启用 CH347 的 Windows x64
（MSYS2 UCRT64）和 Intel macOS 构建。推送到 ``develop`` 后，两个平台的
构建任务均成功时，发布流程会为每个平台发布两种 ZIP。发布页中的
``SHA256SUMS.txt`` 提供这四个 ZIP 的 SHA-256 校验值。

.. list-table::
   :header-rows: 1

   * - 平台
     - 静态链接 ``libflashrom`` 的 CLI
     - 动态链接 ``libflashrom`` 的 CLI
   * - Windows x64
     - ``flashrom-win-x64-<version>.zip``
     - ``flashrom-win-x64-shared-<version>.zip``
   * - Intel macOS
     - ``flashrom-macos-intel-<version>.zip``
     - ``flashrom-macos-intel-shared-<version>.zip``

动态链接版 ZIP 包含 CLI、动态库、``libflashrom.h`` 和带有 C、C++
示例的\ `动态库调用指南`_。两种 CLI 都可能依赖第三方运行库。

* **Windows x64**：保留与可执行文件同目录的包内 DLL。安装 WCH 驱动，
  从 WCH 获取 ``CH347DLLA64.DLL``，并将其放在可执行文件旁。两个版本
  执行 CH347 操作时都需要该 DLL。
* **Intel macOS**：运行 ``sudo port install libusb`` 安装 MacPorts 的
  libusb。两个版本均从 ``/opt/local/lib`` 加载该依赖。

读取备份
~~~~~~~~

解压动态链接版 ZIP，在解压目录下运行对应平台的命令。写入闪存前，请保留
一份备份。

.. code-block:: powershell

   .\flashrom.exe -p ch347_spi -r backup.bin

.. code-block:: sh

   ./flashrom -p ch347_spi -r backup.bin

静态链接版 ZIP 中的可执行文件名带版本号。运行同一条命令时，
请使用解压后的实际文件名。若要以 15 MHz 读取，使用
``-p ch347_spi:spispeed=15M``。

从源码构建
~~~~~~~~~~

准备 Meson、Ninja、C 编译器以及 libusb 开发文件。在 Windows 上使用
MSYS2 UCRT64 shell。以下配置与仅启用 CH347 的发布构建一致，分别使用
独立的构建目录。

.. code-block:: sh

   meson setup build-static -Dprogrammer=ch347_spi -Ddefault_library=static \
       -Drpmc=disabled -Dtests=disabled -Ddocumentation=disabled -Dman-pages=disabled
   meson compile -C build-static

   meson setup build-shared -Dprogrammer=ch347_spi -Ddefault_library=shared \
       -Dcli_link_mode=shared -Drpmc=disabled -Dtests=disabled \
       -Ddocumentation=disabled -Dman-pages=disabled
   meson compile -C build-shared

通用构建和命令选项见\ `上游构建指南`_\ 和 `flashrom 命令手册`_。

发布验证范围
~~~~~~~~~~~~

发布流程运行包内 CLI 的 ``--version``，并检查动态库能否加载、是否导出
预期的公共符号，以及能否初始化和关闭。CH347 探测、读取、写入和擦除需要
单独进行实机验证。Windows 单元测试跳过四个使用 libusb 模拟的 CH347
生命周期与故障用例。

Upstream and credits / 上游与致谢
---------------------------------

Thanks to the `upstream flashrom project`_ and
`ZhiyuanYuanNJ/flashrom`_ for their work. The upstream project also maintains
the `official flashrom website`_.

感谢\ `上游 flashrom 项目`_\ 和 `ZhiyuanYuanNJ/flashrom`_ 的工作。
`flashrom 官方网站`_\ 由上游项目维护。

.. _fork's GitHub Releases: https://github.com/RichardWei/flashrom/releases
.. _本 fork 的 GitHub Releases: https://github.com/RichardWei/flashrom/releases
.. _shared library guide: https://github.com/RichardWei/flashrom/blob/develop/SHARED_CLI.md
.. _动态库调用指南: https://github.com/RichardWei/flashrom/blob/develop/SHARED_CLI.md
.. _upstream build guide: https://github.com/flashrom/flashrom/blob/main/doc/dev_guide/building_from_source.rst
.. _上游构建指南: https://github.com/flashrom/flashrom/blob/main/doc/dev_guide/building_from_source.rst
.. _flashrom CLI manual: https://github.com/flashrom/flashrom/blob/main/doc/classic_cli_manpage.rst
.. _flashrom 命令手册: https://github.com/flashrom/flashrom/blob/main/doc/classic_cli_manpage.rst
.. _upstream flashrom project: https://github.com/flashrom/flashrom
.. _上游 flashrom 项目: https://github.com/flashrom/flashrom
.. _ZhiyuanYuanNJ/flashrom: https://github.com/ZhiyuanYuanNJ/flashrom
.. _official flashrom website: https://www.flashrom.org/
.. _flashrom 官方网站: https://www.flashrom.org/
