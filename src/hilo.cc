#include "hilo.h"
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Hilo::Hilo(int id){
	this->id = id;
	this->tarea_id = -1;
	cerr << "Inicializado el hilo# " << id << endl;
	sem_init(&mutex, 0, 1);
}

Tarea* Hilo::getTarea(){
	return &(this->t);
}

bool Hilo::getTerminado(){
	return this->terminado;
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

void Hilo::setDisponible(){
	this->disponible = true;
}

bool Hilo::getDisponible(){
	return this->disponible;
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
			sem_wait(&(h->mutex));
			tieneTarea = h->getTareaId() > -1 ? true : false;
			sem_post(&(h->mutex));
		}
		cerr << "Ya tengo tarea asignada \n";
		char* tareas_dir = getenv("PLN_DIR_TAREAS");
		strcat(tareas_dir, "/");
		strcat(tareas_dir, (h->getTarea())->tareaAEjecutar);
		execl(tareas_dir, (h->getTarea())->tareaAEjecutar, NULL);
		cerr << "Acabo de terminar la tarea\n";
		h->setTerminado(true);
		sem_wait(&(h->mutex));
		h->setTareaId(-1);
		sem_post(&(h->mutex));
	}
}

void Hilo::ejecutar(){
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
	sem_wait(&mutex);
	this->tarea_id = id_tarea;
	sem_post(&mutex);
	this->disponible = false;
}
