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
pushd build && ctest -C Debug --output-on-failure --verbose && popd
```


TODO:
https://github.com/include-what-you-use/include-what-you-use
