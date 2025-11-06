#include "Goomba.hpp"

Goomba::Goomba(const sf::Vector2f& posicionInicial)
    : Enemigo(posicionInicial, 100.0f, 200.0f), // Velocidad 100, patrulla 200px
      siendoPisado(false),
      tiempoMuerte(0.0f) {
}

void Goomba::actualizar(float deltaTime) {
    if (siendoPisado) {
        actualizarAnimacionMuerte(deltaTime);
    } else {
        Enemigo::actualizar(deltaTime);  // ✅ Llama al método base
    }
}

void Goomba::actualizarAnimacionMuerte(float deltaTime) {
    tiempoMuerte += deltaTime;
    
    // Efecto de "aplastamiento"
    float escalaY = 1.0f - (tiempoMuerte * 2.0f);
    if (escalaY < 0.1f) {
        escalaY = 0.1f;
        vivo = false; // Desaparecer después de la animación
    }
    
    sprite.setScale({sprite.getScale().x, escalaY});
    
    // Hacer que se hunda en el suelo
    posicion.y += 50.0f * deltaTime;
    sprite.setPosition(posicion);
}

void Goomba::serPisado() {
    if (!siendoPisado) {
        siendoPisado = true;
        velocidad.x = 0; // Dejar de moverse
    }
}

void Goomba::dibujar(sf::RenderWindow& ventana) {
    if (vivo) {
        ventana.draw(sprite);
    }
}