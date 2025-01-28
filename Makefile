# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Hedef dosya adı
TARGET = mv

# Kaynak dosyaları
SRC_DIR = src
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/file_utils.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/move_utils.c $(SRC_DIR)/globals.c

# Nesne dosyaları
OBJECTS = $(SOURCES:.c=.o)

# Tüm hedefler
all: $(TARGET)

# Hedef dosyayı oluştur
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Nesne dosyalarını oluştur
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme işlemi
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean