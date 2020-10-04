from math import ceil, sqrt


container = [   
                (8389057, 50354, 641736), 
                (8389099, 81194, 4611664), 
                (8391037, 68226, 7343254)
            ]

# container = [   
#                 ( 13 , 6 , 5 ),             #9
#                 ( 7 , 2 , 5 ),            #no
#                 (17389, 9704, 13896),   #1159
#                 (59, 3, 19)
#             ]

def bsgs(p,g,h):
    '''
    Solve for x in h = g^x mod p given a prime p.
    If p is not prime, you shouldn't use BSGS anyway.
    '''
    N = ceil(sqrt(p - 1))  # phi(p) is p-1 if p is prime

    # Store hashmap of g^{1...m} (mod p). Baby step.
    tbl = {pow(g, i, p): i for i in range(N)}

    # Precompute via Fermat's Little Theorem
    c = pow(g, N * (p - 2), p)

    # Search for an equivalence in the table. Giant step.
    for j in range(N):
        y = (h * pow(c, j, p)) % p
        if y in tbl:
            return j * N + tbl[y]
    # Solution not found
    return None

for i in container:
    p = i[0]
    g = i[1]
    h = i[2]
    print(bsgs(p,g,h))
