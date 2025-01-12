import functools as ft
import time

#def sum(*args):
#    return(ft.reduce(lambda a, b: a+b, args))

def log_execution(func):
    def inner(*args, **kwargs):
        begin = time.gmtime(time.time())
        func(*args, **kwargs)
        f=open("execution_log.txt", "w")

        f.write(str(begin.tm_mday) + '/' + str(begin.tm_mon) + '/' + str(begin.tm_year) + "\n")
        f.write(str(begin.tm_hour) + ':' + str(begin.tm_min) + "\n")
        f.write(func.__name__ + "\n")
        f.write(str(args) + "\n")
        f.close()
    return inner

@log_execution
def somma(*args):
    return sum(args)

somma(50, 24)
