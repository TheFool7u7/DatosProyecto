#include "Grafo.h"

void Grafo::agregarNodo(Nodo* nodo) {
    nodos.push_back(nodo);
}

void Grafo::agregarArista(Arista* arista) {
    aristas.push_back(arista);
}

void Grafo::dibujar(sf::RenderWindow& ventana) {
    for (Nodo* nodo : nodos) {
        nodo->dibujar(ventana);
    }
    for (Arista* arista : aristas) {
        arista->dibujar(ventana);
    }
}