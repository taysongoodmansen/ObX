ObX

ObX is a language designed almost entirely just for configuration for C based projects.

It is being made to be the directly built configuration language for a future project
of mine, a Wayland compositor named Myx.

It is made to make everything for configuration easy to use. It makes everything accesssable
from anywhere within a file. It is designed with a very specifc paradigm in place to try
and help users easily make their computer their own.

The paradigm:
    The main idea it to give full control to the user to do whatever they want
    with ease.
    To do so most things will guide and warn the user but never stop them,
    An example is that Errors and Warnings within the program will never
    stop the program, only give sufficient warning to the user before continuing.

    All variables are also part of a file system like heirarchy to make it so any
    file can access anything anywhere.

General Syntax:
    It is designed similarly to python to be easily readble, but allow advanced
    code when needed.
    Variables:
    All variables act as an attribute of some parent variable, and they all start
    at root which is marked with $
    Variable paths with be automatically resolved as relative paths. So for
    example when you write name = "jerry" it knows you means $.name. But you can
    also change your current path, either with dir, entering a function, or by
    temporarily entering an objects attributes.
    Values:
    There are a lot of simple types, currently int,str,float,bool,collections,
    and eventual implimentation for events
    Operatations:
    Almost all just have a basic syntax of A O B where A and B are inputs and 
    O is the operations, so like 7+3 or age+5 where age is a number. Most
    numerical operations can take interger or float and output depening on
    which are inputted.

Status:
    version 0.0.1
    Operations being implimented
    Future things to impliment:
    All in one collection setting (using : in a collection for any non-indexed keys)
    Functions
    Dictators (explained in later section)
