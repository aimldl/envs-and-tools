##### aimldl > cpp > README.md
* Revision:
* Draft: Some time ago

# cpp | c++ | C Plus Plus
* Revision: 2019-10-31 (Thu)
* Draft: long time ago

## Table of Contents
* [1. Compiling the C++ Source Codes](#compiling_the_cpp_source_codes)
  * [1.1. Compiling g++ on Linux](#compiling_gpp_on_linux)
  * [1.2. Compiling with Microsoft Visual Studio](#compiling_with_microsoft_visual_studio)
* [2. Google C++ Style Guide](google_cpp_style_guide)

## 1. Compiling the C++ Source Codes <a name="compiling_the_cpp_source_codes"></a>
### 1.1. Compiling g++ on Linux <a name="compiling_gpp_on_linux"></a>
Basic g++ commands to compile C++ source codes are presented below.
#### 1.1.1. Compiling a file
To compile a file "file_name.cc", use g++ with the -o option followed by the desired executable_name.
```bash
  $ g++ -o executable_name file_name.cc
```
After compilation, run the executable by typing in:
```bash
  $ ./executable_name
```
For example, "hello_world.cc" is compiled to executable "hello_world".
```bash
  $ g++ -o hello_world hello_world.cc
```
In "hello_world.cc",
```c++
#include <iostream>

int main()
{
  std:cout << "Hello, world!" << std::endl;
  return 0
}
```

Run 'ls' to check if the executable "hello_world" is created.
```bash
  $ ls
  hello_world   hello_world.cpp
  $
```
To run "hello_world", simply type in:
```bash
  $ ./hello_world
  Hello, world!
  $
```
#### 1.1.2. Compiling multiple files
Run the following command to compile three files a.cc, b.cc, c.cc and create an executable exec_name.
```
  $ g++ -o exec_name a.cc b.cc c.cc
```
To run exec_name, simply type in:
```
  $ ./exec_name
```
#### 1.1.3. Compiling multiple files with Makefile
[TODO]

### 1.2. Compiling with Microsoft Visual Studio <a name="compiling_with_microsoft_visual_studio"></a>
Microsoft Visual Studio runs on Windows. Tips to compile a source code with Microsoft Visual Studio is presented below.

#### 1.2.1. Including "pch.h" for Microsoft Visual Studio
The source codes in this repository are written to compile on Linux with Visual Studio in mind. Including "pch.h" will basically make the same code run on Windows.
```cpp
#include "pch.h"
```
Some codes have the following line for convenience. For g++ on Linux, leave it as it is.
```cpp
//#include "pch.h"
```
For Visual Studio on Windows, uncomment this line.

#### 1.2.2. Caution: "pch.h" Must Be on Top
The order to include "pch.h" does matter. "pch.h" must come first. Otherwise some weird compile errors which don't make sense will occur. As an example, the following hello world code will show an error "'cout' : undeclared identifier".
```cpp
#include <iostream>
#include "pch.h"

int main() {
    std::cout << "Hello World!\n";
}
```
All the syntax is correct, so I wasn't able to fix the bug quickly at first. To fix the problem, move #include "pch.h" on top.
```cpp
#include "pch.h"
#include <iostream>

int main() {
    std::cout << "Hello World!\n";
}
```
#### 1.2.3. _CRT_SECURE_NO_WARNINGS
When the following error occurs,
> C4996: 'scanf': This function or variable may be unsafe. Consider using scanf_s instead. To disable deprecation, use
> _CRT_SECURE_NO_WARNINGS. See online help for details.

define _CRT_SECURE_NO_WARNINGS to fix the error.
```cpp
// This file is the source code that you have scanf.
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
```
Note the order to define _CRT_SECURE_NO_WARNINGS is important. If the definition comes BEFORE pch.h, an error occurs.
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
```

An alternative way is to put the definition inside "pch.h". For example,
```cpp
// This file is pch.h
#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#endif //PCH_H
```
For details about _CRT_SECURE_NO_WARNINGS, refer to https://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis.

## 2. Google C++ Style Guide <a name="google_cpp_style_guide"></a>
I tried to follow [Googld C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
[TODO: Summarize frequently used styles]
