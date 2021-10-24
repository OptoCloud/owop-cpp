#ifndef GOAPI_H
#define GOAPI_H

#ifdef __cplusplus
#include "godef.h"
#endif // __cplusplus

#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void FreeString(_GoString_ s);

void* GetWorld(_GoString_ name);
void* CreateWorld(_GoString_ name, _GoString_ password);
void DestroyWorld(_GoString_ name);
_GoString_ WorldGetName(void* worldPtr);
void WorldGetPlayers(void* worldPtr);
void WorldGetUpdates(void* worldPtr);
void WorldGetChunk(void* worldPtr, void* chunkRef);
struct Color WorldGetPixel(void* worldPtr, int64_t x, int64_t y);
uint8_t WorldFillChunk(void* worldPtr, int32_t x, int32_t y);
uint8_t WorldSetPixel(void* worldPtr, int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // GOAPI_H
