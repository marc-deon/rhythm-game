# export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
# PKGS=raylib
# CPPFLAGS=-ggdb -pedantic -std=c++17 `pkg-config --static --cflags $(PKGS)`
CPPFLAGS=-ggdb -pedantic -std=c++17 -I./raylib/include
# LIBS=`pkg-config --static --libs $(PKGS)`
SOURCES=$(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
WARNINGS=-Wall -Wextra
IGNORES=-Wno-parentheses -Wno-narrowing -Wno-write-strings -Wno-missing-field-initializers -Wno-sign-compare -Wno-vla -Wno-format

rhythm: src/*.cpp src/**/*.cpp include/*.hpp include/**/*.hpp
#	g++ $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include $(LIBS)
	g++ $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include -L./raylib/lib -lraylib -lGLU -lrt -lm -ldl
	
