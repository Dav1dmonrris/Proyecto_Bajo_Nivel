#include "ObjetoRectangulo.hpp"

ObjetoRectangulo::ObjetoRectangulo(float ancho, float alto, float posicionX, float posicionY) {      
    rectangulo.setSize(Vector2f(ancho, alto));                  // Definir tamaño del rectángulo.
    rectangulo.setPosition(Vector2f(posicionX, posicionY));     // Definir Posición x,y.
    rectangulo.setFillColor(Color(205, 133, 63));              
}

/*ObjetoRectangulo::ObjetoRectangulo(const Vector2f& tamaño, const Vector2f& posicion)
{      
    rectangulo.setSize(tamaño);
    rectangulo.setPosition(posicion);
    rectangulo.setFillColor(Color(205, 133, 63));
}*/

void ObjetoRectangulo::dibujar(RenderWindow& ventana) {
    ventana.draw(rectangulo);
}

Vector2f ObjetoRectangulo::ObtenerPosicion() const {
    return rectangulo.getPosition();
}

Vector2f ObjetoRectangulo::ObtenerTamaño() const {
    return rectangulo.getSize();
}

// Métodos opcionales *- Por el momento no necesarios *-
// **************************************************************************************
//----------------------------------------------------------------------------*
// Método para cambiar posición del rectángulo.                               |   
//----------------------------------------------------------------------------*
void ObjetoRectangulo::CambiarPosicion(float PosicionX, float PosicionY) 
{
    rectangulo.setPosition(Vector2f(PosicionX, PosicionY));
}
//----------------------------------------------------------------------------*
// Método para cambiar el color del rectángulo.                               |
//----------------------------------------------------------------------------*
void ObjetoRectangulo::CambiarColor(const Color& color)
{
    rectangulo.setFillColor(color);
}
//----------------------------------------------------------------------------*
// Método para cambiar el tamaño del rectángulo.                              |
//----------------------------------------------------------------------------*
void ObjetoRectangulo::CambiarTamaño(float ancho, float altura)
{
    rectangulo.setSize(Vector2f(ancho, altura));
}
// **************************************************************************************

//----------------------------------------------------------------------------*
// Método para obtener los límites del rectángulo                             |
//----------------------------------------------------------------------------*
FloatRect ObjetoRectangulo::ObtenerLimites() const
{
    return rectangulo.getGlobalBounds();
}

//----------------------------------------------------------------------------*
// Método para verificar colisión con otro rectángulo                         |
//----------------------------------------------------------------------------*
/*bool ObjetoRectangulo::VerificarColision(const FloatRect& OtroObjeto) const
{
    FloatRect misLimites = ObtenerLimites();
    
    // Detección manual de colisión AABB - FUNCIONA EN TODAS LAS VERSIONES DE SFML
    return misLimites.left < OtroObjeto.left + OtroObjeto.width &&
           misLimites.left + misLimites.width > OtroObjeto.left &&
           misLimites.top < OtroObjeto.top + OtroObjeto.height &&
           misLimites.top + misLimites.height > OtroObjeto.top;

}*/