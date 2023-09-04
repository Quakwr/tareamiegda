
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>

void TryExplotar(int fila, int columna) {
    Tierra* tierra = (Tierra*)tablero[fila][columna];
    if (tablero[fila][columna] != NULL) {
        Bomba* bomba = (Bomba*)tablero[fila][columna];
        if (bomba->contador_turnos > 0) {
            if (bomba->contador_turnos == 1) {
                // Comprobar el tipo de bomba solo si contador_turnos es 1
                if (bomba->explotar == ExplosionPunto) {
                    printf("hola");
                    ExplosionPunto(fila, columna);
                } else if (bomba->explotar == ExplosionX) {
                    ExplosionX(fila, columna);
                }
            }
            printf("La vida de la tierra antes de Borrar BOMBaen (%d, %d) es: %d\n", fila, columna, tierra->vida);
            BorrarBomba(fila, columna);
            printf("La vida de la tierra en (%d, %d) es: %d\n", fila, columna, tierra->vida);
        }
    }
}



void BorrarBomba(int fila, int columna) {
    if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
        if (tablero[fila][columna] != NULL) {
            Bomba* bomba = (Bomba*)tablero[fila][columna];
            Tierra* tierra = bomba->tierra_debajo;  // Get the existing Tierra object
            
            // Cast the void pointer to Tierra* and update the values
            Tierra* tablero_tierra = (Tierra*)(tablero[fila][columna]);
            tablero_tierra->vida = tierra->vida;
            tablero_tierra->es_tesoro = tierra->es_tesoro;
            
            free(bomba);
        }
    }
}






void ExplosionPunto(int fila, int columna) {
    printf("haaa");
    Tierra* tierra = (Tierra*)tablero[fila][columna];
    printf("La vida de la tierra en (%d, %d) es: %d\n", fila, columna, tierra->vida);
    if (tablero[fila][columna] != NULL) {
        Tierra* tierra = (Tierra*)tablero[fila][columna];
        tierra->vida -= 3;
        if (tierra->vida < 0) {
            tierra->vida = 0;
        }
        printf("La vida de la tierra en (%d, %d) es: %d\n", fila, columna, tierra->vida);
    }
}


void ExplosionX(int fila, int columna) {
    int i, j;
    printf("haaa");
    for (i = -2; i <= 2; i++) {
        for (j = -2; j <= 2; j++) {
            int new_fila = fila + i;
            int new_columna = columna + j;

            if (new_fila >= 0 && new_fila < dimension && new_columna >= 0 && new_columna < dimension) {
                Tierra* tierra = (Tierra*)tablero[new_fila][new_columna];
                if (tierra != NULL) {
                    tierra->vida -= 1;  // Incrementa la vida en 2 unidades
                    printf("La vida de la tierra en (%d, %d) es: %d\n", new_fila, new_columna, tierra->vida);
                }
            }
        }
    }
}
