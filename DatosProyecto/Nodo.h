#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>

class Nodo {
public:
    int id;
    sf::Vector2f posicion;

    Nodo(int id, sf::Vector2f posicion);
    void dibujar(sf::RenderWindow& ventana);
};

#endif // NODO_H