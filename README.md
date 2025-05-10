# MineBreaker

Cross-platform 2D Game Project using C++ / OpenGL / GLFW / Premake5.

---

## 🔧 Build Instructions

### Requirements
- Visual Studio 2022 or later
- [Premake5](https://premake.github.io/download/)
- Git (for submodules)

### Clone with Submodules

```bash
git clone --recursive https://github.com/heosumin518/MineBreaker.git
```

### If you forgot --recursive, run:
```bash
git submodule update --init --recursive
```

### Generate Visual Studio project files

1. [Download premake5.exe](https://github.com/premake/premake-core/releases) and place it in the project root directory (next to generate.bat and premake5.lua).
2. Then run:

```bash
./generate.bat
```

### Output Structure (after build)

All compiled output files are placed into the `Binaries/` directory,  
and intermediate object files go into `Intermediate/`.
