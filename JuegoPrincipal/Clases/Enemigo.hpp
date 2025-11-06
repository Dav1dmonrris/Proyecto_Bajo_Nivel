#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Enemigo {
private:
    sf::Sprite sprite;
    sf::Vector2f posicion;
    sf::Vector2f velocidad;
    sf::Vector2f tamaño;
    
    float velocidadMovimiento;
    float distanciaRecorrida;
    float distanciaMaxima;
    bool mirandoDerecha;
    bool vivo;

public:
    // Constructor simple
    Enemigo(float x, float y);
    
    // Métodos básicos
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    
    // Métodos NUEVOS
    void configurarTextura(const sf::Texture& textura);
    sf::FloatRect obtenerBounds() const;
    void matar();
    
    // Getters
    bool estaVivo() const { return vivo; }
    sf::Vector2f getPosicion() const { return posicion; }
    
    // Para Goomba
    void serPisado();
    
private:
    void actualizarMovimiento(float deltaTime);
    void cambiarDireccion();
};