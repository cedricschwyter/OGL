CFLAGS = -std=c++17 -Iext/SDL/include -Iext/tinyobjloader -Iext/stbimage -Iext/glad/include
LDFLAGS = `pkg-config --static --libs glfw3` -lGL -lassimp -lSDL2 -lSDL2_image -lpthread

OGLTest: OGL/*.cpp
	$(CXX) $(CFLAGS) -v -o "bin/Linux/x64/OGL by D3PSI" OGL/*.cpp ext/glad/src/glad.c $(LDFLAGS)

.PHONY: run clean

run: OGLTest
	./RUN.sh

clean:
	rm -f "OGL/OGL by D3PSI" "bin/Linux/x64/OGL by D3PSI"
