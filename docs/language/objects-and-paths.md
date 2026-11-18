# Paths

Every variable is stored with a path and is allowed to be accessed from anywhere within the file.

Every absolute path starts with a `$`, which is called root (similar to Linux file systems). From there, you use a `.` to separate attributes of a variable. For example, you may have `ball.color = "red"` or `cars["ford"].engine.on = true`.

You can also type relative paths, and they will be automatically resolved based on the current directory. So, if our current directory is `$.ball`, we could just do `color = "red"` and it will work. The current directory can be changed with `dir` or in special cases that will be explained later.

You can also use `^` as a modifier for a path. If our current path was `$.myx.theme.colors`, for example, and we wanted to access `myx`, we could do `dir $.myx`, but sometimes we don't know the full path to our destination, or it is quicker to type something else.

What we could do is `dir ^2`. The `^` means to go up one parent, and if followed by a number, it will go up that many parents. It can also be used in combination with longer paths, so we could do something like `^2.background.color = "green"`.

Another use of `^` is `^f`, which is used to get the path of the function being run. See more in [Functions](../language/functions.md#Scope).

# Objects

Anything that can have attributes and methods (in Python terminology) is an object.

In doing `$.myx.background.color = "blue"`, we can see that `$`, `myx`, and `background` are all objects, but `color` isn't, and is instead a string.

Trying to set an attribute or method of a non-object variable will result in an error.

Setting anything where the parents aren't yet set will automatically set them to objects. So, in `messages.greet = "hi"`, if `messages` hasn't been set as an object, it will automatically become one. It is the same when doing `messages {greet = "hi"}` and `messages = {greet = "hi"}`. An explanation of those last two examples is in the next section.

## Easy attribute setting

To make attribute setting for objects easier, you can define lots of attributes bundled up in curly brackets.

To do so, you just put the object, and then inside the curly brackets, put any definitions you want.

Example:

```obx
ball = {
    color = "red"
    size = 14
}

ball {
    size = 12
}
```

There is a difference between when there is and isn't an equal sign. With an equal sign, it will set that object's attributes to those specified and delete every other attribute beforehand.

The one without an equal sign can be used for both initial setting and updating. More specifically, to ObX, it means to just enter this object for `dir`, run the code inside, and then go back to the previous path.

## OOP

In ObX, Object-Oriented Programming isn't really heavily designed in, in the normal sense of classes, `init`, public or private, etc. Instead, it's basically just a little functionality added onto the already existing attribute system, with some keyword stuff to make things easier.

To make a class, you use the `@class` metadata modifier. This specifically only adds a `.new()` to the class, which is used to actually make instances.

Classes act as frameworks that just get copied whenever a new object is made. So every method and attribute will just get copied over to the new location as is. The `.new()` will do that for the user cleanly, as shown in an example soon.

There is also no built-in argument system for creating an object