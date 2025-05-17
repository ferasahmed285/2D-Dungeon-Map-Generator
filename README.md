## 2D Dungeon Map Generator

A C++ implementation of a **Binary Space Partitioning** (BSP) algorithm for procedurally generating 2D dungeon layouts.

### Features

* **BSP-based partitioning** of a rectangular map into smaller cells
* **Room placement** within leaf cells
* **Corridor generation** to connect rooms
* Cleanly separated code in `Header Files/` and `Source Files/` directories

### Prerequisites

* A C++17‑compatible compiler (e.g. GCC, Clang, MSVC)
* (Optional) CMake for build automation

### Building

**Using CMake**

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

**Manual compilation**

```bash
g++ -std=c++17 \
    -I"Header Files" \
    Source\ Files/*.cpp \
    -o DungeonGenerator
```

### Usage

1. Compile as above to produce the `DungeonGenerator` executable.
2. Run it (e.g. `./DungeonGenerator`) – adjust parameters in the code to control map size, minimum room size, etc.
3. Integrate the generated geometry (room bounds and corridor segments) into your game or rendering pipeline.

### Project Structure

```
/
├── Header Files/       ← BSP classes and data structures (.h)
├── Source Files/       ← Algorithm implementation (.cpp)
└── README.md           ← Project title & description
```

### Contributing

1. Fork the repository.
2. Create a feature branch.
3. Submit a pull request with your improvements.

### License

*No license specified.* If you plan to use or contribute, consider adding an explicit open‑source license.

---

Feel free to tweak any of the build instructions or feature descriptions to match your local setup!
