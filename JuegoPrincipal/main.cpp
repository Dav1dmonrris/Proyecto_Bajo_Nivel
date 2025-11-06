#include <SFML/Graphics.hpp>
#include <iostream>

#include "Clases/Movimiento.hpp"

using namespace std;
using namespace sf;

// ----------------------------------------------------------------------------
// Función auxiliar para verificar colisión entre dos rectángulos
// ----------------------------------------------------------------------------
bool checkCollision(float x1, float y1, float w1, float h1, 
                   float x2, float y2, float w2, float h2) {
    return x1 < x2 + w2 &&
           x1 + w1 > x2 &&
           y1 < y2 + h2 &&
           y1 + h1 > y2;
}

// ----------------------------------------------------------------------------
// Función principal
// ----------------------------------------------------------------------------
int main() {
    // ==================== CONFIGURACIÓN INICIAL =============================
    
    // Cargar texturas.
    // ---------------------------------------------------------------*
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

    /*Texture MarioTexture;
    if (!MarioTexture.loadFromFile("Recursos/MarioXD.png")) {
        cout << "ERROR: No se pudo cargar la imagen de Mario!" << endl;
        return -1;
    }*/
    
    // Crear ventana.
    // ---------------------------------------------------------------*
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), "Juego de Plataformas");
    
    window.setFramerateLimit(60);
    
    // Crear sprites.
    //---------------------------------------------------------------*
    Sprite backgroundSprite(backgroundTexture);
    Sprite playerSprite(playerTexture);
    //Sprite MarioSprite(MarioTexture);
    
    // Obtener tamaño del personaje
    //---------------------------------------------------------------*
    Vector2u playerSizeU = playerTexture.getSize();
    Vector2f playerSize(static_cast<float>(playerSizeU.x), static_cast<float>(playerSizeU.y));

    /*Vector2u MarioSizeU = MarioTexture.getSize();
    Vector2f MarioSize(static_cast<float>(MarioSizeU.x), static_cast<float>(MarioSizeU.y));*/
    
    // ========== VARIABLES DEL JUGADOR ==========
    Vector2f playerPosition(imageSize.x / 2.0f - playerSize.x / 2, 
                           imageSize.y / 2.0f - playerSize.y / 2);
    Vector2f playerVelocity(0.0f, 0.0f);
    Vector2f previousPosition = playerPosition;


    
    // Constantes de física
    const float MOVE_SPEED = 500.0f;
    const float JUMP_FORCE = -600.0f;
    const float GRAVITY = 1100.0f;
    const float FRICTION = 0.85f;
    bool isOnGround = false;
    bool isOnPlatform = false;
    
    playerSprite.setPosition(playerPosition);
    
    // ===================== ELEMENTOS DEL ESCENARIO ==========================
    
    // Suelo principal
    //-----------------------------------------------------------------*
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30));
    
    // Bloque flotante (plataforma - SOLO colisión por arriba)
    // ---------------------------------------------------------------*
    RectangleShape floatingBlock(Vector2f(50.0f, 50.0f));
    floatingBlock.setPosition({200.0f, imageSize.y - 200.0f});
    floatingBlock.setFillColor(Color(100, 70, 30));

    // Bloque flotante para prueba 1
    RectangleShape floatingBlock2(Vector2f(50.0f, 50.0f));
    floatingBlock2.setPosition({400.0f, imageSize.y - 350.0f});
    floatingBlock2.setFillColor(Color(120, 90, 40));
    
    // Variables para el bloque
    // -----------------------------------------------*
    Vector2f blockPosition = floatingBlock.getPosition();
    Vector2f blockSize = floatingBlock.getSize();
    Vector2f block2Position = floatingBlock2.getPosition();
    
    // Reloj para deltaTime
    // --------------------*
    Clock clock;
    
    // ========================= INFORMACIÓN INICIAL ==========================
    // Salida por consola
    // -----------------------------------------------------------------------*
    cout << "Imagen cargada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Tamaño del personaje: " << playerSize.x << " x " << playerSize.y << endl;
    cout << "Controles: A/D o Flechas para mover, W/ESPACIO para saltar" << endl;
    cout << "Presiona ESC para salir" << endl;
    
    // ========================== BUCLE PRINCIPAL =============================
    // Configuración del bucle para el juego.
    // Mientras la ventana esté abierta...
    // -----------------------------------------------------------------------*
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Procesar eventos. -------------------------------------------------*
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            
            if (auto* keyEvent = event->getIf<Event::KeyPressed>()) {
                if (keyEvent->code == Keyboard::Key::Escape) {
                    window.close();
                }
                
                // Manejo de salto
                // -------------------------------------------------*
                if ((keyEvent->code == Keyboard::Key::Space || 
                     keyEvent->code == Keyboard::Key::W ||
                     keyEvent->code == Keyboard::Key::Up) && 
                    (isOnGround || isOnPlatform)) {
                    playerVelocity.y = JUMP_FORCE;
                    isOnGround = false;
                    isOnPlatform = false;
                }
            }
        }
        
        // ========================= ENTRADA Y FÍSICA =========================
        
        // Guardar posición anterior
        previousPosition = playerPosition;
        
        // Movimiento horizontal
        float horizontalInput = 0.0f;
        
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || 
            Keyboard::isKeyPressed(Keyboard::Key::A)) {
            horizontalInput -= 1.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) || 
            Keyboard::isKeyPressed(Keyboard::Key::D)) {
            horizontalInput += 1.0f;
        }
        
        playerVelocity.x = horizontalInput * MOVE_SPEED;
        
        // Aplicar gravedad
        if (!isOnGround && !isOnPlatform) {
            playerVelocity.y += GRAVITY * deltaTime;
        } else {
            playerVelocity.y = 0.0f;
        }
        
        // Aplicar fricción
        if (horizontalInput == 0.0f && (isOnGround || isOnPlatform)) {
            playerVelocity.x *= FRICTION;
            if (abs(playerVelocity.x) < 1.0f) {
                playerVelocity.x = 0.0f;
            }
        }
        
        // Calcular nueva posición
        playerPosition.x += playerVelocity.x * deltaTime;
        playerPosition.y += playerVelocity.y * deltaTime;
        
        // ===================== DETECCIÓN DE COLISIONES ======================
        
        // Resetear estados
        isOnGround = false;
        
        // **COLISIÓN MEJORADA: Plataforma de un solo sentido (solo por arriba)**
        isOnPlatform = false;
        
        // Verificar si el jugador está cayendo SOBRE la plataforma
        bool wasAbovePlatform = previousPosition.y + playerSize.y <= blockPosition.y;
        bool isCollidingWithPlatform = checkCollision(
            playerPosition.x, playerPosition.y, playerSize.x, playerSize.y,
            blockPosition.x, blockPosition.y, blockSize.x, blockSize.y
        );
        
        // **SOLUCIÓN: Solo colisionar si viene desde arriba y está cayendo**
        if (isCollidingWithPlatform && wasAbovePlatform && playerVelocity.y >= 0) {
            // Colocar al jugador encima de la plataforma
            playerPosition.y = blockPosition.y - playerSize.y;
            isOnPlatform = true;
            playerVelocity.y = 0.0f;
        }
        
        // **IMPORTANTE: Permitir pasar a través de la plataforma por los lados y por debajo**
        // No hacemos ninguna colisión lateral ni desde abajo
        
        // Colisión con el suelo principal
        float groundLevel = imageSize.y - 50.0f - playerSize.y;
        if (playerPosition.y >= groundLevel) {
            playerPosition.y = groundLevel;
            isOnGround = true;
            playerVelocity.y = 0.0f;
        }
        
        // **DETECCIÓN DE CAÍDA DE LA PLATAFORMA**
        if (isOnPlatform) {
            // Verificar si el jugador ya no está sobre la plataforma
            bool stillOnPlatform = checkCollision(
                playerPosition.x, playerPosition.y + 1.0f, // Pequeño margen hacia abajo
                playerSize.x, playerSize.y,
                blockPosition.x, blockPosition.y, 
                blockSize.x, blockSize.y
            );
            
            if (!stillOnPlatform) {
                isOnPlatform = false;
            }
            
            // También permitir saltar a través de la plataforma
            if (playerVelocity.y < 0) { // Si está saltando hacia arriba
                isOnPlatform = false;
            }
        }
        
        // ========== LÍMITES DE PANTALLA ==========
        if (playerPosition.x < 0) {
            playerPosition.x = 0;
            playerVelocity.x = 0;
        }
        if (playerPosition.x + playerSize.x > imageSize.x) {
            playerPosition.x = imageSize.x - playerSize.x;
            playerVelocity.x = 0;
        }
        
        // ========== ACTUALIZAR GRÁFICOS ==========
        playerSprite.setPosition(playerPosition);
        
        // Rotación del sprite según dirección
        if (playerVelocity.x > 0.1f) {
            playerSprite.setScale({1.0f, 1.0f});
        } else if (playerVelocity.x < -0.1f) {
            playerSprite.setScale({-1.0f, 1.0f});
        }
        
        // ============================ RENDERIZADO ===========================
        // Mostrar todo en pantalla
        // Mostrar elementos creados.
        // -------------------------------------------------------------------*
        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(ground);
        window.draw(floatingBlock);
        window.draw(floatingBlock2);
        window.draw(playerSprite);
        window.display();
    }
    
    return 0;
}