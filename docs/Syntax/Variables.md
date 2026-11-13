# Variables and Variable Types

Variables and variable setting are very similar to Python in how they work.

Variables can be set without declaring their types. They can also change types throughout the program.

## Types

The types are also similar to Python.

### Integers
Whole numbers. Examples: `3`, `7`, `207`.

### Floats
Numbers with decimal points. Examples: `2.7`, `19.20`, `0.3`.

### Strings
Words and letters. Examples: `"hello"`, `"jerry"`, `"he is 513"`.

### Booleans
`True` or `False`.

### Collections
Multiple variables stored under one variable. Python's lists and dictionaries in one.

Use keys and values for everything, but if no keys are given, it will default to indexed keys. So, `["a","b","c"]` will set the keys as `0`, `1`, and `2` (indexes start at 0).

To specify keys, you would do `["name":"bob","age":13,"employed":True]`.

They can also be combined, but it is unrecommended to do so when setting the collection as a whole, like `[1,7,34,"Title":"employee"]`.

Any value inside can be accessed by doing `variable[key]`, where indexed ones are just their number.

### Events (currently unsupported)
Used to dynamically connect one piece of code to another. Very useful for making code that won't run during startup of the window manager, but instead waits until something later to run.