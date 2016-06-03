#include "hilo.h"
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Hilo::Hilo(int id){
	this->id = id;
	this->tarea_id = -1;
	this->terminado = false;
	this->disponible = true;
	cerr << "Soy el hilo " << id << " y estoy disponible." << endl;
	sem_init(&mutex, 0, 1);
}

Tarea* Hilo::getTarea(){
	return &(this->t);
}

bool Hilo::getTerminado(){
	return terminado;
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
	return disponible;
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
	Hilo *h;
	h= static_cast<Hilo *>(hilo);
	cerr << "EjecutarTarea. hilo id: " << h->getId() << endl;
	cerr << "Tarea que está en el hilo: " << h->getTarea()->tareaAEjecutar << endl;
	while(true){
		bool tieneTarea = false;
		while(!tieneTarea){
			//cerr << "Id del hilo: " << h->getId() << endl;
			sem_wait(&(h->mutex));
			tieneTarea = h->getTareaId() > -1 ? true : false;
			sem_post(&(h->mutex));
		}
		char* tareas_dir = getenv("PLN_DIR_TAREAS");
		strcat(tareas_dir, "/");
		strcat(tareas_dir, (h->getTarea())->tareaAEjecutar);
		int s = execl(tareas_dir, (h->getTarea())->tareaAEjecutar, NULL);
		h->setTerminado(true);
		sem_wait(&(h->mutex));
		h->setTareaId(-1);
		sem_post(&(h->mutex));
	}
}

int Hilo::getId(){
	return id;
}

void Hilo::ejecutar(){
//	cerr << "Antes de llamar el pthread_create, hilo id: " << this->getId() << endl; 
	void* p;
	p = this;
	pthread_create(&h, NULL, ejecutarTarea, p);
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
	cerr << "Soy el hilo# " << id << " Me asignaron " << t.tareaAEjecutar << endl;
	cerr << "Me asignaron la tarea: " << id_tarea;
	cerr << endl;
	this->tarea_id = id_tarea;
	this->t = t;
	sem_post(&mutex);
	this->disponible = false;
}
