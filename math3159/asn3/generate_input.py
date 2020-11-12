import sys
import random
from random import randrange

primes_list = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
              31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
              73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
              127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
              233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
              353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
              467, 479, 487, 491, 499, 503, 509, 521, 523, 541]

# given a prime p and deg n, randomly generates a list containing n integers between 0 and p-1
def random_polynomial(p,n) :
    wts = [p//2]
    for i in range(p-1) :
        wts.append(1)
    return random.choices(range(p),weights=wts,k=n)

def trim_polynomial(coeff):
    while coeff[-1] == 0:
        coeff.pop()
        if len(coeff) == 0:
            return
    return

# given a list of coefficients [a_0,a_1,...,a_n], prints out the polynomial a_0 + a_1 x + ... + a_n x^n
def print_polynomial(coeff):
    trim_polynomial(coeff)
    if coeff == []:
        print(0)
        return
    n = len(coeff)-1
    for i in range(0,n+1):

        # coefficient of x^i
        if coeff[i] == 0:
            continue
        if coeff[i] == 1 and i > 0:
            c = ""
        else:
            c = str(coeff[i])

        # prints a_i x^i
        if i == 0:
            print(c, end = '')
        elif i == 1:
            print(c + "x", end = '')
        elif i < n:
            print(c + "x^" + str(i), end = '')
        else:
            print(c + "x^" + str(i), end = '')

        # prints " + " or new line 
        if i < n:
            print(" + ", end ='')
        elif i == n:
            print()
    

def generate_input(s,count) :
    for token in range(s,s+count):
        print("Input #" + str(token-s+1))
        
        # initialize the random number generator
        random.seed(token)
        
        # pick out a random prime  p from the stored list of primes
        p = random.choice(primes_list)

        # pick out a integer n between 6 and 20
        n = random.choice(range(6,21))

        # picks out two integers a and b such that a, b < n but a + b > n
        a = random.choice(range(n//2 + 1,n-1))
        b = random.choice(range(n//2 + 1,n-1))

        # picks out three random polynomials with coefficients in F_p with degrees n, a, and b respectively
        coeff_m = random_polynomial(p,n)
        coeff_m.append(1)
        coeff_q1 = random_polynomial(p,a)
        coeff_q1.append(1)
        coeff_q2 = random_polynomial(p,b)
        coeff_q2.append(1)

        # prints out the prime p and the three polynomials
        print("p = " + str(p))
        #print()
        print("m(x) = ", end = '')
        print_polynomial(coeff_m)
        print("coeff_m = ", end = '')
        print(coeff_m)
        #print()
        print("q1(x) = ", end = '')
        print_polynomial(coeff_q1)
        while len(coeff_q1) < len(coeff_m)-1:
            coeff_q1.append(0)
        print("coeff_q1 = ", end = '')
        print(coeff_q1)
        #print()
        print("q2(x) = ", end = '')
        print_polynomial(coeff_q2)
        while len(coeff_q2) < len(coeff_m)-1:
            coeff_q2.append(0)
        print("coeff_q2 = ", end = '')
        print(coeff_q2)
        print()
    
if __name__ == "__main__":
    if len(sys.argv) == 1 :
        print("    Usage: run\n        python generate_input2.py [last three digits of your student number]\n    to obtain three tuples (N,(a1,a2,a3,a4)).\n    You must use your own code to determine p and q such that N=pq.")
    else :
        generate_input(int(sys.argv[1]),3)
