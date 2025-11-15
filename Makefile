CC			= clang
CFLAGS		= -Wall -Iincludes -I/opt/X11/include -Iminilibx_macos
FRAMEWORKS	= -framework Cocoa -framework CoreServices -framework OpenGL -framework AppKit
LDFLAGS		= $(FRAMEWORKS) -L/opt/X11/lib -Lminilibx_macos -lXext -lX11 -lmlx

SRC_DIR = src
OBJ_DIR = obj

SRC		= $(wildcard $(SRC_DIR)/*.c)
OBJ		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS	= $(OBJ:.o=.d)

TARGET	= wireframe_renderer

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $(TARGET) ..."
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	
-include $(DEPS)

clean:
	@echo "Cleaning obj..."
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Removing executable..."
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
