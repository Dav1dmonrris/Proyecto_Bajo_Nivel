#include "ObjetoRectangulo.hpp"

ObjetoRectangulo::ObjetoRectangulo(float ancho, float alto, float posicionX, float posicionY) {      
    rectangulo.setSize(Vector2f(ancho, alto));
    rectangulo.setPosition(Vector2f(posicionX, posicionY));
    rectangulo.setFillColor(Color(205, 133, 63));
}

void ObjetoRectangulo::dibujar(RenderWindow& ventana) {
    ventana.draw(rectangulo);
}

Vector2f ObjetoRectangulo::ObtenerPosicion() const {
    return rectangulo.getPosition();
}

Vector2f ObjetoRectangulo::ObtenerTamaño() const {
    return rectangulo.getSize();
}