#include "mensaje.h"

class Proceso {
		private:
			Mensaje* mensaje;
		public:
			void setMensaje(Mensaje* m);
			Mensaje* getMensaje();
			virtual void procesarMensaje();
};
