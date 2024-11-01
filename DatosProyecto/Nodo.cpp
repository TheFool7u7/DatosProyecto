#include "Nodo.h"
#include <iostream>

Nodo::Nodo(int id, sf::Vector2f posicion) : id(id), posicion(posicion) {
    forma.setRadius(10.0f);  // Radio más grande para ser más visible
    forma.setFillColor(sf::Color::Red);  // Color sólido
    forma.setPosition(posicion.x - 10.0f, posicion.y - 10.0f);  // Centrar la forma
    std::cout << "Nodo " << id << " creado en posición " << posicion.x << "," << posicion.y << std::endl;
}

void Nodo::dibujar(sf::RenderWindow& ventana) {
    sf::CircleShape circulo(10.0f); // Radio de 10 píxeles
    circulo.setPosition(posicion.x - 10.0f, posicion.y - 10.0f);
    circulo.setFillColor(sf::Color::Red);
    circulo.setOutlineThickness(2.0f);
    circulo.setOutlineColor(sf::Color::White);
    ventana.draw(circulo);

    // Dibujar el ID del nodo
    sf::Text texto;
    texto.setString(std::to_string(id));
    texto.setCharacterSize(20);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(posicion.x - 5.0f, posicion.y - 15.0f);
    ventana.draw(texto);
}