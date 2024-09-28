//Fabio Willian Lima Ramos - 202319060712
//Gustavo Florentin - RGA
#ifndef FUNCOES_H
#define FUNCOES_H

#include <vector>
using std::vector;

//fabio implementar
void gerarPrecosAleatorios(vector<int>& precos, int n);
void mergeSort(vector<int>&precos, int n);
void merge(const vector<int>&left, const vector<int>&right, vector<int>&precos);
int bottom_up(const vector<int>&precos, int n);
int greedy(const vector<int>& precos, int tamanho);
float medirTempo(int (*algoritmo)(const vector<int>&, int), const vector<int>& precos, int n);
void imprimirResultados(int n, int vDP, float tDP, int vGreedy, float tGreedy, float percentual);
void salvarDados(int n, int vDP, float tDP, int vGreedy, float tGreedy, float percentual);
void calcular(int inc, int fim, int stp);
#endif
