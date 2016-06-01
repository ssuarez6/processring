BIN=./bin
SRC=./src

EXECS=$(BIN)/pcp $(BIN)/plp $(BIN)/planificador

all: $(EXECS)

$(BIN)/pcp: $(SRC)/pcp.cc $(SRC)/proceso.cc $(SRC)/hilo.cc
	g++ -g -o pcp $^ -lrt -pthread
	mv pcp $(BIN)

$(BIN)/plp: $(SRC)/plp.cc $(SRC)/proceso.cc
	g++ -g -o plp $^
	mv plp $(BIN)

$(BIN)/planificador: $(SRC)/*.cc
	g++ -g -o planificador $(SRC)/planificador.cc
	mv planificador $(BIN)


clean:
	rm $(BIN)/*
