# Sam's C/C++ CLI project setup builder
## Generate a barebones C/C++ project structure using CMake
### Usage: mmaker -l \<language\> -p \<project-name\>
### Help command: mmaker -h

#### Example C:
```sh
mmaker -l c -p c-project
```

#### Example C++:
```sh
mmaker -l cpp -p cpp-project
```
or
```sh
mmaker -l cc -p cpp-project
```

# Installation
```sh
git clone https://github.com/Sampie159/makefile-maker.git
cd makefile-maker
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

# Uninstall
```sh
sudo rm /usr/local/bin/mmaker
```
