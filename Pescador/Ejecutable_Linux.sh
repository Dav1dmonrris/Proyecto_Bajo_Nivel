#!/bin/bash

# - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Script para Archivo ejecutable en Linux
# - - - - - - - - - - - - - - - - - - - - - - - - - -

#Comando para limpiar los archivos objeto y binario viejos
rm main.o Juego

#Comando para convertir un archivo en objeto
g++ -c ./Pescador/main.cpp

#Comando para convertir un archivo objeto en binario
g++ main.o -o Juego -lsfml-graphics -lsfml-window -lsfml-system

#Comando para ejecutar el archivo binario
./Juego
