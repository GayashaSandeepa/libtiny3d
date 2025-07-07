# libtiny3d
### 3D Software Renderer Library in C

#### Project Overview

**libtiny3d** is a C library designed for 3D software rendering. It aims to provide a lightweight, efficient, and easy-to-integrate solution for rendering 3D graphics in environments where hardware acceleration is unavailable or unnecessary.

### Features

- **Pure Software Rendering:** No GPU or hardware acceleration required.
- **Written in C:** Ensures portability and ease of integration into C/C++ projects.
- **Basic 3D Primitives:** Supports rendering of triangles, lines, and points.
- **Customizable Pipeline:** Modular design allows for extending or modifying the rendering pipeline.
- **Minimal Dependencies:** Designed to be lightweight and easy to build.

### Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/GayashaSandeepa/libtiny3d.git
   ```
2. **Build the Library:**
   - Navigate to the project directory.
   - Use the provided `Makefile` (if available) or compile the source files manually:
     ```bash
     cd libtiny3d
     make
     ```
   - Alternatively, compile with:
     ```bash
     gcc -o libtiny3d.a *.c
     ```

### Usage Example

```c
#include "tiny3d.h"

int main() {
    // Initialize renderer and context
    tiny3d_context ctx;
    tiny3d_init(&ctx, width, height);

    // Define your 3D objects and transformations here

    // Render loop
    while (running) {
        tiny3d_clear(&ctx);
        // Draw your objects
        tiny3d_draw_triangle(&ctx, ...);
        // Present frame
        tiny3d_present(&ctx);
    }

    tiny3d_destroy(&ctx);
    return 0;
}
```

### Folder Structure

| Folder/File      | Description                    |
|------------------|-------------------------------|
| `src/`           | Library source code           |
| `include/`       | Header files                  |
| `examples/`      | Example/demo applications     |
| `tests/`         | Unit tests (if available)     |
| `README.md`      | Project documentation         |
| `LICENSE`        | License information           |
