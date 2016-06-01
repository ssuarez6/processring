#include <pthread.h>
#include "mensaje.h"
class Hilo{
private:
	bool terminado = false;
	bool disponible = true;
	pthread_t h;
	Tarea t;
	int tarea_id, id;
	char* rutaATarea;
public:
	Hilo(int id);
	void reset();
	void suicidar();
	void asignarTarea(Tarea t, int id_tarea);
	void ejecutarTarea();
	void ejecutar(char* rutaATarea);
	Estadistica genEstadistica(int procesoID);
	int getTareaId();
}