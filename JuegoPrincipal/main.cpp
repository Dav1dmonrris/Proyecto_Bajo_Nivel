#include <SFML/Graphics.hpp>
#include <iostream>
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
        imageSize.y / 2.0f - playerSize.y / 2,  // posY
        playerSize.x,                           // ancho
        playerSize.y                            // alto
    );
    
    // Suelo principal
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30));
    
    // Plataformas
    ObjetoRectangulo plataforma1(50.0f, 50.0f, 200.0f, imageSize.y - 200.0f);
    ObjetoRectangulo plataforma2(50.0f, 50.0f, 100.0f, imageSize.y - 350.0f);
    
    // Reloj para deltaTime
    Clock clock;
    
    // ========================= INFORMACIÓN INICIAL ==========================
    cout << "Imagen cargada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Tamaño del personaje: " << playerSize.x << " x " << playerSize.y << endl;
    cout << "Controles: A/D o Flechas para mover, W/ESPACIO para saltar" << endl;
    cout << "Presiona ESC para salir" << endl;
    
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
        
        // ========================= ACTUALIZAR JUEGO =========================
        
        // Manejar entrada del jugador
        jugador.manejarEntrada();
        jugador.manejarSalto();
        
        // Actualizar física
        jugador.actualizar(deltaTime);
        
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
        window.draw(backgroundSprite);
        window.draw(ground);
        plataforma1.dibujar(window);
        plataforma2.dibujar(window);
        window.draw(playerSprite);
        window.display();
    }
    
    return 0;
}