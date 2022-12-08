CC := g++
LIB := lib
SRC := src
BIN := gf
RM := rm

compile:
	$(CC) $(SRC)/*.cpp -I$(LIB) -o $(BIN) -g3


clean:
	-$(RM) $(BIN)