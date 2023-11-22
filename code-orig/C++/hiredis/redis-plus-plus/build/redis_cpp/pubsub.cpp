#include <bits/stdc++.h>
#include <iostream>
#include "redis_wrapper.h"

#include <thread>
#include <chrono>
int main() {
    PubSubManager publisher1;
    PubSubManager publisher2;
    PubSubManager subscriber1;
    PubSubManager subscriber2;

    // Start a subscriber in a separate thread subscribing to both channels
    std::thread subscriberThread([&subscriber1]() {
        subscriber1.subscribe("channel1", [](const std::string& ch, const std::string& message) {
            std::cout << "Subscriber received from " << ch << ": " << message << std::endl;
        });   
    });

    std::thread subscriberThread2([&subscriber1]() {
        subscriber1.subscribe("channel2", [](const std::string& ch, const std::string& message) {
            std::cout << "Subscriber received from " << ch << ": " << message << std::endl;
        });
    });

    std::thread subscriberThread3([&subscriber2]() {
        subscriber2.subscribe("channel2", [](const std::string& ch, const std::string& message) {
            std::cout << "Subscriber received from " << ch << ": " << message <<std::endl;
        });
    });

    // Allow some time for the subscriber to start before publishing messages
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Publish messages from the publishers
    auto initial_start = std::chrono::steady_clock::now();
    auto final_end=std::chrono::steady_clock::now();
    for(int i=0;i<1002000;i++){
        std::string s= "this is the data point : "+ std::to_string(i);
        publisher1.publish("channel1",s );
    }
    publisher2.publish("channel2", "Greetings from Publisher2!");

    // Let the threads run asynchronously

    // Wait for the subscriber threads to finish
    publisher1.publish("channel1", "Hello from Publisher1 again haha!");
    subscriberThread.join();
    subscriberThread2.join();
    subscriberThread3.join();
    return 0;
}