#include "proceso.h"

class Plp : public Proceso{
public:
	void initMensaje(int nTareas);
	int genRndmTareas();
	bool terminoTareas = false;
	void procesarMensaje();
};