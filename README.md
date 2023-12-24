<div align="center">

[![xc compatible](https://xcfile.dev/badge.svg)](https://xcfile.dev)

</div>

# Simple QMK Inspired Runtime Editable Library (SQIREL)
<sup>(Pronounced *squirrel*)</sup>

## Goals:
- Create an easy to understand and simple keyboard library that allows for runtime layout and configuration edits.
- Make sure it is as documented and clearly organised as possible.
- Keep it independent of any microcontroller.

## Tasks

### Build
Env: PICO_SDK_PATH
Directory: ./build

Builds the keyboard firmware.

```bash
cmake ..
make -j16
cp compile_commands.json ../ # Required file for LSP autocomplete.
```

### Clean
Cleans the build directory for a fresh build.

```bash
rm -rf ./build
mkdir build
```
