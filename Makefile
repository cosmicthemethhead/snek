CC = clang
CXX = clang++

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
BUILD = .build/debug
else
BUILD = .build/relese
endif

# gen = generic

INCGEN   += -Ilib/glad/include
INCFLAGS += -Ilib/glfw/include
INCFLAGS += -Isrc

GENFLAGS += -g
GENFLAGS += -O2
GENFLAGS += -Wall -Wextra -Wpedantic
GENFLAGS += -Wno-c99-extensions -Wno-unused-parameter
GENFLAGS += $(INCGEN)
CXXFLAGS += -std=c++17
CXXFLAGS += $(GENFLAGS)
CXXFLAGS += $(INCFLAGS)

LDFLAGS += -lstdc++
LDFLAGS += lib/glfw/src/libglfw3.a
LDFLAGS += lib/glad/src/glad.o

.PHONY: all init build lib build_libs
all: build

init:
	@ printf "\033[1;33mif you don't have pacman installed please install cmake manualy and add the --no-pacman fag\033[0m\n"
ifeq (,$(wildcard .build))
	@ printf "\033[1;32mcreating the build dir\033[0m\n"
	mkdir .build
else
	@ printf "\033[1;32mbuild dir found\033[0m\n"
endif

	mkdir .build/relese
	mkdir .build/debug

	sudo pacman -Sy > /dev/null 2>&1
	sudo pacman -S --noconfirm cmake > /dev/null 2>&1

	git submodule init
	git submodule update

	build_libs

build_libs:
# glfw
	cmake lib/glfw  > /dev/null 2>&1
	cd lib/glfw/src && make > /dev/null 2>&1

# glad
	$(CC) -o lib/glad/src/glad.o -c lib/glad/src/glad.c $(GENFLAGS)

build: $(OBJ)
	$(CXX) -o $(BUILD)/decaf.out $(filter %.o,$^) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

run: build
	$(BUILD)/decaf.out
