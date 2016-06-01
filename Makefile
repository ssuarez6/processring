BIN=./bin
SRC=./src

EXECS=$(BIN)/pcp $(BIN)/plp $(BIN)/planificador

all: $(EXECS)

$(BIN)/pcp: $(SRC)/pcp.cc $(SRC)/proceso.cc $(SRC)/hilo.cc
	g++ -o pcp $^ -lpthread -lrt
	mv pcp $(BIN)

$(BIN)/plp: $(SRC)/plp.cc $(SRC)/proceso.cc
	g++ -o plp $^
	mv plp $(BIN)

$(BIN)/planificador: $(SRC)/*.cc
	g++ -o planificador $(SRC)/planificador.cc
	mv planificador $(BIN)


clean:
	rm $(BIN)/*
