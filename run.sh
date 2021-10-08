#!/bin/bash
echo "Compilado"
gcc -o main main.cpp -lglut -lGL -lGLU -lm
./main
echo "FIM"