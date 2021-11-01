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
    ChatMessage,
    EventPlayerJoin,
    EventPlayerLeave,
    EventPlayerUpdate,
    EventPixelUpdate,
    EventChunkLoaded,
    EventChunkUpdateFill,
    EventChunkUpdateFlags,
};

struct Uuid {
    std::span<std::uint8_t, 16> data;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }

    static constexpr std::size_t FixedSize = 16;
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        ptr += FixedSize;
        size -= FixedSize;

        return true;
    }
};
struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }

    static constexpr std::size_t FixedSize = sizeof(Color::r) + sizeof(Color::g) + sizeof(Color::b);
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        ptr += FixedSize;
        size -= FixedSize;

        return true;
    }
};
template <typename T>
struct Position {
    T x;
    T y;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }

    static_assert (std::is_arithmetic<T>(), "Bad type for Positon struct");

    static constexpr std::size_t FixedSize = sizeof(Position<T>::x) + sizeof(Position<T>::y);
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (size < FixedSize) {
            return false;
        }

        ptr += FixedSize;
        size -= FixedSize;

        return true;
    }
};
struct Cursor {
    typedef Position<double> PosType;

    Uuid userId;
    PosType pos;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }

    static constexpr std::size_t FixedSize = Uuid::FixedSize + Cursor::PosType::FixedSize;
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (!Uuid::Validate(ptr, size)) {
            return false;
        }

        return Cursor::PosType::Validate(ptr, size);
    }
};
template <typename T = std::uint8_t>
struct String {
    std::string_view data;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }

    static_assert (std::is_integral<T>(), "Bad type for String struct");

    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (size < 4) {
            return false;
        }

        std::uint8_t len = *(T*)ptr;
        std::size_t totalSize = sizeof(T) + len;

        if (size < totalSize) {
            return false;
        }

        ptr += totalSize;
        size -= totalSize;

        return true;
    }
};
struct MsgSwitchWorld {
    String<> worldName;
    String<> nickName;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (!String<>::Validate(ptr, size)) {
            return false;
        }

        return String<>::Validate(ptr, size);
    }
};
struct MsgGetChunk {
    Position<std::int32_t> pos;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Position<std::int32_t>::Validate(ptr, size);
    }
};
struct MsgSelectTool {


    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
};
struct MsgUseTool {
    Position<std::int64_t> pos;
    Color color;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (!Position<std::int64_t>::Validate(ptr, size)) {
            return false;
        }

        return Color::Validate(ptr, size);
    }
};
struct MsgMove {
    Position<std::int64_t> pos;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Color::Validate(ptr, size);
    }
};
struct MsgChatMessage {
    Uuid senderId;
    String<> message;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (!Uuid::Validate(ptr, size)) {
            return false;
        }

        return String<>::Validate(ptr, size);
    }
};
struct MsgEventPlayerJoin {
    Uuid playerId;
    String<> nickname;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        if (!Uuid::Validate(ptr, size)) {
            return false;
        }

        return String<>::Validate(ptr, size);
    }
};
struct MsgEventPlayerLeave {
    Uuid playerId;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};
struct MsgEventPlayerUpdate {
    Uuid playerId;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};
struct MsgEventPixelUpdate {
    Position<std::int64_t> pos;
    Color col;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};
struct MsgEventChunkLoaded {
    Uuid playerId;
    std::span<std::uint8_t, 768> data;
    std::uint8_t flags;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};
struct MsgEventChunkUpdateFill {
    Position<std::int32_t> pos;
    Color col;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};
struct MsgEventChunkUpdateFlags {
    Position<std::int32_t> pos;
    std::uint8_t flags;

    constexpr bool deserialize(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return true;
    }
    static constexpr bool Validate(const std::uint8_t*& ptr, std::size_t& size) noexcept {
        return Uuid::Validate(ptr, size);
    }
};

constexpr std::pair<bool, MsgType> GetMsgType(std::span<const std::uint8_t> msg) noexcept {
    if (msg.size() < sizeof(MsgType)) {
        return { false, MsgType::Invalid };
    }

    MsgType type = *(MsgType*)msg.data();
    const std::uint8_t* ptr = msg.data() + sizeof(MsgType);
    std::size_t size = msg.size() - sizeof(MsgType);

    switch (type) {
    case MsgType::SwitchWorld:
        return { MsgSwitchWorld::Validate(ptr, size), MsgType::SwitchWorld };
    case MsgType::GetChunk:
        return { MsgGetChunk::Validate(ptr, size), MsgType::GetChunk };
    case MsgType::SelectTool:
        return { MsgSelectTool::Validate(ptr, size), MsgType::SelectTool };
    case MsgType::UseTool:
        return { MsgUseTool::Validate(ptr, size), MsgType::UseTool };
    case MsgType::Move:
        return { MsgMove::Validate(ptr, size), MsgType::Move };
    case MsgType::ChatMessage:
        return { MsgChatMessage::Validate(ptr, size), MsgType::ChatMessage };
    case MsgType::EventPlayerJoin:
        return { MsgEventPlayerJoin::Validate(ptr, size), MsgType::EventPlayerJoin };
    case MsgType::EventPlayerLeave:
        return { MsgEventPlayerLeave::Validate(ptr, size), MsgType::EventPlayerLeave };
    case MsgType::EventPlayerUpdate:
        return { MsgEventPlayerUpdate::Validate(ptr, size), MsgType::EventPlayerUpdate };
    case MsgType::EventPixelUpdate:
        return { MsgEventPixelUpdate::Validate(ptr, size), MsgType::EventPixelUpdate };
    case MsgType::EventChunkLoaded:
        return { MsgEventChunkLoaded::Validate(ptr, size), MsgType::EventChunkLoaded };
    case MsgType::EventChunkUpdateFill:
        return { MsgEventChunkUpdateFill::Validate(ptr, size), MsgType::EventChunkUpdateFill };
    case MsgType::EventChunkUpdateFlags:
        return { MsgEventChunkUpdateFlags::Validate(ptr, size), MsgType::EventChunkUpdateFlags };
    default:
        return { false, MsgType::Invalid };
    }
}
constexpr std::pair<bool, MsgType> GetMsgType(std::string_view msg) noexcept {
    return GetMsgType(std::span<const std::uint8_t>((std::uint8_t*)msg.data(), msg.size()));
}

struct MsgRoot {
    MsgType type;
    union {
        MsgSwitchWorld swithWorld;
        MsgGetChunk getChunk;
        MsgSelectTool selectTool;
        MsgUseTool useTool;
        MsgMove move;
        MsgChatMessage chatMessage;
        MsgEventPlayerJoin eventPlayerJoin;
        MsgEventPlayerLeave eventPlayerLeave;
        MsgEventPlayerUpdate eventPlayerUpdate;
        MsgEventPixelUpdate eventPixelUpdate;
        MsgEventChunkLoaded eventChunkLoaded;
        MsgEventChunkUpdateFill eventChunkUpdateFill;
        MsgEventChunkUpdateFlags eventChunkUpdateFlags;
    } messages;

    constexpr bool deserialize(std::span<const std::uint8_t> msg) noexcept {
        type = *(MsgType*)msg.data();
        const std::uint8_t* ptr = msg.data() + sizeof(MsgType);
        std::size_t size = msg.size() - sizeof(MsgType);

        switch (type) {
        case MsgType::SwitchWorld:
            return messages.swithWorld.deserialize(ptr, size);
        case MsgType::GetChunk:
            return messages.getChunk.deserialize(ptr, size);
        case MsgType::SelectTool:
            return messages.selectTool.deserialize(ptr, size);
        case MsgType::UseTool:
            return messages.useTool.deserialize(ptr, size);
        case MsgType::Move:
            return messages.move.deserialize(ptr, size);
        case MsgType::ChatMessage:
            return messages.chatMessage.deserialize(ptr, size);
        case MsgType::EventPlayerJoin:
            return messages.eventPlayerJoin.deserialize(ptr, size);
        case MsgType::EventPlayerLeave:
            return messages.eventPlayerLeave.deserialize(ptr, size);
        case MsgType::EventPlayerUpdate:
            return messages.eventPlayerUpdate.deserialize(ptr, size);
        case MsgType::EventPixelUpdate:
            return messages.eventPixelUpdate.deserialize(ptr, size);
        case MsgType::EventChunkLoaded:
            return messages.eventChunkLoaded.deserialize(ptr, size);
        case MsgType::EventChunkUpdateFill:
            return messages.eventChunkUpdateFill.deserialize(ptr, size);
        case MsgType::EventChunkUpdateFlags:
            return messages.eventChunkUpdateFlags.deserialize(ptr, size);
        default:
            return false;
        }
    }
    constexpr bool deserialize(std::string_view msg) noexcept {
        return deserialize(std::span<const std::uint8_t>((std::uint8_t*)msg.data(), msg.size()));
    }
};

#endif // SERIALIZATION_H
