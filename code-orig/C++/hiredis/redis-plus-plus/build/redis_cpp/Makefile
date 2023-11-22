CXX := g++
CXXFLAGS := -std=c++17
LDFLAGS := -pthread
REDIS_LIB := /Users/ameyakasture/hiredis/redis-plus-plus/build/libredis++.a
HIREDIS_LIB := /usr/local/lib/libhiredis.a
TARGET := pubsub_tester
TARGET2:= pubsub
TARGET3:= pubsub2
CACHE_TARGET := cache
.PHONY: all clean

test: $(TARGET)
pub: $(TARGET2)
pub2: $(TARGET3)
cache: $(CACHE_TARGET)


$(TARGET): pubsub_tester.cpp redis_wrapper_tester.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(REDIS_LIB) $(HIREDIS_LIB) $(LDFLAGS)

$(TARGET3): redis.cpp redis_wrapper.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(REDIS_LIB) $(HIREDIS_LIB) $(LDFLAGS)

$(TARGET2): pubsub.cpp redis_wrapper.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(REDIS_LIB) $(HIREDIS_LIB) $(LDFLAGS)

$(CACHE_TARGET): cache.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(REDIS_LIB) $(HIREDIS_LIB) $(LDFLAGS)


clean:
	rm -f $(TARGET)
