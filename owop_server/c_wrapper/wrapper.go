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
	impl C.struct_CPixel
}

func (p *Pixel) R() uint8 {
	return uint8(p.impl.data[0])
}
func (p *Pixel) G() uint8 {
	return uint8(p.impl.data[1])
}
func (p *Pixel) B() uint8 {
	return uint8(p.impl.data[2])
}
func (p *Pixel) Data() [3]byte {
	return *(*[3]byte)(unsafe.Pointer(&p.impl.data))
}

type Chunk struct {
	impl C.struct_CChunk
}

func (c *Chunk) Data() [768]byte {
	return *(*[768]byte)(unsafe.Pointer(&c.impl.data))
}
func (c *Chunk) IsProtected() bool {
	return (c.impl.flags & 0b1) != 0
}

type ChunkSystem struct {
	impl unsafe.Pointer
}

func NewChunkSystem() *ChunkSystem {
	cs := &ChunkSystem{}

	cs.impl = C.CreateChunkSystem()

	runtime.SetFinalizer(cs, func(c *ChunkSystem) {
		C.DestroyChunkSystem(c.impl)
	})

	return cs
}
func (cs *ChunkSystem) GetPixel(x, y int64) Pixel {
	return Pixel{C.ChunkSystemGetPixel(cs.impl, C.int64_t(x), C.int64_t(y))}
}
func (cs *ChunkSystem) SetPixel(x, y int64, r, g, b uint8) bool {
	return C.ChunkSystemSetPixel(cs.impl, C.int64_t(x), C.int64_t(y), C.uint8_t(r), C.uint8_t(g), C.uint8_t(b)) != 0
}
func (cs *ChunkSystem) GetChunk(x, y int32) Chunk {
	return Chunk{C.ChunkSystemGetChunk(cs.impl, C.int32_t(x), C.int32_t(y))}
}
func (cs *ChunkSystem) FillChunk(x, y int32, r, g, b uint8) bool {
	return C.ChunkSystemFillChunk(cs.impl, C.int32_t(x), C.int32_t(y), C.uint8_t(r), C.uint8_t(g), C.uint8_t(b)) != 0
}
