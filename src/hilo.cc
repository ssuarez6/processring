#include "hilo.h"

Hilo::Hilo(int id){
	this->id = id;
	this->tarea_id = -1;
}

void Hilo::suicidar(){
	pthread_cancel(this->h);
}

void Hilo::reset(){
	this->terminado = false;
	this->disponible = true;
	this->t = NULL;
}

void Hilo::ejecutar(char* rutaATarea){
	this->rutaATarea = rutaATarea;
	pthread_create(&(this->h), NULL, ejecutarTarea, NULL);
}

void* Hilo::ejecutarTarea(){
	while(true){
		bool tieneTarea = false;
		while(!tieneTarea){
			wait(&sem);
			tieneTarea = this->tarea_id > -1 ? true : false;
			signal(&sem);
		}
		exec(tarea);
		terminado = true;
		wait(&sem);
		this->tarea_id = -1;
		signal(&sem);
	}
}

Estadistica Hilo::genEstadistica(int procesoId){
	Estadistica e = {
		t.tareaAEjecutar,
		procesoId,
		id
	};
	reset();
	return e;
}

void Hilo::asignarTarea(Tarea t, int id_tarea){
	this->tarea_id = id_tarea;
	wait(&sem);
	this->tarea_id = id_tarea;
	signal(&sem);
	this->disponible = false;
}