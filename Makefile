CXX = clang++
SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
BUILD = .build/debug
else
BUILD = .build/relese
endif

INCFLAGS += -Isrc
INCFLAGS += -Iinc
INCFLAGS += -Ilib/glfw/include
INCFLAGS += -Ilib/glm

CXXFLAGS += -std=c++17 -O2 -g -Wall -Wextra -Wpedantic -Wno-c99-extensions
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += $(INCFLAGS)

LDFLAGS += -lstdc++
LDFLAGS += lib/glfw/src/libglfw3.a

.PHONY: all init build lib
all: build

init:
	@ printf "\033[1;33mNOTE: if you don't have pacman installed please install cmake manualy\033[0m\n"
ifeq (,$(wildcard .build))
	@ printf "\033[1;32mcreating the build dir\033[0m\n"
	mkdir .build
else
	@ printf "\033[1;32mbuild dir found\033[0m\n"
endif

	mkdir .build/relese
	mkdir .build/debug

	sudo pacman -Sy > /dev/null 2>&1
	sudo pacman -S --noconfirm cmake        > /dev/null 2>&1

	git submodule init
	git submodule update

	cd lib/glfw && cmake .  > /dev/null 2>&1
	cd lib/glfw/src && make > /dev/null 2>&1

build: $(OBJ)
	$(CXX) -o $(BUILD)/decaf.out $(filter %.o,$^) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

run: build
	$(BUILD)/decaf.out
