#include "Arista.h"
#include <cmath>
#include <iostream>

Arista::Arista(int id, Nodo* nodoOrigen, Nodo* nodoDestino, float peso, bool dirigido)
    : id(id), nodoOrigen(nodoOrigen), nodoDestino(nodoDestino),
    pesoOriginal(peso), pesoActual(peso), nivelTrafico(1),
    esDirigido(dirigido), color(sf::Color::Blue) {

    std::cout << "Arista creada: " << id << " (Origen: " << nodoOrigen->id
        << ", Destino: " << nodoDestino->id << ")" << std::endl;
}

void Arista::actualizarTrafico(int nuevoNivel) {
    nivelTrafico = nuevoNivel;
    pesoActual = pesoOriginal * nivelTrafico;
    std::cout << "Tráfico actualizado en arista " << id << ": Nivel " << nuevoNivel
        << " (Peso actual: " << pesoActual << ")" << std::endl;
}

void Arista::dibujar(sf::RenderWindow& ventana) {
    // Hacer las líneas más gruesas
    sf::RectangleShape linea;
    sf::Vector2f direccion = nodoDestino->posicion - nodoOrigen->posicion;
    float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
    float angulo = std::atan2(direccion.y, direccion.x) * 180 / 3.14159f;

    linea.setSize(sf::Vector2f(longitud, 3.0f)); // Línea más gruesa (3 píxeles)
    linea.setPosition(nodoOrigen->posicion);
    linea.setRotation(angulo);
    linea.setFillColor(color);
    ventana.draw(linea);

    // Dibujar el peso de la arista
    sf::Text textoDistancia;
    sf::Font font;
    if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        textoDistancia.setFont(font);
        textoDistancia.setString(std::to_string((int)pesoActual));
        textoDistancia.setCharacterSize(15);
        textoDistancia.setFillColor(color);

        // Posicionar el texto en el punto medio de la arista
        sf::Vector2f puntoMedio = nodoOrigen->posicion + direccion * 0.5f;
        textoDistancia.setPosition(puntoMedio);
        ventana.draw(textoDistancia);
    }

    if (esDirigido) {
        // Flecha más grande y visible
        sf::Vector2f puntoMedio = nodoOrigen->posicion + direccion * 0.8f;

        sf::ConvexShape flecha;
        flecha.setPointCount(3);
        flecha.setPoint(0, sf::Vector2f(0, 0));
        flecha.setPoint(1, sf::Vector2f(-15, -8)); // Flecha más grande
        flecha.setPoint(2, sf::Vector2f(-15, 8));  // Flecha más grande
        flecha.setFillColor(color);
        flecha.setPosition(puntoMedio);
        flecha.setRotation(angulo);

        ventana.draw(flecha);
    }
}

void Arista::resaltar(bool activo) {
    if (activo) {
        color = sf::Color::Yellow;
        std::cout << "Arista " << id << " resaltada" << std::endl;
    }
    else {
        color = sf::Color::Red;
        std::cout << "Arista " << id << " no resaltada" << std::endl;
    }
}