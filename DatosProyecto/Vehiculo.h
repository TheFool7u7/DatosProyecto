#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Nodo.h"

class Vehiculo {
private:
    sf::Sprite sprite;
    sf::Texture textura;
    std::vector<Nodo*> ruta;
    size_t nodoActual;
    float velocidad;
    float progreso;

public:
    Vehiculo();
    void cargarTextura(const std::string& rutaArchivo);
    void setRuta(const std::vector<Nodo*>& nuevaRuta);
    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& ventana);
    bool haLlegadoAlDestino() const;
    void setPosition(sf::Vector2f pos);
};