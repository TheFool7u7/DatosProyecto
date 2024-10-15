#ifndef ARISTA_H
#define ARISTA_H

#include <SFML/Graphics.hpp>
#include "Nodo.h"

class Arista {
public:
    int id;
    Nodo* nodoOrigen;
    Nodo* nodoDestino;
    float peso;

    Arista(int id, Nodo* nodoOrigen, Nodo* nodoDestino, float peso);
    void dibujar(sf::RenderWindow& ventana);
};

#endif // ARISTA_H