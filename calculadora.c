#include <stdio.h>

int main() {
    double num1, num2, resultado;
    char op;

    printf("=== CALCULADORA EM C ===\n");
    printf("Operacoes disponiveis: +, -, *, /\n\n");

    printf("Digite a operacao (Ex: 10 + 5): ");
    if (scanf("%lf %c %lf", &num1, &op, &num2) != 3) {
        printf("Entrada invalida!\n");
        return 1;
    }

    switch (op) {
        case '+': resultado = num1 + num2; break;
        case '-': resultado = num1 - num2; break;
        case '*': resultado = num1 * num2; break;
        case '/': 
            if (num2 == 0) {
                printf("Erro: Divisao por zero nao permitida!\n");
                return 1;
            }
            resultado = num1 / num2; 
            break;
        default:
            printf("Operador invalido!\n");
            return 1;
    }

    printf("Resultado: %.2lf\n", resultado);
    return 0;
}