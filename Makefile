# 編譯器
CC = gcc

# 編譯選項
CFLAGS = -Wall -g

# 目標文件
TARGET = cbb113111

# 所有的源文件
SRCS = main.c function.c

# 定義物件文件存放的資料夾
OBJ_DIR = obj

# 對應的目標文件
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# 最終生成的目標
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 確保物件文件的資料夾存在
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 規則: 如何從 .c 源文件編譯成 .o 目標文件
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理編譯生成的文件
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(OBJ_DIR)
