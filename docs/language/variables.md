# Variables

Variables in ObX are very similar to Python, and are made to be easy to use.
They are auto-type determined, and don't need to have type declarations.

They can also change types throughout the program, but type changes for
anything runtime like [events](docs/language/events.md) and [code sections](docs/language/dictators-and-metadata.md#code) will return warnings if a variable type can change.
More details on warnings [here](docs/language/errors-and-warnings.md)

[More on implementation](docs/architecture/implementation.md#Variables)