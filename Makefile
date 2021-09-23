CFLAGS = -g -Wall 
CC = g++

objects = analytical.cpp customer.cpp serviceCenter.cpp main.cpp

main: $(objects)
	$(CC) -o main $(objects)

analytical.o: analytical.cpp analytical.hpp
customer.o: customer.cpp customer.hpp
serviceCenter.o: serviceCenter.cpp serviceCenter.hpp customer.hpp
main.o: serviceCenter.cpp customer.cpp analytical.cpp main.cpp
.PHONY : clean
clean: 
	rm main $(objects)
