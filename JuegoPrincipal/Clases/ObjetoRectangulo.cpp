// ObjetoRectangulo.cpp
// Implementación de la clase ObjetoRectangulo
//=============================================================================
#include "ObjetoRectangulo.hpp"

//----------------------------------------------------------------------------*
// Constructor de la clase ObjetoRectangulo                                   |
//----------------------------------------------------------------------------*
ObjetoRectangulo::ObjetoRectangulo(float ancho, float alto, float posicionX, float posicionY)
{      
    rectangulo.setSize(Vector2f(ancho, alto));
    rectangulo.setPosition(Vector2f(posicionX, posicionY));
    rectangulo.setFillColor(Color(205, 133, 63)); // Color marrón claro
}

//----------------------------------------------------------------------------*
// Método para dibujar el rectángulo en la ventana                            |
//----------------------------------------------------------------------------*
void ObjetoRectangulo::dibujar(RenderWindow& ventana)
{
    ventana.draw(rectangulo);
}

