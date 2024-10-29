#include "Arista.h"
#include <cmath>

Arista::Arista(int id, Nodo* nodoOrigen, Nodo* nodoDestino, float peso, bool dirigido)
    : id(id), nodoOrigen(nodoOrigen), nodoDestino(nodoDestino),
    pesoOriginal(peso), pesoActual(peso), nivelTrafico(1),
    esDirigido(dirigido), color(sf::Color::White) {}

void Arista::actualizarTrafico(int nuevoNivel) {
    nivelTrafico = nuevoNivel;
    pesoActual = pesoOriginal * nivelTrafico;
}

void Arista::dibujar(sf::RenderWindow& ventana) {
    sf::Vertex line[] = {
        sf::Vertex(nodoOrigen->posicion, color),
        sf::Vertex(nodoDestino->posicion, color)
    };
    ventana.draw(line, 2, sf::Lines);

    if (esDirigido) {
        // Calcular punto medio y dirección para la flecha
        sf::Vector2f direccion = nodoDestino->posicion - nodoOrigen->posicion;
        float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        direccion /= longitud;

        sf::Vector2f puntoMedio = nodoOrigen->posicion + direccion * (longitud * 0.8f);

        // Dibujar flecha
        sf::ConvexShape flecha;
        flecha.setPointCount(3);
        flecha.setPoint(0, puntoMedio);
        flecha.setPoint(1, puntoMedio + sf::Vector2f(-10, -10));
        flecha.setPoint(2, puntoMedio + sf::Vector2f(-10, 10));
        flecha.setFillColor(color);

        float angulo = atan2(direccion.y, direccion.x) * 180 / 3.14159f;
        flecha.setRotation(angulo);

        ventana.draw(flecha);
    }
}

void Arista::resaltar(bool activo) {
    color = activo ? sf::Color::Yellow : sf::Color::White;
}