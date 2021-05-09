#!/bin/bash

g++ -std=c++11 -c src/*.cpp

g++ *.o -o LastGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

rm *.o

./LastGame
