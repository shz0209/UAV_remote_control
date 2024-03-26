CC=gcc
SRC_DIR=./src
all:
	$(CC) $(SRC_DIR)/client.c -o client
	$(CC) $(SRC_DIR)/server.c -o server