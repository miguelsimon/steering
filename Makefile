

CPPFLAGS += -Iinclude/
CPPFLAGS += -Ideps/Catch2/single_include
CPPFLAGS += -Ideps/imgui/
CPPFLAGS += -Ideps/eigen/
CPPFLAGS += -Isrc/
CPPFLAGS += -I/usr/local/include/SDL2
CPPFLAGS += -Wall -std=c++17

TIDY_CHECKS=bugprone-*,clang-analyzer-*,modernize-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-pro-bounds-array-to-pointer-decay

fmt:
	cd src && clang-format -i -style=file *.cpp
	cd include && clang-format -i -style=file *.h
	cd cmd && clang-format -i -style=file *.cpp
	cd test && clang-format -i -style=file *.cpp

# should integrate clang-tidy run into the cmake build at some point
# https://gitlab.kitware.com/cmake/cmake/issues/18926
.PHONY: tidy
tidy:
	clang-tidy src/*.cpp -header-filter=include/ -checks=$(TIDY_CHECKS) -- $(CPPFLAGS) $(CXXFLAGS)

.PHONY: build
build:
	mkdir -p build
	cd build && cmake .. && make

.PHONY: wasm-build
wasm-build:
	mkdir -p wasm-build
	cd wasm-build && \
		emcmake cmake .. && \
		emmake make

.PHONY: docs
docs: wasm-build
	rm -rf docs
	mkdir docs
	pandoc website/index.md -o docs/index.html
	cp wasm-build/*.wasm docs/
	cp wasm-build/*.js docs/
	cp wasm-build/*.html docs/

.PHONY: local_server
local_server: docs
	cd docs && python3 -m http.server

test: build
	build/test

clean:
	rm -rf build wasm-build
