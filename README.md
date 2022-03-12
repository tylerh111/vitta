# ViTTA

A C++ variadic (i) template type aggregation tool.

## Problem
There are cases where it may be necessary to extend a C++ variant's type.
This can be done by nesting variants, but it does collapse the nested variants.

One particular reason is if a nested variant is visited, another visit is necessary to get to the nested type.
Moreover, assignment becomes an issue when trying to assign the "super"-variant with a type of a nested variant.


```c++
using var_t = std::variant<int>;

using var_new_t = std::variant<var_t,       double>;
//              = std::variant<std::variant<int>, double>
//                std::variant<int,               double>  // want


int main() {
    // var holds a std::variant<int>
    var_new_t var = 3;

    std::visit([] <typename T> (T&& arg) {
        if      constexpr (std::is_same_v<T, double>)   {/*...*/}
        else if constexpr (std::is_same_v<T, var_t>)    {/*...*/}
        else if constexpr (std::is_same_v<T, int>)      {/*...*/} // unused
    }, var);
}
```

Nested variants causes issues when creating generic code.
Instead, we want to collapse and aggregate all the variant alternatives in each nested type into one large variant.
This insures we can visit this variant without having to nest calls to variants.

Enter ViTTA.

ViTTA is a header only library that adds two type triats that collapse/aggregates variants and tuples.

```c++
using var_t std::variant<int>;

using var_new_t = vitta::variant_aggregate_t<var_t, double>;
//              = std::variant<int, double>


int main() {
    // var hold an int
    var_new_t var = 3;

    std::visit([] <typename T> (T&& arg) {
        if      constexpr (std::is_same_v<T, double>)   {/*...*/}
        else if constexpr (std::is_same_v<T, var_t>)    {/*...*/} // unused
        else if constexpr (std::is_same_v<T, int>)      {/*...*/}
    }, var);
}
```

## Usage
Simply include either `vitta/tuple_aggregate.hpp` or `vitta/variant_aggregate.hpp`.
This library defines the following types for the end user.

```c++
// variant aggregation
template <typename T, typename... NewTVs>
struct vitta::variant_aggregate;

template <typename TV, typename... NewTVs>
using vitta::variant_aggregate_t =
    typename variant_aggregate<TV, NewTVs...>::type;


// tuple aggregation
template <typename T, typename... NewTVs>
struct vitta::tuple_aggregate;

template <typename TV, typename... NewTVs>
using vitta::tuple_aggregate_t =
    typename tuple_aggregate<TV, NewTVs...>::type;
```

## Thoughts
These aggregation tools give the ability to **extend** a variant or tuple.
Since variants are type-safe unions, `vitta::variant_aggregate` provides the ability to "extend" a variants' types.
Similarly, tuples can be viewed as structs. Then  `vitta::tuple_aggregate` provides the ability to "inherit" from other tuples.

Here is an example of inheritance using `vitta::tuple_aggregate`.
```c++
// using inheritance
struct X { int; };
struct Y : X { double; };

// using aggregation
using X = std::tuple<int>;
using Y = vitta::tuple_aggregate_t<X, double>;
```

It's not apparent what the use of this would be (if any), but any interesting outcome for this problem.

## Development
While I only created aggregation for two types (tuple and variants), this could clearly work for other variadic templates.

A generic version of variadic template aggregation is on the list of things to do.

