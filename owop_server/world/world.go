package world

import (
	"owop_server/c_wrapper"
	"sync"
)

type World struct {
	name        string
	passwHash   [32]uint8
	players     sync.Map
	ChunkSystem *c_wrapper.ChunkSystem
}

func NewWorld(name string, passwHash [32]uint8) *World {
	world := &World{}

	world.name = name
	world.passwHash = passwHash
	world.players = sync.Map{}
	world.ChunkSystem = c_wrapper.NewChunkSystem()

	return world
}
