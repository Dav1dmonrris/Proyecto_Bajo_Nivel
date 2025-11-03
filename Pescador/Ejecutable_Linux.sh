#!/bin/bash

# - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Script para Archivo ejecutable en Linux
# - - - - - - - - - - - - - - - - - - - - - - - - - -

#Comando para limpiar los archivos objeto y binario viejos
rm ../Juego

#Comando para convertir un archivo en objeto
g++ -c ./main.cpp

#Comando para convertir un archivo objeto en binario
g++ main.o -o ../Juego -lsfml-graphics -lsfml-window -lsfml-system

#Comando para eliminar archivo objeto y ejecutar juego
rm main.o && ../Juego
