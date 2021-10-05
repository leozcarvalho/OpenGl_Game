#!/bin/bash
echo "Compilado"
gcc -o main TesteOpenGL.cpp -lglut -lGL -lGLU -lm
./main
echo "FIM"