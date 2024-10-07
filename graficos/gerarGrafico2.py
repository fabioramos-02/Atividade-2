import matplotlib.pyplot as plt
import csv

# Ler os dados do arquivo CSV
dados = []
with open('../resultados.csv', 'r') as arquivo_csv:  
    leitor_csv = csv.reader(arquivo_csv, delimiter=',') 
    next(leitor_csv)  # Pula o cabeçalho
    for linha in leitor_csv:
        dados.append([float(valor) for valor in linha])  # Converte valores para float

# Separando os dados
n = [row[0] for row in dados] #n
tDP = [row[2] for row in dados] #tDP
tGreedy = [row[4] for row in dados]  #tGreedy

# Criando o gráfico
plt.figure(figsize=(10, 6))

# Definindo cores explícitas para cada algoritmo
plt.plot(n, tDP, color='black', marker='v', label='Dynamic Programming')
plt.plot(n, tGreedy, color='red', marker='o', label='Greedy')

# Configurando os eixos
plt.xlabel('n', fontsize=12)
plt.ylabel('Tempo de execução', fontsize=12)

# Ajustando o título
plt.title('(b) Tempo de execução dos algoritmos.', fontsize=14, weight='bold')

# Exibindo a grade
plt.grid(True)

# Exibindo a legenda
plt.legend()

# Mostrar o gráfico
plt.show()
