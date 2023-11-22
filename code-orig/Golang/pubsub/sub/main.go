package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"time"

	"github.com/go-redis/redis/v8"
)

func subscribeMessages(ctx context.Context, client *redis.Client, channelName string) {
	sub := client.Subscribe(ctx, channelName)
	defer sub.Close()

	var publishSubscribeTimeTotal time.Duration
	messageCount := 0

	for {
		msg, err := sub.ReceiveMessage(ctx)
		if err != nil {
			log.Fatal(err)
		}

		var messageData map[string]interface{}
		json.Unmarshal([]byte(msg.Payload), &messageData)

		messageTimestamp := int64(messageData["timestamp"].(float64))
		currentTime := time.Now().UnixNano()
		publishSubscribeTimeTotal += time.Duration(currentTime - messageTimestamp)

		messageCount++
		fmt.Printf("%v\n", msg.Payload)

		if messageCount >= 10000 {
			break
		}
	}

	if messageCount > 0 {
		avgTime := publishSubscribeTimeTotal / time.Duration(messageCount)
		log.Printf("Average publish-subscribe time per message: %v", avgTime)
	}
}

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0,
	})

	ctx := context.Background()

	// Start subscribing to messages in a separate Go routine
	go subscribeMessages(ctx, client, "channelName")

	// Wait for the user to terminate the program
	select {}
}
