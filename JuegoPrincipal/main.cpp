#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Clases/Movimiento.hpp"
#include "Clases/ObjetoRectangulo.hpp"
#include "Clases/Enemigo.hpp"

using namespace std;
using namespace sf;

// Función para verificar colisiones con múltiples plataformas
bool verificarColisiones(Movimiento& jugador, const vector<ObjetoRectangulo*>& plataformas) {
    bool enPlataforma = false;
    
    for (auto& plataforma : plataformas) {
        if (jugador.verificarColisionConPlataforma(plataforma->ObtenerPosicion(), plataforma->ObtenerTamaño())) {
            jugador.resolverColisionPlataforma(plataforma->ObtenerPosicion(), plataforma->ObtenerTamaño());
            enPlataforma = true;
        }
    }
    
    return enPlataforma;
}

int main() {

    // ========================================================================
    // ==================== CONFIGURACIÓN INICIAL =============================
    // ========================================================================

    // ------------------------------------------------------------------------
    //                         Cargar texturas
    // ------------------------------------------------------------------------

    // Fondo del juego.

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Recursos/Sky.png")) {
        cout << "ERROR: No se pudo cargar la imagen de fondo!" << endl;
        return -1;
    }
    
    // Imagen de Mario.

    Texture playerTexture;
    if (!playerTexture.loadFromFile("Recursos/MarioXD.png")) {
        cout << "ERROR: No se pudo cargar la imagen del personaje!" << endl;
        return -1;
    }
    
    // Imagen del enemigo.

    Texture enemyTexture;
    bool tieneTexturaEnemigo = enemyTexture.loadFromFile("Recursos/goomba.png");

    if (!tieneTexturaEnemigo) {

        cout << " No se pudo cargar goomba.png - Los enemigos serán invisibles" << endl;

    } else {

        cout << "Textura de enemigo cargada correctamente" << endl;

    }
    
    // ========================================================================
    //                             Crear ventana
    // ========================================================================
    Vector2u imageSize = backgroundTexture.getSize();
    RenderWindow window(VideoMode({imageSize.x, imageSize.y}), "Juego de Plataformas");
    window.setFramerateLimit(60);
    
    //                             Crear sprites 
    Sprite backgroundSprite(backgroundTexture);
    Sprite playerSprite(playerTexture);
    Sprite EnemigoSpirte(enemyTexture);
    
    //                      Obtener tamaño del personaje 
    Vector2u playerSizeU = playerTexture.getSize();
    Vector2f playerSize(static_cast<float>(playerSizeU.x), static_cast<float>(playerSizeU.y));
    
    //=========================================================================
    // ==========                 CREAR OBJETOS                 ===============
    // ========================================================================

    //                              Jugador 
    Movimiento jugador(
        imageSize.x / 2.0f - playerSize.x / 2, imageSize.y - 150.0f, playerSize.x, playerSize.y
    ); 
    
    // Suelo 
    RectangleShape ground(Vector2f(imageSize.x, 50.0f));
    ground.setPosition({0.0f, imageSize.y - 50.0f});
    ground.setFillColor(Color(100, 70, 30));
    
    
    // Plataformas | Tamaño igualitaro 200 x 20 
    // --------------------------------------------------------------------------
    float anchoP = 200.0f;           // Variable local para ancho de plataforma.
    float alturaP = 20.0f;           // Variable local para altura de plataforma.

    //Escaleras de plataformas adicionales 
    float ancho_Barandal_Escaleras = 10.0f;           // ancho de los soportes de las escaleras.
    float altura_Barandal_Escaleras = 150.0f;           // altura de los soportes de las escaleras.

    float ancho_Escalones = 40.0f;           // ancho de los escalones.
    float altura_Escalones = 10.0f;           // altura de los escalones.

    // Sección 1. -------------*

    //======================================================================
    //PLATAFORMA 1
    //======================================================================
    float posicion_Plataforma_S1 = imageSize.y - 200.0f;
    ObjetoRectangulo Plataforma1_1(anchoP, alturaP, 100.0f, posicion_Plataforma_S1);
    ObjetoRectangulo Plataforma1_2(anchoP, alturaP, 500.0f, posicion_Plataforma_S1);
    ObjetoRectangulo Plataforma1_3(anchoP, alturaP, 900.0f, posicion_Plataforma_S1);

    //Plataforma superior
    float posicion_Plataforma_Superior = imageSize.y - 430.0f;
    float anchoP_Superior = 600.0f;           // Variable local para ancho de plataforma.
    float alturaP_Superior = 20.0f;           // Variable local para altura de plataforma.
    ObjetoRectangulo Plataforma1_4(anchoP_Superior, alturaP_Superior, 500.0f, posicion_Plataforma_Superior);

    //======================================================================
    //ESCALERA 1
    //======================================================================
    float posicionS1 = imageSize.y - 200.0f;
    ObjetoRectangulo Barandal_1(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 100.0f, posicionS1);
    ObjetoRectangulo Barandal_2(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 140.0f, posicionS1);

    float posicionS1_1 = imageSize.y - 90.0f;
    ObjetoRectangulo Escalon_1_1(ancho_Escalones, altura_Escalones, 100.0f, posicionS1_1);

    float posicionS1_2 = imageSize.y - 130.0f;
    ObjetoRectangulo Escalon_2_1(ancho_Escalones, altura_Escalones, 100.0f, posicionS1_2);

    float posicionS1_3 = imageSize.y - 170.0f;
    ObjetoRectangulo Escalon_3_1(ancho_Escalones, altura_Escalones, 100.0f, posicionS1_3);

    // Sección 2. --------------*

    //======================================================================
    //ESCALERA 2
    //======================================================================
    float posicionS2 = imageSize.y - 200.0f;
    ObjetoRectangulo Barandal_3(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 500.0f, posicionS2);
    ObjetoRectangulo Barandal_4(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 540.0f, posicionS2);

    float posicionS2_1 = imageSize.y - 90.0f;
    ObjetoRectangulo Escalon1_2(ancho_Escalones, altura_Escalones, 500.0f, posicionS2_1);

    float posicionS2_2 = imageSize.y - 130.0f;
    ObjetoRectangulo Escalon2_2(ancho_Escalones, altura_Escalones, 500.0f, posicionS2_2);
    
    float posicionS2_3 = imageSize.y - 170.0f;
    ObjetoRectangulo Escalon3_2(ancho_Escalones, altura_Escalones, 500.0f, posicionS2_3);

    // Sección 3. --------------*

    //======================================================================
    //ESCALERA 3
    //======================================================================
    float posicionS3 = imageSize.y - 200.0f;

    ObjetoRectangulo Barandal_5(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 900.0f, posicionS3);
    ObjetoRectangulo Barandal_6(ancho_Barandal_Escaleras, altura_Barandal_Escaleras, 940.0f, posicionS3);

    float posicionS3_1 = imageSize.y - 90.0f;
    ObjetoRectangulo Escalon1_3(ancho_Escalones, altura_Escalones, 900.0f, posicionS3_1);

    float posicionS3_2 = imageSize.y - 130.0f;
    ObjetoRectangulo Escalon2_3(ancho_Escalones, altura_Escalones, 900.0f, posicionS3_2);
    
    float posicionS3_3 = imageSize.y - 170.0f;
    ObjetoRectangulo Escalon3_3(ancho_Escalones, altura_Escalones, 900.0f, posicionS3_3);


    //=======================================================================
    //ESCALERA 4
    //=======================================================================
    float ancho_Barandal_Escaleras2 = 10.0f;           // Variable local para ancho de plataforma.
    float altura_Barandal_Escaleras2 = 220.0f;           // Variable local para altura de plataforma.
    float posicionS4 = imageSize.y - 420.0f;

    ObjetoRectangulo Barandal_7(ancho_Barandal_Escaleras2, altura_Barandal_Escaleras2, 990.0f, posicionS4);
    ObjetoRectangulo Barandal_8(ancho_Barandal_Escaleras2, altura_Barandal_Escaleras2, 1030.0f, posicionS4);

    float posicionS4_1 = imageSize.y - 260.0f;
    ObjetoRectangulo Escalon1_4(ancho_Escalones, altura_Escalones, 990.0f, posicionS4_1);

    float posicionS4_2 = imageSize.y - 300.0f;
    ObjetoRectangulo Escalon2_4(ancho_Escalones, altura_Escalones, 990.0f, posicionS4_2);
    
    float posicionS4_3 = imageSize.y - 350.0f;
    ObjetoRectangulo Escalon3_4(ancho_Escalones, altura_Escalones, 990.0f, posicionS4_3);


    // ========================================================================
    // Vectores para agrupar las plataformas
    // ========================================================================
    vector<ObjetoRectangulo*> todosBarandales = {&Barandal_1, &Barandal_2, &Barandal_3, &Barandal_4, &Barandal_5, &Barandal_6, &Barandal_7, &Barandal_8};

    vector<ObjetoRectangulo*> todosEscalones = {&Escalon_1_1, &Escalon_2_1, &Escalon_3_1, &Escalon1_2, &Escalon2_2, &Escalon3_2, &Escalon1_3, &Escalon2_3, &Escalon3_3, &Escalon1_4, &Escalon2_4, &Escalon3_4};
    
    vector<ObjetoRectangulo*> todasPlataformas = {&Plataforma1_1, &Plataforma1_2, &Plataforma1_3, &Plataforma1_4};
    
    vector<ObjetoRectangulo*> todosLosObjetos = {

        &Barandal_1, &Barandal_2, &Barandal_3, &Barandal_4, &Barandal_5, &Barandal_6,
        &Escalon_1_1, &Escalon_2_1, &Escalon_3_1, &Escalon1_2, &Escalon2_2, &Escalon3_2, 
        &Escalon1_3, &Escalon2_3, &Escalon3_3, &Escalon1_4, &Escalon2_4, &Escalon3_4, &Plataforma1_1, &Plataforma1_2, &Plataforma1_3, &Plataforma1_4
    };

    //  CREAR ENEMIGOS
    vector<Enemigo> enemigos;
    enemigos.emplace_back(150.0f, 470.0f);
    enemigos.emplace_back(550.0f, 470.0f);  
    enemigos.emplace_back(950.0f, 220.0f);
    
    // Aplicar textura
    if (tieneTexturaEnemigo) {
        for (auto& enemigo : enemigos) {
            enemigo.configurarTextura(enemyTexture);
        }
    }
    
    cout << "👾 " << enemigos.size() << " enemigos creados" << endl;
    
    // Variables del juego
    bool jugadorVivo = true;
    int puntuacion = 0;
    Clock clock;
    
    // ========================== BUCLE PRINCIPAL =============================
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Procesar eventos
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
        
        if (!jugadorVivo) continue;
        
        // ========================= ACTUALIZAR JUEGO =========================
        
        // Jugador
        jugador.manejarEntrada();
        jugador.manejarSalto();
        jugador.actualizar(deltaTime);
        
        //  ACTUALIZAR ENEMIGOS
        for (auto& enemigo : enemigos) {
            if (enemigo.estaVivo()) {
                enemigo.actualizar(deltaTime);
            }
        }
        
        // ===================== DETECCIÓN DE COLISIONES ======================
        
        // OBTENER POSICIÓN DEL JUGADOR UNA SOLA VEZ
        Vector2f posJugador = jugador.obtenerPosicion();
        
        // Colisión con suelo
        float nivelSuelo = imageSize.y - 50.0f - playerSize.y;
        if (jugador.verificarColisionConSuelo(nivelSuelo)) {
            jugador.resolverColisionSuelo(nivelSuelo);
        } else {
            jugador.establecerEnSuelo(false);
        }
        
        // COLISIÓN CON PLATAFORMAS USANDO LA FUNCIÓN
        bool enPlataforma = verificarColisiones(jugador, todosLosObjetos);

        jugador.establecerEnPlataforma(enPlataforma);
        
        // COLISIÓN CON ENEMIGOS
        for (auto& enemigo : enemigos) {
            if (!enemigo.estaVivo()) continue;
            
            sf::Vector2f posEnemigo = enemigo.getPosicion();
            
            // Detección MANUAL
            bool hayColision = (posJugador.x < posEnemigo.x + 50.0f) &&
                               (posJugador.x + playerSize.x > posEnemigo.x) &&
                               (posJugador.y < posEnemigo.y + 50.0f) &&
                               (posJugador.y + playerSize.y > posEnemigo.y);
            
            if (hayColision) {
                bool jugadorPorEncima = (posJugador.y + playerSize.y) < (posEnemigo.y + 25.0f);
                
                if (jugadorPorEncima) {
                    enemigo.matar();
                    puntuacion += 100;
                    cout << "👾 Enemigo eliminado! Puntuación: " << puntuacion << endl;
                    jugador.establecerVelocidadY(-300.0f);
                } else {
                    jugadorVivo = false;
                    cout << "💀 El jugador ha muerto! Puntuación final: " << puntuacion << endl;
                }
            }
        }
        
        // Límites de pantalla - USAR LA MISMA posJugador
        if (posJugador.x < 0) {
            jugador.establecerPosicion(Vector2f(0, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        if (posJugador.x + playerSize.x > imageSize.x) {
            jugador.establecerPosicion(Vector2f(imageSize.x - playerSize.x, posJugador.y));
            jugador.establecerVelocidadX(0);
        }
        
        // ===================== ACTUALIZAR GRÁFICOS =====================
        playerSprite.setPosition(posJugador);
        
        // Rotación del sprite -----------------------*
        Vector2f velocidad = jugador.obtenerVelocidad();
        if (velocidad.x > 0.1f) {
            playerSprite.setScale({1.0f, 1.0f});
        } else if (velocidad.x < -0.1f) {
            playerSprite.setScale({-1.0f, 1.0f});
        }
        
        // ============================ RENDERIZADO ===========================
        // ====================================================================
        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(ground);

        // Dibujar barandal de escaleras en pantalla.
        //Escalera 1
        Barandal_1.dibujar(window);
        Barandal_2.dibujar(window);

        Escalon_1_1.dibujar(window);
        Escalon_2_1.dibujar(window);
        Escalon_3_1.dibujar(window);
        
        //Escalera 2
        Barandal_3.dibujar(window);
        Barandal_4.dibujar(window);

        Escalon1_2.dibujar(window);
        Escalon2_2.dibujar(window);
        Escalon3_2.dibujar(window);

        //Escalera 3
        Barandal_5.dibujar(window);
        Barandal_6.dibujar(window);

        Escalon1_3.dibujar(window); 
        Escalon2_3.dibujar(window);
        Escalon3_3.dibujar(window);

        //Escalera 4
        Barandal_7.dibujar(window);
        Barandal_8.dibujar(window);

        Escalon1_4.dibujar(window);
        Escalon2_4.dibujar(window);
        Escalon3_4.dibujar(window);

        // Dibujar plataformas en pantalla.
        Plataforma1_1.dibujar(window);
        Plataforma1_2.dibujar(window);
        Plataforma1_3.dibujar(window);
        Plataforma1_4.dibujar(window);

        // ✅ DIBUJAR ENEMIGOS
        for (auto& enemigo : enemigos) {
            enemigo.dibujar(window);
        }
        
        window.draw(playerSprite);
        window.display();
        
    }

    return 0;
}