# Functions

Functions have the syntax `name = (args){code}`. 

An example could be add = (a,b) {return a+b}. Line in C the stuff within the curly brackets can move around seperate lines, and so something like this would also work:
```obx
add = (a,b){
    sum = a + b
    return sum
}
```
### Scope
Functions get a special wrapper in their scope. The new scope will change to current_directory.|function_directory|.

So lets say we did this:
```obx
add = (a,b){
    print(_dir)
    return a+b
} //adds path is $.add

add(5,6) //prints $.|$.add|
dir windows
add(27,9) //prints $.windows.|$.add|

```
This path system works with out [path modification](), because using `^.` will use the directory that ran the function, and `^f.` will go to the directory inside the `||` which in our case would be the `$.add`.

See more on [paths](/docs/language/objects-and-paths.md)