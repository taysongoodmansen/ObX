# The problem to fix

**Some parts are relevant only with consideration for Myx**

A common issue within user interface, is a constant compromise between one thing and another.

Specifically within Window Manager and Desktop environments it's seen a lot. For windows its built around simplicity for the user, everything is easy to set up, and can all be found within a GUI. But the big sacrifice for that is looks and customizability, where there's a very limited amount of things you can change. 

Then you get to the other end with Linux WMs. A good example is just the whole Arch experience. You can do relatively whatever you want. You want dolphins to swim across your screen go ahead, you want every click to make particle effects go ahead and do that too. But the issue is everything is hard to do, including the 'easy' stuff that would as simple as a single click on windows.

One goal of ObX and Myx is to find a good balance to both sides, and to let the user do whatever they want with as little friction as possible.

### How it's achieved
To try and get a good balance, majority of things will happen inside a `.obx` file where we can interpret the users desired effect.

For simple things it's only a few lines of code, For Harder things you can put as many lines of code you want.

If someone isn't super tech savvy, and wants to do something hard, they can have access to a GUI just like windows to change what they want. It will have access to all of the main things you would want to change, and will be only a few clicks away. But if they want more complicated things, they have an easy to access community of things for their configuration. They don't have to know anything about code, but could find a package that says "Modern toolbar" and add it to their config. They don't need to know the stuff inside of it, but can just search on a website for what they want and get it.

For more code inclined people they can code what they want. They don't have to be experts to do everything though. If they have a decent grasp on Object Oriented Programming they should be fine. A lot of the easy stuff is just Variable setting. For example it could be something like `myx.windows.border_color = "green"`.

But it still goes beyond that. For really complex things that would for sure not be included in the original files, like the dolphins across your screen, you can do it all within a single ObX file. This is capable because ObX allows creation of many different files within the code of one file, and you can even change files within Myx itself (with warnings). This could make it so anyone could just write C code in ObX or write it somewhere else and paste it into ObX, and it will incorporate it. Which also makes sharing much easier because everything could be in one file if wanted.

All of these things allow maximum power and control, like what is wanted for the 'Arch like' users, while still having the built in ease to those 'Windows like' users.