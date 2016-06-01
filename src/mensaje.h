const int MAX_TAREAS=256;
const int MAX_TEXT_AREA=64;

struct Tarea{
	bool asignado;
	char tareaAEjecutar[MAX_TEXT_AREA];
	unsigned short procesoId;
	unsigned short hiloId;
};

struct Estadistica {
	char tareaAEjecutar[MAX_TEXT_AREA];
	unsigned short procesoId;
	unsigned short hiloId;
};

struct Mensaje{
	int nTareas;
	int nEstadisticas;
	Tarea tareas[MAX_TAREAS];
	Estadistica estadisticas[MAX_TAREAS];
};
