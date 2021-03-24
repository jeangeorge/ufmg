import csv

from knapsack import *

files = ["f1_l-d_kp_10_269", "f2_l-d_kp_20_878", "f3_l-d_kp_4_20", "f4_l-d_kp_4_11", "f5_l-d_kp_15_375", "f6_l-d_kp_10_60",
        "f7_l-d_kp_7_50", "f8_l-d_kp_23_10000", "f9_l-d_kp_5_80", "f10_l-d_kp_20_879"]

def write_results():
    with open("results.csv", "w") as file:
        w = csv.writer(file, delimiter =';',quotechar =';',quoting=csv.QUOTE_MINIMAL)
        w.writerow(["Aluno","Caso de Teste","Algoritmo","Tempo de Execução","Valor Calculado"])

def main():
    for file_name in files:
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

            # knapsack.solve_backtracking(0,0,0)
            # print(file_name + " \t " + " Backtracking\t " + str(knapsack.solution))
            # knapsack.solution = 0
            knapsack.solve_branch_and_bound()
            print(file_name + " \t " + " Branch and Bound\t " + str(knapsack.solution))

if __name__ == "__main__":
	main()