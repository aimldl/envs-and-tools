* Draft: 2020-11-27 (Fri)

# How to Convert a .xmind File to an Image File in a Linux Terminal

## Goal

is to render a .xmind file to an image file so I can use the .xmind file for a Github repository.

## Problem

* Github does not support .xmind file.
* I can't convert a .xmind file to an image file, e.g. .png or .jpg, in a Linux terminal.
  * Doing so allows me to convert a batch of .xmind files to the corresponding image files.
  * Let me call this a batch rendering job of .xmind files to image files.

## Google search

### keywords: `xmind convert to png in command line`

* [Xmind not accept command line parameters?](https://github.com/xmindltd/xmind/issues/200)

  * This article discusses errors to run `xmind` in a terminal. These threads are years old and do not apply for XMind 2020.

  * This article urged me to see the command line options 

    * > $ xmind --help
      >
      > $ xmind man
      >
      > $

    * Hmm. No information is available. No wonder XMind 2020 is a commercial software.

### keywords:`xmind convert to jpg in command line`

Very few clues exist.

* [There is any linux command line tool of Xmind or any external tool or some java code, for emulate the export function and convert a .xmind file to a pdf file?](https://groups.google.com/g/xmind/c/xpocvq0nHUE)

> 21 views
>
> tenti...@gmail.com Nov 19, 2018, 11:02:41 AM
>
> Hi , i need to find a way, or with some linux command tool (xmind or external tool) , or with some
>
> solomon....@gmail.com Sep 29, 2019, 11:29:15 AM
>
> to xm...@googlegroups.com
>
> Try pandoc or https://github.com/sky-y/xmindoc
>
> I know pandoc converts a whole bunch of stuff, so I just googled "pandoc xmind" and xmindoc showed up. Never used it before.
>
> On Monday, 19 November 2018 13:02:41 UTC+11, Marco Tenti wrote:
>
> > Hi , i need to find a way, or with some linux command tool (xmind or external tool) , or with some java code to convert a .xmind file to a .pdf file, or any other image file (png,,jpeg,svg,ecc.).
> >
> > Anyone can help me whit that?

* https://github.com/sky-y/xmindoc

> **Xmindoc**
>
> Exports XMind Mindmap to any documents with Pandoc.
>
> Copyright (c) 2013 Yuki Fujiwara <[sky.y.0079@gmail.com](mailto:sky.y.0079@gmail.com)>
>
> **Requirement**
>
> - Ruby 1.9.3 or above
> - Pandoc 1.9.4.2 or above
>   - See installation: http://johnmacfarlane.net/pandoc/installing.html
>   - You can choose either:
>     - cabal install (with Haskell Platform, I prefer personally) or
>     - Pandoc Package Installer (without Haskell Platform)
>
> **Install**
>
> **libiconv**
>
> **Linux**
>
> ```
> $ wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz
> $ tar zxvf libiconv-1.14.tar.gz
> $ cd libiconv-1.14
> $ ./configure
> $ make
> $ su -
> # make install
> ```
>
> **Xmindoc**
>
> ```
> $ gem install xmindoc
> ```
>
> **Usage**
>
> ```
> Usage: xmindoc [options] input.xmind
> -o, --output FILE                Output Filename
> -t, --to=FORMAT                  Output formats: markdown, org, html, latex, rst,  ...
> -w, --write=FORMAT               Output formats: markdown, org, html, latex, rst,  ...
>     --pandoc-options=OPTIONS     Pandoc options (Use double quotes like "--atx-headers")
> -h, --help                       Display this screen
> ```
>
> - For detail of formats and Pandoc options: See [Pandoc User's Guide](http://johnmacfarlane.net/pandoc/README.html)
>
> **Examples**
>
> Sample files are in `samples/` directory.
>
> **Example 1 (Japanese: 寿限無)**
>
> ```
> xmindoc -t markdown -o test1.md samples/test1.xmind --pandoc-options="--atx-headers"
> ```
>
> - It makes a file "test1.md" as in Markdown (ATX-headered) style.
>
> **Example files**
>
> - Original XMind file: test1.xmind (test1.png as image)
> - Sample Result (Org File): test1.org
> - Sample Result (Markdown File): test1.md
> - "--atx-headers": use `#` and `##` as `<h1>` and `<h2>` header output
>
> **Example 2 (English: Lorem Ipsum)**
>
> ```
> xmindoc -t org -o test2.org samples/test2.xmind
> ```
>
> - It makes a file "test2.org" in Org style.
>
> **Example files**
>
> - Original XMind file: test2.xmind (test2.png as image)
> - Result (Org File): test2.org
> - Result (Markdown File): test2.md

An error occurred when `make` is executed. 

```bash
$ wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz
$ tar zxvf libiconv-1.14.tar.gz
$ cd libiconv-1.14
$ ./configure
$ make
  ...
make  all-am
make[2]: 디렉터리 '/home/k8smaster/github/tools/xmind/temp/libiconv-1.14/srclib' 들어감
make[3]: 디렉터리 '/home/k8smaster/github/tools/xmind/temp/libiconv-1.14' 들어감
make[3]: 'am--refresh'을(를) 위해 할 일이 없습니다.
make[3]: 디렉터리 '/home/k8smaster/github/tools/xmind/temp/libiconv-1.14' 나감
gcc -DHAVE_CONFIG_H -DEXEEXT=\"\" -I. -I.. -I../lib  -I../intl -DDEPENDS_ON_LIBICONV=1 -DDEPENDS_ON_LIBINTL=1   -g -O2 -c allocator.c
gcc -DHAVE_CONFIG_H -DEXEEXT=\"\" -I. -I.. -I../lib  -I../intl -DDEPENDS_ON_LIBICONV=1 -DDEPENDS_ON_LIBINTL=1   -g -O2 -c areadlink.c
gcc -DHAVE_CONFIG_H -DEXEEXT=\"\" -I. -I.. -I../lib  -I../intl -DDEPENDS_ON_LIBICONV=1 -DDEPENDS_ON_LIBINTL=1   -g -O2 -c careadlinkat.c
gcc -DHAVE_CONFIG_H -DEXEEXT=\"\" -I. -I.. -I../lib  -I../intl -DDEPENDS_ON_LIBICONV=1 -DDEPENDS_ON_LIBINTL=1   -g -O2 -c malloca.c
gcc -DHAVE_CONFIG_H -DEXEEXT=\"\" -I. -I.. -I../lib  -I../intl -DDEPENDS_ON_LIBICONV=1 -DDEPENDS_ON_LIBINTL=1   -g -O2 -c progname.c
In file included from progname.c:26:0:
./stdio.h:1010:1: error: ‘gets’ undeclared here (not in a function); did you mean ‘fgets’?
 _GL_WARN_ON_USE (gets, "gets is a security hole - use fgets instead");
 ^
Makefile:914: recipe for target 'progname.o' failed
make[2]: *** [progname.o] Error 1
make[2]: 디렉터리 '/home/k8smaster/github/tools/xmind/temp/libiconv-1.14/srclib' 나감
Makefile:865: recipe for target 'all' failed
make[1]: *** [all] Error 2
make[1]: 디렉터리 '/home/k8smaster/github/tools/xmind/temp/libiconv-1.14/srclib' 나감
Makefile:33: recipe for target 'all' failed
make: *** [all] Error 2
$
```

## TODO

- [ ] Install Ruby & Pandoc.
- [ ] Run `$ make` again.
- [ ] Test this program.
- [ ] Try to convert .xmind to another format and then convert it again to an image it if possible.