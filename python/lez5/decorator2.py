def change_in(func):
    def inner(*args, **kwargs):
        new_input = args
        if len(args) == 1:
            print("Valore di input attuale:\n" + str(args[0]))
            print("digita nuovo valore di input:")
            new_input = [int(input())]

        a = func(*new_input)
        print(a)
        return a
    return inner

@change_in
def somma(*args):
    return sum(args)

a=somma(12)
