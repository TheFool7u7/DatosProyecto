#include "Simulacion.h"

Simulacion::Simulacion() : ventana(sf::VideoMode(800, 600), "Simulación de Grafo") {}

void Simulacion::inicializar() {
    // Inicializa el grafo
    Nodo* nodo1 = new Nodo(1, sf::Vector2f(100, 100));
    Nodo* nodo2 = new Nodo(2, sf::Vector2f(300, 300));
    Nodo* nodo3 = new Nodo(3, sf::Vector2f(500, 500));

    Arista* arista1 = new Arista(1, nodo1, nodo2, 10.0f);
    Arista* arista2 = new Arista(2, nodo2, nodo3, 20.0f);
    Arista* arista3 = new Arista(3, nodo3, nodo1, 30.0f);

    grafo.agregarNodo(nodo1);
    grafo.agregarNodo(nodo2);
    grafo.agregarNodo(nodo3);

    grafo.agregarArista(arista1);
    grafo.agregarArista(arista2);
    grafo.agregarArista(arista3);
}

void Simulacion::actualizar() {
    // Actualiza el estado del grafo
}

void Simulacion::dibujar() {
    ventana.clear();
    grafo.dibujar(ventana);
    ventana.display();
}