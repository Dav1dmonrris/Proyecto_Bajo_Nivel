#include "Enemigo.hpp"
#include <iostream>

// Texture shared for default-initializing sprites when no texture is provided
static sf::Texture g_emptyTexture;

Enemigo::Enemigo(const sf::Vector2f& posicionInicial, float velocidad, float distanciaPatrulla)
    : posicion(posicionInicial),
      sprite(g_emptyTexture),
      velocidad(velocidad, 0.0f),
      velocidadMovimiento(velocidad),
      distanciaRecorrida(0.0f),
      distanciaMaxima(distanciaPatrulla),
      mirandoDerecha(true),
      vivo(true) {
    
    // Tamaño por defecto (se ajustará con la textura)
    tamaño = sf::Vector2f(50.0f, 50.0f);
}

// ✅ IMPLEMENTADO: método virtual
void Enemigo::actualizar(float deltaTime) {
    if (!vivo) return;
    
    actualizarMovimiento(deltaTime);
    sprite.setPosition(posicion);
}

// ✅ IMPLEMENTADO: método virtual que faltaba
void Enemigo::actualizarMovimiento(float deltaTime) {
    // Guardar posición anterior
    sf::Vector2f posicionAnterior = posicion;
    
    // Mover el enemigo
    posicion.x += velocidad.x * deltaTime;
    
    // Actualizar distancia recorrida
    distanciaRecorrida += std::abs(velocidad.x * deltaTime);
    
    // Cambiar dirección si alcanzó la distancia máxima
    if (distanciaRecorrida >= distanciaMaxima) {
        cambiarDireccion();
        distanciaRecorrida = 0.0f;
    }
    
    // Actualizar orientación del sprite
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

// ✅ IMPLEMENTADO: método virtual
void Enemigo::dibujar(sf::RenderWindow& ventana) {
    if (vivo) {
        ventana.draw(sprite);
    }
}

sf::FloatRect Enemigo::obtenerBounds() const {

    return sf::FloatRect(posicion, tamaño);
}

void Enemigo::configurarTextura(const sf::Texture& textura) {
    sprite.setTexture(textura);
    
    // Obtener tamaño de la textura
    sf::FloatRect bounds = sprite.getLocalBounds();
    tamaño = bounds.size;  // Acceso directo a size en SFML 3.0
    
    // Configurar el origen en el centro para mejor flip
    sprite.setOrigin({tamaño.x / 2.0f, tamaño.y / 2.0f});
}