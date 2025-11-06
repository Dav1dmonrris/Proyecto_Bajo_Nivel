#include "AdministradorEnemigos.hpp"
#include <iostream>
#include <algorithm>

// Función de colisión para SFML 3.0 - CORREGIDO
bool hayColision(const sf::FloatRect& a, const sf::FloatRect& b) {
    // ✅ CORRECTO: usar .position y .size DIRECTAMENTE
    sf::Vector2f posA = a.position;  // ← SIN getPosition()
    sf::Vector2f sizeA = a.size;     // ← SIN getSize()
    sf::Vector2f posB = b.position;
    sf::Vector2f sizeB = b.size;
    
    return posA.x < posB.x + sizeB.x &&
           posA.x + sizeA.x > posB.x &&
           posA.y < posB.y + sizeB.y &&
           posA.y + sizeA.y > posB.y;
}

AdministradorEnemigos::AdministradorEnemigos() {
    if (!cargarRecursos()) {
        std::cout << "ADVERTENCIA: No se pudieron cargar las texturas de enemigos" << std::endl;
    }
    crearEnemigosIniciales();
}

bool AdministradorEnemigos::cargarRecursos() {
    if (!texturaGoomba.loadFromFile("Recursos/goomba.png")) {
        std::cout << "ERROR: No se pudo cargar la textura de Goomba" << std::endl;
        return false;
    }
    return true;
}

void AdministradorEnemigos::crearEnemigosIniciales() {
    agregarGoomba(sf::Vector2f(300.0f, 400.0f));
    agregarGoomba(sf::Vector2f(600.0f, 400.0f));
    agregarGoomba(sf::Vector2f(900.0f, 300.0f));
}

void AdministradorEnemigos::agregarGoomba(const sf::Vector2f& posicion) {
    auto goomba = std::make_unique<Goomba>(posicion);
    goomba->configurarTextura(texturaGoomba);
    enemigos.push_back(std::move(goomba));
}

void AdministradorEnemigos::actualizar(float deltaTime) {
    for (auto& enemigo : enemigos) {
        enemigo->actualizar(deltaTime);
    }
    limpiarEnemigosMuertos();
}

void AdministradorEnemigos::dibujar(sf::RenderWindow& ventana) {
    for (auto& enemigo : enemigos) {
        enemigo->dibujar(ventana);
    }
}

std::vector<Enemigo*> AdministradorEnemigos::obtenerEnemigosEnArea(const sf::FloatRect& area) {
    std::vector<Enemigo*> enemigosEnArea;
    
    for (auto& enemigo : enemigos) {
        if (!enemigo->estaVivo()) continue;
        
        // ✅ CORRECTO: Usar nuestra función de colisión
        if (hayColision(area, enemigo->obtenerBounds())) {
            enemigosEnArea.push_back(enemigo.get());
        }
    }
    
    return enemigosEnArea;
}

void AdministradorEnemigos::verificarColisionJugador(sf::FloatRect boundsJugador, bool& jugadorMuerto, int& puntosGanados) {
    for (auto& enemigo : enemigos) {
        if (!enemigo->estaVivo()) continue;
        
        sf::FloatRect boundsEnemigo = enemigo->obtenerBounds();
        
        // ✅ CORRECTO: Usar nuestra función de colisión
        if (hayColision(boundsJugador, boundsEnemigo)) {
            // ✅ CORRECTO: Acceder a .position y .size DIRECTAMENTE
            sf::Vector2f posJugador = boundsJugador.position;  // ← SIN getPosition()
            sf::Vector2f sizeJugador = boundsJugador.size;     // ← SIN getSize()
            sf::Vector2f posEnemigo = boundsEnemigo.position;
            sf::Vector2f sizeEnemigo = boundsEnemigo.size;
            
            // Verificar si el jugador está cayendo sobre el enemigo
            bool jugadorPorEncima = (posJugador.y + sizeJugador.y) < (posEnemigo.y + 30.0f);
            
            if (jugadorPorEncima) {
                // Jugador pisó al enemigo
                Goomba* goomba = dynamic_cast<Goomba*>(enemigo.get());
                if (goomba) {
                    goomba->serPisado();
                    puntosGanados += 100;
                }
            } else {
                // Jugador tocó al enemigo por los lados
                jugadorMuerto = true;
            }
        }
    }
}

void AdministradorEnemigos::limpiarEnemigosMuertos() {
    enemigos.erase(
        std::remove_if(enemigos.begin(), enemigos.end(),
            [](const std::unique_ptr<Enemigo>& enemigo) {
                return !enemigo->estaVivo();
            }),
        enemigos.end()
    );
}