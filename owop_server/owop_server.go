package main

// #cgo LDFLAGS: -lstdc++ libowopcpp.a
// #include "goapi.h"
import "C"
import (
	"fmt"
	"log"
	"net/http"
	"strconv"
)

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
	for i := 0; i <= 10000; i++ {
		ptr := C.CreateWorld("main_"+strconv.Itoa(i), "uwu")
		name := C.WorldGetName(ptr)
		fmt.Println(name)
		C.WorldSetPixel(ptr, 0, 0, C.uint8_t(i%32), C.uint8_t(i%64), C.uint8_t(i%128))
		fmt.Println(C.WorldGetPixel(ptr, 0, 0))
		C.FreeString(name)

	}
	Run(1234)
}
