#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
    // Cargar textura del fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Recursos/fondo_final3.jpg")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    // Cargar textura del pez
    sf::Texture fishTexture;
    if (!fishTexture.loadFromFile("Recursos/tiburon.jpg")) { // Ajusta el nombre de tu archivo
        cout << "ERROR: No se pudo cargar la imagen del pez!" << endl;
        return -1;
    }
    
    // Crear ventana con el tamaño exacto de la imagen
    sf::Vector2u imageSize = backgroundTexture.getSize();
    sf::RenderWindow window(sf::VideoMode({imageSize.x, imageSize.y}), 
                           "Juego pescador");

    window.setFramerateLimit(60);
    
    // Crear sprites
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Sprite fishSprite(fishTexture);
    
    // Configurar posición inicial del pez (centro de la pantalla)
    fishSprite.setPosition({imageSize.x / 2.0f, imageSize.y / 2.0f});
    
    // Velocidad de movimiento del pez
    float fishSpeed = 5.0f;
    
    cout << "Imagen cargada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Ventana creada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Controles: Flechas o WASD para mover el pez" << endl;
    cout << "Presiona ESC para salir" << endl;
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        
        
        sf::Vector2f movement(0.0f, 0.0f);
        
        // Flechas o WASD para movimiento
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            movement.x -= fishSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            movement.x += fishSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            movement.y -= fishSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            movement.y += fishSpeed;
        }
        
        // Aplicar movimiento al pez
        fishSprite.move(movement);
        
        // **LIMITES DE LA PANTALLA** (para que el pez no se salga)
        sf::Vector2f fishPosition = fishSprite.getPosition();
        sf::FloatRect fishBounds = fishSprite.getGlobalBounds();
        
        // Limite izquierdo
        if (fishPosition.x < 0) {
            fishSprite.setPosition({0, fishPosition.y});
        }
        // Limite derecho
        if (fishPosition.x > imageSize.x) {
            fishSprite.setPosition({imageSizls e.x - fishBounds.width, fishPosition.y});
        }
        // Limite superior
        if (fishPosition.y < 0) {
            fishSprite.setPosition({fishPosition.x, 0});
        }
        // Limite inferior
        if (fishPosition.y + fishBounds.height > imageSize.y) {
            fishSprite.setPosition({fishPosition.x, imageSize.y - fishBounds.height});
        }
        
        // **DIBUJADO**
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(fishSprite);  // Dibujar el pez
        window.display();
    }
    
    return 0;
}