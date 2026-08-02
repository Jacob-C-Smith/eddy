# Makefile for eddy project (build artifacts in build/)

# Detect OS for platform-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    SHARED_EXT = dylib
else
    SHARED_EXT = so
endif

# SDL3
SDL_CFLAGS := $(shell pkg-config --cflags sdl3 sdl3-image sdl3-ttf)
SDL_LIBS := $(shell pkg-config --libs sdl3 sdl3-image sdl3-ttf)

# Compiler and flags
CXX = clang++
CXXFLAGS = -g -Wall -Wextra -Iinclude -std=c++23 $(SDL_CFLAGS)

# Directories
BUILD_DIR = build
EDDY_SRC_DIR = src

# Sources / objects
EDDY_SRC = $(shell find $(EDDY_SRC_DIR) -name "*.cpp")
EDDY_OBJ = $(patsubst $(EDDY_SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(EDDY_SRC))

# Library / executables (in build/)
EDDY_LIB_BASENAME = eddy
EDDY_LIB = $(BUILD_DIR)/lib$(EDDY_LIB_BASENAME).$(SHARED_EXT)
EDDY_BIN = $(BUILD_DIR)/eddy_bin

# Types
TYPE_DIR = type
TYPES = $(if $(wildcard $(TYPE_DIR)/*/),$(notdir $(patsubst %/,%,$(wildcard $(TYPE_DIR)/*/))),)
TYPE_LIBS = $(patsubst %,$(BUILD_DIR)/lib%.$(SHARED_EXT),$(TYPES))

.PHONY: all clean info run 

# Default target
all: $(EDDY_LIB) $(EDDY_BIN) 

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Object files
$(BUILD_DIR)/%.o: $(EDDY_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@printf "c++ $<\n"
	@$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

# Shared library
$(EDDY_LIB): $(EDDY_OBJ)
	@$(CXX) -shared -o $@ $^ $(SDL_LIBS) 

# Rules for type libraries
define TYPE_RULE
$(BUILD_DIR)/lib$(1).$(SHARED_EXT): $(wildcard $(TYPE_DIR)/$(1)/*.cpp) $(EDDY_LIB) | $(BUILD_DIR)
	$$(CXX) $$(CXXFLAGS) -fPIC -shared -o $$@ $$^  $$(RPATH_FLAGS) -I$(TYPE_DIR)/$(1)
endef

$(foreach type,$(TYPES),$(eval $(call TYPE_RULE,$(type))))

# Executables
$(EDDY_BIN): main.cpp $(EDDY_LIB)
	@printf "c++ $<\n"
	@$(CXX) $(CXXFLAGS) -o $@ $< $(EDDY_LIB) $(TYPE_LIBS) $(SDL_LIBS) $(RPATH_FLAGS)

# Info
info:
	@echo "eddy sources   : $(EDDY_SRC)"
	@echo "eddy objects   : $(EDDY_OBJ)"
	@echo "eddy library   : $(EDDY_LIB)"
	@echo "eddy exec      : $(EDDY_BIN)"
	@echo "type libs      : $(TYPE_LIBS)"

# Clean
clean:
	rm -rf $(BUILD_DIR)

run: all
	@./$(EDDY_BIN)