#ifndef OBJETORECTANGULO_HPP
#define OBJETORECTANGULO_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ObjetoRectangulo {
private:
    RectangleShape rectangulo;
    
public:
    ObjetoRectangulo(float ancho, float alto, float posicionX, float posicionY);
    
    void dibujar(RenderWindow& ventana);
    Vector2f ObtenerPosicion() const;
    Vector2f ObtenerTamaño() const;
};

#endif // OBJETORECTANGULO_HPP