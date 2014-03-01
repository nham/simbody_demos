all:
	g++ -Wall -std=c++11 pendulum.cpp -L/usr/local/lib/ -lSimTKsimbody -lSimTKmath -lSimTKcommon -o pendulum
