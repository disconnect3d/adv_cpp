MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0
LIB_NAME=liblist.so.$(MAJOR_VERSION)

REQUIRED_DEBUG_FLAGS=-DDEBUG -DDEBUG_FULL_DSC
ADDITIONAL_DEBUG_FLAGS=-DDEBUG_TIMER -DDEBUG_NODE -DDEBUG_ITER
FULL_DEBUG_FLAGS=$(REQUIRED_DEBUG_FLAGS) $(ADDITIONAL_DEBUG_FLAGS)

CC=g++ -std=c++11
LIB_OBJ_FLAGS=-fPIC -c -Wall
LIB_GLUE_FLAGS=-shared -Wl,-soname,$(LIB_NAME) -o $(LIB_NAME).$(MINOR_VERSION).$(PATCH_VERSION)

SRC=list.cpp
OBJ=$(SRC:.cpp=.o)

CPP_TO_OBJ=$(SRC) -o $(OBJ)
OBJ_TO_LIB=$(OBJ) -lc

CREATE_LIB=$(CC) $(LIB_GLUE_FLAGS) $(OBJ_TO_LIB)

full_debug:
	$(CC) $(LIB_OBJ_FLAGS) $(FULL_DEBUG_FLAGS) $(CPP_TO_OBJ) 
	$(CREATE_LIB)

debug:
	$(CC) $(LIB_OBJ_FLAGS) $(REQUIRED_DEBUG_FLAGS) $(CPP_TO_OBJ)
	$(CREATE_LIB)

release:
	$(CC) $(LIB_OBJ_FLAGS) $(CPP_TO_OBJ)
	$(CREATE_LIB)

help:
	@echo "### Possible options:"
	@echo "make full_debug   - creates library with full debug options"
	@echo "make release      - creates release version, which doesn't contain any debuging"
	@echo "make debug        - creates standard debug version"
	@echo "make mydebug      - creates debug with your debug flags, defined in MY_DEBUG environment variable"
	@echo "make clean        - cleans the directory from .o files"
	@echo ""
	@echo "### Possible debug flags:"
	@echo "-DDEBUG           - standard debuging (all other flags requires this to work)"
	@echo "-DDEBUG_TIMER     - introduces timer into debug"
	@echo "-DDEBUG_FULL_DSC  - launches full descriptions, not just function/method names"
	@echo "-DDEBUG_NODE      - launches debug in node class (list contains nodes)"
	@echo "-DDEBUG_ITER      - launches debug in iterator class"
	
clean:
	rm *.o
