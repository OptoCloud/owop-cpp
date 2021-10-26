package c_wrapper

// #cgo CFLAGS: -DCOMPILE_GOAPI
// #cgo LDFLAGS: -lstdc++ libowopcpp.a
// #include "../../include/goapi.h"
import "C"
import (
	"runtime"
	"unsafe"
)

type Pixel struct {
	Data [3]byte
}
type Chunk C.struct_CChunk
type ChunkSystem struct {
	ptr unsafe.Pointer
}

func (p *Pixel) R() uint8 {
	return p.Data[0]
}
func (p *Pixel) G() uint8 {
	return p.Data[1]
}
func (p *Pixel) B() uint8 {
	return p.Data[2]
}

func (c *Chunk) GetPixel(x, y uint8) (Pixel, bool) {
	if x < 16 && y < 16 {
		index := 3 * ((x * 16) + y)
		return Pixel{*(*[3]byte)(unsafe.Pointer(uintptr(unsafe.Pointer(&c.data)) + uintptr(index)))}, true
	}
	return Pixel{}, false
}
func (c *Chunk) Data() [768]byte {
	return *(*[768]byte)(unsafe.Pointer(&c.data))
}
func (c *Chunk) IsProtected() bool {
	return (c.flags & 0b1) != 0
}

func NewChunkSystem() *ChunkSystem {
	cs := &ChunkSystem{}

	cs.ptr = C.CreateChunkSystem()

	runtime.SetFinalizer(cs, func(c *ChunkSystem) {
		C.DestroyChunkSystem(c.ptr)
	})

	return cs
}
func (cs *ChunkSystem) GetPixel(x, y int64) Pixel {
	cpixel := C.ChunkSystemGetPixel(cs.ptr, C.int64_t(x), C.int64_t(y))
	return Pixel{*(*[3]uint8)(unsafe.Pointer(&cpixel.data))}
}
func (cs *ChunkSystem) SetPixel(x, y int64, r, g, b uint8) bool {
	return C.ChunkSystemSetPixel(cs.ptr, C.int64_t(x), C.int64_t(y), C.uint8_t(r), C.uint8_t(g), C.uint8_t(b)) != 0
}
func (cs *ChunkSystem) GetChunk(x, y int32) Chunk {
	cchunk := C.ChunkSystemGetChunk(cs.ptr, C.int32_t(x), C.int32_t(y))
	return (Chunk)(cchunk)
}
func (cs *ChunkSystem) FillChunk(x, y int32, r, g, b uint8) bool {
	return C.ChunkSystemFillChunk(cs.ptr, C.int32_t(x), C.int32_t(y), C.uint8_t(r), C.uint8_t(g), C.uint8_t(b)) != 0
}
func (cs *ChunkSystem) ProtectChunk(x, y int32) {
	C.ChunkSystemProtectChunk(cs.ptr, C.int32_t(x), C.int32_t(y))
}
func (cs *ChunkSystem) UnprotectChunk(x, y int32) {
	C.ChunkSystemUnprotectChunk(cs.ptr, C.int32_t(x), C.int32_t(y))
}

func (cs *ChunkSystem) IsChunkProtected(x, y int32) bool {
	return C.ChunkSystemIsChunkProtected(cs.ptr, C.int32_t(x), C.int32_t(y)) != 0
}
