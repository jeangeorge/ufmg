import csv
import time

from knapsack import *

files = ["f1_l-d_kp_10_269", "f2_l-d_kp_20_878", "f3_l-d_kp_4_20", "f4_l-d_kp_4_11", "f5_l-d_kp_15_375", "f6_l-d_kp_10_60",
        "f7_l-d_kp_7_50", "f8_l-d_kp_23_10000", "f9_l-d_kp_5_80", "f10_l-d_kp_20_879"]

def write_results(results):
    with open("results.csv", "w") as file:
        w = csv.writer(file, delimiter =';', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        w.writerow(["Aluno", "Caso de Teste", "Algoritmo","Valor Calculado","Tempo de Execução (em segundos)"])
        for result in results:
            w.writerow(result)

def main():
    print("Iniciando execução...")
    results = []
    for file_name in files:
        print("Trabalhando em '" + file_name + "'...")
        with open(file_name, "r") as file:
            knapsack = Knapsack()
            first_line = True
            for line in file:
                line_splitted = line.split()
                if first_line:
                    knapsack.max_items = float(line_splitted[0])
                    knapsack.max_weight = float(line_splitted[1])
                    first_line = False
                else:
                    knapsack.items.append(Item(float(line_splitted[0]), float(line_splitted[1])))
            start = time.time()
            knapsack.solve_backtracking(0,0,0)
            end = time.time()
            results.append(["Jean George Alves Evangelista", file_name, "Backtracking", knapsack.solution, end - start])
            knapsack.solution = 0
            start = time.time()
            knapsack.solve_branch_and_bound()
            end = time.time()
            results.append(["Jean George Alves Evangelista", file_name, "Branch and Bound", knapsack.solution, end - start])
    write_results(results)
    print("Execução finalizada!")

if __name__ == "__main__":
	main()