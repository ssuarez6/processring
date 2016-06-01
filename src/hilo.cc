#include "hilo.h"
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
Hilo::Hilo(int id){
	this->id = id;
	this->tarea_id = -1;
	sem_init(mutex, 0, 1);
}

Tarea* Hilo::getTarea(){
	return &(this->t);
}

void Hilo::setTerminado(bool t){
	this->terminado = t;
}

int Hilo::getTareaId(){
	return this->tarea_id;
}

void Hilo::setTareaId(int t){
	this->tarea_id = t;
}

sem_t* Hilo::getMutex(){
	return this->mutex;
}

void Hilo::setDisponible(){
	this->disponible = true;
}

void Hilo::suicidar(){
	pthread_cancel(this->h);
}

void Hilo::reset(){
	this->terminado = false;
	this->disponible = true;
	//this->t = NULL;
}

void* ejecutarTarea(void* hilo){
	Hilo *h = (Hilo *)hilo;
	while(true){
		bool tieneTarea = false;
		while(!tieneTarea){
			sem_wait(h->getMutex());
			tieneTarea = h->getTareaId() > -1 ? true : false;
			sem_post(h->getMutex());
		}
		char* tareas_dir = getenv("PLN_DIR_TAREAS");
		strcat(tareas_dir, "/");
		strcat(tareas_dir, (h->getTarea())->tareaAEjecutar);
		execl(tareas_dir, (h->getTarea())->tareaAEjecutar, NULL);
		h->setTerminado(true);
		sem_wait(h->getMutex());
		h->setTareaId(-1);
		sem_post(h->getMutex());
	}
}

void Hilo::ejecutar(char* rutaATarea){
	this->rutaATarea = rutaATarea;
	pthread_create(&(this->h), NULL, ejecutarTarea, this);
}


Estadistica Hilo::genEstadistica(int procesoId){
	Estadistica e;
	memcpy(e.tareaAEjecutar, t.tareaAEjecutar, sizeof(t.tareaAEjecutar));
	e.procesoId = procesoId;
	e.hiloId = id;
	reset();
	return e;
}

void Hilo::asignarTarea(Tarea t, int id_tarea){
	this->tarea_id = id_tarea;
	sem_wait(mutex);
	this->tarea_id = id_tarea;
	sem_post(mutex);
	this->disponible = false;
}
