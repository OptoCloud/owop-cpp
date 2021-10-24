#include "uuid.h"

#ifdef _WIN32
#include <WinSock2.h>
#elif __linux__
#include <arpa/inet.h>
#endif

#include <cstdint>
#include <cstring>
#include <cstring>
#include <random>
#include <unordered_map>

constexpr char slow_nibble_to_hex(std::uint8_t nibble) {
    if (nibble >= 0x0A) {
        nibble -= 0x0A;
        return 'a' + nibble;
    }

    return '0' + nibble;
}

struct HexToBinTable {
    constexpr HexToBinTable() : table{0} {
        for (int i = 0; i < 10; i++) {
            table['0' + i] = i;

            if (i < 6) {
                table['a' + i] = 0xA + i;
                table['A' + i] = 0xA + i;
            }
        }
    }

    constexpr std::uint8_t operator[](char hex) const {
        return table[(std::size_t)hex];
    }
private:
    std::uint8_t table[256];
};
struct BinToHexTable {
    constexpr BinToHexTable() : table{0} {
        for (int i = 0; i < 256; i++) {
            table[(i * 2) + 0] = slow_nibble_to_hex((i & 0xF0) >> 4);
            table[(i * 2) + 1] = slow_nibble_to_hex( i & 0x0F      );
        }
    }

    constexpr const char* operator[](std::uint8_t byte) const {
        return table + (byte * 2);
    }
private:
    char table[512];
};
constexpr HexToBinTable s_table_htb;
constexpr BinToHexTable s_table_bth;

constexpr std::uint8_t hex_to_bin(const char* twochars) {
    std::uint8_t nh = s_table_htb[twochars[0]];
    std::uint8_t nl = s_table_htb[twochars[1]];

    return nh << 4 | nl;
}
constexpr void bin_to_hex(std::uint8_t bin, char* twochars) {
    const char* hex = s_table_bth[bin];

    twochars[0] = hex[0];
    twochars[1] = hex[1];
}

constexpr bool is_hex_char(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}
constexpr bool is_uuidv4_seperator_position_str(std::size_t pos) {
    return pos == 8 || pos == 13 || pos == 18 || pos == 23;
}
constexpr bool is_uuidv4_seperator_position_bin(std::size_t pos) {
    return pos == 4 || pos == 6 || pos == 8 || pos == 10;
}
constexpr bool is_valid_uuidv4_string(const char* string, std::size_t len) {
    if (len != 36) {
        return false;
    }

    for (int i = 0; i < 36; i++) {
        if (!is_hex_char(string[i]) && !is_uuidv4_seperator_position_str(i)) {
            return false;
        }
    }

    return string[14] == '4';
}

constexpr void parse_uuidv4_string(const char* string, std::array<std::uint8_t, 16>& dataOut) {
    for (int i = 0; i < 16; i++) {

        if (is_uuidv4_seperator_position_bin(i)) {
            string++;
        }

        dataOut[i] = hex_to_bin(string);
        string += 2;
    }
}
constexpr void generate_uuidv4_string(const std::array<std::uint8_t, 16> data, char* stringOut) {
    for (int i = 0; i < 16; i++) {

        if (is_uuidv4_seperator_position_bin(i)) {
            *(stringOut++) = '-';
        }

        bin_to_hex(data[i], stringOut);
        stringOut += 2;
    }
}

std::random_device rd{};
const std::uint32_t uuidv4_version_mask = htonl(0xFFFF0FFF);
const std::uint32_t uuidv4_version_data = htonl(0x00004000);

OWOP::Uuid OWOP::Uuid::NewUuid()
{
    std::array<std::uint8_t, 16> data;
    *reinterpret_cast<std::uint32_t*>(data.data() +  0) =  rd();
    *reinterpret_cast<std::uint32_t*>(data.data() +  4) = (rd() & uuidv4_version_mask) | uuidv4_version_data;
    *reinterpret_cast<std::uint32_t*>(data.data() +  8) =  rd();
    *reinterpret_cast<std::uint32_t*>(data.data() + 12) =  rd();

    return OWOP::Uuid(data);
}

bool OWOP::Uuid::TryParse(const char* string, OWOP::Uuid& guidOut)
{
    std::size_t len = strlen(string);

    if (!is_valid_uuidv4_string(string, len)) {
        return false;
    }

    parse_uuidv4_string(string, guidOut.m_data);

    return true;
}

const OWOP::Uuid OWOP::Uuid::Empty()
{
    return OWOP::Uuid();
}

OWOP::Uuid::Uuid() noexcept
    : m_data{0}
{
}

OWOP::Uuid::Uuid(const OWOP::Uuid& other) noexcept
    : m_data(other.m_data)
{
}

OWOP::Uuid::Uuid(std::array<std::uint8_t, 16> data) noexcept
    : m_data(data)
{
}

OWOP::Uuid::Uuid(std::span<const std::uint8_t, 16> data) noexcept
{
    std::memcpy(m_data.data(), data.data(), 16);
}

std::array<std::uint8_t, 16> empty{0};
bool OWOP::Uuid::isEmpty() const noexcept
{
    return m_data == empty;
}

std::string OWOP::Uuid::toString() const
{
    std::string str;
    str.resize(36);
    generate_uuidv4_string(m_data, str.data());

    return str;
}

std::span<const std::uint8_t, 16> OWOP::Uuid::toBytes() const
{
    return m_data;
}

bool OWOP::Uuid::operator==(const OWOP::Uuid& rhs) const noexcept
{
    return m_data == rhs.m_data;
}
bool OWOP::Uuid::operator!=(const OWOP::Uuid& rhs) const noexcept
{
    return !(*this == rhs);
}
bool OWOP::Uuid::operator<(const OWOP::Uuid& rhs) const noexcept
{
    return m_data < rhs.m_data;
}
bool OWOP::Uuid::operator<=(const OWOP::Uuid& rhs) const noexcept
{
    return !(rhs < *this);
}
bool OWOP::Uuid::operator>(const OWOP::Uuid& rhs) const noexcept
{
    return rhs < *this;
}
bool OWOP::Uuid::operator>=(const OWOP::Uuid& rhs) const noexcept
{
    return !(*this < rhs);
}

void OWOP::Uuid::swap(OWOP::Uuid& other) noexcept
{
    m_data.swap(other.m_data);
}

OWOP::Uuid OWOP::Uuid::operator=(const OWOP::Uuid& other) noexcept
{
    std::memcpy(m_data.data(), other.m_data.data(), 16);
    return *this;
}
