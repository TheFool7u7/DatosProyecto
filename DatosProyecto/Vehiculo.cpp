#include "Vehiculo.h"
#include <cmath>
#include <iostream>

Vehiculo::Vehiculo() : nodoActual(0), velocidad(50.0f), progreso(0.0f) {
    std::cout << "Vehículo creado con velocidad: " << velocidad << std::endl;
}

void Vehiculo::cargarTextura(const std::string& rutaArchivo) {
    if (!textura.loadFromFile(rutaArchivo)) {
        std::cout << "Error al cargar la textura del vehículo!" << std::endl;
        return;
    }

    sprite.setTexture(textura);

    // Ajustar el origen al centro del sprite
    sprite.setOrigin(textura.getSize().x / 2.0f, textura.getSize().y / 2.0f);

    // Ajustar el tamaño del sprite (prueba diferentes valores)
    sprite.setScale(0.05f, 0.05f);  // Hace el sprite más pequeño

    // Color visible para asegurar que se está dibujando
    sprite.setColor(sf::Color::White);

    std::cout << "Textura cargada exitosamente. Tamaño original: "
        << textura.getSize().x << "x" << textura.getSize().y << std::endl;
}

void Vehiculo::setRuta(const std::vector<Nodo*>& nuevaRuta) {
    ruta = nuevaRuta;
    nodoActual = 0;
    progreso = 0.0f;

    if (!ruta.empty()) {
        sprite.setPosition(ruta[0]->posicion);
        std::cout << "Ruta establecida con " << ruta.size() << " nodos" << std::endl;
        std::cout << "Vehículo colocado en posición inicial: ("
            << ruta[0]->posicion.x << "," << ruta[0]->posicion.y << ")" << std::endl;
    }
}

void Vehiculo::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
    std::cout << "Vehículo posicionado en: (" << pos.x << "," << pos.y << ")" << std::endl;
}

void Vehiculo::actualizar(float deltaTime) {
    if (ruta.empty()) {
        std::cout << "Ruta vacía" << std::endl;
        return;
    }

    if (nodoActual >= ruta.size() - 1) {
        std::cout << "Fin de la ruta alcanzado" << std::endl;
        return;
    }

    sf::Vector2f posActual = ruta[nodoActual]->posicion;
    sf::Vector2f posSiguiente = ruta[nodoActual + 1]->posicion;

    // Calcular dirección
    sf::Vector2f direccion = posSiguiente - posActual;
    float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

    std::cout << "Moviendo de nodo " << nodoActual << " a nodo " << (nodoActual + 1)
        << " Progreso: " << progreso << std::endl;

    if (distancia > 0) {
        direccion /= distancia;

        // Actualizar progreso
        progreso += (velocidad * deltaTime) / distancia;

        if (progreso >= 1.0f) {
            nodoActual++;
            progreso = 0.0f;
            std::cout << "Avanzando al siguiente nodo: " << nodoActual << std::endl;
            return;
        }

        // Calcular nueva posición
        sf::Vector2f nuevaPosicion = posActual + (direccion * distancia * progreso);
        sprite.setPosition(nuevaPosicion);

        // Rotar el sprite
        float angulo = std::atan2(direccion.y, direccion.x) * 180 / 3.14159f;
        sprite.setRotation(angulo);
    }
}

void Vehiculo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

bool Vehiculo::haLlegadoAlDestino() const {
    return nodoActual >= ruta.size() - 1;
}