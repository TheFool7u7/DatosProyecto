#pragma once
#include <SFML/Graphics.hpp>
#include "Grafo.h"
#include "Vehiculo.h"

class Simulacion {
private:
    sf::RenderWindow ventana;
    Grafo grafo;
    Vehiculo* vehiculo;
    bool rutaSeleccionada;
    Nodo* nodoInicio;
    Nodo* nodoFin;
    sf::Clock reloj;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    bool mostrarMenuAlgoritmo;
    sf::Font fuente;
    sf::RectangleShape botonDijkstra;
    sf::RectangleShape botonFloyd;
    sf::Text textoDijkstra;
    sf::Text textoFloyd;
    sf::Text tituloMenu;
    bool algoritmoSeleccionado;
    bool usarDijkstra; // true para Dijkstra, false para Floyd

    void inicializarMenu();
    void dibujarMenu();
    bool checkBotonClick(const sf::RectangleShape& boton, sf::Vector2i posicionMouse);


    void manejarSeleccionNodos(const sf::Event::MouseButtonEvent& mouseEvento);

public:
    Simulacion();
    void inicializar();
    void manejarEventos();
    void actualizar();
    void dibujar();
    bool estaAbierta() const { return ventana.isOpen(); } // Método nuevo
    void cerrarVentana() { ventana.close(); }            // Método nuevo
    ~Simulacion();
    void manejarClick(const sf::Event::MouseButtonEvent& mouseEvent);
    void calcularRuta();
};