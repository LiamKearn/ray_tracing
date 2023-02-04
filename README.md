# Building

Configure:
```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
```

Build:
```sh
cmake --build build --config Debug
```

Run (and view):
```sh
./build/bin/renderer 1> out.ppm && open out.ppm
```

Test:
```sh
pushd build && ctest -C Debug --output-on-failure --verbose && popd
```


TODO:
https://github.com/include-what-you-use/include-what-you-use
