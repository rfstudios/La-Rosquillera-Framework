export CC = g++

export EJECUTABLE = Marcianitos

export OBJ_FOLDER = obj

export INCLUDES = -I../../include \
-I../../src \

export LIBS = -lSDL2 \
-lSDL2main \
-lSDL2_image \
-lSDL2_ttf \
-lSDL2_mixer

export CFLAGS = -std=c++11 -Wall -O2 $(INCLUDES)

export CFILES = execontrol.cpp \
main.cpp \
mainprocess.cpp \
enemigo.cpp \
prota.cpp \
laser.cpp \
../../src/rf_3d.cpp \
../../src/rf_3d_object.cpp \
../../src/rf_asset_list.cpp \
../../src/rf_background.cpp \
../../src/rf_engine.cpp \
../../src/rf_parallax.cpp \
../../src/rf_parallax_layer.cpp \
../../src/rf_process.cpp \
../../src/rf_soundmanager.cpp \
../../src/rf_time.cpp \
../../src/rf_window.cpp

export OBJECTS = $(CFILES:.cpp=.o)

$(EJECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

