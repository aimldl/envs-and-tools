#pragma once  // GetOpt.hpp

#include  <cstdio>   // fprintf
#include  <cstdlib>  // getenv
#include  <cstring>  // strcmp

using namespace std;

// See Disclaimer and Comments below.
// getopt for GNU
// getopt.h is a GNU libc header to parse command line arguments.
// GetOpt.hpp is the C++ version while getopt.h is for C.
//
// Refer to C++ version of the GNU getopt function at https://www.slac.stanford.edu/comp/unix/gnu-info/libg++_38.html
// This document is not the user guide for this GetOpt.{hpp, cpp>, but will give you an insight.
//
// The source codes are available at Github's gcc-mirror/gcc
//   gcc-include/getopt.h  https://github.com/gcc-mirror/gcc/blob/master/include/getopt.h
//   gcc/libiberty/getopt.c  https://github.com/gcc-mirror/gcc/blob/master/libiberty/getopt.c
//
// Note: I didn't use this C-version. It failed to compile on Windows10 with Microsoft Visual Studio 2017 Express.

//==================================================================
//                      Class Declaration                         //
//==================================================================

// getopt for GNU
class GetOpt {
public:
  GetOpt(int argc, char** argv, const char* optstring);
  
  int operator () (void);
  int nargc;
  char** nargv;
  int optind;
  int opterr;
  char* optarg;
  const char* noptstring;

private:
  void exchange(char** argv);

  static char* nextchar;
  static int first_nonopt;
  static int last_nonopt;
  enum OrderingEnum { REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER };
  OrderingEnum  ordering;
};

//==============================================================================
//                                  Disclaimer
//==============================================================================

// Getopt for GNU.
//   Copyright (C) 1987, 1989, 1992 Free Software Foundation, Inc.
//   (Modified by Douglas C. Schmidt for use with GNU G++.)
//
// This file is part of the GNU C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms of
// the GNU Library General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your
// option) any later version.  This library is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU Library General Public License for more details.
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// This version of `getopt' appears to the caller like standard Unix `getopt'
//   but it behaves differently for the user, since it allows the user
//   to intersperse the options with the other arguments.
//
//   As `getopt' works, it permutes the elements of `argv' so that,
//   when it is done, all the options precede everything else.  Thus
//   all application programs are extended to handle flexible argument order.
//
//   Setting the environment variable _POSIX_OPTION_ORDER disables permutation.
//   Then the behavior is completely standard.
//
//   GNU application programs can use a third alternative mode in which
//   they can distinguish the relative order of options and other arguments.

//==============================================================================
//                                  Comments
//==============================================================================

// char* optarg;
//   For communication from `getopt' to the caller.
//   When `getopt' finds an option that takes an argument,
//   the argument value is returned here.
//   Also, when `ordering' is RETURN_IN_ORDER,
//   each non-option ARGV-element is returned here.
//
// int optind;
//   Index in ARGV of the next element to be scanned.
//   This is used for communication to and from the caller
//   and for communication between successive calls to `getopt'.
//   On entry to `getopt', zero means this is the first call; initialize.
//
//   When `getopt' returns EOF, this is the index of the first of the
//   non-option elements that the caller should itself scan.
//
//   Otherwise, `optind' communicates from one call to the next
//   how much of ARGV has been scanned so far.
//
// int opterr;
//   Callers store zero here to inhibit the error message
//   for unrecognized options.
//
// static char* nextchar;
//   The next char to be scanned in the option-element
//   in which the last option character we returned was found.
//   This allows us to pick up the scan where we left off.
//
//   If this is zero, or a null string, it means resume the scan
//   by advancing to the next ARGV-element.
//
//
// static int first_nonopt; and static int last_nonopt;
//   Handle permutation of arguments.
//
//   Describe the part of ARGV that contains non-options that have
//   been skipped.  `first_nonopt' is the index in ARGV of the first of them;
//   `last_nonopt' is the index after the last of them.
//
// enum OrderingEnum{ REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER };
// OrderingEnum ordering;
//   Describe how to deal with options that follow non-option ARGV-elements.
//
//   UNSPECIFIED means the caller did not specify anything;
//   the default is then REQUIRE_ORDER if the environment variable
//   _OPTIONS_FIRST is defined, PERMUTE otherwise.
//
//   REQUIRE_ORDER means don't recognize them as options.
//   Stop option processing when the first non-option is seen.
//   This is what Unix does.
//
//   PERMUTE is the default.  We permute the contents of `argv' as we scan,
//   so that eventually all the options are at the end.  This allows options
//   to be given in any order, even with programs that were not written to
//   expect this.
//
//   RETURN_IN_ORDER is an option available to programs that were written
//   to expect options and other ARGV-elements in any order and that care about
//   the ordering of the two.  We describe each non-option ARGV-element
//   as if it were the argument of an option with character code zero.
//   Using `-' as the first character of the list of option characters
//   requests this mode of operation.
//
//   The special argument `--' forces an end of option-scanning regardless
//   of the value of `ordering'.  In the case of RETURN_IN_ORDER, only
//    `--' can cause `getopt' to return EOF with `optind' != ARGC.