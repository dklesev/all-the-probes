package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	seed := time.Now().UnixNano()

	fmt.Printf("Seed: %d\n", seed)

	rand.Seed(seed)
	if rand.Intn(2) != 1 {
		panic("Oh no!!!")
	}
	fmt.Println("Nice nice")
}