SRC_FILES = \
	src/test.c    \
	src/display.c \
	src/shader.c  \
	src/mesh.c    \
	src/texture.c
OBJ_PATH = bin
OBJ_FILES = $(patsubst %,$(OBJ_PATH)/%,$(notdir $(SRC_FILES:.c=.o)))

all: test

test: $(OBJ_FILES)
	gcc -g -o test $(OBJ_FILES) \
	`sdl2-config --libs` -lm -lGL -lGLEW

define make-obj
$(patsubst %.c, $(OBJ_PATH)/%.o, $(notdir $(1))): $(1)
	gcc -g -c $$< `sdl2-config --cflags` -o $$@
endef

$(foreach src,$(SRC_FILES),$(eval $(call make-obj,$(src))))

.PHONY : clean

clean :
	-rm -f $(OBJ_FILES) test
