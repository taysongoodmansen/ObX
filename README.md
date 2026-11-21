# ObX

ObX is a language designed almost entirely for configuration in C-based projects.

I'm making ObX so it can be directly built into my future Wayland compositor, Myx. The goal is to make configuration easy to write, accessible anywhere within a file, and give users as much control as possible over how a program works.

## The Paradigm

It and Myx are designed with a few things to solve a common
issue in user envionrment. [read about here](docs/design/problem-fixed.md)

ObX is designed around a few main ideas:

- **User control:** Users should have as much control over configuration as possible.
- **Guidance over stopping:** ObX should try to guide users and warn them about problems instead of stopping the program whenever something goes wrong.
- **Object-based structure:** Variables are part of a hierarchy, similar to a filesystem. This makes it possible to organize configuration and access values from different places.

You can read more about these ideas in the [design philosophy](docs/design/philosophy.md).

## General Syntax

ObX is designed to be somewhat similar to Python in how it looks, mainly to make it easier to read and write. It also has more advanced features for when they are needed.

## Variables

Variables work somewhat similarly to Python. They can be set without declaring their types, and they can change types throughout the program.

Variables are also attributes of their parent objects. For example, setting `name = "jerry"` will set the `name` attribute of the current object. The current object is represented by a path, with `$` representing the root.

You can read more about [variables](docs/language/variables.md) and the [object hierarchy and paths](docs/language/objects-and-paths.md).

## Values and Types

ObX currently has several basic types:

- **Integers:** Whole numbers, such as `3`, `7`, and `207`.
- **Floats:** Numbers with decimal points, such as `2.7`, `19.20`, and `0.3`.
- **Strings:** Text, such as `"hello"` or `"jerry"`.
- **Booleans:** `True` or `False`.
- **Collections:** Multiple values stored under one variable. They combine the functionality of Python's lists and dictionaries, using keys and values for everything. If no keys are provided, indexed keys are used automatically.

For example:

```obx
people = ["bob", "jerry", "sam"]
```

This creates a collection with keys `0`, `1`, and `2`. You can also specify keys:

```obx
person = ["name":"bob", "age":13, "employed":True]
```

Collections can also be accessed using `variable[key]`.

More information about [types](docs/language/types.md) and [collections](docs/language/collections.md) is available in the documentation.

## Operations

ObX uses a basic `A O B` format for operations. For example, `7+3` or `age+5`.

Numerical operations can use integers and floats. The result depends on the values being used.

See [expressions and operators](docs/language/expressions-and-operators.md) for more information.

## Events

Events are intended to let one piece of code connect to another and run later when something happens. This could be useful for things like a window manager, where some code shouldn't run when the program first starts, but should wait until a certain event occurs.

Events are not currently supported. You can read more about the planned system in the [events documentation](docs/language/events.md).

## Current Status

ObX is still being developed, and some features are not implemented yet.

**Current version:** `0.0.1`

Some of the things currently being worked on include:

- Operations and expressions
- Collections
- Improving the interpreter and parsing

Some planned features include:

- [Functions](docs/language/functions.md)
- [Dictators](docs/language/dictators-and-metadata.md)
- [Includes](docs/language/includes.md)
- [Events](docs/language/events.md)
- [Dependency handling](docs/language/dependencies.md)

These features and their designs may change as development continues.

## Documentation

The documentation goes into more detail about how ObX works, how its features are designed, and how the interpreter is implemented.

See the [documentation index](docs/index.md) for the full documentation.

### Language

- [Language Overview](docs/language/overview.md)
- [Syntax](docs/language/syntax.md)
- [Variables](docs/language/variables.md)
- [Types](docs/language/types.md)
- [Objects and Paths](docs/language/objects-and-paths.md)
- [Collections](docs/language/collections.md)
- [Expressions and Operators](docs/language/expressions-and-operators.md)
- [Control Flow](docs/language/control-flow.md)
- [Functions](docs/language/functions.md)
- [Events](docs/language/events.md)
- [Includes](docs/language/includes.md)
- [Dependencies](docs/language/dependencies.md)
- [Errors and Warnings](docs/language/errors-and-warnings.md)
- [Dictators and Metadata](docs/language/dictators-and-metadata.md)

### Architecture

- [Architecture Overview](docs/architecture/overview.md)
- [Interpreter](docs/architecture/interpreter.md)
- [Value System](docs/architecture/value-system.md)
- [Parsing and Execution](docs/architecture/parsing-and-execution.md)
- [C Integration](docs/architecture/c-integration.md)

### Design

- [Design Philosophy](docs/design/philosophy.md)
- [Design Decisions](docs/design/design-decisions.md)
- [Roadmap](docs/design/roadmap.md)
- [Problem fixed](docs/design/problem-fixed.md)
- [Permissions and packages](docs/design/permissions-and-packages.md)