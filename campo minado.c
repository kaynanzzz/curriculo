#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 6
#define BOMBAS 5

char tabVisivel[TAM][TAM];
int tabOculto[TAM][TAM]; // -1 para Bomba, 0-8 para contagem de bombas vizinhas

void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabVisivel[i][j] = '*';
            tabOculto[i][j] = 0;
        }
    }

    // Colocar bombas aleatoriamente
    int colocadas = 0;
    while (colocadas < BOMBAS) {
        int r = rand() % TAM;
        int c = rand() % TAM;
        if (tabOculto[r][c] != -1) {
            tabOculto[r][c] = -1;
            colocadas++;
        }
    }

    // Calcular vizinhos
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabOculto[i][j] == -1) continue;
            int minas = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < TAM && nj >= 0 && nj < TAM && tabOculto[ni][nj] == -1) {
                        minas++;
                    }
                }
            }
            tabOculto[i][j] = minas;
        }
    }
}

void exibirTabuleiro() {
    printf("\n   ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabVisivel[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    inicializarTabuleiro();
    int jogadasRestantes = (TAM * TAM) - BOMBAS;

    while (1) {
        exibirTabuleiro();
        int lin, col;
        printf("\nDigite a linha e coluna (ex: 1 2): ");
        if (scanf("%d %d", &lin, &col) != 2 || lin < 0 || lin >= TAM || col < 0 || col >= TAM) {
            printf("Posicao invalida!\n");
            continue;
        }

        if (tabOculto[lin][col] == -1) {
            printf("\n*** BOOM! Voce acertou uma mina. Fim de jogo. ***\n");
            break;
        }

        if (tabVisivel[lin][col] == '*') {
            tabVisivel[lin][col] = '0' + tabOculto[lin][col];
            jogadasRestantes--;
        }

        if (jogadasRestantes == 0) {
            printf("\n*** PARABENS! Voce limpou o campo minado! ***\n");
            break;
        }
    }
    return 0;
}