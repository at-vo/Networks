def funky(x):
    if x > 0:
        x-=1
        funky(x)
    print(x)

funky(5)