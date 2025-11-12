#include "Meta.hpp"
#include <iostream>

Meta::Meta(float x, float y) : posicion(x, y), alcanzada(false) {
    // Constructor vacío - no necesita inicializar sprite
}

void Meta::dibujar(sf::RenderWindow& ventana) {
    if (!alcanzada) {
        // Dibujar poste de bandera
        sf::RectangleShape poste(sf::Vector2f(5, 80));
        poste.setPosition(posicion);
        poste.setFillColor(sf::Color::White);
        ventana.draw(poste);
        
        // Dibujar bandera
        sf::ConvexShape bandera(3);
        bandera.setPoint(0, sf::Vector2f(posicion.x + 5, posicion.y + 10));
        bandera.setPoint(1, sf::Vector2f(posicion.x + 35, posicion.y + 20));
        bandera.setPoint(2, sf::Vector2f(posicion.x + 5, posicion.y + 30));
        bandera.setFillColor(sf::Color::Red);
        ventana.draw(bandera);
    }
}

bool Meta::verificarColision(const sf::Vector2f& posJugador, const sf::Vector2f& tamJugador) {
    if (alcanzada) return false;
    
    // ✅ CORREGIDO para SFML 3.0 - usar Vector2f para tamaño
    sf::FloatRect boundsMeta(posicion, sf::Vector2f(40, 80));
    sf::FloatRect boundsJugador(posJugador, tamJugador);
    
    // ✅ CORREGIDO para SFML 3.0 - usar intersects
    if (boundsJugador.findIntersection(boundsMeta)) {
        alcanzada = true;
        std::cout << "🎉 ¡META ALCANZADA! 🎉" << std::endl;
        return true;
    }
    
    return false;
}

bool Meta::fueAlcanzada() const {
    return alcanzada;
}

void Meta::reiniciar() {
    alcanzada = false;
    std::cout << "🔄 Meta reiniciada" << std::endl;
}