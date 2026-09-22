#include <stdio.h>

char tabuleiro[3][3];

void inicializar() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tabuleiro[i][j] = ' ';
}

void desenhar() {
    printf("\n %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

int verificarVitoria(char c) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == c && tabuleiro[i][1] == c && tabuleiro[i][2] == c) return 1;
        if (tabuleiro[0][i] == c && tabuleiro[1][i] == c && tabuleiro[2][i] == c) return 1;
    }
    if (tabuleiro[0][0] == c && tabuleiro[1][1] == c && tabuleiro[2][2] == c) return 1;
    if (tabuleiro[0][2] == c && tabuleiro[1][1] == c && tabuleiro[2][0] == c) return 1;
    return 0;
}

int main() {
    inicializar();
    char jogador = 'X';
    int jogadas = 0, lin, col;

    while (jogadas < 9) {
        desenhar();
        printf("Jogador %c, informe linha e coluna (0-2): ", jogador);
        scanf("%d %d", &lin, &col);

        if (lin < 0 || lin > 2 || col < 0 || col > 2 || tabuleiro[lin][col] != ' ') {
            printf("Jogada invalida! Tente novamente.\n");
            continue;
        }

        tabuleiro[lin][col] = jogador;
        jogadas++;

        if (verificarVitoria(jogador)) {
            desenhar();
            printf("Parabens! O jogador %c venceu!\n", jogador);
            return 0;
        }

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    desenhar();
    printf("Deu Empate (Velha)!\n");
    return 0;
}