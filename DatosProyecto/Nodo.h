#pragma once
#include <SFML/Graphics.hpp>

class Nodo {
public:
    int id;
    sf::Vector2f posicion;
    sf::CircleShape forma;

    Nodo(int id, sf::Vector2f posicion);
    void dibujar(sf::RenderWindow& ventana);
};