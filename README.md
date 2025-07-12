# ViTTA

A C++ variadic template type aggregation tool.

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
        if      constexpr (std::is_same_v<std::decay_t<T>, double>) {/*...*/}
        else if constexpr (std::is_same_v<std::decay_t<T>, var_t>)  {/*...*/}
        else if constexpr (std::is_same_v<std::decay_t<T>, int>)    {/*...*/} // unused
    }, var);
}
```

Nested variants causes issues when creating generic code.
Instead, we want to collapse and aggregate all the variant alternatives in each nested type into one large variant.
This insures we can visit this variant without having to nest calls to variants.

Enter ViTTA.

ViTTA is a header only library that adds two type traits that collapse/aggregates variants and tuples.

```c++
using var_t = std::variant<int>;

using var_new_t = vitta::aggregate_variant_t<var_t, double>;
//              = std::variant<int, double>

int main() {
    // var hold an int
    var_new_t var = 3;

    std::visit([] <typename T> (T&& arg) {
        if      constexpr (std::is_same_v<std::decay_t<T>, double>) {/*...*/}
        else if constexpr (std::is_same_v<std::decay_t<T>, var_t>)  {/*...*/} // unused
        else if constexpr (std::is_same_v<std::decay_t<T>, int>)    {/*...*/}
    }, var);
}
```

## Usage

The generic `vitta::aggregate` is defined in `vitta.hpp`.
A convenience aliases for `std::tuple` and `std::variant` aggregation in `vitta_std.hpp`.
This library defines the following types for the end user.

```c++
// generic aggregation
template <template <typename...> class G, typename Ts...>
struct vitta::aggregate;

template <template <typename...> class G, typename Ts...>
using vitta::aggregate_t = typename vitta::aggregate<G, Ts...>::type;

// variant aggregation
template <typename... Ts>
struct vitta::aggregate_variant;

template <typename... Ts>
using vitta::aggregate_variant_t = typename vitta::aggregate_variant<Ts...>::type;

// tuple aggregation
template <typename... Ts>
struct vitta::aggregate_tuple;

template <typename... Ts>
using vitta::aggregate_tuple_t = typename vitta::aggregate_tuple<Ts...>::type;
```

## Examples

The following are example use cases for the library.
Note that the types remain in order.

```c++
#include <type_traits>
#include <vitta.hpp>

template <typename...> test;
template <typename... Ts> using aggregate_test_t = vitta::aggregate_t<test, Ts...>;

static_assert(std::is_same_v< test<int, float>, aggregate_test_t<int,            float > >);
static_assert(std::is_same_v< test<int, float>, aggregate_test_t<test<int>,      float > >);
static_assert(std::is_same_v< test<int, float>, aggregate_test_t<     int,  test<float>> >);
static_assert(std::is_same_v< test<int, float>, aggregate_test_t<test<int>, test<float>> >);
static_assert(std::is_same_v< test<int, float>, aggregate_test_t<test<int,       float>> >);
```

## Thoughts

Structs are comparable to `std::tuple` as they are ordered types.
Likewise, unions are comparable to `std::variant` as they are advertised as type-safe unions.
Then aggregation with `std::tuple` and `std::variant` are synonymous with struct inheritance and nested unions.
Below is an example of aggregation that emulates C++ behavior with structs and unions.

```c++
// structs and tuples
struct X { int; };
struct Y : X { double; };

using X = vitta::aggregate_tuple_t<int>;
using Y = vitta::aggregate_tuple_t<X, double>;

// unions and variants
union X { int };
union Y { X, double };

using X = vitta::aggregate_variant_t<int>;
using Y = vitta::aggregate_variant_t<X, double>;
```

It's not apparent what the use of this would be (if any), but any interesting outcome for this problem.
