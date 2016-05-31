#include "mensaje.h"

class Proceso {
	private:
		Mensaje* mensaje;
	public:
		void setMensaje(Mensaje* m);
		Mensaje* getMensaje();
		void imprimirMensaje();
		void leerMensaje();
		virtual void procesarMensaje()=0;
		void printMessagetoErr();
};
