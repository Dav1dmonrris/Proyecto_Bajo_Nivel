#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    // Cargar textura del fondo
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Recursos/Sky.png")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    // Cargar textura del personaje
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Recursos/Mario.png")) {
        cout << "ERROR: No se pudo cargar la imagen del personaje!" << endl;
        return -1;
    }
    
    // Crear ventana con el tamaño exacto de la imagen
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), 
                       "Juego de Plataformas");

    window.setFramerateLimit(60);
    
    // Crear sprites
    Sprite backgroundSprite(backgroundTexture);
    Sprite playerSprite(playerTexture);
    
    // Obtener el tamaño del personaje
    Vector2u playerSizeU = playerTexture.getSize();
    Vector2f playerSize(static_cast<float>(playerSizeU.x), static_cast<float>(playerSizeU.y));
    
    // **VARIABLES DE FÍSICA HUMANA**
    Vector2f playerPosition(imageSize.x / 2.0f - playerSize.x / 2, 
                           imageSize.y / 2.0f - playerSize.y / 2);
    Vector2f playerVelocity(0.0f, 0.0f);
    
    // Constantes de física (ajustadas para humano en tierra)
    float moveSpeed = 500.0f;        // Velocidad de movimiento horizontal
    float jumpForce = -600.0f;       // Fuerza de salto (negativa porque Y crece hacia abajo)
    float gravity = 1100.0f;         // Gravedad terrestre
    float friction = 0.85f;          // Fricción al soltar teclas
    bool isOnGround = false;         // Si está tocando el "suelo"
    
    // Configurar posición inicial
    playerSprite.setPosition(playerPosition);
    
    // Crear un "suelo" visual (para debug)
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30)); // Color marrón

    // **CircleShape - CORREGIDO**
    RectangleShape testCircle(Vector2f(50.0f,50.0f)); // Radio de 25 píxeles
    testCircle.setFillColor(Color(100,70,30));
    
    // Posicionar el círculo - IMPORTANTE: setPosition establece la ESQUINA SUPERIOR IZQUIERDA del rectángulo delimitador
    // Para centrarlo visualmente en (30, imageSize.y - 30), ajustamos la posición
    testCircle.setPosition({200.0f, imageSize.y - 200.0f}); // Ajustar para que el centro esté en (30, imageSize.y - 30)

    // Otra opción: usar setOrigin para cambiar el punto de referencia
    // testCircle.setOrigin(25.0f, 25.0f); // Centrar el origen
    // testCircle.setPosition({30.0f, imageSize.y - 30.0f}); // Ahora la posición es el centro
    
    // Reloj para deltaTime
    Clock clock;
    
    cout << "Imagen cargada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Tamaño del personaje: " << playerSize.x << " x " << playerSize.y << endl;
    cout << "Controles: A/D o Flechas para mover, W/ESPACIO para saltar" << endl;
    cout << "Presiona ESC para salir" << endl;
    
    while (window.isOpen()) {
        // Calcular deltaTime para física consistente
        float deltaTime = clock.restart().asSeconds();
        
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            
            if (auto* keyEvent = event->getIf<Event::KeyPressed>()) {
                if (keyEvent->code == Keyboard::Key::Escape) {
                    window.close();
                }
                
                if ((keyEvent->code == Keyboard::Key::Space || 
                     keyEvent->code == Keyboard::Key::W ||
                     keyEvent->code == Keyboard::Key::Up) && 
                    isOnGround) {
                    playerVelocity.y = jumpForce;
                    isOnGround = false;
                }
            }
        }
        
        // **MOVIMIENTO HORIZONTAL**
        float horizontalInput = 0.0f;
        
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || 
            Keyboard::isKeyPressed(Keyboard::Key::A)) {
            horizontalInput -= 1.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) || 
            Keyboard::isKeyPressed(Keyboard::Key::D)) {
            horizontalInput += 1.0f;
        }
        
        // Aplicar movimiento horizontal
        playerVelocity.x = horizontalInput * moveSpeed;
        
        // **APLICAR GRAVEDAD** 
        if (!isOnGround) {
            playerVelocity.y += gravity * deltaTime;
        } else {
            playerVelocity.y = 0.0f; // No cae si está en suelo
        }
        
        // **APLICAR FRICCIÓN** cuando no hay input horizontal
        if (horizontalInput == 0.0f && isOnGround) {
            playerVelocity.x *= friction;
            // Detener completamente si la velocidad es muy pequeña
            if (abs(playerVelocity.x) < 1.0f) {
                playerVelocity.x = 0.0f;
            }
        }
        
        // **CALCULAR NUEVA POSICIÓN**
        playerPosition.x += playerVelocity.x * deltaTime;
        playerPosition.y += playerVelocity.y * deltaTime;
        
        // **DETECCIÓN DE SUELO**
        float groundLevel = imageSize.y - 50.0f - playerSize.y; // Nivel del suelo visual
        isOnGround = false;

        float groundBlockTop = imageSize.y - 50.0f;
        // Colisión con el bloque de prueba
        if (playerPosition.x + playerSize.x > testCircle.getPosition().x &&
            playerPosition.x < testCircle.getPosition().x + testCircle.getSize().x &&
            playerPosition.y + playerSize.y > testCircle.getPosition().y &&
            playerPosition.y < testCircle.getPosition().y + testCircle.getSize().y) {
            // Colisión detectada - colocar al jugador encima del bloque
            playerPosition.y = testCircle.getPosition().y - playerSize.y;
            isOnGround = true;
            playerVelocity.y = 0.0f;
        }
        
        if (playerPosition.y >= groundLevel) {
            playerPosition.y = groundLevel;
            isOnGround = true;
            playerVelocity.y = 0.0f;
        }
        
        // **LÍMITES DE PANTALLA (solo horizontales)**
        if (playerPosition.x < 0) {
            playerPosition.x = 0;
            playerVelocity.x = 0;
        }
        if (playerPosition.x + playerSize.x > imageSize.x) {
            playerPosition.x = imageSize.x - playerSize.x;
            playerVelocity.x = 0;
        }
        
        // **ACTUALIZAR POSICIÓN DEL SPRITE**
        playerSprite.setPosition(playerPosition);
        
        // **ROTACIÓN/FLIP DEL SPRITE** (opcional - para que mire hacia donde se mueve)
        if (playerVelocity.x > 0.1f) {
            playerSprite.setScale({1.0f, 1.0f}); // Mirando a la derecha
        } else if (playerVelocity.x < -0.1f) {
            playerSprite.setScale({-1.0f, 1.0f}); // Mirando a la izquierda (flip horizontal)
        }
        
        // **DIBUJADO - ¡AQUÍ ESTÁ LA SOLUCIÓN!**
        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(ground); 
        window.draw(playerSprite);
        window.draw(testCircle); 
        
        window.display();
    }
    
    return 0;
}