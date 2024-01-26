TARGET_EXEC := main
BUILD_DIR := ./build
LIB_DIR := ./lib
SRC_DIR := ./src

LIBS := $(wildcard $(LIB_DIR)/*.cpp)
LIBS_OBJS := $(LIBS:${LIB_DIR}/%.cpp=$(BUILD_DIR)/%.o)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_OBJS := $(SRCS:${SRC_DIR}/%.cpp=$(BUILD_DIR)/%.o)

CC = g++


all: $(BUILD_DIR)/$(TARGET_EXEC).exe
	@echo "finish"


$(BUILD_DIR)/%.o : $(LIB_DIR)/%.cpp
	$(CC) -c  $< -o $@


$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -c  $< -o $@


$(BUILD_DIR)/$(TARGET_EXEC).exe: clean $(LIBS_OBJS) $(SRCS_OBJS)
	$(CC) $(LIBS_OBJS) $(SRCS_OBJS) -o $@


clean:
	rm -f $(BUILD_DIR)/*.o all
	rm -f $(BUILD_DIR)/*.exe all