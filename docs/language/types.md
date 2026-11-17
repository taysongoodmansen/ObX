# Types

ObX automatically determines the type of a variable whenever it is set. You don't need to declare a type beforehand, and ObX figures it out from the value being assigned.

Types are currently stored as simple strings within ObX. For more information about how types are handled internally, see [Implementation](../architecture/implementation.md#variables).

## Implemented

<details>
<summary>Integers</summary>

Integers are whole numbers without decimal places. They can be positive, negative, or zero.

Examples include:

```obx
age = 17
count = 4
temperature = -315
```

A value is automatically identified as an integer when it is assigned as a number without a decimal point.

Integers can be used with numerical operators, including addition, subtraction, multiplication, and division. Some operators may specifically require integer values.

See [Expressions and Operators](expressions-and-operators.md) for more information.

</details>

<details>
<summary>Floats</summary>

Floats are numbers that contain a decimal point. They are useful when working with values that aren't whole numbers.

Examples include:

```obx
height = 1.83
price = 103.04
temperature = 19.8
```

A value is automatically identified as a float when it is assigned with a decimal point. Even a number such as `10.00` is treated as a float.

Floats can be used with most numerical operators, although some operators require integers and cannot be used with floats.

See [Expressions and Operators](expressions-and-operators.md) for more information.

</details>

<details>
<summary>Strings</summary>

Strings are used to store text. They can contain letters, numbers, symbols, and other characters.

Strings are written inside quotation marks:

```obx
name = "Tyler"
message = "Hello, world!"
version = "0.0.2"
```

Numbers inside quotation marks are treated as text rather than numerical values. For example, `"123"` is a string, while `123` is an integer.

Strings can be used to store names, messages, paths, configuration values, and other text-based information.

</details>

<details>
<summary>Booleans</summary>

Booleans represent one of two possible values: `true` or `false`.

They are useful for storing states and conditions, such as whether a window is visible or whether a feature is enabled.

```obx
visible = true
enabled = false
```

Boolean values can also be produced by comparisons and other expressions. For example:

```obx
is_adult = age >= 18
```

The result of the comparison is a boolean, depending on whether the condition is true or false.

</details>

<details>
<summary>Collections</summary>

Collections are used to store multiple values within a single variable. They can contain both indexed and keyed entries, allowing them to work as lists and dictionaries.

A basic collection uses square brackets:

```obx
ages = [7, 3, 5, 2]
```

Each value is automatically assigned an index, starting at `0`.

Collections can also contain keyed entries:

```obx
person = [name:"Jerry", age:17, state:"Arizona"]
```

This allows values to be accessed using either their index or their key. Indexed and keyed entries can exist together in the same collection.

Collections can contain different types of values, including other collections. This makes it possible to create more complex structures without needing separate collection types.

See [Collections](/docs/language/collections.md) for more information.

</details>

## Future

<details>
<summary>Events</summary>

Events are planned as a way to handle things that happen within ObX. They will allow code to respond to specific actions or occurrences instead of only running through instructions in order.

For example, events could be used for things such as responding to a button press, a window being opened, or a value being changed.

The exact implementation and syntax are still being developed.

</details>

<details>
<summary>Blocks</summary>

Blocks are planned to provide a way to store and work with groups of ObX instructions.

Rather than always executing their contents immediately, blocks can be saved and used in different ways depending on their context. This could allow them to be passed around, assigned to variables, or executed later.

Blocks will also be important for features such as functions and other areas where code needs to be stored before it is executed.

The exact behavior and implementation are still being developed.

More explaination in [functions](/docs/language/functions.md)

</details>