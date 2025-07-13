#ifndef VITTA_HPP_
#define VITTA_HPP_

namespace vitta {
namespace details {

/**
 * @brief Forward declaration of specialized structure for recursively
 *  adding new types to a generic variadic template type.
 *
 * @par Details
 *  This is the forward declaration for the specialized recursive cases.
 *  The metastructure will recursively aggregate new types or the types
 *  stored in a variadic template type the aggregation. The parameter
 *
 *  @li Notes, @ref aggregate_recursive is not meant to be instantiated
 *  directly. Use @ref aggregate and @ref aggregate_t.
 *
 * @tparam G     generic variadic type
 * @tparam C     complete variadic type
 * @tparam NewTs new types
 */
template <
    template <typename...> class G,
    typename                     C,
    typename...                  NewTs
> struct aggregate_recursive;


/**
 * @brief Aggregation base case.
 *
 * @par Details
 *  This partial specialization is used when there are no remaining types
 *  to be added to the aggregate.
 *
 * @tparam G  generic variadic type
 * @tparam Ts variadic aggregation types
 */
template <
    template <typename...> class G,
    typename...                  Ts
>
struct aggregate_recursive <
    G,
    G<Ts...>
> {
    using type = G<Ts...>;
};


/**
 * @brief Aggregation recursive case for new non @c G types.
 *
 * @par Details
 *  This partial specialization is used when the @c NewT is not a @c G.
 *  The type is appended to the end of @c G<Ts...>. Then the rest of
 *  @c OtherTs are recursively added.
 *
 * @tparam G       generic variadic type
 * @tparam Ts      variadic aggregation types
 * @tparam NewT    new type (newly added)
 * @tparam OtherTs new types (recursively added)
 */
template <
    template <typename...> class G,
    typename...                  Ts,
    typename                     NewT,
    typename...                  OtherTs
>
struct aggregate_recursive <
    G,
    G<Ts...>,
    NewT,
    OtherTs...
> {
    using type =
        typename aggregate_recursive <
            G,
            G<Ts..., NewT>,
            OtherTs...
        >::type;
};


/**
 * @brief Aggregation recursive case for new @c G types.
 *
 * @par Details
 *  This partial specialization is used when the new type is a @c G.
 *  The types @c NewTs are appended to the end of @c G<Ts...>. Then the
 *  rest of @c OtherTs are recursively added.
 *
 * @tparam G       generic variadic type
 * @tparam Ts      variadic aggregation types
 * @tparam NewTs   new types (newly added)
 * @tparam OtherTs new types (recursively added)
 */
template <
    template <typename...> class G,
    typename...                  Ts,
    typename...                  NewTs,
    typename...                  OtherTs
>
struct aggregate_recursive <
    G,
    G<Ts...>,
    G<NewTs...>,
    OtherTs...
> {
    using type =
        typename aggregate_recursive <
            G,
            G<Ts..., NewTs...>,
            OtherTs...
        >::type;
};

}  // namespace details


/**
 * @brief Forward declaration for aggregating a generic variadic type.
 *
 * @par Details
 *  It is the starting point for recursion of aggregating types into @c G.
 *  This is the general case that starts the aggregation with the new type.
 *
 * @tparam G     generic variadic type
 * @tparam NewTs new types
 */
template <
    template <typename...> class G,
    typename...                  NewTs
>
struct aggregate;


/**
 * @brief Aggregation case for non @c G types.
 *
 * @par Details
 *  This is a specialization of @c aggregate for non @c G types.
 *  All other types are added recursively.
 *
 * @tparam G     generic variadic type
 * @tparam T     initial type
 * @tparam NewTs new types (recursively added)
 */
template <
    template <typename...> class G,
    typename                     T,
    typename...                  NewTs
>
struct aggregate <
    G,
    T,
    NewTs...
> {
    using type =
        typename details::aggregate_recursive<
            G,
            G<T>,
            NewTs...
        >::type;
};


/**
 * @brief Aggregate types to a generic variadic type;
 * @brief Aggregation case for @c G<Ts...> types.
 *
 * @par Details
 *  This is a specialization of @c aggregate for @c G<Ts...> types.
 *  All other types are added recursively.
 *
 * @tparam G     generic variadic type
 * @tparam Ts    initial variadic aggregation types
 * @tparam NewTs new types (recursively added)
 */
template <
    template <typename...> class G,
    typename...                  Ts,
    typename...                  NewTs
>
struct aggregate <
    G,
    G<Ts...>,
    NewTs...
> {
    using type =
        typename details::aggregate_recursive<
            G,
            G<Ts...>,
            NewTs...
        >::type;
};


/**
 * @brief Alias for @ref vitta::aggregate<>::type.
 *
 * @tparam G  generic variadic type
 * @tparam Ts new types
 */
template <
    template <typename...> class G,
    typename...                  Ts
>
using aggregate_t = typename aggregate<G, Ts...>::type;

}  // namespace vitta

#endif  // VITTA_HPP_
