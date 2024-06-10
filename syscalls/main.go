package main

import (
	"fmt"
	"os"
	"log"
	"net/http"

	"github.com/gin-gonic/gin"
	"gopkg.in/yaml.v2"
)

// Config structure for the YAML data
type Config struct {
	Port int `yaml:"port"`
}

// Function to read the YAML configuration
func readConfig(path string) (Config, error) {
	var config Config
	yamlFile, err := os.ReadFile(path)
	if err != nil {
		return config, err
	}
	err = yaml.Unmarshal(yamlFile, &config)
	return config, err
}

// Start the server based on the configuration
func startServer(port int) {
	r := gin.Default()
	htmlData, err := os.ReadFile("index.html")
	if err != nil {
		log.Fatalf("Failed to load HTML file: %v", err)
	}
	htmlContent := fmt.Sprintf(string(htmlData), port)

	r.GET("/", func(c *gin.Context) {
		c.Header("Content-Type", "text/html")
		c.String(http.StatusOK, htmlContent)
	})
	log.Fatal(r.Run(fmt.Sprintf(":%d", port)))
}

func main() {
	config, err := readConfig("config.yaml")
	if err != nil {
		log.Fatalf("Error reading config: %v", err)
	}

	startServer(config.Port)
}