# oatpp C++ API example

This project runs the oatpp HTTP server in [`src/main.cpp`](src/main.cpp). The
server listens on `localhost:8000`.

## Prerequisites

The oatpp installation must provide:

- headers under `/usr/local/include/oatpp-1.4.0`
- libraries under `/usr/local/lib/oatpp-1.4.0`
- the CMake package under `/usr/local/lib/cmake/oatpp-1.4.0`

The example uses CMake to find and link the installed oatpp package.

## VS Code setup

The repository includes `.vscode/settings.json`, which points the Microsoft C/C++
extension at CMake's generated `compile_commands.json`. This gives IntelliSense
the same include paths and C++ standard used by the actual build.

After opening the project in VS Code, configure it once so the compilation
database is generated:

```sh
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/usr/local
```

If the warning remains, run **Developer: Reload Window** from the VS Code
Command Palette. Make sure the Microsoft **C/C++** extension is installed.

## Build and run

From the project directory:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH=/usr/local
cmake --build build
./build/cpp-api
```

`CMAKE_PREFIX_PATH=/usr/local` tells CMake where to find oatpp's installed
`oatppConfig.cmake`. If oatpp was installed somewhere else, replace
`/usr/local` with that installation prefix.

You should see a message indicating that the server is running on port `8000`.
While the process is running, test it from another terminal:

```sh
curl http://localhost:8000
```

## Ninja development workflow

Configure the project with Ninja once:

```sh
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/usr/local
```

After changing a `.cpp` or header file, rebuild incrementally with:

```sh
cmake --build build
./build/cpp-api
```

Only files affected by the change are rebuilt. To automatically rebuild and
restart the server when source files change, install `entr` and run:

```sh
sudo apt install entr
find src -type f \( -name '*.cpp' -o -name '*.hpp' \) | entr -r sh -c 'cmake --build build && ./build/cpp-api'
```

## Run tests

Configure and build the test executable with the application:

```sh
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/usr/local
cmake --build build
```

Run all tests through CTest:

```sh
ctest --test-dir build --output-on-failure
```

You can also run the test executable directly:

```sh
./build/cpp-api-tests
```

The tests use oatpp's in-memory virtual network, so they do not need the
application server running and do not bind to port `8000`.

## Rebuild from scratch

To remove the CMake cache and generated files, then configure again:

```sh
rm -rf build
cmake -S . -B build -DCMAKE_PREFIX_PATH=/usr/local
cmake --build build
```

## Troubleshooting

### CMake cannot find oatpp

Check that the package file exists:

```sh
find /usr/local/lib/cmake -name oatppConfig.cmake
```

If it is present, configure with the explicit package directory:

```sh
cmake -S . -B build \
  -Doatpp_DIR=/usr/local/lib/cmake/oatpp-1.4.0
```

### The port is already in use

Another process is using port `8000`. Stop that process or change the port in
`src/main.cpp`, then rebuild and run the executable again.
