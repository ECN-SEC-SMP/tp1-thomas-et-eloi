all: main.out
main.out: main.o utilitaire.o
	g++ -o build/main.out build/main.o build/utilitaire.o
main.o: src/main.cpp src/utilitaire.cpp include/utilitaire.hpp
	g++ -c src/main.cpp -o build/main.o
utilitaire.o: src/utilitaire.cpp include/utilitaire.hpp
	g++ -c src/utilitaire.cpp -o build/utilitaire.o
clean:
	rm -rfv build/
# 	rm -f *.o main.out ./out/*.pgm