#include "Game.h"
#include "Player.h"
#include "Ghost.h" 
#include "Mapa.h"
#include <iostream>

// Constructor
Game::Game() 
    : m_window{sf::VideoMode({800, 600}), "Pac-Man SFML 3.0"}
    , m_player{nullptr}
    , m_ghosts{}
    , m_map{nullptr}
    , m_isRunning{false}
    , m_score{0}
    , m_lives{3} {
    
    std::cout << "🎮 Game constructor llamado!\n";
}

// Destructor - IMPORTANTE por los punteros
Game::~Game() {
    cleanup();
    std::cout << "🧹 Game destructor llamado!\n";
}

// Inicializar recursos
void Game::initialize() {
    std::cout << "🚀 Inicializando juego...\n";
    
    // Crear jugador (gestión manual de memoria)
    m_player = new Player();
    
    // Crear algunos fantasmas
    m_ghosts.push_back(new Ghost());
    m_ghosts.push_back(new Ghost());
    
    // Crear mapa
    m_map = new Map{};
    
    m_isRunning = true;
    std::cout << "✅ Juego inicializado!\n";
}

// Limpiar recursos
void Game::cleanup() {
    std::cout << "🧹 Limpiando recursos...\n";
    
    // Liberar memoria manualmente
    if (m_player) {
        delete m_player;
        m_player = nullptr;
    }
    
    // Liberar fantasmas
    for (auto ghost : m_ghosts) {
        if (ghost) {
            delete ghost;
        }
    }
    m_ghosts.clear();
    
    if (m_map) {
        delete m_map;
        m_map = nullptr;
    }
    
    std::cout << "✅ Recursos liberados!\n";
}

// Bucle principal del juego
void Game::run() {
    initialize();
    
    std::cout << "🎯 Game loop iniciado!\n";
    
    // Game loop
    while (m_isRunning && m_window.isOpen()) {
        // Calcular delta time
        float deltaTime = m_clock.restart().asSeconds();
        
        handleEvents();
        update(deltaTime);
        render();
    }
    
    std::cout << "🛑 Game loop terminado!\n";
}

void Game::handleEvents() {
    sf::Event event();
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            m_isRunning = false;
        }
        
        // Aquí añadirás input del jugador después
    }
}

void Game::update(float deltaTime) {
    // Actualizar lógica del juego
    if (m_player) {
        m_player->update(deltaTime);
    }
    
    for (auto ghost : m_ghosts) {
        if (ghost) {
            ghost->update(deltaTime);
        }
    }
    
    checkCollisions();
}

void Game::render() {
    m_window.clear(sf::Color::Black);
    
    // Dibujar mapa
    if (m_map) {
        m_map->render(m_window);
    }
    
    // Dibujar jugador
    if (m_player) {
        m_player->render(m_window);
    }
    
    // Dibujar fantasmas
    for (auto ghost : m_ghosts) {
        if (ghost) {
            ghost->render(m_window);
        }
    }
    
    m_window.display();
}

void Game::checkCollisions() {
    // Por implementar - colisiones entre jugador y fantasmas
}

void Game::resetGame() {
    // Por implementar - reiniciar juego
}