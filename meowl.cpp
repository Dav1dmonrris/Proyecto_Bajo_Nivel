#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    // Cargar la textura para obtener su tamaño
    // ----------------------------------------------------------------*
    Texture meowl;

    // Cargar las imágenes
    // ----------------------------------------------------------------*

    if (!meowl.loadFromFile("Archivos/meowl2.png"))
    {
        cout << "ERROR: No se pudo cargar la imagen de Meowl!" << endl;
        return -1;
    }

    // Verificar que la textura de Meowl tenga tamaño válido
    // ----------------------------------------------------------------*
    Vector2u meowlSize = meowl.getSize();
    if (meowlSize.x == 0 || meowlSize.y == 0) {
        cout << "ERROR: La textura de Meowl está vacía o no válida!" << endl;
        return -1;
    }

    // Crear ventana con el tamaño exacto de la imagen
    // ---------------------------------------------------------------*
    RenderWindow window(VideoMode({1440, 780}), "Pacman", Style::Close);

    // Restricción de fotogramas.
    // ---------------------------------------------------------------*
    window.setFramerateLimit(60);
    
    // Crear sprite de fondo
    // ---------------------------------------------------------------*
    Sprite meowlSprite(meowl);

    // Posiciones iniciales
    // ---------------------------------------------------------------*
    meowlSprite.setPosition({500.f, 300.f});

    // Velocidad (pixeles por segundo)
    // ---------------------------------------------------------------*
    float meowlspeed = 150.f;

    // Dirección inicial aleatoria (dx, dy) con magnitud meowlspeed
    // ---------------------------------------------------------------*
    float angle = (std::rand() % 360) * 3.14159265f / 180.f;
    float dx = std::cos(angle) * meowlspeed;
    float dy = std::sin(angle) * meowlspeed;

    // Reloj para deltaTime
    // ---------------------------------------------------------------*
    Clock clock;

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

        // Calcular deltaTime
        // ---------------------------------------------------------------*
        float deltaTime = clock.restart().asSeconds();

        // Movimiento
        // ---------------------------------------------------------------*
        meowlSprite.move({dx * deltaTime, dy * deltaTime});

        // Tamaño visible del sprite (textura * escala)
        // ---------------------------------------------------------------*
        Vector2f scale = meowlSprite.getScale();
        Vector2u texSize = meowl.getSize();
        float spriteWidth  = static_cast<float>(texSize.x) * scale.x;
        float spriteHeight = static_cast<float>(texSize.y) * scale.y;

        // Posición y tamaño de ventana
        // ---------------------------------------------------------------*
        Vector2f pos = meowlSprite.getPosition();
        Vector2u winSize = window.getSize();

        // Rebote en eje X
        // ---------------------------------------------------------------*
        if (pos.x <= 0.f) {
            pos.x = 0.f;
            dx = std::abs(dx);
            meowlSprite.setPosition(pos);
        } else if (pos.x + spriteWidth >= static_cast<float>(winSize.x)) {
            pos.x = static_cast<float>(winSize.x) - spriteWidth;
            dx = -std::abs(dx);
            meowlSprite.setPosition(pos);
        }

        // Rebote en eje Y
        // ---------------------------------------------------------------*
        if (pos.y <= 0.f) {
            pos.y = 0.f;
            dy = std::abs(dy);
            meowlSprite.setPosition(pos);
        } else if (pos.y + spriteHeight >= static_cast<float>(winSize.y)) {
            pos.y = static_cast<float>(winSize.y) - spriteHeight;
            dy = -std::abs(dy);
            meowlSprite.setPosition(pos);
        }
        
        window.clear(sf::Color::Black);     // Limpiar la ventana.
        window.draw(meowlSprite);           // Dibujar el sprite de Meowl.
        window.display();                   // Mostrar el contenido de la ventana.
    }

    return 0;
}