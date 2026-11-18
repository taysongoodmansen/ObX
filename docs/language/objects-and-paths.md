# Paths

Every variable is stored with a path, and is allowed to be accessed from anywhere within the file.

Every path starts with a `$`, which is called root (similar to Linux files). From there, you use a `.` to separate attributes of a variable. So, for example, you may have `ball.color = "red"` or `cars["ford"].engine.on = True`.

You can also type relative paths, and they will be automatically resolved based on the current directory. So if our current directory is `$.ball`, we could just do `color = "red"` and it will work. The current directory can be changed with `dir` or, in special cases, in ways that will be explained.

You can also use `^` as a modifier for a path. If our current path was `$.myx.theme.colors`, for example, and we wanted to access `myx`, we could do `dir $.myx`, but sometimes we don't know the full path to our destination, or it is quicker to type something else. What we could do is `dir ^2`. The `^` means to go up a parent, and if followed by a number, will go up that many parents. It can also be used in combination with longer paths, so, for example, `^2.background.color = "green"`.

Another use of `^` is `^f`, which is used to get the path of the function being run. See more in [functions](/docs/language/functions.md#Scope).

# Objects

Anything that can have attributes and methods (in Python terminology) is an object.

In doing `$.myx.background.color = "blue"`, we can see `$`, `myx`, and `background` are all objects, but `color` isn't, and is instead a string.

Trying to set an attribute or method of a non-object variable will result in an error.

Setting anything where the parents aren't yet set will automatically set them to objects. So, in `messages.greet = "hi"`, if `messages` hasn't been set as an object, it will automatically be. It is the same as doing `messages {greet = "hi"}` and `messages = {greet = "hi"}`. Explanation of those last two examples in the next section.

## Easy attribute setting

To make attribute setting for objects easier, you can define lots of attributes bundled up in curly brackets.

To do so, you just put the object, and then inside the curly brackets put any definitions.

Ex:
```obx
ball = {color = "red"
    size = 14
}
ball {size = 12}
```

There is a difference between when there is and isn't an equal sign. With an equal sign, it will set that object's attributes to those specified, and delete every other attribute beforehand.

The one without an equal sign can be used for both initial setting and updating. More specifically, to ObX, it is just entering this object as the `dir`, running the code inside, and then going back to the previous path.

## OOP

In ObX, Object Oriented Programming isn't really heavily designed in, in the normal sense of classes and init, public or private, etc. Instead, it's basically just a little functionality added onto the already existing attribute system, with some keyword stuff for making things easier.

To make a class, you use the `@class` metadata modifier. This specifically only makes a `.new()` to the class, which is used to actually make things.

Classes act as frameworks that just get copied whenever a new object is made. So every method and attribute will just get copied over to the new location as is. The `.new()` will do that for the user cleanly, an example shown soon.

There is also no built-in argument system for creating an object, because instead you can just modify the object after creation.

Ex:
```obx
//Without OOP
dir $
myx.C_window = {
    x = 0
    y = 0
    height = 10
    width = 10
    title = "unknown"
    render = (){
        draw(self.x,self.y,self.width,self.height)
    }
}

windows = []
windows[0] = copy(myx.C_window)
windows[0] {
    x = 20
    y = 40
    height = 100
    width = 300
    title = "firefox"
}

//With OOP incorporated
dir $
@class
myx.C_window = {
    init = (x,y,h,w,t){
        self.x = x
        self.y = y
        self.height = h
        self.width = w
        self.title = t
    }
    x = 0
    y = 0
    height = 10
    width = 10
    title = "unknown"
    render = (){
        draw(self.x,self.y,self.width,self.height)
    }
}

windows = []
windows[0] = myx.C_window.new().init(20,40,100,300,"firefox")
```

With the `.new()` area, ObX will treat it as if the `=` to the end of `.new()` are removed, and then continue running. So it will copy everything with `.new()`, and then remove that section and be left with `windows[0].init(...)`, which will do as we want.

The `init` function is unspecific and can be any word you want.

### Inheritance

To have a class inherit, you just add onto the metadata before it, adding `@inherit class` to the next line.

Code-wise, it will be as if it did its parent's `.new()` first, and then did its `.new()` second. For any repeated variables, it will just replace them. For any functions, it will also replace them, but first move them to `.super`, which is useful in `.init()`.

Ex:
```obx
@class
animal = {
    init = (name){
        self.name = name
    }
    name = ""
    sound = "?"
    speak = (){
        print(self.sound)
    }
}

@class
@inherit animal
dog = {
    init = (name,breed){
        super.init(name)
        self.breed = breed
    }
    sound = "bark"
    breed = "?"
}
```

Because `init` would be overwritten, it's saved to `.super` so we can still use it. It will stack for multiple inheritances.

The `self` acts identically to `^` inside a function for an object, and when inside an object, will just be ignored because paths already add the current directory to paths.