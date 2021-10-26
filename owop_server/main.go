package main

import (
	"fmt"
	"log"
	"math/rand"
	"net/http"
	"owop_server/world"
	"sync"
)

type Chunk struct {
	data  [768]uint8
	flags uint8
}

var server *http.Server

func Run(port uint16) error {
	server = &http.Server{
		Addr: fmt.Sprintf("localhost:%v", port),
	}
	log.Printf("Server running on port %v...\n", port)
	return server.ListenAndServe()
}
func Close() error {
	return server.Close()
}

func main() {
	wrld := world.NewWorld("lol", [32]uint8{})
	var wg sync.WaitGroup

	for i := 0; i <= 8; i++ {
		wg.Add(1)
		go func(wrld *world.World, wg *sync.WaitGroup) {
			defer wg.Done()
			for i := 0; i <= 100000; i++ {
				rgba := rand.Uint32()
				wrld.ChunkSystem.SetPixel(rand.Int63(), rand.Int63(), uint8((rgba>>0)&0xF), uint8((rgba>>8)&0xF), uint8((rgba>>16)&0xF))
			}
			fmt.Println("Done!")
		}(wrld, &wg)
	}
	wg.Wait()

	Run(1234)
}
