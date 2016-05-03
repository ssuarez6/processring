#include <unist.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv){
	extern char* optarg;
	extern int optind, opterr, optopt;
	int option;
	while((option = getopt(argc, argv, "WDF?")) != -1){
					switch(option){
									case '':
					}
	}
}
