#ifndef UUID_H
#define UUID_H

#if defined(_WIN32) && defined(QT_VERSION)
#define GUID_STRUCT_EXISTS
#include <QUuid>
#endif

#include <span>
#include <array>
#include <string>

namespace OWOP {

struct Uuid
{
private:
    friend std::hash<OWOP::Uuid>;
public:
    static OWOP::Uuid NewUuid();
    static bool TryParse(const char* string, OWOP::Uuid& uuidOut);
    static const OWOP::Uuid Empty();

    Uuid() noexcept;
#ifdef GUID_STRUCT_EXISTS
    Uuid(const QUuid& other) {
        auto rfc4122 = other.toRfc4122();
        std::memcpy(m_data.data(), rfc4122.data(), 16);
    }
#endif
    Uuid(const OWOP::Uuid& other) noexcept;
    Uuid(std::array<std::uint8_t, 16> data) noexcept;
    Uuid(std::span<const std::uint8_t, 16> data) noexcept;

    bool isEmpty() const noexcept;

    std::string toString() const;
    std::span<const std::uint8_t, 16> toBytes() const;
#ifdef GUID_STRUCT_EXISTS
    QUuid toQUuid() const {
        return QUuid(*(GUID*)m_data.data());
    }
#endif

    bool operator==(const OWOP::Uuid& rhs) const noexcept;
    bool operator!=(const OWOP::Uuid& rhs) const noexcept;
    bool operator< (const OWOP::Uuid& rhs) const noexcept;
    bool operator<=(const OWOP::Uuid& rhs) const noexcept;
    bool operator> (const OWOP::Uuid& rhs) const noexcept;
    bool operator>=(const OWOP::Uuid& rhs) const noexcept;

    void swap(OWOP::Uuid& other) noexcept;

    OWOP::Uuid operator=(const OWOP::Uuid& other) noexcept;
private:
    std::array<std::uint8_t, 16> m_data;
};
}

namespace std {
template <>
struct hash<OWOP::Uuid>
{
std::size_t operator()(const OWOP::Uuid& k) const noexcept
{
    return (std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(k.m_data.data() + 0)) ^
           (std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(k.m_data.data() + 8)) << 1)) >> 1;
}
};
/*
template<>
void swap(OWOP::Uuid& lhs, OWOP::Uuid& rhs) noexcept
{
   lhs.swap(rhs);
}
*/

}

#endif // UUID_H
