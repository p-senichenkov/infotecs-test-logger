# Logger

"Logger" test task for Infotecs company.
Consists of two parts: logger and demo application.

## Building

Logger is considered to be built with CMake.
It's recommended to use a separate build directory (`build` in this README).
Personally, I prefer Ninja as a build tool, so all instruction assume that Ninja is used.

```sh
cmake -S . -B build -G Ninja && cmake --build build
```

You can build different parts of project separately.
Run `ninja -t targets` from inside of `build` directory to see availible targets.

### CMake options

- `STATIC_LIB` -- build static library.
Otherwise, shared library is built.
Default is `OFF`.
- `TESTS` -- build tests.
Default is `ON`.

## Running application

```sh
build/target/DemoApplication
```

## Running tests

```sh
build/target/LoggerTests
```
