#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemigo.hpp"
#include "Goomba.hpp"

class AdministradorEnemigos {
private:
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    sf::Texture texturaGoomba;
    
public:
    AdministradorEnemigos();
    
    bool cargarRecursos();
    void agregarGoomba(const sf::Vector2f& posicion);
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    
    // Colisiones
    std::vector<Enemigo*> obtenerEnemigosEnArea(const sf::FloatRect& area);
    void verificarColisionJugador(sf::FloatRect boundsJugador, bool& jugadorMuerto, int& puntosGanados);
    
    void limpiarEnemigosMuertos();
    
private:
    void crearEnemigosIniciales();
};