#323
container = [   
                (8389057, 50354, 641736), 
                (8389099, 81194, 4611664), 
                (8391037, 68226, 7343254)
            ]


#test
container = [   
                #( 13 , 6 , 5 ),             #9
                 #( 7 , 2 , 5 ),            #no
                 #( 17389 , 9704 , 13896)   #1159
                 (59, 3, 19)
            ]


def solve(p,g,h):
    M = 1 + int(p**(1/2))
    list1 = []
    list2 = []
    n = -1
    for i in range (M+1):
        list1.append(g**i)
        list2.append(h*(g**(-i*M)))
        

    for i in range(M+1):
        if list1[i] % p == list2[i] % p:
            return i + (i * M)
    



for i in container:
    p = i[0]
    g = i[1]
    h = i[2]
    solution = solve(p,g,h)
    # if (solution != -1):
    print("x = {} is a solution".format(solution))
    # else:
    #     print("there is no solution")