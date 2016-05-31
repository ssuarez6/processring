#include "proceso.h"

class Plp : Proceso{
public:
	void initMensaje(int nTareas, Tarea* t);
	Tarea* generarTareas(int nTareas);
	int genRndmTareas();
	void procesarMensaje();
private:
	static bool end;
};

/**
INSTRUCCIONES PARA CONSTRUIR ESTE PROGRAMA
1. Arreglar el metodo del numero aleatorio (ver plp.cc)
2. Inicializar el arreglo de punteros a Tarea.
3. Crear tareas a medida que se itera sobre dicho arreglo
4. Inicializar arreglo de Estadisticas con el mismo numero de tareas
5. Asignar tareaAEjecutar en Estadistica (el mismo de Tarea)
6. Imprimir el mensaje a stdout con la llamada al sistema: write.
7. Crear una bandera que diga si todas las tareas fueron ejecutadas.
8. Hacer un while mientras la bandera falsa, en el while hacer cin del mensaje
9. llamar el metodo procesarMensaje, el cual debe decir si todas las tareas
acabaron
10. cuando todas las tareas acaben, imprimir en cerr el mensaje para saber la
ultima información
**/
