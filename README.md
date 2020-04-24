# Overview

Steering behaviours implemented in C++ and compiled to WebAssembly via [emscripten](https://emscripten.org/).

This should force me to learn [cmake](https://cmake.org/) while [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) teaches me modern C++.

## Prerequisites

Depending on what you want to do, you'll need:

* The [emscripten](https://emscripten.org/) toolchain
* [cmake](https://cmake.org/)
* A modern C++ compiler
* SDL2 library should be findable by cmake
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)

## Usage

This repo uses [submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules), so the easiest way to get started is
```
git clone --recurse-submodules git@github.com:miguelsimon/steering.git
```

* `make build` builds a locally-executable version under `./build`
* `make wasm-build` builds html pages with WebAssembly under `./wasm-build`
* `make fmt` runs clang-format on the source
* `make tidy` runs clang-tidy on the source
