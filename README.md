
---

# seeb - A C++ Multi-Project Build System

**seeb** is a lightweight, customizable, and scalable build system for C++ projects. It allows you to manage and compile multiple C++ projects through a simple configuration file, making it ideal for developers working with multiple codebases or libraries.

This tool is designed to make compiling C++ projects easier by handling project-specific settings such as compilers, include directories, library paths, and libraries.

---

## Features

- **Multi-Project Support**: Manage and build multiple C++ projects with a single configuration.
- **Simple Configuration**: Use a JSON file to define project settings, including compilers, include paths, and libraries.
- **Customizable**: Easily configure different settings for each project, including the compiler and dependencies.
- **Template Generation**: Automatically generate a default configuration template when no configuration file exists.
- **Scalable Design**: Designed to scale well for managing multiple projects and their dependencies.

---

## Installation

### Prerequisites

- **C++17 or later**: Make sure you are using a compiler that supports C++17.
- **Dependencies**:
  - [nlohmann::json](https://github.com/nlohmann/json) for JSON parsing.
  - **C++ Standard Library** (filesystem, etc.).

### Clone the Repository

```bash
git clone https://github.com/vishal-ahirwar/seeb.git
cd seeb
```

### Build and Compile

To compile the project, run the following:
if aura is installed
```bash
aura compile
```
otherwise
```
cmake -S . -B build -DJSON_INCLUDE_DIR=external/json -DCMAKE_CXX_COMPILER=clang++ -DSTATIC_LINK=ON
cmake --build build

```
---

## Usage

### 1. Configure Your Projects

Create a configuration file called `see-config.json` in the root of your project directory. This JSON file defines the settings for each C++ project you want to manage.

#### Example `see-config.json`

```json
{
  "yourprojectname": {
    "compiler": "g++",
    "include": ["include", "/usr/include"],
    "libsDir": ["/path/to/libs"],
    "libs": ["lib1", "lib2"]
  },
  "youranotherproject": {
    "compiler": "clang++",
    "include": ["include"],
    "libsDir": ["/path/to/libs"],
    "libs": ["lib3"]
  }
}
```

- **`compiler`**: The C++ compiler to use (e.g., `g++`, `clang++`).
- **`include`**: List of directories containing header files for the project.
- **`libsDir`**: List of directories containing libraries to link.
- **`libs`**: List of libraries to link against.

### 2. Run the Build System

Once the configuration file is ready, you can start the build process by running the following command in the root directory:

```bash
./seeb
```

This command will use the settings in the `see-config.json` file to compile the projects defined in it.

---

## Advanced Features (Planned)

- **Dependency Resolution**: Future versions will handle dependencies between projects and ensure that projects are compiled in the correct order.
- **Parallel Compilation**: Support for multi-threaded builds to improve the build time.
- **Cross-Platform Support**: Extending support for different platforms (Windows, Linux, macOS) and additional compilers.

---

## Contributing

We welcome contributions! If you'd like to contribute to the **seeb** project, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to your fork (`git push origin feature-branch`).
6. Open a pull request to the main repository.

If you find any bugs or have feature requests, please [open an issue](https://github.com/vishal-ahirwar/seeb/issues).

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- [nlohmann::json](https://github.com/nlohmann/json) for JSON parsing.
- [CMake](https://cmake.org/) for managing the build process.
- [GitHub](https://github.com) for providing the platform to share and collaborate on the project.

---
