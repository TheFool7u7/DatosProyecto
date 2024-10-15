#ifndef GRAFO_H
#define GRAFO_H

#include <SFML/Graphics.hpp>
#include "Nodo.h"
#include "Arista.h"

class Grafo {
public:
    std::vector<Nodo*> nodos;
    std::vector<Arista*> aristas;

    void agregarNodo(Nodo* nodo);
    void agregarArista(Arista* arista);
    void dibujar(sf::RenderWindow& ventana);
};

#endif // GRAFO_H