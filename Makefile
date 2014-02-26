all:
	g++ -Wall -g pendulum.cpp -L/usr/local/lib/ -lSimTKsimbody -lSimTKmath -lSimTKcommon -o pendulum
