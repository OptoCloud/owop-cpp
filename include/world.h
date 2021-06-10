#ifndef OWOPCPP_WORLD_H
#define OWOPCPP_WORLD_H

#include "color.h"
#include "tooltype.h"

#include <string>

namespace OWOP {
class World
{
public:
    World();

    bool join(const std::string& world = "main");
    void leave();
    void destroy();

    bool move(std::int64_t x, std::int64_t y);
    OWOP::Color getPixel(std::int64_t x, std::int64_t y);
    bool setPixel(std::int64_t x, std::int64_t y, OWOP::Color color, bool sneaky);

    // bool paste( ??? );

    bool setTool(OWOP::ToolType tool);
    bool setColor(OWOP::Color color);

    void requestChunk(std::int64_t x, std::int64_t y, bool inaccurate);
    bool protectChunk(std::int64_t x, std::int64_t y, bool newState);
    bool clearChunk(std::int64_t x, std::int64_t y, OWOP::Color color);
};
}

#endif // OWOPCPP_WORLD_H
