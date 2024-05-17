# CC:=arm-linux-gnueabihf-g++-7
CC:=g++
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
TAR=$(BIN_DIR)/client

# LDFLAGS := -lopencv_video -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -llibopenjp2 -llibpng -llibwebp -littnotify -llibjpeg-turbo -llibtiff -lzlib -lpthread -ldl 
LDFLAGS := $(shell pkg-config --libs opencv)

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TAR)


# 生成目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -std=c++11 -c $< -o $@

# 链接目标文件生成可执行文件
$(TAR):$(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread

#清除中间文件
clean:
	rm -rf $(OBJ_DIR)/*.o $(TAR)



