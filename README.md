# RayClay Tutorial App

A small RayClay application with a collapsible sidebar, browser-style zoom,
a tintable SVG logo, and a custom cross-platform titlebar.

RayClay is fetched from GitHub at configure time, so there is no library source
in this repository. `GIT_TAG main` follows the latest release.

To pin a version, replace `main` in `CMakeLists.txt` with a commit SHA. Do that
for anything you intend to keep building: `main` moves to each new release, and
a release can change the API.

## Prerequisites

CMake 3.21 or newer, a C compiler, and git.

On Linux, RayClay's vendored GLFW needs the X11 and Wayland development headers.
On Debian and Ubuntu:

```sh
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
```

macOS and Windows need only the compiler toolchain. RayClay's own
[getting-started guide](https://github.com/impizulu/rayclay/blob/main/docs/getting-started.md)
is the canonical list if your distribution differs.

## Build

Linux and macOS:

```sh
cmake -S . -B build
cmake --build build --parallel 4
./build/app
```

Windows with a multi-configuration generator:

```powershell
cmake -S . -B build
cmake --build build --config Release --parallel 4
.\build\Release\app.exe
```

This builds Release by default. RayClay only defaults itself to Release when it
is the top-level project, which it is not here, so `CMakeLists.txt` sets the
default on this side.

While developing a custom titlebar, build `Debug` instead. A debug build checks
the two things a custom band has to get right and names them: that the band is
tagged `RC_ID_WINDOW_DRAG`, and that its height matches the strip the OS treats
as draggable. Both checks are compiled out by `NDEBUG`.

The first configure clones RayClay into `build/_deps/`, which needs network
access; later builds in the same directory reuse it. For an air-gapped or
CI-cached build, clone RayClay once yourself and pass
`-DFETCHCONTENT_SOURCE_DIR_RAYCLAY=/path/to/rayclay`, which skips the download
entirely.

Run the executable from the repository root: the window icon and the SVG
artwork are loaded at runtime from `assets/icons/`, by a path relative to the
working directory. On Wayland the window icon is a no-op by design, because the
compositor owns it; check it under X11, Windows or macOS.

## Editor setup

Configure once before opening the project in an editor:

```sh
cmake -S . -B build
```

That writes `build/compile_commands.json`, which is how an editor discovers the
include paths and, more importantly, *which compiler* to ask for the system
header locations. Without it an editor has nothing to work from and marks
includes unresolvable - system headers such as `<stdlib.h>` included - while the
build itself is perfectly fine.

clangd-based editors find the database in `build/` unaided. In VS Code, install
the **CMake Tools** extension and let it configure the project: it supplies
IntelliSense directly and needs no database path at all. To drive the C/C++
extension without it, set `C_Cpp.default.compileCommands` to
`${workspaceFolder}/build/compile_commands.json`.

If the warnings outlive a configure, run **C/C++: Reset IntelliSense Database**
from the command palette. The extension caches hard, and a stale cache looks
exactly like a broken include path.

## Layout

```
main.c              window options and the root layout
src/theme.h         colours, as macros
src/sidebar.h       the collapsible sidebar
src/content.h       the tintable logo and the shortcut list
src/titlebar.h      the custom titlebar and window controls
assets/icons/       runtime SVG artwork and the window icon
```

## Licences

The application code is MIT; see `LICENSE`. `assets/icons/` carries six icons from
[Lucide](https://lucide.dev); their ISC and MIT terms are in
`assets/icons/LICENSE-Lucide.md`. RayClay itself is MIT, and its own dependency
notices ship with it.
