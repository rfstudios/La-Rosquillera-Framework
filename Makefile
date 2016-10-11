export CC = g++

export EJECUTABLE = La-Rosquillera-Framework

export OBJ_FOLDER = obj

export INCLUDES = -Iinclude \
-Isrc \
-Iexample

export LIBS = -lSDL2 \
-lSDL2main \
-lSDL2_image \
-lSDL2_ttf \
-lSDL2_mixer

export CFLAGS = -std=c++11 -Wall -O2 $(INCLUDES)

export CFILES = example/execontrol.cpp \
example/main.cpp \
example/mainmenu.cpp \
example/mainprocess.cpp \
example/scene2.cpp \
example/scenetest.cpp \
example/splashscreen.cpp \
src/rf_3d.cpp \
src/rf_3d_object.cpp \
src/rf_background.cpp \
src/rf_engine.cpp \
src/rf_parallax.cpp \
src/rf_parallax_layer.cpp \
src/rf_process.cpp \
src/rf_time.cpp \
src/rf_window.cpp

export OBJECTS = $(CFILES:.cpp=.o)

$(EJECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

