// #ifndef REDIS_WRAPPER_H
// #define REDIS_WRAPPER_H

// #include <sw/redis++/redis++.h>
// #include <iostream>
// #include <vector>
// #include <string>

// using namespace sw::redis;

// class REDIS {
// public:
//     REDIS(const std::string& server_address);
//     std::string ping();
//     void set(const std::string& key, const std::string& value);
//     OptionalString get(const std::string& key);
//     void rpush(const std::string& key, const std::vector<std::string>& values);
//     std::vector<std::string> lrange(const std::string& key, int start, int stop);
//     void remove(const std::string& key);

// private:
//     Redis redis;
// };

// #endif  // REDIS_WRAPPER_H
// PubSubManager.h
#pragma once

#include <sw/redis++/redis++.h>
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

using namespace sw::redis;

class PubSubManager {
public:
    PubSubManager();

    void subscribe(const std::string& channel, const std::function<long long(const std::string&, const std::string&)>& callback);
    void publish(const std::string& channel, const std::string& message);

private:
    static long long onMessageCallback(const std::string& channel, const std::string& message,long long * cum_val);

    static std::unordered_map<std::string, std::function<long long(const std::string&, const std::string&)>> subscribers;
    long long latest_value;
    Redis redis;
};