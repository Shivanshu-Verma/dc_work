# Makefile for building parser and loop_cfg into build/

CXX        := g++
CXXFLAGS   := -std=c++17 -O2 -Wall -Wextra
BUILD_DIR  := build

.PHONY: all clean

all: $(BUILD_DIR)/parser $(BUILD_DIR)/loop_cfg

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/parser: parser.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/loop_cfg: loop_cfg.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
