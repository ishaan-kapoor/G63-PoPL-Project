// // redis_wrapper.cpp
#include "redis_wrapper.h"

std::unordered_map<std::string, std::function<long long(const std::string&, const std::string&)>> PubSubManager::subscribers;

PubSubManager::PubSubManager() : redis("tcp://127.0.0.1:6379") {}

long long PubSubManager::onMessageCallback(const std::string& channel, const std::string& message,long long * val) {
    auto it = subscribers.find(channel);
    if (it != subscribers.end()) {
        it->second(channel, message);
    }
}

void PubSubManager::subscribe(const std::string& channel, const std::function<long long(const std::string&, const std::string&)>& callback) {
    auto pubsub = redis.subscriber();

    // Store the callback in the static map
    subscribers[channel] = callback;

    // Set up the on_message callback with a static member function
    pubsub.on_message (&PubSubManager::onMessageCallback);

    pubsub.subscribe(channel);
     
    while (true) {
        auto start = std::chrono::steady_clock::now();  // Record start time

        // Check for and handle messages
        pubsub.consume();

        auto end = std::chrono::steady_clock::now();  // Record end time

    }
}

void PubSubManager::publish(const std::string& channel, const std::string& message) {
    redis.publish(channel, message);
}