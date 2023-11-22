package main

import (
	"context"
	"encoding/json"
	"log"
	"strconv"
	"time"

	"github.com/go-redis/redis/v8"
)

func publishMessages(ctx context.Context, client *redis.Client, channelName string, messageCount int) {
	var errorCount int
	for i := 0; i < messageCount; i++ {
		message := map[string]interface{}{
			"data":      strconv.Itoa(i),
			"timestamp": time.Now().UnixNano(),
		}
		messageJSON, _ := json.Marshal(message)

		err := client.Publish(ctx, channelName, string(messageJSON)).Err()
		if err != nil {
			log.Printf("Error publishing message: %v", err)
			errorCount++
		}
	}
	log.Printf("Total errors: %d", errorCount)
}

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0,
	})

	ctx := context.Background()
	messageCount := 1000000 // Number of messages to publish

	// Start publishing messages in a separate Go routine
	go publishMessages(ctx, client, "channelName", messageCount)

	// Wait for the user to terminate the program
	select {}
}
