#include "Simulacion.h"

int main() {
    Simulacion simulacion;
    simulacion.inicializar();

    while (simulacion.estaAbierta()) {
        simulacion.manejarEventos();
        simulacion.actualizar();
        simulacion.dibujar();
    }

    return 0;
}