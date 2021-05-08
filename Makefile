#SRC_DIR specifies where source files are stored
SRC_DIR = src

#OBJ_DIR specifies where object files will be created
OBJ_DIR = objs

#BIN_DIR specifies where bin files will be created
BIN_DIR = bin

#OUT_BIN specifies the name of our exectuable
OUT_BIN = $(BIN_DIR)/Application

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CFLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LDFLAGS = -lglfw -lGL -lGLEW

#Tell make all is not a real target
.PHONY: all
.PHONY: clean

#This is the target that compiles our executable
all : $(OUT_BIN)

$(OUT_BIN) : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(OUT_BIN)

$(OBJS) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -r $(OBJ_DIR)/*
