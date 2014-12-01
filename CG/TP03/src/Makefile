OBJ = main.o
INC = -I "./"

TP03: $(OBJ)
	g++ $(OBJ) -o TP03
	rm -f $(OBJ)
	
main.o:
	g++ -c main.cpp $(INC)
	
clean:
	rm -f $(OBJ) TP03
