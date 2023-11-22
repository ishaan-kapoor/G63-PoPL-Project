#include <bits/stdc++.h>
#include <iostream>

#include <chrono>
#include <iomanip>
#include <sstream>

#include "redis_wrapper.h"

#include <thread>
#include <chrono>



// using namespace std::chrono;

int main() {
    PubSubManager publisher1;
    PubSubManager publisher2;
    PubSubManager subscriber1;
    PubSubManager subscriber2;

    // Start a subscriber in a separate thread subscribing to both channels
std::thread subscriberThread([&subscriber1]() {
        subscriber1.subscribe("channel1", [](const std::string& ch, const std::string& received_time)-> long long {
        long long messageTimestamp=stoll(received_time);
        auto currentTime = std::chrono::system_clock::now().time_since_epoch();
        long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>(currentTime).count();
        // Calculate the time difference
        auto microsec_diff = (timestamp - messageTimestamp);
        std::cout << "Time difference: " << microsec_diff << " microseconds." << std::endl;
        return microsec_diff;
        });
    });


    // std::thread subscriberThread2([&subscriber1]() {
    //     subscriber1.subscribe("channel2", [](const std::string& ch, const std::string& message) {
    //         std::cout << "Subscriber received from " << ch << ": " << message << std::endl;
    //     });
    // });

    // std::thread subscriberThread3([&subscriber2]() {
    //     subscriber2.subscribe("channel2", [](const std::string& ch, const std::string& message) {
    //         std::cout << "Subscriber received from " << ch << ": " << message <<std::endl;
    //     });
    // });

    // Allow some time for the subscriber to start before publishing messages
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Publish messages from the publishers
    auto initial_start = std::chrono::steady_clock::now();
    auto final_end=std::chrono::steady_clock::now();
       for (int i = 0; i < 100000; i++) {
            auto currentTime = std::chrono::system_clock::now().time_since_epoch();
            auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(currentTime).count();
        
        publisher1.publish("channel1", std::to_string(timestamp));
    }

    // publisher2.publish("channel2", "Greetings from Publisher2!");

    // Let the threads run asynchronously

    // Wait for the subscriber threads to finish
    // publisher1.publish("channel1", "Hello from Publisher1 again haha!");
    subscriberThread.join();
    // subscriberThread2.join();
    // subscriberThread3.join();
    return 0;
}