# wex
A 2D Game Engine written in C++ that embeds the Vyse programming language

# Build instructions

```
mkdir -p out
cd out
cmake -G Ninja .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=1
ninja
./wex
```