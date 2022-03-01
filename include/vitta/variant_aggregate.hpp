#ifndef VITTA_VARIANT_AGGREGATE_HPP
#define VITTA_VARIANT_AGGREGATE_HPP

#include <variant>

namespace vitta {

namespace detail {


    /**
     * @brief Creates a variant aggregate from variants and types recursively.
     * 
     * @par Details
     *  This is the forward declaration for specializations. A variant and a new
     *  variant or type is required. More variants and types are allows. This
     *  metastruct will recursively aggregate new types or variant types to
     *  the provided base variant. The parameter pack must end with a @c void and
     *  @c X (any type). The @c void parameter marks the end of the recursion.
     * 
     *  @li Notes, @ref variant_aggregate_recursive is not meant to be called directly.
     * 
     * @tparam V        variant aggregate.
     * @tparam NewTV    new type and/or variant to be added to aggregate.
     * @tparam NewTVs   new types and/or variants for recursion.
     */
    template <typename V, typename NewTV, typename... NewTVs>
    struct variant_aggregate_recursive;


    /**
     * @brief Specialized base case.
     * 
     * @par Details
     *  The type @c void marks the end of the recursion. @p Ignored1 and @p Ignored2
     *  are ignored; however, @p Ignored1 must be specified.
     * 
     * @tparam Ts       variant types of aggregate.
     * @tparam Ignored1 ignored.
     * @tparam Ignored2 ignored.
     */
    template <typename... Ts, typename Ignored1, typename... Ignored2>
    struct variant_aggregate_recursive
        <   std::variant<Ts...>,
            void,
            Ignored1,
            Ignored2...>
    {
        using type = std::variant<Ts...>;    
    };


    /**
     * @brief Specialized recursive case for a type.
     * 
     * @par Details
     *  The recursive case for a signular type (non @c std::variant). The singular
     *  type is appended to the end of variant aggregate.
     * 
     * @tparam Ts       variant types of aggregate.
     * @tparam NewT     new non-variant type to be added to aggregate.
     * @tparam NewTVs   new types or new variants for recursion.
     */
    template <typename... Ts, typename NewT, typename... NewTVs>
    struct variant_aggregate_recursive
        <   std::variant<Ts...>,
            NewT,
            NewTVs...>
    {
        using type = typename variant_aggregate_recursive
            <   std::variant<Ts..., NewT>,
                NewTVs...>::type;
    };


    /**
     * @brief Specialized recursive case for a variants.
     * 
     * @par Details
     *  The recursive case variant types held within a @c std::variant. The types
     *  are appended to the end of the variant aggregate.
     * 
     * @tparam Ts       variant types of aggregate.
     * @tparam NewTs    new variant types to be added to aggregate.
     * @tparam NewTVs   new types or new variants for recursion.
     */
    template <typename... Ts, typename... NewTs, typename... NewTVs>
    struct variant_aggregate_recursive
        <   std::variant<Ts...>,
            std::variant<NewTs...>,
            NewTVs...>
    {
        using type = typename variant_aggregate_recursive
            <   std::variant<Ts..., NewTs...>,
                NewTVs...>::type;
    };


    /**
     * @brief Helper type for @ref variant_aggregate_recursive.
     * 
     * @tparam V        variant aggregate
     * @tparam NewTV    new type or new variant to be added to aggregate
     * @tparam NewTVs   new types or new variants for recursion
     */
    template <typename V, typename NewTV, typename... NewTVs>
    using variant_aggregate_recursive_t =
        typename variant_aggregate_recursive
            <   V,
                NewTV,
                NewTVs...>::type;


} // detail



/**
 * @brief Creates a variant aggregate from variants and types.
 * 
 * @par Details
 *  It is the starting point for recursion of aggregating variants and types.
 *  This is the general case that takes a non-variant type. A variant aggregate
 *  is created from this non-variant type. This is a proxy for
 *  @ref variant_aggregate_recursion.
 * 
 * @tparam T        first variant types of aggregate.
 * @tparam NewTVs   new types or variants for recursion.
 */
template <typename T, typename... NewTVs>
struct variant_aggregate
{
    using type = detail::variant_aggregate_recursive_t
        <   std::variant<T>,
            NewTVs...,
            void,
            void>;
};


/**
 * @brief Specialized case for a variant.
 * 
 * @par Details
 *  It is the starting point for recursion of aggregating variants and types.
 *  This is a specialized case that takes a base variant which becomes the base
 *  variant aggregate. This is a proxy for @ref variant_aggregate_recursion
 * 
 * @tparam Ts       first set of variant typess of aggregate
 * @tparam NewTVs   new types or variants for recursion.
 */
template <typename... Ts, typename... NewTVs>
struct variant_aggregate
    <   std::variant<Ts...>,
        NewTVs...>
{
    using type = detail::variant_aggregate_recursive_t
        <   std::variant<Ts...>,
            NewTVs...,
            void,
            void>;
};


/**
 * @brief Helper type for @ref variant_aggregate
 * 
 * @tparam TV       first type or variant typess of aggregate
 * @tparam NewTVs   new types of variants for recursion.
 */
template <typename TV, typename... NewTVs>
using variant_aggregate_t =
    typename variant_aggregate
        <   TV,
            NewTVs...>::type;


} // namespace vitta

#endif // VITTA_VARIANT_AGGREGATE_HPP
