#pragma once
#include "Enemigo.hpp"

class Goomba : public Enemigo {
private:
    bool siendoPisado;
    float tiempoMuerte;
    
public:
    Goomba(const sf::Vector2f& posicionInicial);
    
    void actualizar(float deltaTime) override;
    void dibujar(sf::RenderWindow& ventana) override;
    
    void serPisado();
    bool estaSiendoPisado() const { return siendoPisado; }
    
private:
    void actualizarAnimacionMuerte(float deltaTime);
};