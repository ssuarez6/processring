#include "proceso.h"
#include <unistd.h>
void Proceso::setMensaje(Mensaje* m){
				this->mensaje = m;
}

Mensaje* Proceso::getMensaje(){
				return this->mensaje;
}

void Proceso::imprimirMensaje(){
				write(STDOUT_FILENO, mensaje, sizeof(Mensaje));
				write(STDOUT_FILENO, &(mensaje->nTareas), sizeof(mensaje->nTareas));
				write(STDOUT_FILENO, &(mensaje->nEstadisticas), 
												sizeof(mensaje->nEstadisticas));
				//envia tareas
				for(int i=0; i<mensaje->nTareas; ++i)
								write(STDOUT_FILENO, &(mensaje->tareas[i]), sizeof(Tarea));
				//envia estadisticas
				for(int i=0; i<mensaje->nEstadisticas; ++i)
								write(STDOUT_FILENO, &(mensaje->estadisticas[i]), 
																sizeof(Estadistica));
}

Mensaje* Proceso::leerMensaje(){
				Mensaje* m;
				while(read(STDIN_FILENO, m, sizeof(Mensaje))>0){
								read(STDIN_FILENO,&(m->nTareas), sizeof(m->nTareas));
								read(STDIN_FILENO, &(m->nEstadisticas), sizeof(m->nEstadisticas));
								m->tareas[m->nTareas];
								m->estadisticas[m->nEstadisticas];
								for(int i=0; i<m->nTareas; ++i){
												m->tareas[i] = *(new Tarea);
												read(STDIN_FILENO, &(m->tareas[i]), sizeof(Tarea));
								}
								for(int i=0; i<m->nEstadisticas; ++i){
												m->estadisticas[i] = *(new Estadistica);
												read(STDIN_FILENO, &(m->estadisticas[i]),
																				sizeof(Estadistica));
								}
				}
				return m;

}
