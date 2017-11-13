CC=		g++
FLAGS := -std=c++11
OBJS=		strtokenizer.o dataset.o utils.o model.o
MAIN=		lda
 
all:	$(OBJS) $(MAIN).cpp
	$(CC) $(FLAGS) -o $(MAIN) $(MAIN).cpp $(OBJS)
	strip $(MAIN)

strtokenizer.o:	strtokenizer.h strtokenizer.cpp
	$(CC) $(FLAGS) -c -o strtokenizer.o strtokenizer.cpp

dataset.o:	dataset.h dataset.cpp
	$(CC) $(FLAGS) -c -o dataset.o dataset.cpp

utils.o:	utils.h utils.cpp
	$(CC) $(FLAGS) -c -o utils.o utils.cpp

model.o:	model.h model.cpp
	$(CC) $(FLAGS) -c -o model.o model.cpp

test: strtokenizer.h strtokenizer.cpp test.h test.cpp
	$(CC) $(FLAGS) -o $@ $^


clean:
	rm $(OBJS) 
	rm $(MAIN)

cleant:
	rm $(OBJS)
