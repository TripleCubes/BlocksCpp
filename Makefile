OBJS = shaders $\
		vectormath $\
		chunkLoader $\
		player $\
		physics $\
		time $\
		globals $\
		ui $\
		raycast $\
		textures $\
		frameBuffers $\
		mainScene $\
		bloom 
		
INCLUDES = -I"./Libs/glfw-3.3.8.bin.WIN64/include" $\
		-I"./Libs/glad/include" $\
		-I"./Libs/glm" $\
		-I"./Libs/FastNoiseLite" $\
		-I"./Libs/stb_image"

LIBS = -L"./Libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64" $\

FLAGS = -lglfw3 -lopengl32 -lgdi32

OBJPATHS = $(foreach obj,$(OBJS),./Build/$(obj).o)

define NEWLINE


endef

rebuild:
	$(foreach obj,$(OBJS),g++ -c ./Codes/$(obj).cpp -o ./Build/$(obj).o $(INCLUDES) $(LIBS) $(FLAGS)$(NEWLINE))
	g++ -c ./Codes/main.cpp -o ./Build/main.o $(INCLUDES) $(LIBS) $(FLAGS)
	gcc -c ./Libs/glad/src/glad.c -o ./Build/glad.o $(INCLUDES) $(LIBS) $(FLAGS) 
	g++ -c ./Codes/stb_image.cpp -o ./Build/stb_image.o -I"./Libs/stb_image"
	g++ -o ./Build/blocks.exe $(OBJPATHS) ./Build/stb_image.o ./Build/glad.o ./Build/main.o $(INCLUDES) $(LIBS) $(FLAGS) -static-libgcc -static-libstdc++

buildRelease:
	g++ -o ./Release/blocks.exe $(OBJPATHS) ./Build/stb_image.o ./Build/glad.o ./Build/main.o $(INCLUDES) $(LIBS) $(FLAGS) -mwindows -static-libgcc -static-libstdc++

./Build/blocks.exe: $(OBJPATHS) ./Build/main.o ./Build/glad.o ./Build/stb_image.o
	g++ -o ./Build/blocks.exe $(OBJPATHS) ./Build/stb_image.o ./Build/glad.o ./Build/main.o $(INCLUDES) $(LIBS) $(FLAGS) -static-libgcc -static-libstdc++

./Build/main.o: ./Codes/main.cpp
	g++ -c ./Codes/main.cpp -o $@ $(INCLUDES) $(LIBS) $(FLAGS)

./Build/glad.o:
	gcc -c ./Libs/glad/src/glad.c -o $@ $(INCLUDES) $(LIBS) $(FLAGS) 

./Build/stb_image.o: ./Codes/stb_image.cpp
	g++ -c ./Codes/stb_image.cpp -o $@ -I"./Libs/stb_image"

$(OBJPATHS): ./Build/%.o: ./Codes/%.cpp ./Codes/%.h
	g++ -c $< -o $@ $(INCLUDES) $(LIBS) $(FLAGS)