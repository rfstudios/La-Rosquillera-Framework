![](http://miguelalbors.noip.me/LaRosquillera_banner.png)

Introduction
------------

[La Rosquillera Framework] es un framework para hacer videojuegos con SDL2 que tiene como objetivo que el usuario pueda hacer juegos como rosquillas (o sea muchos, muy rápido y sin romperse la cabeza).

#¿Qué ventajas ofrece respecto a usar SDL2 directamente?
* Muchas.
* Nah, en serio, ofrece toda una serie de clases ya diseñadas para facilitar la programación.
* La clase RF_Engine mantiene un taskManager, el cual acumula procesos que compartan como clase base la clase RF_Process, y en cada fotograma se encarga de llamar a las distintas funciones de actualización y pintado.

Notas
-----

La rama "3DAmpliation", hasta que adquiera los conocimientos necesarios para desarrollarla,
queda suspendida.

Demos list:
	- Demo or die (http://www.pouet.net/prod.php?which=67837):
		· Branch: DemoOrDie
		· For compile you need the following dependencies:
			- SDL2
			- SDL2_image
			- SDL2_mixer
			- SDL2_ttf
		· Compile with that preferences:
			- Have g++ follow the C++11 ISO C++ language standard [-std=c++11]
	
