#include "Nodo.h"
#include <iostream>

Nodo::Nodo(int id, sf::Vector2f posicion) : id(id), posicion(posicion) {
    forma.setRadius(10.0f);  // Radio más grande para ser más visible
    forma.setFillColor(sf::Color::Red);  // Color sólido
    forma.setPosition(posicion.x - 10.0f, posicion.y - 10.0f);  // Centrar la forma
    std::cout << "Nodo " << id << " creado en posición " << posicion.x << "," << posicion.y << std::endl;
}

void Nodo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(forma);
}