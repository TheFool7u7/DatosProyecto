#include "Nodo.h"
#include <iostream>

Nodo::Nodo(int id, sf::Vector2f posicion) : id(id), posicion(posicion) {
    forma.setRadius(10.0f);  // Radio m�s grande para ser m�s visible
    forma.setFillColor(sf::Color::Red);  // Color s�lido
    forma.setPosition(posicion.x - 10.0f, posicion.y - 10.0f);  // Centrar la forma
    std::cout << "Nodo " << id << " creado en posici�n " << posicion.x << "," << posicion.y << std::endl;
}

void Nodo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(forma);
}