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

### Contribution Guidelines

- Fork the repository and create your feature branch.
- Commit your changes with clear messages.
- Submit a pull request for review.
- Ensure code follows the project's style and passes tests.

### License

This project is licensed under the MIT License. See the `LICENSE` file for details.

### Contact

For issues, suggestions, or contributions, please open an issue on the GitHub repository or contact the maintainer through their GitHub profile.

*Note: If you need more detailed documentation or API references, please check the `docs/` folder or inline code comments in the source files.*

[1] https://github.com/GayashaSandeepa/libtiny3d
[2] https://pypi.org/project/tiny-3d-engine/
[3] https://github.com/granberro/tiny3d
[4] https://github.com/wargio/tiny3D
[5] https://huggingface.co/spaces/yuanwenyue/FiT3D/commit/55a66b73fe624f757f9140449664fca30deb0b11
[6] https://github.com/wargio/tiny3D/blob/master/README.md
[7] https://docs.github.com/en/repositories/working-with-files/using-files/working-with-non-code-files
[8] https://archive.org/details/github.com-nv-tlabs-GET3D_-_2022-09-30_02-16-27
[9] https://github.com/HailToDodongo/tiny3d/blob/main/build.sh
[10] https://dev.to/kerthin/18-amazing-github-repositories-that-will-help-you-make-a-beautiful-project-3pgo
[11] https://gist.github.com/creikey/starred?direction=asc&sort=updated