from generate_input import generate_input


container = [       ( 13 ,   2 ,   2 ,   2 ,   1 ,   2 ),           # (6,10)
                    ( 5 ,   1 ,   3 ,   4 ,   1 ,   2 ),            # (1,0)
                    ( 17 ,   4 ,   12 ,   5 ,   15 ,   3 )          # (-1,-1)
            ]


container = generate_input(323)


# compute 2^iP
def twoPcalc(pX,pY):
    if(pY == 0):
        return 'inf'
    # lambda
    gL = (3 * pow(pX,2) + A) * pow(2 * pY, p-2, p)
    # Nue
    gN = pY - (gL * pX)
    # P coordinates
    x3 = pow(gL,2) - (2 * pX)
    y3 = (-gL * x3) - gN 
    return (x3 % p,y3 % p)

def solve(p,A,B,pX,pY,n):
    if 4 * pow(A,3) + 27 * pow(B,2) == 0:
        return "invalid A,B"
    Q = [0,0]
    # convert n to binary and reverse order
    nBin = [int(d) for d in f'{n:b}'[::-1]]
    # create list of Ps and put P=(Px,Py) in
    Ps = [(pX,pY)]
    # add all the P^i's to a list
    for i in range(1,len(nBin)):
        Pi = twoPcalc(Ps[i-1][0], Ps[i-1][1])
        if Pi == 'inf':
            return (-1,-1)
        Ps.append(Pi)
    # find points of infinity
    for i in range(len(Ps)):
        for j in range(i+1,len(Ps)):
            if Ps[i][0] == Ps[j][0]:
                # print("inf")
                return (-1,-1)
    # step 3: np = n0*p + ... + nk * 2^kP
    for i in range(len(nBin)):
        if nBin[i] !=0:
            Q[0] += Ps[i][0]
            Q[1] += Ps[i][1]
    #print(nBin)
    #print(Ps)
    return (Q[0] % p, Q[1] % p)
    



for i in container:
    p = i[0]
    A = i[1]
    B = i[2]
    pX = i[3]
    pY = i[4]
    n = i[5]
    # print(">> solve({},{},{},{},{},{})\\\\".format(p,A,B,pX,pY,n))
    # print(solve(p,A,B,pX,pY,n))
    print(p,A,B,pX,pY,n)