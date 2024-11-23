# Revolve Labtool

## Build the project

Open ``x86 Native Tools Command Prompt for VS 20XX`` and go to the Revolve Labtool's directory.
```bash
mkdir build
cd build
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug # Configure the project each time you edit CMakeLists.txt
cmake --build . # Build the injector and DLL each time you edit the source code
```

## Pre-commit
When contributing to the project, use pre-commit to maintain a uniform code.

```bash
pre-commit install
```

To fix the formatting, either try to commit to automatically fix, or run this command:
```bash
pre-commit run --all
```
