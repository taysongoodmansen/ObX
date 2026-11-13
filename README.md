# ObX

ObX is a language designed almost entirely just for configuration for C-based projects.

It is being made to be the directly built configuration language for a future project of mine, a Wayland compositor named Myx.

It is made to make everything for configuration easy to use. It makes everything accessible from anywhere within a file. It is designed with a very specific paradigm in place to try and help users easily make their computer their own.

## The paradigm:

The main idea is to give full control to the user to do whatever they want with ease.

To do so, most things will guide and warn the user but never stop them. An example is that errors and warnings within the program will never stop the program, only give sufficient warning to the user before continuing.

All variables are also part of a file-system-like hierarchy to make it so any file can access anything anywhere.

## General Syntax:

It is designed similarly to Python to be easily readable, but allow advanced code when needed.

### Variables:

All variables act as an attribute of some parent variable, and they all start at root, which is marked with `$`.

Variable paths will be automatically resolved as relative paths. So, for example, when you write `name = "jerry"`, it knows you mean `$.name`. But you can also change your current path, either with `dir`, entering a function, or by temporarily entering an object's attributes.

### Values:

There are a lot of simple types, currently int, str, float, bool, collections, and eventual implementation for events.

### Operations:

Almost all just have a basic syntax of A O B, where A and B are inputs and O is the operation, so like `7+3` or `age+5`, where age is a number. Most numerical operations can take integer or float and output depending on which are inputted.

## Status:

**Version:** 0.0.1

Operations being implemented.

### Future things to implement:

- All-in-one collection setting (using `:` in a collection for any non-indexed keys)
- Functions
- Dictators (explained in a later section)