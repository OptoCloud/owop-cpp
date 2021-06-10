#ifndef OWOCPP_CONSTEXPR_MATH_H
#define OWOCPP_CONSTEXPR_MATH_H

#include <cstdlib>
#include <cstdint>

namespace OWOP::Internal::Math {
constexpr std::size_t Pow(std::size_t base, std::size_t exponent) noexcept
{
    std::size_t result = 1;
    while (exponent != 0) {
        result *= base;

        exponent--;
    }

    return result;
}
}

#endif // OWOCPP_CONSTEXPR_MATH_H
