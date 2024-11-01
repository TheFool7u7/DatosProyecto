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

		if (evento.type == sf::Event::MouseButtonPressed) {
			if (evento.mouseButton.button == sf::Mouse::Left) {
				if (mostrarMenuAlgoritmo) {
					sf::Vector2i posicionMouse = sf::Mouse::getPosition(ventana);

					if (checkBotonClick(botonDijkstra, posicionMouse)) {
						usarDijkstra = true;
						mostrarMenuAlgoritmo = false;
						algoritmoSeleccionado = true;
						std::cout << "\n=== Algoritmo seleccionado: Dijkstra ===" << std::endl;
						std::cout << "Por favor, seleccione el nodo de inicio" << std::endl;
					}
					else if (checkBotonClick(botonFloyd, posicionMouse)) {
						usarDijkstra = false;
						mostrarMenuAlgoritmo = false;
						algoritmoSeleccionado = true;
						std::cout << "\n=== Algoritmo seleccionado: Floyd-Warshall ===" << std::endl;
						std::cout << "Por favor, seleccione el nodo de inicio" << std::endl;
					}
				}
				else {
					// Convertir la posición del mouse a coordenadas de la ventana
					sf::Vector2f posicionMouse = ventana.mapPixelToCoords(
						sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y)
					);

					std::cout << "Click en posición: " << posicionMouse.x << "," << posicionMouse.y << std::endl;

					Nodo* nodoSeleccionado = grafo.encontrarNodoCercano(posicionMouse);
					if (nodoSeleccionado) {
						if (!nodoInicio) {
							nodoInicio = nodoSeleccionado;
							std::cout << "Nodo inicial seleccionado: " << nodoInicio->id << std::endl;
							std::cout << "Por favor, seleccione el nodo de destino" << std::endl;
						}
						else if (!nodoFin) {
							nodoFin = nodoSeleccionado;
							std::cout << "Nodo final seleccionado: " << nodoFin->id << std::endl;

							// Calcular ruta
							std::vector<Nodo*> ruta;
							if (usarDijkstra) {
								ruta = grafo.dijkstra(nodoInicio, nodoFin);
							}
							else {
								ruta = grafo.floydWarshall(nodoInicio, nodoFin);
							}

							if (!ruta.empty()) {
								vehiculo->setRuta(ruta);
								grafo.resaltarRuta(ruta);
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
	Nodo* nodo1 = new Nodo(1, sf::Vector2f(356, 21));
	Nodo* nodo2 = new Nodo(2, sf::Vector2f(311, 55));
	Nodo* nodo3 = new Nodo(3, sf::Vector2f(254, 309));
	Nodo* nodo4 = new Nodo(4, sf::Vector2f(43, 537));
	Nodo* nodo5 = new Nodo(5, sf::Vector2f(477, 773));
	Nodo* nodo6 = new Nodo(6, sf::Vector2f(605, 454));

	std::cout << "Creando nodos en posiciones:" << std::endl;
	std::cout << "Nodo 1: " << nodo1->posicion.x << "," << nodo1->posicion.y << std::endl;
	std::cout << "Nodo 2: " << nodo2->posicion.x << "," << nodo2->posicion.y << std::endl;
	std::cout << "Nodo 3: " << nodo3->posicion.x << "," << nodo3->posicion.y << std::endl;
	std::cout << "Nodo 4: " << nodo4->posicion.x << "," << nodo4->posicion.y << std::endl;
	std::cout << "Nodo 5: " << nodo5->posicion.x << "," << nodo5->posicion.y << std::endl;

	// Función auxiliar para calcular distancias (para simplificar el código)
	auto calcularDistancia = [](Nodo* n1, Nodo* n2) {
		return std::sqrt(std::pow(n2->posicion.x - n1->posicion.x, 2) +
			std::pow(n2->posicion.y - n1->posicion.y, 2));
		};



	// Creación de las aristas (asumiendo que todos los nodos se conectan entre sí):
	std::vector<std::pair<Nodo*, Nodo*>> conexiones = {
		{nodo1, nodo2}, {nodo1, nodo3}, {nodo1, nodo4}, {nodo1, nodo5}, {nodo1, nodo6}, 
		{nodo2, nodo3}, {nodo2, nodo4}, {nodo2, nodo5}, {nodo2, nodo6}, 
		{nodo3, nodo4}, {nodo3, nodo5}, {nodo3, nodo6}, 
		{nodo4, nodo5}, {nodo4, nodo6}, 
		{nodo5, nodo6}
	};

	int idArista = 1;
	for (const auto& conexion : conexiones) {
		float distancia = calcularDistancia(conexion.first, conexion.second);
		grafo.agregarArista(new Arista(idArista++, conexion.first, conexion.second, distancia));
	}

	// Agregar los nodos al grafo
	grafo.agregarNodo(nodo1);
	grafo.agregarNodo(nodo2);
	grafo.agregarNodo(nodo3);
	grafo.agregarNodo(nodo4);
	grafo.agregarNodo(nodo5);
	grafo.agregarNodo(nodo6);

	// Crear aristas que conecten los nodos siguiendo el camino rojo
	Arista* arista1 = new Arista(1, nodo1, nodo2, 1.0f);
	Arista* arista2 = new Arista(2, nodo2, nodo3, 1.0f);
	Arista* arista3 = new Arista(3, nodo3, nodo4, 1.0f);
	Arista* arista4 = new Arista(4, nodo4, nodo5, 1.0f);
	Arista* arista5 = new Arista(5, nodo5, nodo6, 1.0f);
	// Añade más aristas según sea necesario

	// Agregar las aristas al grafo
	grafo.agregarArista(arista1);
	grafo.agregarArista(arista2);
	grafo.agregarArista(arista3);
	grafo.agregarArista(arista4);
	grafo.agregarArista(arista5);


	// Inicializar nodos de inicio y fin
	nodoInicio = nodo1;
	nodoFin = nodo6;

	vehiculo = new Vehiculo();
	vehiculo->cargarTextura("C:\\Users\\Usuario\\Desktop\\vehiculo.png");
}


void Simulacion::manejarSeleccionNodos(const sf::Event::MouseButtonEvent& mouseEvento) {
	sf::Vector2f posicionMouse(static_cast<float>(mouseEvento.x), static_cast<float>(mouseEvento.y));
	Nodo* nodoSeleccionado = grafo.encontrarNodoCercano(posicionMouse);

	if (nodoSeleccionado) {
		if (!nodoInicio) {
			nodoInicio = nodoSeleccionado;
			std::cout << "\n=== Selección de Nodos ===" << std::endl;
			std::cout << "Nodo de inicio seleccionado: Nodo " << nodoInicio->id << std::endl;
			std::cout << "Por favor, seleccione el nodo de destino" << std::endl;
		}
		else if (!nodoFin) {
			nodoFin = nodoSeleccionado;
			std::cout << "Nodo de destino seleccionado: Nodo " << nodoFin->id << std::endl;
			std::cout << "\n=== Calculando Ruta ===" << std::endl;
			std::cout << "Buscando ruta de Nodo " << nodoInicio->id << " a Nodo " << nodoFin->id << std::endl;

			std::vector<Nodo*> ruta;
			if (usarDijkstra) {
				std::cout << "Utilizando algoritmo Dijkstra" << std::endl;
				ruta = grafo.dijkstra(nodoInicio, nodoFin);
			}
			else {
				std::cout << "Utilizando algoritmo Floyd-Warshall" << std::endl;
				ruta = grafo.floydWarshall(nodoInicio, nodoFin);
			}

			if (!ruta.empty()) {
				std::cout << "\n=== Ruta encontrada ===" << std::endl;
				std::cout << "Secuencia de nodos: ";
				for (size_t i = 0; i < ruta.size(); i++) {
					std::cout << ruta[i]->id;
					if (i < ruta.size() - 1) std::cout << " -> ";
				}
				std::cout << std::endl;

				vehiculo->setRuta(ruta);
				grafo.resaltarRuta(ruta);
				rutaSeleccionada = true;

				// Mostrar costo de la ruta
				float costoTotal = grafo.calcularCostoRuta(ruta);
				std::cout << "Costo total de la ruta: " << costoTotal << std::endl;
			}
			else {
				std::cout << "ERROR: No se pudo encontrar una ruta válida" << std::endl;
			}

			nodoInicio = nullptr;
			nodoFin = nullptr;
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