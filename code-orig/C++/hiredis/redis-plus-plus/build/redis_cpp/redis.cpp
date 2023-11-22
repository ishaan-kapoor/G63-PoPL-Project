#include <bits/stdc++.h>
#include <iostream>
#include "redis_wrapper.h"
// using namespace std;
// #include "redis_wrapper.h"

// class Message {
// public:
//     std::string content;

//     Message(const std::string& data = "") : content(data) {}
   
// };


// class Subscribers {
// private:
//     int subscriber_id;

// public:
//     // void update( Message& message,int Publisher_id){
//     //     ump[Publisher_id].content=message.content;
//     //     std::cout << "Received message: " << message.content <<"from the publisher whose id is "<<Publisher_id<< std::endl;
//     // }
// };

// class Publisher {
// private:
//     std::vector<Subscribers*> subscriberss;
//     int Publisher_id;

// public:
    
//     Publisher(int id){
//         this->Publisher_id=id;

//     }
    
//     void subscribe(Subscribers* subscribers){
//         subscriberss.push_back(subscribers);
//     }

//     void unsubscribe(Subscribers* subscribers){
//         // Assuming no duplicate subscriberss for simplicity
//         auto it = std::find(subscriberss.begin(), subscriberss.end(), subscribers);
//         if (it != subscriberss.end()) {
//             subscriberss.erase(it);
//         }
//     }

//     void notify(Message& message){
//         for (Subscribers* subscribers : subscriberss) {
//             //subscribers->update(message,Publisher_id);
//         }
//     }
// };



// int main(){
//     REDIS redis("tcp://127.0.0.1:6379");

//     if (redis.ping()=="PONG") {
//         std::cout << "Connected to Redis" << std::endl;
//     }
//     else{
//        std::cerr << "Failed to connect to Redis" << std::endl;
//     }

//   return 0;
// }
#include <thread>
#include <chrono>
int main() {
    PubSubManager publisher1;
    PubSubManager publisher2;
    PubSubManager subscriber1;
    PubSubManager subscriber2;

    // Start a subscriber in a separate thread subscribing to both channels
   
    // Allow some time for the subscriber to start before publishing messages
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Publish messages from the publishers
    publisher1.publish("channel1", "Hello from a different server");
    
    // Let the threads run asynchronously

   
    return 0;
}