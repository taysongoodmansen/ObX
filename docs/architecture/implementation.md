# Implementation

## Variables

Since ObX is a run once language, Variables can be implemented in a 'lazy' way.
Every variable is just stored in a big dictionary with a key and value, where the key
is the absolute path and the value is just the raw value.

So for example when I type `name = "jerry"` into ObX, it will first add the current directory
and the absolute path becomes `$.name` assuming $ is the current directory. Then ObX will 
store a value with key `"$.name"`, value `"jerry"` and type `"string"`. 

This also extends into collections, and object attributes. So things could have keys of 
`"$.people["sarah"].age"` or like `"$.array[3][7][1][17]"`