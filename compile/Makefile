MAKEFILE      = Makefile

VPATH = ../src/

####### Compiler, tools and options
TARGET        = road-generation		
CC            = gcc
CXX           = g++
DEFINES       = -D_GNU_SOURCE=1 -D_REENTRANT
CFLAGS        = -m64 -pipe -O2 -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -std=c++0x -Wall -W -fPIE $(DEFINES)
INCPATH       = -I../src -I../src/glm -I/usr/include/SDL
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS) -lSDL

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		tile.cpp \
		l_element.cpp \
		rng_utility.cpp \
		l_system.cpp \
		road_network.cpp 
OBJECTS       = main.o \
		tile.o \
		l_element.o \
		rng_utility.o \
		l_system.o \
		road_network.o

GLM_SOURCES   = glm/glm/core/_fixes.hpp \
		glm/glm/core/setup.hpp \
		glm/glm/core/_detail.hpp \
		glm/glm/core/type.hpp \
		glm/glm/core/type_half.hpp \
		glm/glm/core/type_half.inl \
		glm/glm/core/type_float.hpp \
		glm/glm/core/type_int.hpp \
		glm/glm/core/type_gentype.hpp \
		glm/glm/core/type_size.hpp \
		glm/glm/core/type_vec1.hpp \
		glm/glm/core/type_vec.hpp \
		glm/glm/core/_swizzle.hpp \
		glm/glm/core/_swizzle_func.hpp \
		glm/glm/core/type_vec1.inl \
		glm/glm/core/type_vec2.hpp \
		glm/glm/core/type_vec2.inl \
		glm/glm/core/type_vec3.hpp \
		glm/glm/core/type_vec3.inl \
		glm/glm/core/type_vec4.hpp \
		glm/glm/core/type_vec4.inl \
		glm/glm/core/type_mat2x2.hpp \
		glm/glm/core/type_mat.hpp \
		glm/glm/core/type_mat2x2.inl \
		glm/glm/core/type_mat2x3.hpp \
		glm/glm/core/type_mat2x3.inl \
		glm/glm/core/type_mat2x4.hpp \
		glm/glm/core/type_mat2x4.inl \
		glm/glm/core/type_mat3x2.hpp \
		glm/glm/core/type_mat3x2.inl \
		glm/glm/core/type_mat3x3.hpp \
		glm/glm/core/type_mat3x3.inl \
		glm/glm/core/type_mat3x4.hpp \
		glm/glm/core/type_mat3x4.inl \
		glm/glm/core/type_mat4x2.hpp \
		glm/glm/core/type_mat4x2.inl \
		glm/glm/core/type_mat4x3.hpp \
		glm/glm/core/type_mat4x3.inl \
		glm/glm/core/type_mat4x4.hpp \
		glm/glm/core/type_mat4x4.inl \
		glm/glm/core/func_trigonometric.hpp \
		glm/glm/core/func_trigonometric.inl \
		glm/glm/core/_vectorize.hpp \
		glm/glm/core/func_exponential.hpp \
		glm/glm/core/func_exponential.inl \
		glm/glm/core/func_common.hpp \
		glm/glm/core/func_common.inl \
		glm/glm/core/func_packing.hpp \
		glm/glm/core/func_packing.inl \
		glm/glm/core/func_geometric.hpp \
		glm/glm/core/func_geometric.inl \
		glm/glm/core/func_matrix.hpp \
		glm/glm/core/func_matrix.inl \
		glm/glm/core/func_vector_relational.hpp \
		glm/glm/core/func_vector_relational.inl \
		glm/glm/core/func_integer.hpp \
		glm/glm/core/func_integer.inl \
		glm/glm/core/func_noise.hpp \
		glm/glm/core/func_noise.inl

####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	rm -f $(TARGET)
	rm -f $(OBJECTS)

####### Compile

main.o: main.cpp /usr/include/SDL/SDL.h \
		/usr/include/SDL/SDL_main.h \
		/usr/include/SDL/SDL_stdinc.h \
		/usr/include/SDL/SDL_config.h \
		/usr/include/SDL/SDL_platform.h \
		/usr/include/SDL/begin_code.h \
		/usr/include/SDL/close_code.h \
		/usr/include/SDL/SDL_audio.h \
		/usr/include/SDL/SDL_error.h \
		/usr/include/SDL/SDL_endian.h \
		/usr/include/SDL/SDL_mutex.h \
		/usr/include/SDL/SDL_thread.h \
		/usr/include/SDL/SDL_rwops.h \
		/usr/include/SDL/SDL_cdrom.h \
		/usr/include/SDL/SDL_cpuinfo.h \
		/usr/include/SDL/SDL_events.h \
		/usr/include/SDL/SDL_active.h \
		/usr/include/SDL/SDL_keyboard.h \
		/usr/include/SDL/SDL_keysym.h \
		/usr/include/SDL/SDL_mouse.h \
		/usr/include/SDL/SDL_video.h \
		/usr/include/SDL/SDL_joystick.h \
		/usr/include/SDL/SDL_quit.h \
		/usr/include/SDL/SDL_loadso.h \
		/usr/include/SDL/SDL_timer.h \
		/usr/include/SDL/SDL_version.h \
		SDLauxiliary.h \
		$(GLM_SOURCES) \
		tile.h \
		rng_utility.h \
		l_system.h \
		l_element.h \
		road_network.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o "$<"

tile.o: tile.cpp tile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tile.o "$<"

l_element.o: l_element.cpp l_element.h $(GLM_SOURCES) rng_utility.h tile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o l_element.o "$<"

rng_utility.o: rng_utility.cpp \
		$(GLM_SOURCES) \
		rng_utility.h \
		tile.h \
		lodepng/lodepng.cpp \
		lodepng/lodepng.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rng_utility.o "$<"

l_system.o: l_system.cpp l_system.h \
		l_element.h \
		$(GLM_SOURCES) \
		rng_utility.h \
		tile.h \
		road_network.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o l_system.o "$<"

road_network.o: road_network.cpp road_network.h \
		rng_utility.h \
		$(GLM_SOURCES) \
		tile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o road_network.o "$<"
