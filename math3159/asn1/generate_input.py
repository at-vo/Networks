import random
import sys

pms = [32416187567, 32416188223, 32416188809, 32416189391,
       32416187627, 32416188227, 32416188839, 32416189459,
       32416187651, 32416188241, 32416188859, 32416189469,
       32416187659, 32416188257, 32416188877, 32416189493,
       32416187701, 32416188269, 32416188887, 32416189499,
       32416187719, 32416188271, 32416188899, 32416189511,
       32416187737, 32416188331, 32416188949, 32416189573,
       32416187747, 32416188349, 32416189019, 32416189633,
       32416187761, 32416188367, 32416189031, 32416189657,
       32416187773, 32416188397, 32416189049, 32416189669,
       32416187827, 32416188449, 32416189061, 32416189681,
       32416187863, 32416188451, 32416189063, 32416189717,
       32416187893, 32416188491, 32416189079, 32416189721,
       32416187899, 32416188499, 32416189081, 32416189733,
       32416187927, 32416188517, 32416189163, 32416189753,
       32416187929, 32416188527, 32416189181, 32416189777,
       32416187933, 32416188583, 32416189193, 32416189853,
       32416187953, 32416188589, 32416189231, 32416189859,
       32416187977, 32416188601, 32416189261, 32416189867,
       32416187987, 32416188647, 32416189277, 32416189877,
       32416188011, 32416188689, 32416189291, 32416189909,
       32416188037, 32416188691, 32416189321, 32416189919,
       32416188113, 32416188697, 32416189349, 32416189987,
       32416188127, 32416188767, 32416189361, 32416190039,
       32416188191, 32416188793, 32416189381, 32416190071]

def big_random_numbers_less_than(s,top,count) :
    random.seed(s)
    return(random.sample(range(int(top/2),top),count))

def random_primes(s,count) :
    random.seed(s)
    return(random.sample(pms,count))

def generate_inputs(s) :
    N = 1000000000000

    ps = random_primes(s,3)

    p = ps[0]
    pa = big_random_numbers_less_than(s,p,1)[0]

    c = ps[1] * ps[2]
    ca = ps[1]

    n = big_random_numbers_less_than(s+2,N,1)[0]
    na = big_random_numbers_less_than(s+2,n,1)[0]

    print((p,pa),(c,ca),(n,na))


if __name__ == "__main__":
    if len(sys.argv) == 1 :
        print("    Usage: run\n        python generate_input.py [last three digits of your student number]\n    to obtain three pairs (N,a).\n    You must use your own code to compute a^(-1) (mod N).")
    else :
        generate_inputs(int(sys.argv[1]))
