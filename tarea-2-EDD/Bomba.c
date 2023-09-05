
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
                if (bomba->explotar == ExplosionPunto) {
                    printf("hola");
                    ExplosionPunto(fila, columna);
                } 
                else if (bomba->explotar == ExplosionX) {
                    ExplosionX(fila, columna);
                }
            }
            
            BorrarBomba(fila, columna);
            
        }
    }
}



void BorrarBomba(int fila, int columna) {
    if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
        if (tablero[fila][columna] != NULL) {
            Bomba* bomba = (Bomba*)tablero[fila][columna];
         
            tablero[fila][columna] = bomba->tierra_debajo;
            //Free the Bomba object, but not the Tierra object, as it's shared
            free((void*)bomba);
            
        }
    }
}






void ExplosionPunto(int fila, int columna) {

    if (tablero[fila][columna] != NULL) {   
        Bomba* bomba = (Bomba*)tablero[fila][columna]; 
        bomba->tierra_debajo->vida -= 3;
        if (bomba->tierra_debajo->vida < 0) {
            bomba->tierra_debajo->vida = 0;
        }
        
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
