#include "Movimiento.hpp"

// Constructor
Movimiento::Movimiento(float posX, float posY, float ancho, float alto) 
    : posicion(posX, posY),
      velocidad(0.0f, 0.0f),
      tamaño(ancho, alto),
      velocidadMovimiento(500.0f),
      fuerzaSalto(-470.0f),
      gravedad(1100.0f),
      friccion(0.85f),
      enSuelo(false),
      enPlataforma(false),
      posicionAnterior(posX, posY) {
}

// Manejar entrada de movimiento horizontal
void Movimiento::manejarEntrada() {
    float entradaHorizontal = 0.0f;
    
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) || 
        Keyboard::isKeyPressed(Keyboard::Key::A)) {
        entradaHorizontal -= 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Right) || 
        Keyboard::isKeyPressed(Keyboard::Key::D)) {
        entradaHorizontal += 1.0f;
    }
    
    velocidad.x = entradaHorizontal * velocidadMovimiento;
}

// Manejar salto
void Movimiento::manejarSalto() {
    if ((Keyboard::isKeyPressed(Keyboard::Key::Space) || 
         Keyboard::isKeyPressed(Keyboard::Key::W) ||
         Keyboard::isKeyPressed(Keyboard::Key::Up)) && 
        (enSuelo || enPlataforma)) {
        velocidad.y = fuerzaSalto;
        enSuelo = false;
        enPlataforma = false;
    }
}

// Actualizar física
void Movimiento::actualizar(float deltaTime) {
    posicionAnterior = posicion;
    
    // Aplicar movimiento horizontal
    posicion.x += velocidad.x * deltaTime;
    
    // Aplicar gravedad si no está en superficie
    if (!enSuelo && !enPlataforma) {
        aplicarGravedad(deltaTime);
    } else {
        velocidad.y = 0.0f;
    }
    
    // Aplicar movimiento vertical
    posicion.y += velocidad.y * deltaTime;
    
    // Aplicar fricción
    if ((enSuelo || enPlataforma) && velocidad.x != 0.0f) {
        aplicarFriccion();
    }
}

// Aplicar gravedad
void Movimiento::aplicarGravedad(float deltaTime) {
    velocidad.y += gravedad * deltaTime;
}

// Aplicar fricción
void Movimiento::aplicarFriccion() {
    velocidad.x *= friccion;
    if (abs(velocidad.x) < 1.0f) {
        velocidad.x = 0.0f;
    }
}

// Verificar colisión con suelo
bool Movimiento::verificarColisionConSuelo(float nivelSuelo) {
    return posicion.y >= nivelSuelo;
}

// Verificar colisión con plataforma
bool Movimiento::verificarColisionConPlataforma(const Vector2f& posPlataforma, const Vector2f& tamPlataforma) {
    // Función auxiliar para verificar colisión
    auto verificarColision = [](float x1, float y1, float w1, float h1, 
                               float x2, float y2, float w2, float h2) {
        return x1 < x2 + w2 &&
               x1 + w1 > x2 &&
               y1 < y2 + h2 &&
               y1 + h1 > y2;
    };
    
    return verificarColision(
        posicion.x, posicion.y, tamaño.x, tamaño.y,
        posPlataforma.x, posPlataforma.y, tamPlataforma.x, tamPlataforma.y
    );
}

// Resolver colisión con suelo
void Movimiento::resolverColisionSuelo(float nivelSuelo) {
    posicion.y = nivelSuelo;
    enSuelo = true;
    velocidad.y = 0.0f;
}

// Resolver colisión con plataforma
void Movimiento::resolverColisionPlataforma(const Vector2f& posPlataforma, const Vector2f& tamPlataforma) {
    // Solo colisionar si viene desde arriba y está cayendo
    bool estabaSobrePlataforma = posicionAnterior.y + tamaño.y <= posPlataforma.y;
    
    if (estabaSobrePlataforma && velocidad.y >= 0) {
        posicion.y = posPlataforma.y - tamaño.y;
        enPlataforma = true;
        velocidad.y = 0.0f;
    }
}