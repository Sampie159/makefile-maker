# Sam's C/C++ CLI project setup builder
## Generate a barebones C/C++ project structure including a basic Makefile
### Usage: mmaker \<language\> \<project-name\>

Example C:
```sh
mmaker c c-project
```

Example C++:
```sh
mmaker cpp cpp-project
```

### Output
```
c-project/
|
└───bin/
└───obj/
└───src/
└───Makefile
```

# Install
Clone this repository
```sh
git clone https://github.com/Sampie159/makefile-maker.git
cd makefile-maker
```
Then
```sh
make install
```

# Uninstall
In the project directory run:
```sh
make uninstall
```

or simply run
```sh
sudo rm /usr/local/bin/mmaker
```
from anywhere.
