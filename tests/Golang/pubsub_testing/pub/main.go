package main

import (
	"context"
	"encoding/json"
	"log"
	"strconv"
	"time"
	"github.com/go-redis/redis/v8"
)

func main() {
	client := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		Password: "",
		DB: 0,
	})

	ctx := context.Background()
	messageCount := 1000000 // Number of messages to publish
	var errorCount int

	for i := 0; i < messageCount; i++ {
		message := map[string]interface{}{
			"data": strconv.Itoa(i),
			"timestamp": time.Now().UnixNano(), // Current time in nanoseconds
		}
		messageJSON, _ := json.Marshal(message)

		err := client.Publish(ctx, "coords", string(messageJSON)).Err()
		if err != nil {
			log.Printf("Error publishing message: %v", err)
			errorCount++
		}
	}

	log.Printf("Total errors: %d", errorCount)
}
