# Define the Go compiler
GO := go

# Define the output binaries
PUB_BIN := pub_bin
SUB_BIN := sub_bin

# Default target
all: clean build run

# Build both binaries
build: $(PUB_BIN) $(SUB_BIN)

# Build the pub binary
$(PUB_BIN):
	@echo "Building pub..."
	$(GO) build -o $(PUB_BIN) ./pub

# Build the sub binary
$(SUB_BIN):
	@echo "Building sub..."
	$(GO) build -o $(SUB_BIN) ./sub

# Run both binaries
run: $(SUB_BIN) $(PUB_BIN)
	@echo "Running sub and pub..."
	./$(SUB_BIN) &
	sleep 3
	./$(PUB_BIN)

# Clean up binaries
clean:
	@echo "Cleaning up old binaries..."
	rm -f $(PUB_BIN) $(SUB_BIN)

.PHONY: all build run clean
