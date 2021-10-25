package main

import (
	"fmt"
	"log"
	"net/http"
	"owop_server/world"
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
	for i := 0; i <= 100000; i++ {
		wrld := world.NewWorld("lol", [32]uint8{})
		wrld.SetPixel(0, 0, uint8(i%32), uint8(i%64), uint8(i%128))
		pixel := wrld.GetPixel(0, 0)
		fmt.Println(pixel.R(), pixel.Data())
		wrld.FillChunk(0, 0, uint8(i%13), uint8(i%14), uint8(i%15))
		fmt.Println(wrld.GetChunk(0, 0))
	}
	Run(1234)
}
