// // redis_wrapper.cpp
#include "redis_wrapper.h"

std::unordered_map<std::string, std::function<long long(const std::string&, const std::string&)>> PubSubManager::subscribers;

PubSubManager::PubSubManager() : redis("tcp://127.0.0.1:6379"),latest_value(0){}

long long PubSubManager::onMessageCallback(const std::string& channel, const std::string& message, long long* cum_val) {
    auto it = subscribers.find(channel);
    long long latest_value;
    if (it != subscribers.end()) {
        latest_value=it->second(channel, message);
        std::cout<<latest_value<<std::endl;
    }
    *cum_val += latest_value;
    return latest_value;
}

void PubSubManager::subscribe(const std::string& channel, const std::function<long long(const std::string&, const std::string&)>& callback) {
    auto pubsub = redis.subscriber();
    long long* cumulative_value = (long long*)malloc(sizeof(long long));
    // Store the callback in the static map
    subscribers[channel] = callback;
    // Set up the on_message callback with a static member function
    pubsub.on_message([this,cumulative_value](const std::string& ch, const std::string& msg) {
            // Call the modified onMessageCallback
            PubSubManager::onMessageCallback(ch, msg, cumulative_value);
        });
    pubsub.subscribe(channel);
     
    int count=0;
    int n= 50000;
    while (true) {
        auto start = std::chrono::steady_clock::now();  // Record start time
        
        // Check for and handle messages
        pubsub.consume();
        count++;
        auto end = std::chrono::steady_clock::now();  // Record end time
        // std::cout<<*cumulative_value<<std::endl;
        // Approach 1: Using microseconds
        auto durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        // std::cout << "Time taken for consumption (microseconds): " << durationMicro.count() << " us" << std::endl;
        // std::cout<<latest_value<<std::endl;
        if(count==n){
            std::cout<<"The average time is :"<<*cumulative_value/n<<std::endl;
            break;
        }
    
    }
}

void PubSubManager::publish(const std::string& channel, const std::string& message) {
    redis.publish(channel, message);
}