#include "Arista.h"

Arista::Arista(int id, Nodo* nodoOrigen, Nodo* nodoDestino, float peso) : id(id), nodoOrigen(nodoOrigen), nodoDestino(nodoDestino), peso(peso) {}

void Arista::dibujar(sf::RenderWindow& ventana) {
    sf::Vertex linea[] = {
        sf::Vertex(nodoOrigen->posicion),
        sf::Vertex(nodoDestino->posicion)
    };
    ventana.draw(linea, 2, sf::Lines);
}