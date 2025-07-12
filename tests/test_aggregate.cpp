
#include <type_traits>

#include <vitta.hpp>

template <typename...> struct test {};
template <typename... Ts> using test_agg_t = vitta::aggregate_t<test, Ts...>;


// 1 argument(s)
static_assert(std::is_same< test<int>, test_agg_t<     int > >::value);
static_assert(std::is_same< test<int>, test_agg_t<test<int>> >::value);

// 2 argument(s)
static_assert(std::is_same< test<int, int>, test_agg_t<     int,       int > >::value);
static_assert(std::is_same< test<int, int>, test_agg_t<test<int>,      int > >::value);
static_assert(std::is_same< test<int, int>, test_agg_t<     int,  test<int>> >::value);
static_assert(std::is_same< test<int, int>, test_agg_t<test<int>, test<int>> >::value);
static_assert(std::is_same< test<int, int>, test_agg_t<test<int,       int>> >::value);

// 3 argument(s)
static_assert(std::is_same< test<int, int, int>, test_agg_t<     int,       int,       int > >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int>,      int,       int > >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<     int,  test<int>,      int > >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<     int,       int,  test<int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int>, test<int>,      int > >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int,       int>,      int > >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int>,      int,  test<int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<     int,  test<int>, test<int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<     int,  test<int,       int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int>, test<int>, test<int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int,       int>, test<int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int>, test<int,       int>> >::value);
static_assert(std::is_same< test<int, int, int>, test_agg_t<test<int,       int,       int>> >::value);
