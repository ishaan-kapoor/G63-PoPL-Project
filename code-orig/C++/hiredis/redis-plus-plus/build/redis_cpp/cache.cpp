#include <sw/redis++/redis++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace sw::redis;

class Cache {
public:
    Cache(const std::string& server_address) : redis(server_address) {
    }
    //checker to see if key is formed or not
    std::string ping() {
        return redis.ping();
    }
    //setting a key
    void set(const std::string& key, const std::string& value) {
        redis.set(key, value);
    }
    //getting value of a key 
    OptionalString get(const std::string& key) {
        auto value = redis.get("key");
        if(value){
            this->remove("key");
        }
        return value;
    }

    //pushing a key in list in redis
    void rpush(const std::string& key, const std::vector<std::string>& values) {
        redis.rpush(key, values.begin(), values.end());
    }

    //giving out the list  obtained from redis
    std::vector<std::string> lrange(const std::string& key, int start, int stop) {
        std::vector<std::string> result;
        redis.lrange(key, start, stop, std::back_inserter(result));
        return result;
    }

    //removing the key
    void remove(const std::string& key) {
        redis.del(key);
    }

private:
    Redis redis;
};



int main() {
    Cache redis("tcp://127.0.0.1:6379");

    if (redis.ping()=="PONG") {
        std::cout << "Connected to Redis" << std::endl;

        // SET operation
        redis.set("key", "value");
        redis.set("alpha","beta");


        // GET operation
        auto val = redis.get("key");
        if (val) {
            std::cout << "GET: " << *val << std::endl;
        }


        // RPUSH operation
        std::vector<std::string> vec = {"a", "b"};
        redis.rpush("newlist", vec);

        // LRANGE operation
        vec = redis.lrange("newlist", 0, -1);
        for (const auto& it : vec) {
            std::cout << it << "\t";
        }
        std::cout << std::endl;

        // REMOVE operation
        // redis.remove("key");
        auto value = redis.get("key");
        if (value) {
            std::cout << "GET: " << *val << std::endl;
        }
        else{
            std::cout<<"key not found"<< std::endl;
        }
    } else {
        std::cerr << "Failed to connect to Redis" << std::endl;
    }

    return 0;
}
