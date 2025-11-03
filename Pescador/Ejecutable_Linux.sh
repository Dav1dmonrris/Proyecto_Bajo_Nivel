#!/bin/bash

# - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Script para Archivo ejecutable en Linux
# - - - - - - - - - - - - - - - - - - - - - - - - - -

#Comando para limpiar los archivos objeto y binario viejos
rm main.o ../Juego

#Comando para convertir un archivo en objeto
g++ -c main.cpp

#Comando para convertir un archivo objeto en binario
g++ main.o -o ../Juego -lsfml-graphics -lsfml-window -lsfml-system

#Comando para ejecutar el archivo binario
../Juego

# Compilar CADA archivo .cpp por separado

#g++ -c main.cpp -o main.o

#g++ -c Game.cpp -o Game.o

#g++ -c Player.cpp -o Player.o

#g++ -c Ghost.cpp -o Ghost.o

#g++ -c Mapa.cpp -o Mapa.o

#g++ main.o Game.o Player.o Ghost.o Mapa.o -o Juego -lsfml-graphics -lsfml-window -lsfml-system


