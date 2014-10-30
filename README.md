Brackets coding puzzle
======================

[![Build Status](https://travis-ci.org/emaskovsky/coding-puzzle-brackets.svg?branch=master)](https://travis-ci.org/emaskovsky/coding-puzzle-brackets)

Given a string comprising just the characters (,),{,},[,] determine if
it is well-formed or not by applying the following rules:
* **Each type of bracket needs to be first opened then closed**
  * Good: () or [] or {}
  * Bad: (() or {}}
* **You can only close the last bracket that was opened**
  * Good: ({})
  * Bad: ({)}
* **Inside parenthesis () only braces {} are allowed**
  * Good: ({})
  * Bad: ([]) or (())
* **Inside braces {} only square brackets [] are allowed**
  * Good: {[]}
  * Bad: {()} or {{}}
* **Any bracket can appear (directly) inside square brackets []**
  * Good: [()] or [{}] or [[]] or [[[]]]
  * Bad: [([])]
* **You can use a list of braces where a single one is allowed of that type**
  * Good: [()()] or {[][()()]} or ()()
* **An empty string is not valid a expression**
* **Any other characters than (){}[] will invalidate the string**

For a given string print out ``True`` if the string is well-formed or
``False`` if otherwise.

Part I.)
--------

Write a program that can read from stdin. Process all lines and print
out the result to stdout. 

Part II.)
--------- 

Enhance the program from "Part I" so it uses a multi-threaded
approach. Dispatch the actual strings to test to as many threads as
the machine has cores. Because the order is not necessarily the same
as the input provide the output with the referring index of the nth
input like this (no spaces):

```
0:True 
1:False
```


Usage
=====

Compilation and build
---------------------

### Linux

To build under Linux, invoke the following command in the root directory:
```
make all
```

To run the test, invoke:
```
make test
```

The program uses Boost libraries, therefore they must be installed first.
For example, under Ubuntu the Boost libraries can be installed by:
```
sudo apt-get install libboost-all-dev
```

### Windows

The project for [Microsoft Visual Studio 2013](http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx "Microsoft Visual Studio Express")
is available under the "extras/msvc" directory.

Boost libraries need to be available and built. Refer to the
[Boost manual](http://www.boost.org/doc/libs/1_56_0/more/getting_started/windows.html "Boost: Getting Started on Windows")
for the information on how to obtain and build the Boost library.

The Boost libraries must be build in complete mode to also build dynamic
libraries (which are used by the test project), like this:
```
b2 --build-type=complete
```

In order to find the Boost headers and libraries, the environment variable
"BOOST" must point to the Boost root directory - the environment
variable is used in the setup of the MSVC projects to determine the appropriate
paths (the libraries are looked up under "%BOOST%\stage\lib").


Running the application
-----------------------
The application is run by calling:
```
brackets
```
(under Linux/Unix, you might need to specify the path of current directory, like
"./brackets")

The command to run the multi threaded version of the application is:
```
brackets_mt
```

After starting the application, enter the input lines (use Enter to terminate
a single line).

To finish receiving the input and start processing the entered lines, press:
Ctrl+Z (under Windows) or Ctrl+D (under Linux).

The input can also be redirected to receive the lines from a file:
```
brackets < input.txt
```
All the lines in the input file will be loaded and then processed. Note that
there needs to be a newline after the last line, otherwise the last line will
not be processed.
