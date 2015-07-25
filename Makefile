HEADER_FILES = \
	src/vecs.h       \
	src/display.h    \
	src/shader.h     \
	src/mesh.h       \
	src/texture.h    \
	src/transform.h  \
	deps/linearAlg.h

SRC_FILES = \
	src/test.c       \
	src/vecs.c       \
	src/display.c    \
	src/shader.c     \
	src/mesh.c       \
	src/texture.c    \
	src/transform.c  \
	deps/linearAlg.c
OBJ_PATH = bin
OBJ_FILES = $(patsubst %,$(OBJ_PATH)/%,$(notdir $(SRC_FILES:.c=.o)))

all: test

test: $(OBJ_FILES) $(HEADER_FILES)
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
