#include "Simulacion.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

Simulacion::Simulacion() :
    ventana(sf::VideoMode(663, 813), "Simulación de Grafo"),
    rutaSeleccionada(false),
    nodoInicio(nullptr),
    nodoFin(nullptr),
    mostrarMenuAlgoritmo(true),
    algoritmoSeleccionado(false),
    usarDijkstra(true)
{
    inicializarMenu();
    vehiculo = new Vehiculo();
}

void Simulacion::inicializarMenu() {
    // Cargar la fuente
    if (!fuente.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }

    // Configurar título
    tituloMenu.setFont(fuente);
    tituloMenu.setString("Seleccione el Algoritmo");
    tituloMenu.setCharacterSize(24);
    tituloMenu.setFillColor(sf::Color::White);
    tituloMenu.setPosition(200, 150);

    // Configurar botón Dijkstra
    botonDijkstra.setSize(sf::Vector2f(200, 50));
    botonDijkstra.setPosition(200, 250);
    botonDijkstra.setFillColor(sf::Color(100, 100, 100));

    textoDijkstra.setFont(fuente);
    textoDijkstra.setString("Dijkstra");
    textoDijkstra.setCharacterSize(20);
    textoDijkstra.setFillColor(sf::Color::White);
    textoDijkstra.setPosition(260, 265);

    // Configurar botón Floyd
    botonFloyd.setSize(sf::Vector2f(200, 50));
    botonFloyd.setPosition(200, 350);
    botonFloyd.setFillColor(sf::Color(100, 100, 100));

    textoFloyd.setFont(fuente);
    textoFloyd.setString("Floyd-Warshall");
    textoFloyd.setCharacterSize(20);
    textoFloyd.setFillColor(sf::Color::White);
    textoFloyd.setPosition(245, 365);
}

void Simulacion::dibujarMenu() {
    ventana.draw(tituloMenu);
    ventana.draw(botonDijkstra);
    ventana.draw(textoDijkstra);
    ventana.draw(botonFloyd);
    ventana.draw(textoFloyd);
}

bool Simulacion::checkBotonClick(const sf::RectangleShape& boton, sf::Vector2i posicionMouse) {
    sf::FloatRect bounds = boton.getGlobalBounds();
    return bounds.contains(static_cast<float>(posicionMouse.x), static_cast<float>(posicionMouse.y));
}

void Simulacion::manejarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
        }

        if (mostrarMenuAlgoritmo) {
            if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i posicionMouse = sf::Mouse::getPosition(ventana);

                    if (checkBotonClick(botonDijkstra, posicionMouse)) {
                        usarDijkstra = true;
                        mostrarMenuAlgoritmo = false;
                        algoritmoSeleccionado = true;
                    }
                    else if (checkBotonClick(botonFloyd, posicionMouse)) {
                        usarDijkstra = false;
                        mostrarMenuAlgoritmo = false;
                        algoritmoSeleccionado = true;
                    }
                }
            }
        }
        else {
            // Tu código existente para manejar clicks en nodos
            if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f posicionMouse(static_cast<float>(evento.mouseButton.x),
                        static_cast<float>(evento.mouseButton.y));

                    Nodo* nodoSeleccionado = grafo.encontrarNodoCercano(posicionMouse);
                    if (nodoSeleccionado) {
                        if (!nodoInicio) {
                            nodoInicio = nodoSeleccionado;
                        }
                        else if (!nodoFin) {
                            nodoFin = nodoSeleccionado;

                            // Usar el algoritmo seleccionado
                            std::vector<Nodo*> ruta;
                            if (usarDijkstra) {
                                ruta = grafo.encontrarRuta(nodoInicio, nodoFin);
                            }
                            else {
                                // Usar Floyd-Warshall
                                auto distancias = grafo.floydWarshall();
                                // Implementar la lógica para obtener la ruta usando Floyd
                                // Por ahora usamos Dijkstra como fallback
                                ruta = grafo.encontrarRuta(nodoInicio, nodoFin);
                            }

                            if (!ruta.empty()) {
                                vehiculo->setRuta(ruta);
                                rutaSeleccionada = true;
                            }

                            nodoInicio = nullptr;
                            nodoFin = nullptr;
                        }
                    }
                }
            }
        }
    }
}

void Simulacion::dibujar() {
    ventana.clear();

    if (mostrarMenuAlgoritmo) {
        dibujarMenu();
    }
    else {
        ventana.draw(spriteFondo);
        grafo.dibujar(ventana);
        if (vehiculo) {
            vehiculo->dibujar(ventana);
        }
    }

    ventana.display();
}

void Simulacion::inicializar() {
    if (!texturaFondo.loadFromFile("C:\\Users\\Usuario\\source\\repos\\DatosProyecto\\imagen1.png")) {
        // Manejar error si la imagen no se puede cargar
    }
    spriteFondo.setTexture(texturaFondo);

    // Ajustar el tamaño de la ventana al tamaño de la imagen
    sf::Vector2u tamanoTextura = texturaFondo.getSize();
    ventana.setSize(tamanoTextura);

    // Crear nodos en puntos específicos del camino rojo
    Nodo* nodo1 = new Nodo(1, sf::Vector2f(100, 200));  // Ajusta estas coordenadas
    Nodo* nodo2 = new Nodo(2, sf::Vector2f(200, 200));  // según la ubicación exacta
    Nodo* nodo3 = new Nodo(3, sf::Vector2f(300, 300));  // de tu línea roja
    Nodo* nodo4 = new Nodo(4, sf::Vector2f(400, 300));
    Nodo* nodo5 = new Nodo(5, sf::Vector2f(500, 200));
    // Añade más nodos según sea necesario

    std::cout << "Creando nodos en posiciones:" << std::endl;
    std::cout << "Nodo 1: " << nodo1->posicion.x << "," << nodo1->posicion.y << std::endl;
    std::cout << "Nodo 2: " << nodo2->posicion.x << "," << nodo2->posicion.y << std::endl;
    std::cout << "Nodo 3: " << nodo3->posicion.x << "," << nodo3->posicion.y << std::endl;
    std::cout << "Nodo 4: " << nodo4->posicion.x << "," << nodo4->posicion.y << std::endl;
    std::cout << "Nodo 5: " << nodo5->posicion.x << "," << nodo5->posicion.y << std::endl;

    // Agregar los nodos al grafo
    grafo.agregarNodo(nodo1);
    grafo.agregarNodo(nodo2);
    grafo.agregarNodo(nodo3);
    grafo.agregarNodo(nodo4);
    grafo.agregarNodo(nodo5);

    // Crear aristas que conecten los nodos siguiendo el camino rojo
    Arista* arista1 = new Arista(1, nodo1, nodo2, 1.0f);
    Arista* arista2 = new Arista(2, nodo2, nodo3, 1.0f);
    Arista* arista3 = new Arista(3, nodo3, nodo4, 1.0f);
    Arista* arista4 = new Arista(4, nodo4, nodo5, 1.0f);
    // Añade más aristas según sea necesario

    // Agregar las aristas al grafo
    grafo.agregarArista(arista1);
    grafo.agregarArista(arista2);
    grafo.agregarArista(arista3);
    grafo.agregarArista(arista4);

    // Inicializar nodos de inicio y fin
    nodoInicio = nodo1;
    nodoFin = nodo5;

    vehiculo = new Vehiculo();
    vehiculo->cargarTextura("C:\\Users\\Usuario\\Desktop\\vehiculo.png");
}


void Simulacion::manejarSeleccionNodos(const sf::Event::MouseButtonEvent& mouseEvento) {
    sf::Vector2f posicionMouse(static_cast<float>(mouseEvento.x), static_cast<float>(mouseEvento.y));
    Nodo* nodoSeleccionado = grafo.encontrarNodoCercano(posicionMouse);

    if (nodoSeleccionado) {
        // Si no hay nodo inicio, establecerlo
        if (!nodoInicio) {
            nodoInicio = nodoSeleccionado;
            std::cout << "INICIO establecido en nodo " << nodoInicio->id << std::endl;
        }
        // Si ya hay nodo inicio pero no fin, establecer el fin
        else if (!nodoFin) {
            nodoFin = nodoSeleccionado;
            std::cout << "FIN establecido en nodo " << nodoFin->id << std::endl;

            // Calcular y establecer la ruta
            std::vector<Nodo*> ruta = grafo.encontrarRuta(nodoInicio, nodoFin);
            std::cout << "Calculando ruta de " << nodoInicio->id << " a " << nodoFin->id << std::endl;

            if (!ruta.empty()) {
                std::cout << "Ruta encontrada con " << ruta.size() << " nodos" << std::endl;
                vehiculo->setRuta(ruta);
                rutaSeleccionada = true;

                // Resetear para permitir nueva selección
                nodoInicio = nullptr;
                nodoFin = nullptr;
            }
            else {
                std::cout << "No se pudo encontrar una ruta!" << std::endl;
            }
        }
    }
}

void Simulacion::actualizar() {
    if (rutaSeleccionada && vehiculo) {
        float deltaTime = reloj.restart().asSeconds();
        std::cout << "Actualizando movimiento. DeltaTime: " << deltaTime << std::endl;
        vehiculo->actualizar(deltaTime);
    }
}

Simulacion::~Simulacion() {
    if (vehiculo) {
        delete vehiculo;
    }
}