#ifndef VITTA_TUPLE_AGGREGATE_HPP
#define VITTA_TUPLE_AGGREGATE_HPP

#include <tuple>

namespace vitta {

namespace detail {


    /**
     * @brief Creates a tuple aggregate from tuples and types recursively.
     * 
     * @par Details
     *  This is the forward declaration for specializations. A tuple and a new
     *  tuple or type is required. More tuples and types are allows. This
     *  metastruct will recursively aggregate new types or tuple types to
     *  the provided base tuple. The parameter pack must end with a @c void and
     *  @c X (any type). The @c void parameter marks the end of the recursion.
     * 
     *  @li Notes, @ref tuple_aggregate_recursive is not meant to be called directly.
     * 
     * @tparam V        tuple aggregate.
     * @tparam NewTV    new type and/or tuple to be added to aggregate.
     * @tparam NewTVs   new types and/or tuples for recursion.
     */
    template <typename V, typename NewTV, typename... NewTVs>
    struct tuple_aggregate_recursive;


    /**
     * @brief Specialized base case.
     * 
     * @par Details
     *  The type @c void marks the end of the recursion. @p Ignored1 and @p Ignored2
     *  are ignored; however, @p Ignored1 must be specified.
     * 
     * @tparam Ts       tuple types of aggregate.
     * @tparam Ignored1 ignored.
     * @tparam Ignored2 ignored.
     */
    template <typename... Ts, typename Ignored1, typename... Ignored2>
    struct tuple_aggregate_recursive
        <   std::tuple<Ts...>,
            void,
            Ignored1,
            Ignored2...>
    {
        using type = std::tuple<Ts...>;    
    };


    /**
     * @brief Specialized recursive case for a type.
     * 
     * @par Details
     *  The recursive case for a signular type (non @c std::tuple). The singular
     *  type is appended to the end of tuple aggregate.
     * 
     * @tparam Ts       tuple types of aggregate.
     * @tparam NewT     new non-tuple type to be added to aggregate.
     * @tparam NewTVs   new types or new tuples for recursion.
     */
    template <typename... Ts, typename NewT, typename... NewTVs>
    struct tuple_aggregate_recursive
        <   std::tuple<Ts...>,
            NewT,
            NewTVs...>
    {
        using type = typename tuple_aggregate_recursive
            <   std::tuple<Ts..., NewT>,
                NewTVs...>::type;
    };


    /**
     * @brief Specialized recursive case for a tuples.
     * 
     * @par Details
     *  The recursive case tuple types held within a @c std::tuple. The types
     *  are appended to the end of the tuple aggregate.
     * 
     * @tparam Ts       tuple types of aggregate.
     * @tparam NewTs    new tuple types to be added to aggregate.
     * @tparam NewTVs   new types or new tuples for recursion.
     */
    template <typename... Ts, typename... NewTs, typename... NewTVs>
    struct tuple_aggregate_recursive
        <   std::tuple<Ts...>,
            std::tuple<NewTs...>,
            NewTVs...>
    {
        using type = typename tuple_aggregate_recursive
            <   std::tuple<Ts..., NewTs...>,
                NewTVs...>::type;
    };


    /**
     * @brief Helper type for @ref tuple_aggregate_recursive.
     * 
     * @tparam V        tuple aggregate
     * @tparam NewTV    new type or new tuple to be added to aggregate
     * @tparam NewTVs   new types or new tuples for recursion
     */
    template <typename V, typename NewTV, typename... NewTVs>
    using tuple_aggregate_recursive_t =
        typename tuple_aggregate_recursive
            <   V,
                NewTV,
                NewTVs...>::type;


} // detail



/**
 * @brief Creates a tuple aggregate from tuples and types.
 * 
 * @par Details
 *  It is the starting point for recursion of aggregating tuples and types.
 *  This is the general case that takes a non-tuple type. A tuple aggregate
 *  is created from this non-tuple type. This is a proxy for
 *  @ref tuple_aggregate_recursion.
 * 
 * @tparam T        first tuple types of aggregate.
 * @tparam NewTVs   new types or tuples for recursion.
 */
template <typename T, typename... NewTVs>
struct tuple_aggregate
{
    using type = detail::tuple_aggregate_recursive_t
        <   std::tuple<T>,
            NewTVs...,
            void,
            void>;
};


/**
 * @brief Specialized case for a tuple.
 * 
 * @par Details
 *  It is the starting point for recursion of aggregating tuples and types.
 *  This is a specialized case that takes a base tuple which becomes the base
 *  tuple aggregate. This is a proxy for @ref tuple_aggregate_recursion
 * 
 * @tparam Ts       first set of tuple typess of aggregate
 * @tparam NewTVs   new types or tuples for recursion.
 */
template <typename... Ts, typename... NewTVs>
struct tuple_aggregate
    <   std::tuple<Ts...>,
        NewTVs...>
{
    using type = detail::tuple_aggregate_recursive_t
        <   std::tuple<Ts...>,
            NewTVs...,
            void,
            void>;
};


/**
 * @brief Helper type for @ref tuple_aggregate
 * 
 * @tparam TV       first type or tuple typess of aggregate
 * @tparam NewTVs   new types of tuples for recursion.
 */
template <typename TV, typename... NewTVs>
using tuple_aggregate_t =
    typename tuple_aggregate
        <   TV,
            NewTVs...>::type;


} // namespace vitta

#endif // VITTA_TUPLE_AGGREGATE_HPP
