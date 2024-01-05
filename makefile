main: main.o Order.o User.o Goods.o SQL.o tools.o Calculator.o Order.h User.h Goods.h SQL.h tools.h Calculator.h main.h
	g++ main.o Order.o User.o Goods.o SQL.o tools.o Calculator.o Order.h User.h Goods.h SQL.h tools.h Calculator.h main.h -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
Order.o:Order.cpp
	g++ -c Order.cpp -o Order.o
User.o:User.cpp
	g++ -c User.cpp -o User.o
Goods.o:Goods.cpp
	g++ -c Goods.cpp -o Goods.o
SQL.o: SQL.cpp
	g++ -c SQL.cpp -o SQL.o
tools.o:tools.cpp
	g++ -c tools.cpp -o tools.o 
Calculator.o:Calculator.cpp
	g++ -c Calculator.cpp -o Calculator.o 

clean:
	rm *.o 
	rm main