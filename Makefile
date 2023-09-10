.SECONDARY:

# the directories of the program
TOP := $(shell pwd)/
BUILD := $(TOP)build/
INCLUDE := $(TOP)include/
SRC := $(TOP)src/
BIN := $(TOP)bin/
OBJ := $(BUILD)obj/
TAR_OBJ := $(BUILD)tar_obj/

# add the includes
add_includes = -I$(INCLUDE)
#add_includes += -I/usr/local/eigen-3.4.0/include/eigen3/

# find the CXX libraries
CXXLIBS += $(shell root-config --libs)
CXXLIBS += -lMinuit2

# decide the compile
CXX = g++

# add the cflags
CXXFLAGS = -O -Wall -fPIC $(add_includes)
CXXFLAGS += $(shell root-config --cflags)

# the files of the program
headers = $(wildcard $(INCLUDE)*.h)
sources = $(wildcard $(SRC)*.C)
objects = $(patsubst $(SRC)%.C, $(OBJ)%.o, $(sources))
tar_src = $(wildcard $(TOP)*.C)
targets = $(patsubst $(TOP)%.C, $(BIN)%, $(tar_src))

all: $(targets)

####################### Make Executables #########################

$(BIN)%: $(TAR_OBJ)%.o $(objects)
	$(CXX) $^ $(CXXLIBS) -o $(BIN)$(notdir $@)

######################## Make Objects ############################

-include $(TAR_OBJ)*.d
$(TAR_OBJ)%.o: $(TOP)%.C
	$(CXX) $(CXXFLAGS) -c -MMD $(TOP)$(notdir $<) -o $(TAR_OBJ)$(notdir $@)

-include $(OBJ)*.d
$(OBJ)%.o: $(SRC)%.C
	$(CXX) $(CXXFLAGS) -c -MMD $(SRC)$(notdir $<) -o $(OBJ)$(notdir $@)

######################### Make Clean #############################

.PHYONY: clean
clean:
	rm -rf $(OBJ)*.o
	rm -rf $(TAR_OBJ)*.o
	rm -rf $(BIN)*


.PHYONY: gen_json
gen_json:
	rm -rf build/compile_commands.json
	echo "[" >> build/compile_commands.json
	echo "  {" >> build/compile_commands.json
	echo "    \"directory\": \"$(BUILD)\"," >> ./build/compile_commands.json
	echo "    \"command\": \"$(CXX) $(CXXFLAGS)\"," >> ./build/compile_commands.json
	echo "    \"file\": \"\"" >> ./build/compile_commands.json
	echo "  }" >> build/compile_commands.json
	echo "]" >> build/compile_commands.json
