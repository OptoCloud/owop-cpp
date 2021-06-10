#ifndef OWOPCPP_CLIENTOPTIONS_H
#define OWOPCPP_CLIENTOPTIONS_H

#include "playerrank.h"

#include <string>
#include <array>
#include <cstdlib>
#include <cstdint>

namespace OWOP {
class ClientOptions
{
public:
    static ClientOptions globalOptions;

    ClientOptions();
    ClientOptions(const OWOP::ClientOptions& other);

    constexpr std::uint32_t getMaxChatBuffer() const noexcept {
        return m_maxChatBuffer;
    }
    constexpr void setMaxChatBuffer(std::uint32_t maxChatBuffer) noexcept {
        m_maxChatBuffer = maxChatBuffer;
    }

    constexpr std::uint16_t getMaxMessageLength(OWOP::PlayerRank rank) const noexcept {
        if (rank >= OWOP::PlayerRank::None && rank <= OWOP::PlayerRank::Admin) {
            return m_maxMessageLength[(std::uint8_t)rank];
        }
        return 0;
    }
    constexpr void setMaxMessageLength(std::uint16_t messageLength, OWOP::PlayerRank rank) noexcept {
        if (rank >= OWOP::PlayerRank::None && rank <= OWOP::PlayerRank::Admin) {
            m_maxMessageLength[(std::uint8_t)rank] = messageLength;
        }
    }

    constexpr std::uint16_t getMaxWorldNameLength() const noexcept {
        return m_maxWorldNameLength;
    }
    constexpr void setMaxWorldNameLength(std::uint16_t length) noexcept {
        m_maxWorldNameLength = length;
    }

    constexpr std::int32_t  getWorldBorder() const noexcept {
        return m_worldBorder;
    }
    constexpr void setWorldBorder(std::int32_t border) noexcept {
        m_worldBorder = border;
    }

    std::string   getChatVerificationString() const;
    void setChatVerificationString(const std::string& verificationString);

    std::string   getTokenVerficicationString() const;
    void setTokenVerficicationString(const std::string& verificationString);

    constexpr std::int64_t  getWorldVerificationToken() const noexcept {
        return m_worldVerificationToken;
    }
    constexpr void setWorldVerificationToken(std::int64_t verificationToken) noexcept {
        m_worldVerificationToken = verificationToken;
    }

    ClientOptions& operator=(const ClientOptions& other);
private:
    std::uint32_t m_maxChatBuffer;
    std::array<std::uint16_t, (std::size_t)OWOP::PlayerRank::ENUM_LEN> m_maxMessageLength;
    std::uint16_t m_maxWorldNameLength;
    std::int32_t m_worldBorder;
    std::string m_chatVerificationString;
    std::string m_tokenVerificationString;
    std::int64_t m_worldVerificationToken;
};
}

#endif // OWOPCPP_CLIENTOPTIONS_H
