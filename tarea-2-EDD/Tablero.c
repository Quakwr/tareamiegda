#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"
#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void*** tablero;
int dimension;

void IniciarTablero(int n) {
    dimension = n;
    tablero = (void***)malloc(n * sizeof(void**));
    for (int i = 0; i < n; i++) {
        tablero[i] = (void**)malloc(n * sizeof(void*));
        for (int j = 0; j < n; j++) {
            Tierra* tierra = (Tierra*)malloc(sizeof(Tierra));
            tierra->vida = (rand() % 3) + 1;
            tierra->es_tesoro = (rand() % 20) == 0; // 5% de probabilidad de ser un tesoro
            tablero[i][j] = (void*)tierra;
        }
    }
}

void PasarTurno() {
    
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (tablero[i][j] != NULL) {
                Bomba* bomba = (Bomba*)tablero[i][j];
                if (bomba->explotar != NULL) {
                    TryExplotar(i, j);
                } // Pass the correct row and column indices
            }
        }
    }
}


void ColocarBomba(Bomba* b, int fila, int columna) {
    // Verifica si la celda está dentro de los límites del tablero
    if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
        // Verifica si ya hay una Bomba en esa celda
        if (tablero[fila][columna] != NULL) {
            b->tierra_debajo = (Tierra*)tablero[fila][columna];
            
        }
        // Asigna la nueva Bomba a la celda
        b->explotar = ExplosionPunto;
        b->contador_turnos = 1;
        tablero[fila][columna] = b;
        
    }
}




void MostrarTablero() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (tablero[i][j] != NULL) {
                if (((Tierra*)tablero[i][j])->vida == 0) {
                    if (((Tierra*)tablero[i][j])->es_tesoro) {
                         printf("* | ");
                    }
                    else {
                        printf("0 | ");
                    }
                    
                } else {
                    printf("%d | ", ((Tierra*)tablero[i][j])->vida);
                }
            } else {
                printf("xdxd | "); 
            }
        }
        printf("\n");
    }
}


void MostrarBombas() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (tablero[i][j] != NULL) {
                if (((Bomba*)tablero[i][j])->explotar == ExplosionPunto) {
                    printf("------------------------------------------------------\n");
                    printf("Turnos para explotar: %d\n", ((Bomba*)tablero[i][j])->contador_turnos);
                    printf("Coordenada: %d %d\n", i + 1, j + 1);
                    printf("Forma Explosión: ExplosionPunto\n");
                    printf("------------------------------------------------------\n");
                } else if (((Bomba*)tablero[i][j])->explotar == ExplosionX) {
                    printf("------------------------------------------------------\n");
                    printf("Turnos para explotar: %d\n", ((Bomba*)tablero[i][j])->contador_turnos);
                    printf("Coordenada: %d %d\n", i + 1, j + 1);
                    printf("Forma Explosión: ExplosionX\n");
                    printf("------------------------------------------------------\n");
                }
            }
        }
    }
}

void VerTesoros() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (tablero[i][j] != NULL) {
                if (((Tierra*)tablero[i][j])->es_tesoro) {
                    printf("* | ");
                } else {
                    
                    printf("%d | ", ((Tierra*)tablero[i][j])->vida);
                }
            } else {
                printf(" | "); // Espacio en blanco para casillas NULL
            }
        }
        printf("\n");
    }
}

void BorrarTablero() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            free(tablero[i][j]);
        }
        free(tablero[i]);
    }
    free(tablero);
    tablero = NULL;
}