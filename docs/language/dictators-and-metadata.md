# Dictators and Metadata

Both of these will modify something about the following code, where metadata
will specifically tell ObX and Myx (or any WM) to do something special, while Dictators
change how a section of code runs.
**Some syntax here may change with future implementation.**

## Dictators

Dictators take the format of `<name>{code}`. An example that would be commonly
used is `<eval>{...}`, where whatever code is inside the curly brackets won't actually
run, but instead be stored to run later. Like let's say we have tempC but want to
use the temp in Fahrenheit. We could just have a function C_to_F(temp) but it could
be annoying to call it every time, so instead we could do `tempF = <eval>{(tempC*9/5)+32}`
where now every time you reference tempF it will return tempC turned to F. This way it can stop
repetitive code usage. 

A second example could be with time, instead of writting `get_current_time()` everywhere,
you could instead do `time=<eval>{get_current_time()}` and then just use `time` everywhere instead.

Another important usage of it is to change languages, because ObX has built-in
support for other languages. From install ObX comes with `<code:C>` and `<code:Cdir>`.
This will change the following code to be outsourced to another language. You can 
customize ObX to connect it to any coding language you want, but C is the only one by default.
Cdir is used to modify ObX but is risky to use. Its main benefits would be mods to ObX that you could
add to a file by just doing like `include "ObX_Mod"`.

## Metadata

Metadata is just used to change small things about something during runtime, and
is basically just variable setting with an `@` before it. An example that could come 
up more commonly is `@cache=True` will tell Myx to cache the results of the following
runtime function. Most metadata things are more complex and specific to Myx implementation.

Another common use could relate to the previous section with `<eval>`: by default, it
will reference the variables in the original directory. So like maybe you try and 
do `message=<eval>{"Hello"+name}` and when you run this inside the path `$.people[12]`
you would think it would work, that it would reference `$.people[12].name` which exists,
but instead will try to reference `$.name` which doesn't exist (assuming the message was 
created in `$`); instead, before that line you would put `@use_dir="cur"`. This will
make it so it will use the current directory instead. Now it would reference the name of
whatever person directory you're in.

A good use within commonly used variables is `@global` because it makes accessing a thing
from anywhere much easier. It can also be with an input to change its scope where global.
To do so you use expose instead, so  `@expose = $.myx.windows` would make it act as global, but only inside `$.myx.windows`,
this just makes it easier to stop variable mix up, espcially in shared packages where you dont want
global variables to interfere.