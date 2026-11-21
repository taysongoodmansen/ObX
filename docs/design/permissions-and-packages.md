# Packages
Packages are a built-in system to make code sharing easier and safer.

The first thing included is `$$` as a replacement for `$` inside packages. The reason why is because packages may be placed anywhere within your files; it could be one place for someone and another for someone else. Using `$$` will go to the 'root' of the package, and so people can design things without knowing the original directory at all.

Then for a standard package, it will have some of these things at the top. 
- `<permissions>{...}` is to specify what it can do (more in next section). 
- `<require>{...}` is used for checking if other files exist. It's useful so you can reuse code, both for less rewriting, and so changing one thing can change it in multiple places. Inside you can specify what the package name is, what the package tag is (genre of package), and what the package provides. For checking what it provides, you can either check individual things or the interface type (explained in next thing). The exact syntax is to come later.
- `<provides>{...}` is to show what the package does for others. It specifies what variables in the file there are that are public, and then what other files can do with them. So like `read $$.x`, `write $$.color`, `run $$.add_widget(widget)`. You can also define an interface, which is just a string like `"std toolbar v1"`, which is only used as a tag to make requirements easier.

Because packages also don't know where other packages are, we have to solve it just like the `$$`. When you do `<require>{...}`, it will also write pointer variables for everything. So if you require a toolbar, it will make `$$.toolbar` be the path to that toolbar.
# Permissions

Because ObX is designed with Myx in mind, and Myx is planned to have code sharing, it is important to consider safety.

With no safety features, it would be very easy to inject malicious code. Someone could just add `exec_cmd("rm _")` and remove files.

To solve this, we implement a permissions system that, without defining in a file, will default to none. To use it, people just write `<permissions>{...}` where you write all things allowed. There isn't yet a set list, but in the future there may be things like `read extern`, `run cmd`, and for safety within Myx itself, `edit pkgs` and `edit runtime`.

Within the code, if it ever reaches a piece of code it isn't allowed to run, it will return an error.

Inside of the package website, and on initial run of a package, it will ask the user if it agrees to any of the permissions allowed. It will make it very clear what the package is able to do, so that if there is anything malicious, it is clear to the user.

The permissions of a file only match the package they are in. Permissions will auto-continue when using `include`, but not with `pkg` (see in [include](/docs/language/includes.md)).

If any packages communicate, whatever code is being run will default to the permissions of the file it was defined in.

With that, there is an easy safety issue, in that something may have full permissions, like in the example of ezTerminal. A random package could just require ezT and do `ezT.run("rm _")`, which is an issue because the file running it doesn't have permission to run those.

To fix this, we add requirements for permissions. Someone can leave it blank, and it will default to the permissions of where anything was defined. But then they can specify other things, like needing the caller's permissions to include `exec cmd`. Or it can also run code with the caller's permissions instead.