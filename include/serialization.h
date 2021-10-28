#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <span>
#include <string_view>
#include <cstdint>

enum class MsgType : std::uint8_t {
    Invalid,
    SwitchWorld,
    GetChunk,
    SelectTool,
    UseTool,
    Move,
    Message,
    Event,
};

struct Uuid {
    std::uint8_t data[16];

    static constexpr std::size_t FixedSize = sizeof(Uuid::data);
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        data += FixedSize;
        size -= FixedSize;

        return true;
    }
};
struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    static constexpr std::size_t FixedSize = sizeof(Color::r) + sizeof(Color::g) + sizeof(Color::b);
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        data += FixedSize;
        size -= FixedSize;

        return true;
    }
};
template <typename T>
struct Position {
    T x;
    T y;

    static_assert (std::is_arithmetic<T>(), "Bad type for Positon struct");

    static constexpr std::size_t FixedSize = sizeof(Position<T>::x) + sizeof(Position<T>::y);
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        data += FixedSize;
        size -= FixedSize;

        return true;
    }
};
struct Cursor {
    typedef Position<double> PosType;

    Uuid userId;
    PosType pos;

    static constexpr std::size_t FixedSize = Uuid::FixedSize + Cursor::PosType::FixedSize;
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (!Uuid::Validate(data, size)) {
            return false;
        }

        return Cursor::PosType::Validate(data, size);
    }
};
struct String {
    std::string_view worldName;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (size < 2) {
            return false;
        }

        std::uint8_t strSize = *(std::uint8_t*)data;
        std::size_t totalSize = strSize + sizeof(std::uint8_t);

        if (size < totalSize) {
            return false;
        }

        data += strSize;
        size -= strSize;

        return true;
    }
};
struct MsgSwitchWorld {
    String worldName;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        return String::Validate(data, size);
    }
};
struct MsgGetChunk {
    Position<std::int32_t> pos;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        return Position<std::int32_t>::Validate(data, size);
    }
};
struct MsgSelectTool {
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        return true;
    }

};
struct MsgUseTool {
    Position<std::int64_t> pos;
    Color color;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (!Position<std::int64_t>::Validate(data, size)) {
            return false;
        }

        return Color::Validate(data, size);
    }
};
struct MsgMove {
    Position<std::int64_t> pos;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        return Color::Validate(data, size);
    }
};
struct MsgMessage {
    Uuid senderId;
    String message;

    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        if (!Uuid::Validate(data, size)) {
            return false;
        }

        return String::Validate(data, size);
    }

};
struct MsgEvent {
    static constexpr bool Validate(const std::byte*& data, std::size_t& size) noexcept {
        return true;
    }

};

constexpr std::pair<bool, MsgType> GetMsgType(std::span<const std::byte> msg) noexcept {
    if (msg.size() < sizeof(MsgType)) {
        return { false, MsgType::Invalid };
    }

    MsgType type = *(MsgType*)msg.data();
    const std::byte* data = msg.data();
    std::size_t size = msg.size();

    switch (type) {
    case MsgType::SwitchWorld:
        return { MsgSwitchWorld::Validate(data, size), MsgType::SwitchWorld };
    case MsgType::GetChunk:
        return { MsgGetChunk::Validate(data, size), MsgType::GetChunk };
    case MsgType::SelectTool:
        return { MsgSelectTool::Validate(data, size), MsgType::SelectTool };
    case MsgType::UseTool:
        return { MsgUseTool::Validate(data, size), MsgType::UseTool };
    case MsgType::Move:
        return { MsgMove::Validate(data, size), MsgType::Move };
    case MsgType::Message:
        return { MsgMessage::Validate(data, size), MsgType::Message };
    case MsgType::Event:
        return { MsgEvent::Validate(data, size), MsgType::Event };
    default:
        return { false, MsgType::Invalid };
    }
}
constexpr std::pair<bool, MsgType> GetMsgType(std::string_view msg) noexcept {
    return GetMsgType(std::span<const std::byte>((std::byte*)msg.data(), msg.size()));
}

#endif // SERIALIZATION_H
