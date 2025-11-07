#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Clases/Movimiento.hpp"
#include "Clases/ObjetoRectangulo.hpp"
#include "Clases/Enemigo.hpp"

using namespace std;
using namespace sf;

int main() {
    // ==================== CONFIGURACIÓN INICIAL =============================
    // ========================================================================
    // Cargar texturas
    // ------------------------------------------------------------------------
    // Fondo del juego.
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Recursos/Sky.png")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    // Imagen de Mario.
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Recursos/MarioXD.png")) {
        cout << "ERROR: No se pudo cargar la imagen del personaje!" << endl;
        return -1;
    }
    
    // Imagen del enemigo.
    Texture enemyTexture;
    bool tieneTexturaEnemigo = enemyTexture.loadFromFile("Recursos/goomba.png");
    if (!tieneTexturaEnemigo) {
        cout << "⚠️  No se pudo cargar goomba.png - Los enemigos serán invisibles" << endl;
    } else {
        cout << "✅ Textura de enemigo cargada correctamente" << endl;
    }
    
    // ========================================================================
    //                             Crear ventana
    // ========================================================================
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), "Juego de Plataformas");
    window.setFramerateLimit(60);
    
    // Crear sprites --------------------------*
    Sprite backgroundSprite(backgroundTexture);
    Sprite playerSprite(playerTexture);
    
    // Obtener tamaño del personaje ---------------------------------------------------------*
    Vector2u playerSizeU = playerTexture.getSize();
    Vector2f playerSize(static_cast<float>(playerSizeU.x), static_cast<float>(playerSizeU.y));
    
    //=========================================================================
    // ==========                 CREAR OBJETOS                 ===============
    // ========================================================================
    // Jugador
    Movimiento jugador(
        imageSize.x / 2.0f - playerSize.x / 2,
        imageSize.y - 200.0f,
        playerSize.x,
        playerSize.y
    );
    
    // Suelo
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30));
    
    // Plataformas
    ObjetoRectangulo plataforma1(200.0f, 20.0f, 100.0f, imageSize.y - 150.0f);
    ObjetoRectangulo plataforma2(200.0f, 20.0f, 400.0f, imageSize.y - 250.0f);

    // ✅ CREAR ENEMIGOS
    vector<Enemigo> enemigos;
    enemigos.emplace_back(100.0f, 400.0f);
    enemigos.emplace_back(400.0f, 400.0f);  
    enemigos.emplace_back(700.0f, 300.0f);
    
    // Aplicar textura
    if (tieneTexturaEnemigo) {
        for (auto& enemigo : enemigos) {
            enemigo.configurarTextura(enemyTexture);
        }
    }
    
    cout << "👾 " << enemigos.size() << " enemigos creados" << endl;
    
    // Variables del juego
    bool jugadorVivo = true;
    int puntuacion = 0;
    Clock clock;
    
    // ========================== BUCLE PRINCIPAL =============================
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Procesar eventos
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            
            if (auto* keyEvent = event->getIf<Event::KeyPressed>()) {
                if (keyEvent->code == Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        
        if (!jugadorVivo) continue;
        
        // ========================= ACTUALIZAR JUEGO =========================
        
        // Jugador
        jugador.manejarEntrada();
        jugador.manejarSalto();
        jugador.actualizar(deltaTime);
        
        // ✅ ACTUALIZAR ENEMIGOS
        for (auto& enemigo : enemigos) {
            if (enemigo.estaVivo()) {
                enemigo.actualizar(deltaTime);
            }
        }
        
        // ===================== DETECCIÓN DE COLISIONES ======================
        
        // OBTENER POSICIÓN DEL JUGADOR UNA SOLA VEZ
        Vector2f posJugador = jugador.obtenerPosicion();
        
        // Colisión con suelo
        float nivelSuelo = imageSize.y - 50.0f - playerSize.y;
        if (jugador.verificarColisionConSuelo(nivelSuelo)) {
            jugador.resolverColisionSuelo(nivelSuelo);
        } else {
            jugador.establecerEnSuelo(false);
        }
        
        // Colisión con plataformas
        bool enPlataforma = false;
        if (jugador.verificarColisionConPlataforma(plataforma1.ObtenerPosicion(), plataforma1.ObtenerTamaño())) {
            jugador.resolverColisionPlataforma(plataforma1.ObtenerPosicion(), plataforma1.ObtenerTamaño());
            enPlataforma = true;
        }
        if (jugador.verificarColisionConPlataforma(plataforma2.ObtenerPosicion(), plataforma2.ObtenerTamaño())) {
            jugador.resolverColisionPlataforma(plataforma2.ObtenerPosicion(), plataforma2.ObtenerTamaño());
            enPlataforma = true;
        }
        jugador.establecerEnPlataforma(enPlataforma);
        
        // ✅ COLISIÓN CON ENEMIGOS - CORREGIDO
        for (auto& enemigo : enemigos) {
            if (!enemigo.estaVivo()) continue;
            
            sf::Vector2f posEnemigo = enemigo.getPosicion();
            
            // Detección MANUAL
            bool hayColision = (posJugador.x < posEnemigo.x + 50.0f) &&
                               (posJugador.x + playerSize.x > posEnemigo.x) &&
                               (posJugador.y < posEnemigo.y + 50.0f) &&
                               (posJugador.y + playerSize.y > posEnemigo.y);
            
            if (hayColision) {
                bool jugadorPorEncima = (posJugador.y + playerSize.y) < (posEnemigo.y + 25.0f);
                
                if (jugadorPorEncima) {
                    enemigo.matar();
                    puntuacion += 100;
                    cout << "👾 Enemigo eliminado! Puntuación: " << puntuacion << endl;
                    jugador.establecerVelocidadY(-300.0f);
                } else {
                    jugadorVivo = false;
                    cout << "💀 El jugador ha muerto! Puntuación final: " << puntuacion << endl;
                }
            }
        }
        
        // Límites de pantalla - USAR LA MISMA posJugador
        if (posJugador.x < 0) {
            jugador.establecerPosicion(Vector2f(0, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        if (posJugador.x + playerSize.x > imageSize.x) {
            jugador.establecerPosicion(Vector2f(imageSize.x - playerSize.x, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        
        // ===================== ACTUALIZAR GRÁFICOS =====================
        playerSprite.setPosition(posJugador);
        
        // Rotación del sprite -----------------------*
        Vector2f velocidad = jugador.obtenerVelocidad();
        if (velocidad.x > 0.1f) {
            playerSprite.setScale({1.0f, 1.0f});
        } else if (velocidad.x < -0.1f) {
            playerSprite.setScale({-1.0f, 1.0f});
        }
        
        // ============================ RENDERIZADO ===========================
        // ====================================================================
        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(ground);
        plataforma1.dibujar(window);
        plataforma2.dibujar(window);
        
        // ✅ DIBUJAR ENEMIGOS
        for (auto& enemigo : enemigos) {
            enemigo.dibujar(window);
        }
        
        window.draw(playerSprite);
        window.display();
    }
    
    return 0;
}