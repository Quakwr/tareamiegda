// TreasureFinder.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

int main(int argc, char const *argv[]) {
    
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    int opcion;
    int tamano_tablero;
    
    printf("¡Bienvenido a TreasureFinder!\n");
    printf("Indique el tamaño del tablero a jugar:\n");
    printf("1. 7x7 2. 10x10 3. 12x12\n");
    printf("Su input: ");

    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            tamano_tablero = 7;
            break;
        case 2:
            tamano_tablero = 10;
            break;
        case 3:
            tamano_tablero = 12;
            break;
        default:
            printf("Opción no válida. Saliendo del juego.\n");
            return 1;
    }

    printf("Empezando juego... ¡listo!\n");
    IniciarTablero(tamano_tablero);
    
    int turno = 1;
    int accion;
    int fila, columna;
    int forma_explotar;

    while (1) {
        printf("Tablero (Turno %d)\n", turno);
        MostrarTablero();
        
        printf("Seleccione una acción:\n");
        printf("1. Colocar Bomba 2. Mostrar Bombas 3. Mostrar Tesoros\n");
        printf("Escoja una opción: ");
        scanf("%d", &accion);

        switch (accion) {
            case 1:
                printf("Indique coordenadas de la bomba\n");
                printf("Fila: ");
                scanf("%d", &fila);
                printf("Columna: ");
                scanf("%d", &columna);
                printf("Indique forma en que explota la bomba\n");
                printf("1. Punto 2. X\n");
                printf("Su input: ");
                scanf("%d", &forma_explotar);

                Bomba* bomba = (Bomba*)malloc(sizeof(Bomba));
                bomba->contador_turnos = (forma_explotar == 1) ? 1 : 3;
                bomba->explotar = (forma_explotar == 1) ? ExplosionPunto : ExplosionX;
                
                ColocarBomba(bomba, fila - 1, columna - 1);
                turno++;
                // Después de colocar la bomba, llamamos a TryExplotar para verificar si debe explotar.
                TryExplotar(fila - 1, columna - 1);
                break;
            case 2:
                MostrarBombas();
                break;
            case 3:
                printf("Tablero de Tesoros (Turno %d)\n", turno);
                VerTesoros();
                break;
            default:
                printf("Opción no válida.\n");
        }

        printf("\n");
    }

    // Limpiar la memoria antes de salir
    BorrarTablero();

    return 0;
}
