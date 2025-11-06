#!/bin/bash

# - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Script para Archivo ejecutable 
# - - - - - - - - - - - - - - - - - - - - - - - - - -

rm -f main.o ObjetoRectangulo.o Movimiento.o Enemigo.o Goomba.o AdministradorEnemigos.o 

# Compilar cada archivo fuente a objeto
g++ -c main.cpp 
g++ -c ./Clases/ObjetoRectangulo.cpp 
g++ -c ./Clases/Movimiento.cpp 
g++ -c ./Clases/Enemigo.cpp -o Enemigo.o
g++ -c ./Clases/Goomba.cpp -o Goomba.o
g++ -c ./Clases/Administrador_Enemigos.cpp -o AdministradorEnemigos.o

# Enlazar TODOS los archivos objeto juntos
g++ main.o ObjetoRectangulo.o Movimiento.o Enemigo.o Goomba.o AdministradorEnemigos.o -o Juego -lsfml-graphics -lsfml-window -lsfml-system


#Comando para ejecutar el archivo binario
./Juego

# Compilar CADA archivo .cpp por separado

#g++ -c main.cpp -o main.o

#g++ -c Game.cpp -o Game.o

#g++ -c Player.cpp -o Player.o

#g++ -c Ghost.cpp -o Ghost.o

#g++ -c Mapa.cpp -o Mapa.o

#g++ main.o Game.o Player.o Ghost.o Mapa.o -o Juego -lsfml-graphics -lsfml-window -lsfml-system


