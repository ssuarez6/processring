#include "proceso.h"

class Plp : public Proceso{
public:
	void initMensaje(int nTareas);
	Plp();
	int genRndmTareas();
	bool terminoTareas;
	void procesarMensaje();
};
