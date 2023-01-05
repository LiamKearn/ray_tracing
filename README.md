# Building

Configure:
```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
```

Build:
```sh
cmake --build build --config Debug
```

Test:
```sh
cd build && ctest -C Debug --output-on-failure --verbose
```

