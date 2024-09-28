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
    // Cria o arquivo de resultados
    FILE *arq = fopen("resultados.csv", "w");
    fclose(arq);

    // Imprime os cabeçalhos
    printf("%-8s%-8s%-16s%-16s%-16s%-8s\n", "n", "vDP", "tDP", "vGreedy", "tGreedy", "%");
    printf("----------------------------------------------------------------------\n");

    // Loop para testar diferentes comprimentos de tora
    for (int n = inc; n <= fim; n += stp)
    {
        // Gera os preços para os pedaços da tora
        vector<int> precos(n);
        gerarPrecosAleatorios(precos, n);

        mergeSort(precos, n);
        // executa programacao dinamica
        int vDP = bottom_up(precos, n);
        // Mede o tempo de execução da programação dinâmica
        float tDP = medirTempo(bottom_up, precos, n);

        // //executa estrategia gulosa
        int vG = greedy(precos, n);
        // int vG = 0;
        // // Mede o tempo de execução da estratégia gulosa
        float tG = medirTempo(greedy, precos, n);
        // float tG = 0;

        // Calcula o percentual de acerto do Guloso em relação à Programação Dinâmica
        float p = ((float)0 / vDP) * 100;
        // Imprime a tupla de resultados
        imprimirResultados(n, vDP, tDP, vG, tG, p);

        // salvar os resultados no formato csv
        salvarDados(n, vDP, tDP, vG, tG, p);

        // Limpa o vetor de preços
        precos.clear();
    }
    return 0;
}