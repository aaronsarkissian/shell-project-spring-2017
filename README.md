iterate shell
-------------

This is iterate project for `C/C++` experience; we are making a `UNIX`
shell, this will NOT work on Windows but it will work on `OS X` and
any other `UNIX` aka any `Linux`.

Your code should be implemented in the `.cpp` files with an
appropriate API exposed in the respective `.h` file.

requirements per platforms
--------------------------

# OS X

Congrats, on `OS X` you don't need to do anything other than have
`XCode` installed.

# Linux 

The project uses `clang` and the `fsanitize` so you'll need to have
these installed on your machine, use `aptitude`

```shell
$ aptitude install libc++1 clang lldb make libasan1 libasan1-dbg libasan0
```

For Linux a convenience `Makefile` target has been added to get all
the needed dependencies, just do:

```shell
$ make install_dependencies
```

# Windows

Your options are: 

1. Get rid of Windows, install Linux (Debian or Ubuntu is good)
2. Dual boot Linux and Windows
3. Get a Virtual Machine on Windows, can use VMWare or Virtual Box.


Development Roadmap (Always check for updates as this is always updating)
-------------------------------------------------------------------------

# First steps, getting input, parsing

A shell is a REPL, which stands for: `READ EVALUATE PRINT LOOP`. It
takes a line of input, evaluates it, prints the results and loops
again. So the first step is to write code that takes a line of input
from the user. Once you get that line of input, you need to parse
it, that is turn it into something understand about. Take for example:

```shell
$ git status
```

What will your shell really read in? 

```
*HINT: How much should you keep reading?
When do you stop reading from `stdin`?*
```

You shell will get:

```
"git status"
```

And this isn't useful yet. You need to split the string into different
parts. Remember that many programs have short flags and long flags,
aka `-` and `--`.

```
*HINT: Read about shell redirection, you will need to handle the
special symbols |, <, and >
```

Once you have that all together, you need to think about process
management.

# Process management

Unix process management is a hierarchieral relationship. When we start
a prorgram, say `git`, we have this relationship.

```
bash
  |--git
```

That is, `bash` is the parent of `git`. You can see the entire process
tree with

```
$ pstree
```

If you don't have `pstree` then use `aptitude` to install it,
`$ aptitude install pstree`.

# Testing the shell

You should be invoking `iterate_shell` as so:

```shell
$ make test_shell
```

You should also run the automated test suite with: 

```shell
$ make run_tests
```

YOU MUST run this before submitting any Pull Request.

# System calls you are expected to use

These are C system calls that you are expected to use in this project:

```
execve (To execute the program)
waitpid (To make the parent wait for the child)
fopen (To read a startup script)
fork (To create a new process)
stat (To check if a file exists)
fread (To read from a file)
```

Remember you can always find more details in their respective man
pages, for example you can do in the shell:

```
$ man 2 execve
```
