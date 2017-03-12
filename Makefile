# -*- makefile -*-
main := main/main.cpp
program := iterate_shell
flags := -std=c++14 -g -Wall -Wextra -I./
lib_name := libshell.a
# Just add another file here when you're done, ending in .o
objs := shell.o
os := $(shell uname -s)
python := $(shell which python3)
python_test_runner := tests/run_tests.py

ifeq ($(os),Darwin)
  maybe_static_phrase :=
else
  maybe_static_phrase := -static
endif

# We statically link to avoid shared library hassles.
program:library
	clang++ ${maybe_static_pharse} ${main} -L. \
	-lshell ${flags} -o ${program}

%.o:%.cpp
	clang++ -c ${flags} $<

# Need to have a dependency on things that end with .o to have the
# wildcard pattern go off.
library:${objs}; ar rcs ${lib_name} ${objs}

test_shell:program; PATH='' ./${program}

run_tests:program; env -i ${python} ${python_test_runner}

.PHONY: install_dependencies
install_dependencies:
	sudo aptitude install libc++1 clang lldb make \
	libasan1 libasan1-dbg libasan0 pstree \
	python3-pip -y
	pip3 install pexpect

clean:; @rm -rf ${program} *.dSYM *.o ${lib_name} *.so *.a
