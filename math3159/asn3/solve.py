# Input #1
# p = 491
# m(x) = 213 + 463x^2 + 366x^3 + 82x^4 + 98x^6 + 371x^7 + 15x^8 + 114x^9 + 350x^10 + 198x^11 + 22x^12 + 133x^13 + 336x^14 + 87x^16 + 173x^18 + 67x^19 + x^20
# coeff_m = [213, 0, 463, 366, 82, 0, 98, 371, 15, 114, 350, 198, 22, 133, 336, 0, 87, 0, 173, 67, 1]
# q1(x) = 54 + 423x^2 + 253x^3 + 216x^4 + 314x^5 + 209x^6 + 315x^7 + 38x^8 + 489x^9 + 339x^10 + 146x^11 + x^12
# coeff_q1 = [54, 0, 423, 253, 216, 314, 209, 315, 38, 489, 339, 146, 1, 0, 0, 0, 0, 0, 0, 0]
# q2(x) = 291 + 329x + 116x^3 + 111x^4 + 79x^5 + 175x^6 + 173x^7 + 48x^9 + 157x^12 + x^13
# coeff_q2 = [291, 329, 0, 116, 111, 79, 175, 173, 0, 48, 0, 0, 157, 1, 0, 0, 0, 0, 0, 0]


# Input #2
# p = 383
# m(x) = 116 + 285x + 12x^5 + 13x^6 + 172x^7 + x^8
# coeff_m = [116, 285, 0, 0, 0, 12, 13, 172, 1]
# q1(x) = 37 + 301x + 138x^2 + 265x^3 + 294x^4 + 73x^5 + x^6
# coeff_q1 = [37, 301, 138, 265, 294, 73, 1, 0]
# q2(x) = 220x^2 + 295x^3 + 188x^4 + x^5
# coeff_q2 = [0, 0, 220, 295, 188, 1, 0, 0]


# Input #3
# p = 353
# m(x) = 339 + 205x + 12x^3 + 289x^6 + 140x^7 + 182x^8 + 118x^12 + 73x^14 + 170x^16 + 270x^17 + 117x^18 + x^19
# coeff_m = [339, 205, 0, 12, 0, 0, 289, 140, 182, 0, 0, 0, 118, 0, 73, 0, 170, 270, 117, 1]
# q1(x) = 317x + 272x^2 + 89x^3 + 19x^5 + 27x^7 + 236x^8 + 249x^10 + 81x^11 + x^12
# coeff_q1 = [0, 317, 272, 89, 0, 19, 0, 27, 236, 0, 249, 81, 1, 0, 0, 0, 0, 0, 0]
# q2(x) = 57x + 232x^2 + 209x^4 + 326x^6 + 20x^7 + 74x^10 + x^11
# coeff_q2 = [0, 57, 232, 0, 209, 0, 326, 20, 0, 0, 74, 1, 0, 0, 0, 0, 0, 0, 0]



def output(aList):
    sol = ""

    for num in range(aList):
        if num == 0:
            sol += aList[num]
        elif num == 1:
            sol += aList[num] + "x + "
        elif num == len(aList) - 1:
            sol += aList[num] + "x^" + num + "\n"
        else:
            sol += aList[num] + 'x^' + num + " + "
    return sol


    ###      Summation       ###
def sum(p,m,q1,q2):

    add = []
    longer = 0
    if len(q1) > len(q2):
        longer = len(q1)
    else:
        longer = len(q2)
    for num in range(longer):
        # add numbers with same coefficient
        sol = q1[num] + q2[num]
        # add to the list
        add.append(sol)
        if add[num] % p == 0:
            add[num] = 0
        elif add[num] > p:
            add[num] %= p

    if(len(add) > len(m)):
        division(p,m,add)

    return add



    



    ###      Product       ###
    
def product(p,m,q1,q2):
    product = []
    for x in range(q1):
        for y in range(q2):
            q1q2 = q1[x] * q2[y]

            pass


    if(len(product) > len(m)):
        division(p,m,product)

    return product
    

def division(p, m, l):
    rem = []
    
    degDiff = len(l) - len(m)
    while not degDiff == 0:
        degLCoeff = l[len(l)-1]
        degMCoeff = m[len(l)-1]
        
        k = product(p,m,l,)
        


    return 0


def solve(p,m,q1,q2):

    add = add(p,m,q1,q2)
    sumOut = output(add)



    return sumOut



print(solve( 2 , [ 1 , 1 , 0 , 1 ] , [ 1 , 1 , 0 ] , [ 0 , 1 , 1 ] ))

# print(solve ( 2 , [ 1 , 1 , 0 , 1 ] , [ 1 , 0 , 1 ] , [ 1 , 0 , 1 ] ))

# print(solve( 2 , [ 1 , 1 , 0 , 1 ] , [ 1 , 1 , 0 ] , [ 1 , 1 , 1 ] ))

# print(solve( 5 , [ 1 , 0 , 2 , 0 , 3 , 0 , 4 ] , [ 1 , 0 , 0 , 0 , 0 , 3 ] , [ 4 , 0 , 3 , 0 , 2 , 2 ] ))