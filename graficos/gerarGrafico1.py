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
n = [row[0] for row in dados]
dynamic = [row[1] for row in dados]
greedy = [row[3] for row in dados]  # Coluna correta para os valores do greedy

# Criando o gráfico
plt.figure(figsize=(10, 6))

# Definindo cores explícitas para cada algoritmo
plt.plot(n, dynamic, color='black', marker='v', label='Dynamic Programming')
plt.plot(n, greedy, color='red', marker='o', label='Greedy')

# Configurando os eixos
plt.xlabel('n', fontsize=12)
plt.ylabel('Valor total de venda', fontsize=12)

# Ajustando o título
plt.title('(a) Valor total de venda.', fontsize=14, weight='bold')

# Exibindo a grade
plt.grid(True)

# Exibindo a legenda
plt.legend()

# Mostrar o gráfico
plt.show()
