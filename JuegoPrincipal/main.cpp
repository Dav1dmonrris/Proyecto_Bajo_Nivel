#include <SFML/Graphics.hpp>
#include <iostream>
#include "Clases/AdministradorEnemigos.hpp"
#include "Clases/Movimiento.hpp"
#include "Clases/ObjetoRectangulo.hpp"

using namespace std;
using namespace sf;

int main() {
    // ==================== CONFIGURACIÓN INICIAL =============================
    
    // Cargar texturas
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Recursos/Sky.png")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Recursos/MarioXD.png")) {
        cout << "ERROR: No se pudo cargar la imagen del personaje!" << endl;
        return -1;
    }
    
    // Crear ventana
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), "Juego de Plataformas");
    window.setFramerateLimit(60);
    
    cout << "Tamaño de ventana: " << imageSize.x << " x " << imageSize.y << endl;
    
    // Crear sprites
    Sprite backgroundSprite(backgroundTexture);
    Sprite playerSprite(playerTexture);
    
    // Obtener tamaño del personaje
    Vector2u playerSizeU = playerTexture.getSize();
    Vector2f playerSize(static_cast<float>(playerSizeU.x), static_cast<float>(playerSizeU.y));
    
    // ========== CREAR OBJETOS ==========
    
    // Sistema de movimiento del jugador
    Movimiento jugador(
        imageSize.x / 2.0f - playerSize.x / 2,  // posX
        imageSize.y - 200.0f,  // posY - más arriba para ver mejor
        playerSize.x,                           // ancho
        playerSize.y                            // alto
    );
    
    // Suelo principal
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30));
    
    // Plataformas
    ObjetoRectangulo plataforma1(200.0f, 20.0f, 100.0f, imageSize.y - 150.0f);
    ObjetoRectangulo plataforma2(200.0f, 20.0f, 400.0f, imageSize.y - 250.0f);

    // Administrador de enemigos
    AdministradorEnemigos administradorEnemigos;

    // Variables para el juego
    bool jugadorVivo = true;
    int puntuacion = 0;
    
    // Reloj para deltaTime
    Clock clock;
    
    // ========================= INFORMACIÓN INICIAL ==========================
    cout << "🎮 Juego iniciado correctamente" << endl;
    cout << "👾 Enemigos creados: 3 Goombas" << endl;
    
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

        // Si el jugador está muerto, no procesar entrada
        if (!jugadorVivo) {
            // Podrías añadir aquí una pantalla de game over
            cout << "💀 Game Over! Puntuación: " << puntuacion << endl;
            continue;
        }
        
        // ========================= ACTUALIZAR JUEGO =========================
        
        // Manejar entrada del jugador
        jugador.manejarEntrada();
        jugador.manejarSalto();
        
        // Actualizar física del jugador
        jugador.actualizar(deltaTime);
        
        // Actualizar enemigos
        administradorEnemigos.actualizar(deltaTime);
        
        // ===================== DETECCIÓN DE COLISIONES ======================
        
        // Colisión con suelo
        float nivelSuelo = imageSize.y - 50.0f - playerSize.y;
        if (jugador.verificarColisionConSuelo(nivelSuelo)) {
            jugador.resolverColisionSuelo(nivelSuelo);
        } else {
            jugador.establecerEnSuelo(false);
        }
        
        // Colisión con plataformas
        bool enPlataforma = false;
        
        // Plataforma 1
        if (jugador.verificarColisionConPlataforma(
            plataforma1.ObtenerPosicion(), 
            plataforma1.ObtenerTamaño())) {
            
            jugador.resolverColisionPlataforma(
                plataforma1.ObtenerPosicion(), 
                plataforma1.ObtenerTamaño());
            enPlataforma = true;
        }
        
        // Plataforma 2
        if (jugador.verificarColisionConPlataforma(
            plataforma2.ObtenerPosicion(), 
            plataforma2.ObtenerTamaño())) {
            
            jugador.resolverColisionPlataforma(
                plataforma2.ObtenerPosicion(), 
                plataforma2.ObtenerTamaño());
            enPlataforma = true;
        }
        
        jugador.establecerEnPlataforma(enPlataforma);
        
        // Verificar colisiones con enemigos
        sf::FloatRect boundsJugador = playerSprite.getGlobalBounds();
        administradorEnemigos.verificarColisionJugador(boundsJugador, jugadorVivo, puntuacion);
        
        // Límites de pantalla
        Vector2f posJugador = jugador.obtenerPosicion();
        if (posJugador.x < 0) {
            jugador.establecerPosicion(Vector2f(0, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        if (posJugador.x + playerSize.x > imageSize.x) {
            jugador.establecerPosicion(Vector2f(imageSize.x - playerSize.x, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        
        // ===================== ACTUALIZAR GRÁFICOS =====================
        
        // Actualizar posición del sprite
        playerSprite.setPosition(jugador.obtenerPosicion());
        
        // Rotación del sprite según dirección
        Vector2f velocidad = jugador.obtenerVelocidad();
        if (velocidad.x > 0.1f) {
            playerSprite.setScale({1.0f, 1.0f});
        } else if (velocidad.x < -0.1f) {
            playerSprite.setScale({-1.0f, 1.0f});
        }
        
        // ============================ RENDERIZADO ===========================
        window.clear(Color::Black);
        
        // Dibujar fondo
        window.draw(backgroundSprite);
        
        // Dibujar suelo
        window.draw(ground);
        
        // Dibujar plataformas
        plataforma1.dibujar(window);
        plataforma2.dibujar(window);
        
        // Dibujar enemigos (ANTES del jugador para mejor visualización)
        administradorEnemigos.dibujar(window);
        
        // Dibujar jugador
        window.draw(playerSprite);
        
        // Mostrar información de debug
        static int frames = 0;
        frames++;
        if (frames % 60 == 0) { // Cada segundo aproximadamente
            cout << "🎯 Jugador en: (" << (int)posJugador.x << ", " << (int)posJugador.y << ")" << endl;
            cout << "💰 Puntuación: " << puntuacion << endl;
        }
        
        window.display();
    }
    
    return 0;
}