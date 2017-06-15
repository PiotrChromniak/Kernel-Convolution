#ifndef KERNELCONVOLUTION_VALUE_RANGE_H
#define KERNELCONVOLUTION_VALUE_RANGE_H

#include <limits>
#include <type_traits>

template<class T, class U>
constexpr T value_within_range(U number) {
    using common_type = typename std::common_type<T, U>::type;

    common_type num = static_cast<common_type>(number);
    constexpr auto min_val = std::numeric_limits<T>::min();
    constexpr auto max_val = std::numeric_limits<T>::max();

    if (num > max_val)
        return max_val;
    else if (num < min_val)
        return min_val;
    return static_cast<T>(number);
};

#endif //KERNELCONVOLUTION_VALUE_RANGE_H
