#include "goapi.h"
#include "worldmanager.h"

#include <color.h>

OWOP::WorldManager manager;

inline Color OWOPColorToGoColor(const OWOP::Color& color) {
    Color goColor;
    goColor.r = color.getR();
    goColor.g = color.getG();
    goColor.b = color.getB();
    return goColor;
}

void FreeString(_GoString_ s) {
    FreeGoString(s);
}

void* GetWorld(_GoString_ name) {
    return manager.GetWorld(std::string_view(name.p, name.n));
}
void* CreateWorld(_GoString_ name, _GoString_ password) {
    return manager.CreateWorld(std::string_view(name.p, name.n), std::string_view(password.p, password.n));
}
void DestroyWorld(_GoString_ name) {
    return manager.DestroyWorld(std::string_view(name.p, name.n));
}

_GoString_ WorldGetName(void* worldPtr) {
    return ((OWOP::World*)worldPtr)->nameGostr();
}

Color WorldGetPixel(void *worldPtr, int64_t x, int64_t y) {
    return OWOPColorToGoColor(((OWOP::World*)worldPtr)->GetPixel(x, y));
}

uint8_t WorldSetPixel(void *worldPtr, int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b) {
    return ((OWOP::World*)worldPtr)->SetPixel(x, y, OWOP::Color(r, g, b));
}
