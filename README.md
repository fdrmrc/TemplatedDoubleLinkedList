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

To check the code has no memory leaks:

-
```
make
```

- 
```
valgrind ./exe.x
```

