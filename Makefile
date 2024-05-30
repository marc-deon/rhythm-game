# export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
# PKGS=raylib
# CPPFLAGS=-ggdb -pedantic -std=c++17 `pkg-config --static --cflags $(PKGS)`
CPPFLAGS=-ggdb -pedantic -std=c++17 -I./raylib/include
# LIBS=`pkg-config --static --libs $(PKGS)`
SOURCES=$(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
WARNINGS=-Wall -Wextra
IGNORES=-Wno-parentheses -Wno-narrowing -Wno-write-strings -Wno-missing-field-initializers -Wno-sign-compare -Wno-vla -Wno-format

rhythm: src/*.cpp src/**/*.cpp include/*.hpp include/**/*.hpp
	g++ $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include -L./raylib/lib -lraylib -lGLU -lrt -lm -ldl
	
rhythm-web: src/*.cpp src/**/*.cpp include/*.hpp include/**/*.hpp
	emcc $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm.html \
	$(SOURCES) -I ./include -I C:/raylib/raylib/src/external -L C:/ray/lib/raylib/src -s USE_GLFW=3 -s ASYNCIFY \
	-s TOTAL_STACK=16MB -s FORCE_FILESYSTEM=1 --preload-file graphics --preload-file music --preload-file sfx --preload-file beatmaps \
	--shell-file C:/raylib/raylib/src/minshell.html C:/raylib/raylib/src/web/libraylib.a \
	-DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free", "_malloc", "_main"]' -s EXPORTED_RUNTIME_METHODS=ccall

rhythm-web-debug: src/*.cpp src/**/*.cpp include/*.hpp include/**/*.hpp
	emcc $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm.html \
	$(SOURCES) -I ./include -I C:/raylib/raylib/src/external -L C:/ray/lib/raylib/src -s USE_GLFW=3 -s ASYNCIFY \
	-s TOTAL_STACK=16MB -s FORCE_FILESYSTEM=1 --preload-file graphics --preload-file music --preload-file sfx --preload-file beatmaps \
	--shell-file C:/raylib/raylib/src/shell.html C:/raylib/raylib/src/web/libraylib.a \
	-DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free", "_malloc", "_main"]' -s EXPORTED_RUNTIME_METHODS=ccall