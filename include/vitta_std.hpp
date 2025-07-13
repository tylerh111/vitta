#ifndef VITTA_STD_HPP_
#define VITTA_STD_HPP_

// =============================================================
// aggregate forward declarations
// =============================================================

namespace vitta {

template <template <typename...> class, typename...>
struct aggregate;

template <template <typename...> class, typename...>
using aggregate_t = typename aggregate<G, Ts...>::type;

}  // namespace vitta


// =============================================================
// aggregate tuple
// =============================================================

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus >= 201103L)

#include <tuple>

namespace vitta {

/**
 * @brief Aggregate types to @c std::tuple type.
 *
 * @tparam Ts new types recursively added.
 */
template <typename... Ts>
struct aggregate_tuple {
    using type = typename aggregate<std::tuple, Ts...>::type;
};

/**
 * @brief Alias for @ref vitta::aggregate_tuple<>::type.
 *
 * @tparam Ts new types
 */
template <typename... Ts>
using aggregate_tuple_t = typename aggregate_tuple<Ts...>::type;

}  // namespace vitta

#endif  // version check


// =============================================================
// aggregate variant
// =============================================================

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)

#include <variant>

namespace vitta {

/**
 * @brief Aggregate types to @c std::variant type.
 *
 * @tparam Ts new types recursively added.
 */
template <typename... Ts>
struct aggregate_variant {
    using type = typename aggregate<std::variant, Ts...>::type;
};

/**
 * @brief Alias for @ref vitta::aggregate_variant<>::type.
 *
 * @tparam Ts new types
 */
template <typename... Ts>
using aggregate_variant_t = typename aggregate_variant<Ts...>::type;

}  // vitta

#endif  // version check

#endif  // VITTA_STD_HPP_
