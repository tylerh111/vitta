
#include "vitta/tuple_aggregate.hpp"

#include <type_traits>

#ifndef VARIADIC_ARGS
#error "Must specify 'VARIADIC_ARGS'"
#endif

#ifndef VITTA_ARGS
#error "Must specify 'VITTA_ARGS'"
#endif

#define _STRINGIZE(...) #__VA_ARGS__
#define STRINGIZE(...) _STRINGIZE(__VA_ARGS__)

using variadic_inst = std::tuple<VARIADIC_ARGS>;
using vitta_inst = vitta::tuple_aggregate_t<VITTA_ARGS>;

template <typename T, typename U>
void test() {
    static_assert(
        std::is_same_v<T, U>,
        "std::tuple< " STRINGIZE(VARIADIC_ARGS) " > != "
        "vitta::tuple_aggregate_t< " STRINGIZE(VITTA_ARGS) " >");
}

template void test<variadic_inst, vitta_inst>();
