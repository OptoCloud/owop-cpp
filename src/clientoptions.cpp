#include "clientoptions.h"

#include "constants.h"

OWOP::ClientOptions::ClientOptions()
    : m_maxChatBuffer(256)
    , m_maxMessageLength{ 128, 128, 259, 16384 }
    , m_maxWorldNameLength(24)
    , m_worldBorder(0xFFFFFF)
    , m_chatVerificationString("")
    , m_tokenVerificationString("CaptchA")
    , m_worldVerificationToken(25565)
{
}
OWOP::ClientOptions::ClientOptions(const OWOP::ClientOptions& other)
    : m_maxChatBuffer(other.m_maxChatBuffer)
    , m_maxMessageLength(other.m_maxMessageLength)
    , m_maxWorldNameLength(other.m_maxWorldNameLength)
    , m_worldBorder(other.m_worldBorder)
    , m_chatVerificationString(other.m_chatVerificationString)
    , m_tokenVerificationString(other.m_tokenVerificationString)
    , m_worldVerificationToken(other.m_worldVerificationToken)
{
}

std::string OWOP::ClientOptions::getChatVerificationString() const
{
    return m_chatVerificationString;
}

void OWOP::ClientOptions::setChatVerificationString(const std::string &verificationString)
{
    m_chatVerificationString = verificationString;
}

std::string OWOP::ClientOptions::getTokenVerficicationString() const
{
    return m_tokenVerificationString;
}

void OWOP::ClientOptions::setTokenVerficicationString(const std::string &verificationString)
{
    m_tokenVerificationString = verificationString;
}

OWOP::ClientOptions& OWOP::ClientOptions::operator=(const OWOP::ClientOptions& other)
{
    m_maxChatBuffer = other.m_maxChatBuffer;
    m_maxMessageLength = other.m_maxMessageLength;
    m_maxWorldNameLength = other.m_maxWorldNameLength;
    m_worldBorder = other.m_worldBorder;
    m_chatVerificationString = other.m_chatVerificationString;
    m_tokenVerificationString = other.m_tokenVerificationString;
    m_worldVerificationToken = other.m_worldVerificationToken;
    return *this;
}
