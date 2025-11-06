// ObjetoRectangulo.hpp
// Definición de la clase ObjetoRectangulo
//=============================================================================
#ifndef OBJETORECTANGULO_HPP
#define OBJETORECTANGULO_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ObjetoRectangulo
{
    private: //---------------------------------------------------------------*
    //                                Atributos                               |
    //------------------------------------------------------------------------*
        RectangleShape rectangulo;
    public: //----------------------------------------------------------------*
    //                                Constructor                             |
    //------------------------------------------------------------------------*
    ObjetoRectangulo(float ancho, float alto, float posicionX, float posicionY);

    //------------------------------------------------------------------------*
    //                                Métodos                                 |
    //------------------------------------------------------------------------*
    void dibujar(RenderWindow& ventana);
};

#endif // OBJETORECTANGULO_HPP