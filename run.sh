#!/bin/bash

g++ -std=c++14 -c src/*.cpp

g++ *.o -o LastGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

rm *.o
