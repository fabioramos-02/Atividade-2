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

// Função auxiliar para o problema do corte da tora
/* O vetor memo é usado para verificar se uma solução
    já foi computada ou não */
int cutRodUtil(const vector<int>&price, int n, vector<int>& memo) {
  
    // se n for 0, não podemos mais cortar a vara.
    if (n == 0) return 0;

    // Se o resultado já foi computado, retorne-o.
    if (memo[n] != -1) return memo[n];

    int res = 0;
    for (int i = 0; i < n; i++) 
        res = std::max(res, price[i] + 
                cutRodUtil(price, n - i - 1, memo));

    // Armazena o resultado computado na tabela de 
    // memoização e retorna-o.
    return memo[n] = res;
}

int cutRod(const vector<int>&price, int n) {
  
    // Initialize memoization table with
    // -1 to indicate uncomputed states.
    vector<int> memo(n + 1, -1);
  
    return cutRodUtil(price, n, memo);
}
// Implementação da função de estratégia gulosa
// Estratégia gulosa para o problema do corte da tora
int greedy(const vector<int>& precos, int tamanho) {
   int total = 0;  // Valor total obtido pela venda dos pedaços
    int comprimentoAtual = tamanho;  // Comprimento atual da tora

    // Enquanto ainda houver madeira para cortar
    while (comprimentoAtual > 0) {
        // Encontra o comprimento com a maior densidade (preco / comprimento)
        int melhorIndice = 1;
        double melhorDensidade = static_cast<double>(precos[0]) / 1;  // densidade inicial para o pedaço de comprimento 1

        // Verifica as densidades para todos os pedaços possíveis
        for (int i = 1; i < comprimentoAtual; ++i) {
            double densidadeAtual = static_cast<double>(precos[i]) / (i + 1);  // Calcula a densidade para o pedaço de comprimento (i+1)
            if (densidadeAtual > melhorDensidade) {
                melhorDensidade = densidadeAtual;
                melhorIndice = i + 1;
            }
        }

        // Corta o pedaço com a maior densidade e atualiza o valor total
        total += precos[melhorIndice - 1];  // Adiciona o preço do melhor pedaço
        comprimentoAtual -= melhorIndice;   // Atualiza o comprimento restante da tora
    }

    return total;  // Retorna o valor total obtido
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

void calcular(int inc, int fim, int stp){
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
        int vDP = cutRod(precos, n);
        // Mede o tempo de execução da programação dinâmica
        float tDP = medirTempo(cutRod, precos, n);

        // //executa estrategia gulosa
        int vG = greedy(precos, n);
        // // Mede o tempo de execução da estratégia gulosa
        float tG = medirTempo(greedy, precos, n);

        // Calcula o percentual de acerto do Guloso em relação à Programação Dinâmica
        float p = ((float)vG / vDP) * 100;
        // Imprime a tupla de resultados
        imprimirResultados(n, vDP, tDP, vG, tG, p);

        // salvar os resultados no formato csv
        salvarDados(n, vDP, tDP, vG, tG, p);

        // Limpa o vetor de preços
        precos.clear();
    }
}