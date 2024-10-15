#ifndef SIMULACION_H
#define SIMULACION_H

#include <SFML/Graphics.hpp>
#include "Grafo.h"

class Simulacion {
public:
    Grafo grafo;
    sf::RenderWindow ventana;

    Simulacion();
    void inicializar();
    void actualizar();
    void dibujar();
};

#endif // SIMULACION_H