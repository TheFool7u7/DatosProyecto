#include "Nodo.h"

Nodo::Nodo(int id, sf::Vector2f posicion) : id(id), posicion(posicion) {}

void Nodo::dibujar(sf::RenderWindow& ventana) {
    sf::CircleShape circulo(10);
    circulo.setFillColor(sf::Color::Red);
    circulo.setPosition(posicion);
    ventana.draw(circulo);
}