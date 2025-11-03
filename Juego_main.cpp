#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    // Cargar la textura para obtener su tamaño
    // ----------------------------------------------------------------*
    Texture backgroundTexture;
    Texture pacman;

    if (!backgroundTexture.loadFromFile("Archivos/Fondo.bmp"))
    {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }

    if (!pacman.loadFromFile("Archivos/PacmanXD.bmp"))
    {
        cout << "ERROR: No se pudo cargar la imagen de Pacman!" << endl;
        return -1;
    }

    // Crear ventana con el tamaño exacto de la imagen
    // ---------------------------------------------------------------*
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), "Pacman");

    // Restricción de fotogramas.
    // ---------------------------------------------------------------*
    window.setFramerateLimit(60);

    // Crear sprite de fondo
    // ---------------------------------------------------------------*
    Sprite backgroundSprite(backgroundTexture);
    Sprite pacmanSprite(pacman);

    pacmanSprite.setPosition({100.f, 100.f});

    // Crear sprite de fondo
    // ---------------------------------------------------------------*
    while (window.isOpen()) {
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
        
        window.clear(sf::Color::Black);     // Limpiar la ventana.
        window.draw(backgroundSprite);      // Dibujar el sprite de fondo.
        window.draw(pacmanSprite);          // Dibujar el sprite de Pacman.
        window.display();                   // Mostrar el contenido de la ventana.
    }

    return 0;
}