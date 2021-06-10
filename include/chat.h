#ifndef OWOPCPP_CHAT_H
#define OWOPCPP_CHAT_H

#include <span>
#include <string>
#include <vector>
#include <functional>

namespace OWOP {
class Chat
{
public:
    Chat();

    bool send(const std::string& msg);
    void local(const std::string& msg);

    void setSendModifier(std::function<void(std::string&)> modifier);
    void setRecvModifier(std::function<void(std::string&)> modifier);

    std::span<const std::string> messages() const;
private:
    std::vector<std::string> m_messages;
};
}

#endif // OWOPCPP_CHAT_H
