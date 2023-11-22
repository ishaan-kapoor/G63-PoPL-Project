package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
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
	sub := client.Subscribe(ctx, "coords")
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

        // Corrected type assertion
        messageTimestamp := int64(messageData["timestamp"].(float64))
        currentTime := time.Now().UnixNano()
        publishSubscribeTimeTotal += time.Duration(currentTime - messageTimestamp)

		messageCount++
		fmt.Printf("%v\n", msg.Payload)

		if messageCount >= 1000000 {
			break
		}
	}

	if messageCount > 0 {
		avgTime := publishSubscribeTimeTotal / time.Duration(messageCount)
		log.Printf("Average publish-subscribe time per message: %v", avgTime)
	}
}
