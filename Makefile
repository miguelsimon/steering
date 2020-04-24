

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

tidy:
	clang-tidy src/*.cpp -checks=$(TIDY_CHECKS) -- $(CPPFLAGS) $(CXXFLAGS)

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

test: build
	build/test

clean:
	rm -rf build wasm-build
