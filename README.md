# TemplatedDoubleLinkedList

This repo contains a C++ implementation of a templated, double-linked, list using smart pointers.

# Documentation

You can find a Doxygen generated documentation [here](https://fdrmrc.github.io/TemplatedDoubleLinkedList/).

# How to compile and run

First, clone the repo in your local machine with

```
git clone https://github.com/fdrmrc/TemplatedDoubleLinkedList.git
```

then move in the repo folder and type

```
make
```

and 

```
./exe.x
```

to execute.

# Check memory leaks with **valgrind**

To check if the code leaks memory:

- Use Makefile:
```
make
```

- Execute using *valgrind* (requires [valgrind](https://valgrind.org))
```
valgrind ./exe.x
```

