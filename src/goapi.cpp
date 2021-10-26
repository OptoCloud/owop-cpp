#ifdef COMPILE_GOAPI
#include "goapi.h"
#include "chunksystem.h"

void* CreateChunkSystem() {
    return new OWOP::ChunkSystem();
}
void DestroyChunkSystem(void* chunkSystemPtr) {
    delete reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr);
}

CPixel ChunkSystemGetPixel(void *chunkSystemPtr, std::int64_t x, std::int64_t y) {
    return reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->getPixel(x, y).cpixel();
}
bool ChunkSystemSetPixel(void *chunkSystemPtr, std::int64_t x, std::int64_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    return reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->setPixel(x, y, OWOP::Pixel(r,g,b));
}
CChunk ChunkSystemGetChunk(void* chunkSystemPtr, std::int32_t x, std::int32_t y) {
    return reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->getCChunk(x, y);
}
bool ChunkSystemFillChunk(void *chunkSystemPtr, std::int32_t x, std::int32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    return reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->fillChunk(x, y, OWOP::Pixel(r,g,b));
}
void ChunkSystemProtectChunk(void *chunkSystemPtr, int32_t x, int32_t y) {
    reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->protectChunk(x,y);
}
void ChunkSystemUnprotectChunk(void *chunkSystemPtr, int32_t x, int32_t y) {
    reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->unprotectChunk(x,y);
}
bool ChunkSystemIsChunkProtected(void *chunkSystemPtr, int32_t x, int32_t y) {
    return reinterpret_cast<OWOP::ChunkSystem*>(chunkSystemPtr)->isChunkProtected(x,y);
}

#endif // COMPILE_GOAPI
