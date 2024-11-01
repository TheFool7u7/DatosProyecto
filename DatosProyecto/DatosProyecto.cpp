#include "Simulacion.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Simulacion simulacion;
    simulacion.inicializar();

    while (simulacion.estaAbierta()) {
        simulacion.manejarEventos();
        simulacion.actualizar();
        simulacion.dibujar();
    }

    return 0;
}