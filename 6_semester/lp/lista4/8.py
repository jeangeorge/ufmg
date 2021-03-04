class FormulaError(Exception):
    pass

def main():
    try:
        while True:
            user_input = input()
            try:
                x, op, y = user_input.split()
            except ValueError:
                raise FormulaError("A entrada nao consiste de 3 elementos")

            try:
                x = float(x)
                y = float(x)
            except ValueError:
                raise FormulaError("O primeiro e o terceiro valor de entrada devem ser numeros")

            if op == "+":
                print(x + y)
            elif op == "-":
                print(x - y)
            elif op == "/":
                print(x / y)
            elif op == "*":
                print(x * y)
            else:
                raise FormulaError("x nao e um operador valido")
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()
