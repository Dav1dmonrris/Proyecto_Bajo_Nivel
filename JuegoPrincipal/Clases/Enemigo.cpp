#include "Enemigo.hpp"
#include <iostream>

static sf::Texture g_emptyTexture;

Enemigo::Enemigo(float x, float y)
    : posicion(x, y), velocidad(50.0f, 0.0f), sprite(g_emptyTexture),
      velocidadMovimiento(50.0f), distanciaRecorrida(0.0f), 
      distanciaMaxima(100.0f), mirandoDerecha(true), vivo(true) {
    
    tamaño = sf::Vector2f(50.0f, 50.0f);
}

void Enemigo::actualizar(float deltaTime) {
    if (!vivo) return;
    
    actualizarMovimiento(deltaTime);
    sprite.setPosition(posicion);
}

void Enemigo::actualizarMovimiento(float deltaTime) {
    posicion.x += velocidad.x * deltaTime;
    distanciaRecorrida += std::abs(velocidad.x * deltaTime);
    
    if (distanciaRecorrida >= distanciaMaxima) {
        cambiarDireccion();
        distanciaRecorrida = 0.0f;
    }
    
    if (velocidad.x > 0 && !mirandoDerecha) {
        mirandoDerecha = true;
        sprite.setScale({1.0f, 1.0f});
    } else if (velocidad.x < 0 && mirandoDerecha) {
        mirandoDerecha = false;
        sprite.setScale({-1.0f, 1.0f});
    }
}

void Enemigo::cambiarDireccion() {
    velocidad.x = -velocidad.x;
}

void Enemigo::dibujar(sf::RenderWindow& ventana) {
    if (vivo) {
        ventana.draw(sprite);
        
        // Debug
        sf::CircleShape debugCirculo(25.0f);
        debugCirculo.setPosition(posicion);
        debugCirculo.setFillColor(sf::Color(0, 255, 0, 128));
        debugCirculo.setOutlineColor(sf::Color::White);
        debugCirculo.setOutlineThickness(2.0f);
        ventana.draw(debugCirculo);
    }
}

sf::FloatRect Enemigo::obtenerBounds() const {
    return sf::FloatRect(posicion, tamaño);
}

void Enemigo::configurarTextura(const sf::Texture& textura) {
    sprite.setTexture(textura);
    
    sf::FloatRect bounds = sprite.getLocalBounds();
    tamaño = bounds.size;
    
    sprite.setOrigin({tamaño.x / 2.0f, tamaño.y / 2.0f});
    sprite.setPosition(posicion);
    
    std::cout << " Textura configurada para enemigo - Tamaño: " << tamaño.x << "x" << tamaño.y << std::endl;
}

void Enemigo::matar() {
    vivo = false;
}

void Enemigo::serPisado() {
}