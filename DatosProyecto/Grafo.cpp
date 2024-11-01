#include "Grafo.h"
#include <limits>
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <windows.h>
#include <iomanip>

void Grafo::agregarNodo(Nodo* nodo) {
    nodos.push_back(nodo);
    std::cout << "Nodo " << nodo->id << " agregado al grafo" << std::endl;
}

void Grafo::agregarArista(Arista* arista) {
    aristas.push_back(arista);
    std::cout << "Arista agregada: " << arista->nodoOrigen->id << " -> "
        << arista->nodoDestino->id << " (Peso: " << arista->pesoOriginal << ")" << std::endl;
}

void Grafo::actualizarPesos() {
    std::cout << "\n=== Actualizando pesos de las aristas ===" << std::endl;
    for (Arista* arista : aristas) {
        int nuevoNivelTrafico = rand() % 3 + 1;
        float pesoAnterior = arista->pesoActual;
        arista->actualizarTrafico(nuevoNivelTrafico);
        std::cout << "Arista " << arista->nodoOrigen->id << " -> " << arista->nodoDestino->id
            << ": " << pesoAnterior << " -> " << arista->pesoActual << std::endl;
    }
}

float Grafo::calcularCostoRuta(const std::vector<Nodo*>& ruta) {
    float costo = 0.0f;
    std::cout << "\n=== Calculando costo de la ruta ===" << std::endl;

    for (size_t i = 0; i < ruta.size() - 1; i++) {
        for (Arista* arista : aristas) {
            if (arista->nodoOrigen == ruta[i] && arista->nodoDestino == ruta[i + 1]) {
                costo += arista->pesoActual;
                std::cout << "Segmento " << ruta[i]->id << " -> " << ruta[i + 1]->id
                    << ": +" << arista->pesoActual << std::endl;
                break;
            }
        }
    }

    std::cout << "Costo total de la ruta: " << costo << std::endl;
    return costo;
}

void Grafo::resaltarRuta(const std::vector<Nodo*>& ruta) {
    std::cout << "\n=== Ruta encontrada ===" << std::endl;
    std::cout << "Secuencia de nodos: ";
    for (size_t i = 0; i < ruta.size(); i++) {
        std::cout << ruta[i]->id;
        if (i < ruta.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;

    // Resaltar las aristas de la ruta
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

    calcularCostoRuta(ruta);
}

std::vector<Nodo*> Grafo::dijkstra(Nodo* inicio, Nodo* fin) {
    std::cout << "\n=== Ejecutando algoritmo de Dijkstra ===" << std::endl;
    std::cout << "Buscando ruta del nodo " << inicio->id << " al nodo " << fin->id << std::endl;

    std::map<Nodo*, float> distancias;
    std::map<Nodo*, Nodo*> previos;
    std::set<std::pair<float, Nodo*>> cola;

    // Inicialización
    for (Nodo* nodo : nodos) {
        distancias[nodo] = std::numeric_limits<float>::infinity();
        previos[nodo] = nullptr;
    }
    distancias[inicio] = 0;
    cola.insert({ 0, inicio });

    // Algoritmo principal
    while (!cola.empty()) {
        Nodo* actual = cola.begin()->second;
        cola.erase(cola.begin());

        if (actual == fin) break;

        for (Arista* arista : aristas) {
            if (arista->nodoOrigen == actual) {
                Nodo* vecino = arista->nodoDestino;
                float nuevaDistancia = distancias[actual] + arista->pesoActual;

                if (nuevaDistancia < distancias[vecino]) {
                    cola.erase({ distancias[vecino], vecino });
                    distancias[vecino] = nuevaDistancia;
                    previos[vecino] = actual;
                    cola.insert({ nuevaDistancia, vecino });

                    std::cout << "Actualizando distancia a nodo " << vecino->id
                        << ": " << nuevaDistancia << std::endl;
                }
            }
        }
    }

    // Reconstruir ruta
    std::vector<Nodo*> ruta;
    for (Nodo* actual = fin; actual != nullptr; actual = previos[actual]) {
        ruta.push_back(actual);
    }
    std::reverse(ruta.begin(), ruta.end());

    if (!ruta.empty()) {
        std::cout << "Ruta encontrada exitosamente" << std::endl;
    }
    else {
        std::cout << "No se encontró una ruta válida" << std::endl;
    }

    return ruta;
}

std::vector<Nodo*> Grafo::floydWarshall(Nodo* inicio, Nodo* fin) {
    std::cout << "\n=== Ejecutando algoritmo de Floyd-Warshall ===" << std::endl;
    std::cout << "Buscando ruta del nodo " << inicio->id << " al nodo " << fin->id << std::endl;

    inicializarMatrizAdyacencia();
    int n = nodos.size();

    // Mostrar matriz inicial
    std::cout << "\nMatriz de distancias inicial:" << std::endl;
    Grafo::mostrarMatriz(matrizAdyacencia);

    // Algoritmo principal
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrizAdyacencia[i][k] != std::numeric_limits<float>::infinity() &&
                    matrizAdyacencia[k][j] != std::numeric_limits<float>::infinity()) {
                    float nuevaDistancia = matrizAdyacencia[i][k] + matrizAdyacencia[k][j];
                    if (nuevaDistancia < matrizAdyacencia[i][j]) {
                        matrizAdyacencia[i][j] = nuevaDistancia;
                        siguienteNodo[i][j] = siguienteNodo[i][k];
                    }
                }
            }
        }
    }

    // Mostrar matriz final
    std::cout << "\nMatriz de distancias final:" << std::endl;
    Grafo::mostrarMatriz(matrizAdyacencia);

    // Reconstruir ruta
    std::vector <Nodo*> ruta;
    int inicio_idx = std::find(nodos.begin(), nodos.end(), inicio) - nodos.begin();
    int fin_idx = std::find(nodos.begin(), nodos.end(), fin) - nodos.begin();

    if (siguienteNodo[inicio_idx][fin_idx] == -1) {
        std::cout << "No se encontró una ruta válida" << std::endl;
        return ruta;
    }

    ruta.push_back(inicio);
    for (int actual = inicio_idx; actual != fin_idx; actual = siguienteNodo[actual][fin_idx]) {
        ruta.push_back(nodos[siguienteNodo[actual][fin_idx]]);
    }

    return ruta;
}

void Grafo::inicializarMatrizAdyacencia() {
    int n = nodos.size();
    matrizAdyacencia.resize(n, std::vector<float>(n, std::numeric_limits<float>::infinity()));
    siguienteNodo.resize(n, std::vector<int>(n, -1));

    // Inicializar diagonal
    for (int i = 0; i < n; i++) {
        matrizAdyacencia[i][i] = 0;
    }

    // Llenar matriz con aristas existentes
    for (Arista* arista : aristas) {
        int i = std::find(nodos.begin(), nodos.end(), arista->nodoOrigen) - nodos.begin();
        int j = std::find(nodos.begin(), nodos.end(), arista->nodoDestino) - nodos.begin();
        matrizAdyacencia[i][j] = arista->pesoActual;
        siguienteNodo[i][j] = j;

        if (!arista->esDirigido) {
            matrizAdyacencia[j][i] = arista->pesoActual;
            siguienteNodo[j][i] = i;
        }
    }
}

void Grafo::mostrarMatriz(const std::vector<std::vector<float>>& matriz) {
    int n = matriz.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == std::numeric_limits<float>::infinity()) {
                std::cout << "INF ";
            }
            else {
                std::cout << std::setw(4) << matriz[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Grafo::dibujar(sf::RenderWindow& ventana) {
    // Primero dibujamos las aristas
    for (Arista* arista : aristas) {
        arista->dibujar(ventana);
    }

    // Luego dibujamos los nodos
    for (Nodo* nodo : nodos) {
        nodo->dibujar(ventana);
    }
}

std::vector<Nodo*> Grafo::encontrarRuta(Nodo* inicio, Nodo* fin) {
    if (usarDijkstra) {
        return dijkstra(inicio, fin);
    }
    else {
        return floydWarshall(inicio, fin);
    }
}

Nodo* Grafo::encontrarNodoCercano(sf::Vector2f posicion) {
    const float RADIO_DETECCION = 30.0f; // Aumentamos el radio de detección
    Nodo* nodoCercano = nullptr;
    float distanciaMinima = RADIO_DETECCION;

    for (Nodo* nodo : nodos) {
        float distancia = std::sqrt(
            std::pow(nodo->posicion.x - posicion.x, 2) +
            std::pow(nodo->posicion.y - posicion.y, 2)
        );

        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            nodoCercano = nodo;
            std::cout << "Nodo encontrado: " << nodo->id << " a distancia: " << distancia << std::endl;
        }
    }

    return nodoCercano;
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
        dist[origen][destino] = arista->pesoActual;
        if (!arista->esDirigido) {
            dist[destino][origen] = arista->pesoActual;
        }
    }

    // Algoritmo Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != std::numeric_limits<float>::infinity() &&
                    dist[k][j] != std::numeric_limits<float>::infinity()) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}

Grafo::~Grafo() {
    // Liberar memoria de los nodos
    for (Nodo* nodo : nodos) {
        delete nodo;
    }
    nodos.clear();

    // Liberar memoria de las aristas
    for (Arista* arista : aristas) {
        delete arista;
    }
    aristas.clear();
}