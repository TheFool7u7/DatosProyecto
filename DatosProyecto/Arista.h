#pragma once
#include <SFML/Graphics.hpp>
#include "Nodo.h"

class Arista {
public:
    int id;
    Nodo* nodoOrigen;
    Nodo* nodoDestino;
    float pesoOriginal;
    float pesoActual;
    int nivelTrafico;
    bool esDirigido;
    sf::Color color;

    Arista(int id, Nodo* nodoOrigen, Nodo* nodoDestino, float peso, bool dirigido = false);
    void actualizarTrafico(int nuevoNivel);
    void dibujar(sf::RenderWindow& ventana);
    void resaltar(bool activo);
};