#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Enemigo {
protected:
    sf::Sprite sprite;
    sf::Vector2f posicion;
    sf::Vector2f velocidad;
    sf::Vector2f tamaño;
    
    float velocidadMovimiento;
    float distanciaRecorrida;
    float distanciaMaxima;
    bool mirandoDerecha;
    bool vivo;
    
public:
    Enemigo(const sf::Vector2f& posicionInicial, float velocidad, float distanciaPatrulla);
    virtual ~Enemigo() = default;  // ✅ Destructor virtual
    
    // Métodos principales - TODOS virtuales
    virtual void actualizar(float deltaTime);
    virtual void dibujar(sf::RenderWindow& ventana);
    
    // Métodos de estado
    bool estaVivo() const { return vivo; }
    void matar() { vivo = false; }
    
    // Getters para colisiones
    sf::FloatRect obtenerBounds() const;
    sf::Vector2f obtenerPosicion() const { return posicion; }
    sf::Vector2f obtenerTamaño() const { return tamaño; }
    
    // Método para configurar la textura
    void configurarTextura(const sf::Texture& textura);
    
protected:
    // ✅ Añadido: método virtual que faltaba
    virtual void actualizarMovimiento(float deltaTime);
    void cambiarDireccion();
};