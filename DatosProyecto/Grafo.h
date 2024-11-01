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
    std::vector<std::vector<float>> matrizAdyacencia;
    std::vector<std::vector<int>> siguienteNodo;
    bool usarDijkstra = true;  // Variable para controlar qué algoritmo usar

   

public:
    void agregarNodo(Nodo* nodo);
    void agregarArista(Arista* arista);
    void dibujar(sf::RenderWindow& ventana);
    std::vector<std::vector<float>> floydWarshall();
    std::vector<Nodo*> encontrarRuta(Nodo* inicio, Nodo* fin);
    void actualizarPesos();
    float calcularCostoRuta(const std::vector<Nodo*>& ruta);
    Nodo* encontrarNodoCercano(sf::Vector2f posicion);
    void resaltarRuta(const std::vector<Nodo*>& ruta);
    void inicializarMatrizAdyacencia();
    std::vector<Nodo*> dijkstra(Nodo* inicio, Nodo* fin);
    std::vector<Nodo*> floydWarshall(Nodo* inicio, Nodo* fin);
     void mostrarMatriz(const std::vector<std::vector<float>>& matriz);
    ~Grafo();
};