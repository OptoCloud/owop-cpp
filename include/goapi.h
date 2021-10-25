#ifdef COMPILE_GOAPI
#ifndef GOAPI_H
#define GOAPI_H

#include "pixel.h"
#include "chunk.h"
#include "godef.h"

#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void* CreateChunkSystem();
void DestroyChunkSystem(void* ptr);

struct CPixel ChunkSystemGetPixel(void* chunkSystemPtr, int64_t x, int64_t y);
bool ChunkSystemSetPixel(void* chunkSystemPtr, int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b);
struct CChunk ChunkSystemGetChunk(void* chunkSystemPtr, int32_t x, int32_t y);
bool ChunkSystemFillChunk(void* chunkSystemPtr, int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GOAPI_H
#endif // COMPILE_GOAPI
