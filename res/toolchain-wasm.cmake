set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_CXX_COMPILER clang)
set(CMAKE_AR llvm-ar)
set(CMAKE_RANLIB llvm-ranlib)
# set(CMAKE_LINKER wasm-ld)

set(CMAKE_CXX_FLAGS "--target=wasm32" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS "--target=wasm32" CACHE STRING "")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -fuse-ld=lld -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined")

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".wasm")
