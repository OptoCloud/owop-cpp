package world

import (
	"owop_server/c_wrapper"
	"sync"
)

type World struct {
	name        string
	passwHash   [32]uint8
	players     sync.Map
	chunkSystem c_wrapper.ChunkSystem
}

func NewWorld(name string, passwHash [32]uint8) *World {
	world := &World{}

	world.name = name
	world.passwHash = passwHash
	world.players = sync.Map{}
	world.chunkSystem = *c_wrapper.NewChunkSystem()

	return world
}
func (w *World) GetPixel(x, y int64) c_wrapper.Pixel {
	return w.chunkSystem.GetPixel(x, y)
}
func (w *World) SetPixel(x, y int64, r, g, b uint8) bool {
	return w.chunkSystem.SetPixel(x, y, r, g, b)
}
func (w *World) GetChunk(x, y int32) c_wrapper.Chunk {
	return w.chunkSystem.GetChunk(x, y)
}
func (w *World) FillChunk(x, y int32, r, g, b uint8) bool {
	return w.chunkSystem.FillChunk(x, y, r, g, b)
}
