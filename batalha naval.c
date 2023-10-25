#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>

#define BLK (wint_t)0x2588
#define MAR (wint_t)0x25A1
#define ACERTO (wint_t)0x2713
#define VESGO (wint_t)0x2717

#define TAMANHO 10

void exibirTabuleiro(int board[TAMANHO][TAMANHO]) {
    wint_t symbol;
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (board[i][j] == 1) {
                symbol = BLK; 
            } else if (board[i][j] == 2) {
                symbol = ACERTO; 
            } else if (board[i][j] == 3) {
                symbol = VESGO; 
            } else {
                symbol = MAR; 
            }
            printf("%lc ", symbol);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    int player1Tabela[TAMANHO][TAMANHO];
    int player2Tabela[TAMANHO][TAMANHO];
    int tirosPlayer1[TAMANHO][TAMANHO];
    int tirosPlayer2[TAMANHO][TAMANHO];

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            player1Tabela[i][j] = 0;
            player2Tabela[i][j] = 0;
            tirosPlayer1[i][j] = 0;
            tirosPlayer2[i][j] = 0;
        }
    }

    player1Tabela[2][2] = 1;
    player1Tabela[3][2] = 1;
    player1Tabela[4][2] = 1;
    player1Tabela[5][2] = 1;
    player1Tabela[6][2] = 1;

    player2Tabela[1][1] = 1;
    player2Tabela[2][1] = 1;
    player2Tabela[3][1] = 1;
    player2Tabela[4][1] = 1;

    bool player1Turn = true;
    bool seDeuMal = false;

    while (!seDeuMal) {
        int horizontal, vertical;
        char verticalChar;

        if (player1Turn) {
            printf("Jogador 1, faca um bombardeio (por exemplo, A3): ");
            scanf(" %c%d", &verticalChar, &horizontal);
            vertical = verticalChar - 'A';
        } else {
            printf("Jogador 2, faca um bombardeio (por exemplo, A3): ");
            scanf(" %c%d", &verticalChar, &horizontal);
            vertical = verticalChar - 'A';
        }

        if (horizontal >= 0 && horizontal < TAMANHO && vertical >= 0 && vertical < TAMANHO) {
            if (player1Turn) {
                if (player2Tabela[horizontal][vertical] == 1) {
                    printf("Jogador 1 acertou um navio!\n");
                    player2Tabela[horizontal][vertical] = 2;
                } else {
                    printf("Jogador 1 errou o tiro.\n");
                    tirosPlayer1[horizontal][vertical] = 3;
                }
                exibirTabuleiro(player1Tabela); 
            } else {
                if (player1Tabela[horizontal][vertical] == 1) {
                    printf("Jogador 2 acertou um navio!\n");
                    player1Tabela[horizontal][vertical] = 2;
                } else {
                    printf("Jogador 2 errou o tiro.\n");
                    tirosPlayer2[horizontal][vertical] = 3;
                }
                exibirTabuleiro(player2Tabela);
            }
            printf("\n");
        }

        seDeuMal = true;
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (player1Tabela[i][j] == 1 || player2Tabela[i][j] == 1) {
                    seDeuMal = false;
                    break;
                }
            }
            if (!seDeuMal) {
                break;
            }
        }

        player1Turn = !player1Turn;
    }

    if (player1Turn) {
        printf("marujo venceu!\n");
    } else {
        printf("Cabin Boy venceu!\n");
    }

    return 0;
}

