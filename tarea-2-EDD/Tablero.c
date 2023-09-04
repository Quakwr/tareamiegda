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
                TryExplotar(i, j);
            }
        }
    }
}

void ColocarBomba(Bomba* b, int fila, int columna) {
    if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
        if (tablero[fila][columna] != NULL) {
            // Create a new Tierra object and move the data to tierra_debajo
            Tierra* tierra = (Tierra*)malloc(sizeof(Tierra));
            Tierra* currentTierra = (Tierra*)tablero[fila][columna];

            tierra->vida = currentTierra->vida;
            tierra->es_tesoro = currentTierra->es_tesoro;

            b->tierra_debajo = tierra; // Set tierra_debajo to the new Tierra object

            // Create a new Bomba object and copy the data
            Bomba* bomba = (Bomba*)malloc(sizeof(Bomba));
            memcpy(bomba, b, sizeof(Bomba));

            // Set the new Bomba object in the tablero
            tablero[fila][columna] = (void*)bomba;

            // Free the old Tierra object
            free(currentTierra);

            // Update the bomba counter if necessary
            
        }
    }
}





void MostrarTablero() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (tablero[i][j] != NULL) {
                if (((Tierra*)tablero[i][j])->vida == 0) {
                    printf("%s | ", (((Tierra*)tablero[i][j])->es_tesoro) ? "*" : "0");
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