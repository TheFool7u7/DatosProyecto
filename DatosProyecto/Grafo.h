#pragma once
#include <vector>
#include <queue>
#include <map>
#include "Nodo.h"
#include "Arista.h"
#include <SFML/Graphics.hpp>

class Grafo {
private:
    std::vector<Nodo*> nodos;
    std::vector<Arista*> aristas;
    std::vector<Nodo*> rutaActual;
    std::vector<Nodo*> rutaOriginal;

public:
    void agregarNodo(Nodo* nodo);
    void agregarArista(Arista* arista);
    void dibujar(sf::RenderWindow& ventana);  // Asegúrate de que esta declaración esté presente
    std::vector<std::vector<float>> floydWarshall();
    std::vector<Nodo*> encontrarRuta(Nodo* inicio, Nodo* fin);
    void actualizarPesos();
    float calcularCostoRuta(const std::vector<Nodo*>& ruta);
    Nodo* encontrarNodoCercano(sf::Vector2f posicion);
    void resaltarRuta(const std::vector<Nodo*>& ruta);
    ~Grafo();
};