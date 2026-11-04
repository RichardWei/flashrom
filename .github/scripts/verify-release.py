#!/usr/bin/env python3
"""Check packaged release binaries without accessing programmer hardware."""

import argparse
import ctypes
import os
from pathlib import Path
import re
import subprocess


PUBLIC_SYMBOLS = (
    "flashrom_version_info", "flashrom_init", "flashrom_shutdown",
    "flashrom_create_context", "flashrom_programmer_init",
    "flashrom_programmer_shutdown", "flashrom_flash_probe_v2",
    "flashrom_flash_getsize", "flashrom_image_read", "flashrom_data_free",
    "flashrom_flash_release",
)


def output(*args):
    return subprocess.check_output(args, text=True).strip()


def verify_library(path):
    path = path.resolve(strict=True)
    if ctypes.sizeof(ctypes.c_void_p) != 8:
        raise RuntimeError("Release smoke check requires a 64-bit Python")
    dll_directory = os.add_dll_directory(str(path.parent)) if os.name == "nt" else None
    try:
        library = ctypes.CDLL(str(path))
        for name in PUBLIC_SYMBOLS:
            getattr(library, name)
        library.flashrom_version_info.argtypes = []
        library.flashrom_version_info.restype = ctypes.c_char_p
        library.flashrom_init.argtypes = [ctypes.c_int]
        library.flashrom_init.restype = ctypes.c_int
        library.flashrom_shutdown.argtypes = []
        library.flashrom_shutdown.restype = ctypes.c_int
        print(f"Loaded {path}: {library.flashrom_version_info()!r}", flush=True)
        if library.flashrom_init(1) != 0:
            raise RuntimeError("flashrom_init failed")
        if library.flashrom_shutdown() != 0:
            raise RuntimeError("flashrom_shutdown failed")
    finally:
        if dll_directory is not None:
            dll_directory.close()


def dependencies(path):
    lines = output("otool", "-L", str(path)).splitlines()[1:]
    return [line.strip().split(" (compatibility version", 1)[0] for line in lines]


def verify_macos(paths):
    """Remove build rpaths, check the dependency closure, and ad-hoc sign copies."""
    paths = [path.resolve(strict=True) for path in paths]
    for path in paths:
        if output("lipo", "-archs", str(path)) != "x86_64":
            raise RuntimeError(f"Expected an Intel x64 binary: {path}")
        load_commands = output("otool", "-l", str(path))
        rpaths = re.findall(
            r"cmd LC_RPATH\s+cmdsize \d+\s+path (.*?) \(offset \d+\)",
            load_commands,
        )
        for rpath in dict.fromkeys(rpaths):
            subprocess.run(
                ["install_name_tool", "-delete_rpath", rpath, str(path)], check=True
            )

    queue = list(paths)
    visited = set()
    while queue:
        path = queue.pop()
        if path in visited:
            continue
        visited.add(path)
        print(output("otool", "-L", str(path)), flush=True)
        for dependency in dependencies(path):
            if dependency.startswith(("/usr/lib/", "/System/Library/")):
                continue
            if dependency == "@rpath/libflashrom.1.dylib" and path.name == "libflashrom.1.dylib":
                continue  # The dylib's own install ID, not an imported dependency.
            if dependency == "@executable_path/libflashrom.1.dylib" and path.name == "flashrom":
                target = path.parent / "libflashrom.1.dylib"
                if target not in paths:
                    raise RuntimeError(f"Missing package library: {target}")
                queue.append(target)
                continue
            if dependency == "/opt/local/lib/libusb-1.0.0.dylib":
                target = Path(dependency).resolve(strict=True)
                if output("lipo", "-archs", str(target)).split().count("x86_64") != 1:
                    raise RuntimeError(f"libusb has no Intel x64 slice: {target}")
                queue.append(target)
                continue
            raise RuntimeError(f"Unexpected runtime dependency: {path}: {dependency}")

    for path in paths:
        subprocess.run(["codesign", "--force", "--sign", "-", str(path)], check=True)
        subprocess.run(["codesign", "--verify", "--strict", str(path)], check=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("library").add_argument("path", type=Path)
    commands.add_parser("macos").add_argument("paths", type=Path, nargs="+")
    args = parser.parse_args()
    if args.command == "library":
        verify_library(args.path)
    else:
        verify_macos(args.paths)


if __name__ == "__main__":
    main()
