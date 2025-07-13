#ifndef VITTA_FWD_HPP_
#define VITTA_FWD_HPP_

namespace vitta {

template <template <typename...> class, typename...>
struct aggregate;

template <template <typename...> class, typename...>
using aggregate_t = typename aggregate<G, Ts...>::type;

}  // namespace vitta

#endif  // VITTA_FWD_HPP_
