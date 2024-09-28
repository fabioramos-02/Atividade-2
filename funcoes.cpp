#include "funcoes.h"
#include <vector>
#include <algorithm> 
#include <chrono>
#include "stdio.h"

//Fabio Willian Lima Ramos - 202319060712
//Gustavo Florentin - RGA
using namespace std::chrono;
using std::vector;
//funcao que gera precos aleatorios intervalo [1, n]
void gerarPrecosAleatorios(vector<int>& precos, int n) {
    for (int i = 0; i < n; i++) {
        precos[i] = rand() % n + 1;
    }
}
// Implementação da função de Programação Dinâmica
int bottom_up(const vector<int>&precos, int n) {
    vector<int> receita(n + 1, 0); //armazena os lucros 
    for (int i = 1; i <= n; i++) {
        int max_val = -1; //inicializa o lucro maximo
        for (int j = 0; j < i; j++) {
            max_val = std::max(max_val, precos[j] + receita[i - j - 1]);
        }
        receita[i] = max_val;
    }
    return receita[n];
   
}
// Implementação da função de estratégia gulosa
int greedy(const vector<int>&precos, int n) {
    if (n == 0) {
        return 0;
    }
    int max_val = -1;
    for (int i = 0; i < n; i++) {
        max_val = std::max(max_val, precos[i] + greedy(precos, n - i - 1));
    }
    return max_val;
   
}
void merge(const vector<int>&left, const vector<int>&right, vector<int>&precos) {
    int n = left.size();
    int m = right.size();
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < n && j < m) {
        if (left[i] <= right[j]) {
            precos[k] = left[i];
            i++;
        } else {
            precos[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n) {
        precos[k] = left[i];
        i++;
        k++;
    }
    while (j < m) {
        precos[k] = right[j];
        j++;
        k++;
    }
}
// Implementação do algortimo de ordenacao eficiente nlogn em ordem nao-decrescente
void mergeSort(vector<int>&precos, int n) {
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    vector<int> left(mid);
    vector<int> right(n - mid);
    for (int i = 0; i < mid; i++) {
        left[i] = precos[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = precos[i];
    }
    mergeSort(left, mid);
    mergeSort(right, n - mid);
    merge(left, right, precos);
}

//medir o tempo de execucao
// Função para medir o tempo de execução
float medirTempo(int (*algoritmo)(const vector<int>&, int), const vector<int>& precos, int n) {
    auto start = high_resolution_clock::now();
    algoritmo(precos, n);  // Executa o algoritmo
    auto end = high_resolution_clock::now();
    duration<float> duration = end - start;
    return duration.count();  // Retorna o tempo em segundos
}

//funcao para imprimir resultados tabulado
void imprimirResultados(int n, int vDP, float tDP, int vGreedy, float tGreedy, float percentual)
{
    // Imprimir os resultados
    printf("%-8d%-8d%-16.6f%-16d%-16.6f%-8.2f\n", n, vDP, tDP, vGreedy, tGreedy, percentual);

}

//salvar dados no formato csv
void salvarDados(int n, int vDP, float tDP, int vGreedy, float tGreedy, float percentual)
{
    FILE *arq;
    arq = fopen("resultados.csv", "a");
    fprintf(arq, "%d,%d,%.6f,%d,%.6f,%.2f\n", n, vDP, tDP, vGreedy, tGreedy, percentual);
    fclose(arq);
}


