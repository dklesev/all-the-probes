package main

import (
	"net/http"
	"time"
)

func main() {
	for {
		_, err := http.Get("https://official-joke-api.appspot.com/random_joke")
		if err != nil {
			println("Error making request:", err.Error())
		}

		time.Sleep(10 * time.Second)
	}
}
