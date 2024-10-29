#include "Grafo.h"
#include <limits>
#include <algorithm>
#include <iostream>

void Grafo::agregarNodo(Nodo* nodo) {
    nodos.push_back(nodo);
}

void Grafo::agregarArista(Arista* arista) {
    aristas.push_back(arista);
}

std::vector<Nodo*> Grafo::encontrarRuta(Nodo* inicio, Nodo* fin) {
    std::map<Nodo*, float> distancias;
    std::map<Nodo*, Nodo*> previos;
    std::priority_queue<std::pair<float, Nodo*>> cola;

    for (Nodo* nodo : nodos) {
        distancias[nodo] = std::numeric_limits<float>::infinity();
    }

    distancias[inicio] = 0.0f;
    cola.push(std::make_pair(0.0f, inicio));

    while (!cola.empty()) {
        Nodo* nodoActual = cola.top().second;
        cola.pop();

        if (nodoActual == fin) break;

        for (Arista* arista : aristas) {
            if (arista->nodoOrigen == nodoActual) {
                Nodo* nodoVecino = arista->nodoDestino;
                float distancia = distancias[nodoActual] + arista->pesoActual;

                if (distancia < distancias[nodoVecino]) {
                    distancias[nodoVecino] = distancia;
                    previos[nodoVecino] = nodoActual;
                    cola.push(std::make_pair(distancia, nodoVecino));
                }
            }
        }
    }

    std::vector<Nodo*> ruta;
    Nodo* nodoActual = fin;

    while (nodoActual != inicio) {
        ruta.push_back(nodoActual);
        nodoActual = previos[nodoActual];
    }

    ruta.push_back(inicio);
    std::reverse(ruta.begin(), ruta.end());

    return ruta;
}

void Grafo::actualizarPesos() {
    for (Arista* arista : aristas) {
        // Actualizar pesos aleatoriamente o según condiciones
        int nuevoNivelTrafico = rand() % 3 + 1;
        arista->actualizarTrafico(nuevoNivelTrafico);
    }
}

float Grafo::calcularCostoRuta(const std::vector<Nodo*>& ruta) {
    float costo = 0.0f;

    for (size_t i = 0; i < ruta.size() - 1; i++) {
        // Encontrar arista entre nodos consecutivos
        // Sumar su peso al costo total
    }

    return costo;
}

Nodo* Grafo::encontrarNodoCercano(sf::Vector2f posicion) {
    Nodo* nodoCercano = nullptr;
    float distanciaMinima = 20.0f; // Radio de detección en píxeles

    std::cout << "Buscando nodo cercano a posición: " << posicion.x << "," << posicion.y << std::endl;

    for (Nodo* nodo : nodos) {
        float distancia = std::sqrt(
            std::pow(nodo->posicion.x - posicion.x, 2) +
            std::pow(nodo->posicion.y - posicion.y, 2)
        );

        std::cout << "Nodo " << nodo->id << " a distancia " << distancia << std::endl;

        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            nodoCercano = nodo;
        }
    }

    if (nodoCercano) {
        std::cout << "Nodo más cercano encontrado: " << nodoCercano->id << std::endl;
    }
    else {
        std::cout << "No se encontró ningún nodo cercano" << std::endl;
    }

    return nodoCercano;
}

void Grafo::resaltarRuta(const std::vector<Nodo*>& ruta) {
    for (Arista* arista : aristas) {
        bool rutaActual = false;

        for (size_t i = 0; i < ruta.size() - 1; i++) {
            if (arista->nodoOrigen == ruta[i] && arista->nodoDestino == ruta[i + 1]) {
                rutaActual = true;
                break;
            }
        }

        arista->resaltar(rutaActual);
    }
}

Grafo::~Grafo() {
    for (Nodo* nodo : nodos) {
        delete nodo;
    }

    for (Arista* arista : aristas) {
        delete arista;
    }
}

void Grafo::dibujar(sf::RenderWindow& ventana) {
    // Primero dibujamos las aristas
    for (Arista* arista : aristas) {
        arista->dibujar(ventana);
    }

    // Luego dibujamos los nodos (para que aparezcan encima de las aristas)
    for (Nodo* nodo : nodos) {
        nodo->dibujar(ventana);
    }
}

std::vector<std::vector<float>> Grafo::floydWarshall() {
    int n = nodos.size();
    std::vector<std::vector<float>> dist(n, std::vector<float>(n, std::numeric_limits<float>::infinity()));

    // Inicializar distancias
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (Arista* arista : aristas) {
        int origen = arista->nodoOrigen->id - 1;
        int destino = arista->nodoDestino->id - 1;
        dist[origen][destino] = arista->pesoOriginal; // O pesoActual si deseas usar el peso actualizado
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}