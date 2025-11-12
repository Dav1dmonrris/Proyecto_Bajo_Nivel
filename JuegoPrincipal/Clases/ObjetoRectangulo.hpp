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
        ObjetoRectangulo(const Vector2f& tamaño, const Vector2f& posicion);

    void dibujar(RenderWindow& ventana);
    Vector2f ObtenerPosicion() const;
    Vector2f ObtenerTamaño() const;
    
    void CambiarPosicion(float PosicionX, float PosicionY); // Método para cambiar posición.
    void CambiarColor(const Color& color);  // Método para cambiar el color del rectángulo.
    void CambiarTamaño(float ancho, float alto); // Método para cambiar el tamaño del rectángulo.

    FloatRect ObtenerLimites() const;       // Método para obtener los límites del rectángulo. (Perimetro)
    //bool VerificarColision(const FloatRect& OtroObjeto) const; // Método para verificar colisión con otro rectángulo. (En espera..)
};

#endif // OBJETORECTANGULO_HPP