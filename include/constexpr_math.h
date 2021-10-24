#ifndef OWOCPP_CONSTEXPR_MATH_H
#define OWOCPP_CONSTEXPR_MATH_H

#include <type_traits>

namespace OWOP::Internal::Math {
template <typename T>
constexpr T Mult(T a, T b) noexcept
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    return a * b;
}
template <typename T>
constexpr T Pow(T base, T exponent) noexcept
{
    static_assert(std::is_integral<T>::value, "Integral required.");
    T result = 1;
    while (exponent != 0) {
        result *= base;

        exponent--;
    }

    return result;
}
}

#endif // OWOCPP_CONSTEXPR_MATH_H
