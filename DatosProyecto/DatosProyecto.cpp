#include <SFML/Graphics.hpp>
#include "Simulacion.h"

int main() {
    Simulacion simulacion;
    simulacion.inicializar();

    while (simulacion.ventana.isOpen()) {
        sf::Event evento;
        while (simulacion.ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                simulacion.ventana.close();
            }
        }

        simulacion.actualizar();
        simulacion.dibujar();
    }

    return 0;
}