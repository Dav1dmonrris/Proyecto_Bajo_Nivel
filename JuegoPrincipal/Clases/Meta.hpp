#pragma once
#include <SFML/Graphics.hpp>

class Meta {
private:
    sf::Vector2f posicion;
    bool alcanzada;
    
public:
    Meta(float x, float y);
    void dibujar(sf::RenderWindow& ventana, bool activa = false);
    bool verificarColision(const sf::Vector2f& posJugador, const sf::Vector2f& tamJugador);
    bool fueAlcanzada() const;
    void reiniciar();
};