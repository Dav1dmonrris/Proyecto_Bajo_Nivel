#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Movimiento {
private:
    // Atributos de física
    Vector2f posicion;
    Vector2f velocidad;
    Vector2f tamaño;
    
    // Constantes de física
    float velocidadMovimiento;
    float fuerzaSalto;
    float gravedad;
    float friccion;
    
    // Estados
    bool enSuelo;
    bool enPlataforma;
    Vector2f posicionAnterior;

public:
    // Constructor
    Movimiento(float posX, float posY, float ancho, float alto);
    
    // Métodos de entrada
    void manejarEntrada();
    void manejarSalto();
    
    // Métodos de física
    void actualizar(float deltaTime);
    void aplicarGravedad(float deltaTime);
    void aplicarFriccion();
    
    // Métodos de colisión
    bool verificarColisionConSuelo(float nivelSuelo);
    bool verificarColisionConPlataforma(const Vector2f& posPlataforma, const Vector2f& tamPlataforma);
    void resolverColisionSuelo(float nivelSuelo);
    void resolverColisionPlataforma(const Vector2f& posPlataforma, const Vector2f& tamPlataforma);
    
    // Getters
    Vector2f obtenerPosicion() const { return posicion; }
    Vector2f obtenerVelocidad() const { return velocidad; }
    Vector2f obtenerTamaño() const { return tamaño; }
    bool estaEnSuelo() const { return enSuelo; }
    bool estaEnPlataforma() const { return enPlataforma; }
    
    // Setters
    void establecerPosicion(const Vector2f& nuevaPosicion) { posicion = nuevaPosicion; }
    void establecerVelocidadX(float velX) { velocidad.x = velX; }
    void establecerVelocidadY(float velY) { velocidad.y = velY; }
    void establecerEnSuelo(bool estado) { enSuelo = estado; }
    void establecerEnPlataforma(bool estado) { enPlataforma = estado; }
};

#endif // MOVIMIENTO_HPP