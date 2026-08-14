#! /bin/sh

OBJECTS	= ../objs/Engine.o ../objs/bonus.o ../objs/highscore.o ../objs/launcher.o ../objs/son.o ../objs/Param.o ../objs/brick.o ../objs/intro.o ../objs/main.o ../objs/terrain.o ../objs/balle.o ../objs/figure.o ../objs/jeu.o ../objs/menu.o
TARGET	=	../2H4U
LIBS	=	$(shell sdl-config --libs) -lSDL_image -lSDL_mixer -lSDL_ttf

all: dirs $(OBJECTS)
	g++ $(LIBS) -o $(TARGET) $(OBJECTS)

dirs:
	mkdir -p ../objs

../objs/Engine.o: ../sources/Engine.cpp
	g++ -o $@ -c $<
	
../objs/bonus.o: ../sources/bonus.cpp
	g++ -o $@ -c $<
	
../objs/highscore.o: ../sources/highscore.cpp
	g++ -o $@ -c $<
	
../objs/launcher.o: ../sources/launcher.cpp
	g++ -o $@ -c $<
	
../objs/son.o: ../sources/son.cpp
	g++ -o $@ -c $<
	
../objs/Param.o: ../sources/Param.cpp
	g++ -o $@ -c $<
	
../objs/brick.o: ../sources/brick.cpp
	g++ -o $@ -c $<
	
../objs/intro.o: ../sources/intro.cpp
	g++ -o $@ -c $<
	
../objs/main.o: ../sources/main.cpp
	g++ -o $@ -c $<
	
../objs/terrain.o: ../sources/terrain.cpp
	g++ -o $@ -c $<
	
../objs/balle.o: ../sources/balle.cpp
	g++ -o $@ -c $<
	
../objs/figure.o: ../sources/figure.cpp
	g++ -o $@ -c $<
	
../objs/jeu.o: ../sources/jeu.cpp
	g++ -o $@ -c $<
	
../objs/menu.o: ../sources/menu.cpp
	g++ -o $@ -c $<
	
rebuild:
	superclean
	all
	
clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)
