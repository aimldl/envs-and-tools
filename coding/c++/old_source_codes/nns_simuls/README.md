# cpp, c++ or C Plus Plus

## Google C++ Style Guide
The codes "try to" follow [Googld C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## Linux
### Compiling a source file
To compile a file "file_name.cc", use g++ with the -o option followed by the desired executable_name.
```
  $ g++ -o executable_name file_name.cc
```
After compilation, run the executable by typing in:
```
  $ ./executable_name
```
For example, "hello_world.cc" is compiled to executable "hello_world".
```
  $ g++ -o hello_world hello_world.cc
```
You may check the generated executable "hello_world".
```
  $ ls
  hello_world   hello_world.cpp
  $
```
To run "hello_world", simply type in:
```
  $ ./hello_world
  Hello, world!
  $
```

### Compiling multiple source files
Run the following command to compile three source files a.cc, b.cc, c.cc and create an executable exec_name.
```
  $ g++ -o exec_name a.cc b.cc c.cc
```
To run exec_name, simply type in:
```
  $ ./exec_name
```

## Windows
To compile and run the code on Microsoft Visual Studio, simply uncomment the following line.
```cpp
//#include "pch.h"  // Uncomment this in Visual Studio
```
Caution. The order of the include does matter. pch.h must come first or an error "'cout' : undeclared identifier" will occur.

### Good
```cpp
#include "pch.h"
#include <iostream>

int main() {
    std::cout << "Hello World!\n"; 
}
```
### Bad
```cpp
#include <iostream>
#include "pch.h"

int main() {
    std::cout << "Hello World!\n"; 
}
```

## Problem
C4996: 'scanf': This function or variable may be unsafe. Consider using scanf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

## Solution
Define _CRT_SECURE_NO_WARNINGS after including or inside pch.h.
The order matters. So if the define come BEFORE pch.h, the same error occurs.
Ref. https://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis

### Good
```cpp
#include "pch.h"  // Uncomment this in Visual Studio
#define _CRT_SECURE_NO_WARNINGS
```
or inside "pch.h"
```cpp
#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#endif //PCH_H
```
### Bad
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"  // Uncomment this in Visual Studio
```
