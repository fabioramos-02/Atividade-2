// Fabio Willian Lima Ramos - 202319060712
// Gustavo Florentin - RGA
#include <iostream>
#include "funcoes.h"
#include <ctime>
#include <vector>

using std::vector;

int main()
{
    int inc = 1000;  // Tamanho inicial da entrada
    int fim = 20000; // Tamanho final da entrada
    int stp = 1000;  // Intervalo entre entradas
    srand(time(0));  // Inicializa o gerador de números aleatórios

    calcular(inc, fim, stp); // Executa o cálculo
    return 0;
}