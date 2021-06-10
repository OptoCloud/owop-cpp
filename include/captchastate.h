#ifndef OWOPCPP_CAPTCHASTATE_H
#define OWOPCPP_CAPTCHASTATE_H

#include <string_view>

namespace OWOP {
enum class CaptchaState {
    Waiting   = 0,
    Verifying = 1,
    Verified  = 2,
    Ok        = 3,
    Invalid   = 4,
};
constexpr std::string_view CaptchaStateName(OWOP::CaptchaState state) {
    using namespace std::literals;
    switch (state) {
    case OWOP::CaptchaState::Waiting:
        return "WAITING"sv;
    case OWOP::CaptchaState::Verifying:
        return "VERIFYING"sv;
    case OWOP::CaptchaState::Verified:
        return "VERIFIED"sv;
    case OWOP::CaptchaState::Ok:
        return "OK"sv;
    case OWOP::CaptchaState::Invalid:
    default:
        return "INVALID"sv;
    }
}
}

#endif // OWOPCPP_CAPTCHASTATE_H
