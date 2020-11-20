import sys
import random
from random import randrange

primes_list = [1073741827, 1073741831, 1073741833, 1073741839, 1073741843,
               1073741857, 1073741891, 1073741909, 1073741939, 1073741953,
               1073741969, 1073741971, 1073741987, 1073741993, 1073742037,
               1073742053, 1073742073, 1073742077, 1073742091, 1073742113,
               1073742169, 1073742203, 1073742209, 1073742223, 1073742233,
               1073742259, 1073742277, 1073742289, 1073742343, 1073742353,
               1073742361, 1073742391, 1073742403, 1073742463, 1073742493,
               1073742517, 1073742583, 1073742623, 1073742653, 1073742667,
               1073742671, 1073742673, 1073742707, 1073742713, 1073742721,
               1073742731, 1073742767, 1073742773, 1073742811, 1073742851,
               1073742853, 1073742881, 1073742889, 1073742913, 1073742931,
               1073742937, 1073742959, 1073742983, 1073743007, 1073743037,
               1073743049, 1073743051, 1073743079, 1073743091, 1073743093,
               1073743123, 1073743129, 1073743141, 1073743159, 1073743163,
               1073743189, 1073743199, 1073743207, 1073743243, 1073743291,
               1073743303, 1073743313, 1073743327, 1073743331, 1073743337,
               1073743381, 1073743387, 1073743393, 1073743397, 1073743403,
               1073743417, 1073743421, 1073743427, 1073743457, 1073743459,
               1073743469, 1073743501, 1073743507, 1073743513, 1073743543,
               1073743577, 1073743591, 1073743633, 1073743739, 1073743757]

# the extended Euclidean algorithm for integers
def xgcd(a, b):
    x0, x1, y0, y1 = 0, 1, 1, 0
    while a != 0:
        q, b, a = b // a, a, b % a
        y0, y1 = y1, y0 - q * y1
        x0, x1 = x1, x0 - q * x1
    return b, x0, y0

# computes the multiplicative inverse of a in Z/nZ
def ainv(n,a) :
    g, x, y = xgcd(a,n)
    if g != 1 :
        print(str(a) + " is not invertible mod " + str(n))
    else :
        ainv = x % n
        return ainv

def generate_input(s,count) :
    for token in range(s,s+count) :
        print("Input #" + str(token-s+1))
        
        random.seed(token)
        
        p = random.choice(primes_list)
        q = random.choice(primes_list)
        N = p*q
        phi = (p-1)*(q-1)
        e = phi-1
        d = ainv(phi,e)
        print("Private key (N,d) = " + "(" + str(N) + "," + str(d) + ")")
        m_r = random.choices(range(2**30),k = 2)
        m = m_r[0]
        r = m_r[1]
        m_str = format(m,'b')
        r_str = format(r,'b')
        m_str = m_str.zfill(30)
        r_str = r_str.zfill(30)
        n_str = r_str
        for i in range(30) :
            if m_str[i] == r_str[i] :
                n_str = n_str + "1"
            else :
                n_str = n_str + "0"
        n = int(format(int(n_str,2),'d'),10)
        c = pow(n,e,N)
        print("Ciphertext c = " + str(c))
        
if __name__ == "__main__":
    if len(sys.argv) == 1 :
        print("    Usage: run\n        python generate_input.py [last three digits of your student number]\n    to obtain three sets of inputs, each consisting of an RSA private key (N,d) and a ciphertext c .\n    You must use your own code to determine p and q such that N=pq.")
    else :
        generate_input(int(sys.argv[1]),3)
