CXX 		:= g++
CXXFLAGS	:= -std=c++17 -Wall -DUSEGLEW
LDFLAGS		:= -L/usr/lib -lm
INCLUDES	:= -I./include -I /usr/local/include
SRC_DIR		:= ./
SRC_EXT		:= cpp
BUILD_DIR	:= ./
OBJ_DIR		:= $(BUILD_DIR)/objects
APP_DIR		:= ./
TARGET		:= final
SOURCES		:= $(wildcard $(SRC_DIR)/*.$(SRC_EXT)) $(wildcard $(SRC_DIR)/**/*.$(SRC_EXT))
OBJECTS		:= $(SOURCES:%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJECTS:.o=.d)
LIBS=-lglfw3 -lglew32 -lglu32 -lopengl32 -lm



all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LIBS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rfd $(OBJ_DIR)
	-@rm -rf $(APP_DIR)/$(TARGET)