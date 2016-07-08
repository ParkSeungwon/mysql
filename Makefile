CC = g++
C_OPTION = -g -std=c++11 -fmax-errors=3
SRC = $(wildcard *.cc)
SRCX = $(wildcard *.cpp)
OBJ = $(patsubst %.cc, %.o, $(SRC))
EXE = $(patsubst %.cpp, %.x, $(SRCX))
LIB = -L/usr/local/lib 
INC = -I/usr/local/include
	
all : $(OBJ) $(EXE)
%.x : %.cpp $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(C_OPTION) $(LIB) -lmysqlcppconn 

%.o : %.cc 
	$(CC) -c $(C_OPTION) $< $(INC)

clean :
	rm *.o *.x
