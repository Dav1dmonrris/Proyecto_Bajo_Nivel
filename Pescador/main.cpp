#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
    // Primero cargar la textura para saber su tamaño
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("Recursos/fondo_final3.jpg")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    // Crear ventana con el tamaño exacto de la imagen
    sf::Vector2u imageSize = backgroundTexture.getSize();
    sf::RenderWindow window(sf::VideoMode({imageSize.x, imageSize.y}), 
                           "XDDDDDDDDDD");

    //Prueba de ventana fija. ---------------------------------------------------------*
    //sf::RenderWindow window(sf::VideoMode({400, 500}), "Imagen", sf::Style::Titlebar);
    //---------------------------------------------------------------------------------*

    window.setFramerateLimit(60);
    
    sf::Sprite backgroundSprite(backgroundTexture);
    
    cout << "Imagen cargada: " << imageSize.x << " x " << imageSize.y << endl;
    cout << "Ventana creada: " << imageSize.x << " x " << imageSize.y << endl;
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
        
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.display();
    }
    
    return 0;
}