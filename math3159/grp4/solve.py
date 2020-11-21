from generate_input import generate_input

# student number 323
container = {
                (33555817, 3125, 9765625, 8, 23, 7523293, 28614582, 22256958, 3172621),             # input 1
                (33555751, 243, 30542048, 19, 14, 295845, 20826997, 14325870, 33485282),            #  .
                (33555553, 16807, 14030825, 8, 6, 11030354, 28131596, 11478229, 14555684),          #  .
                (33555493, 32, 32768, 10, 3, 11152483, 15342455, 29806492, 13155273),               #  .
                (33554699, 32, 32768, 14, 13, 2043221, 31335333, 2043221, 32352142), 
                (33554579, 32, 33554432, 31, 16, 24539544, 31870077, 24539544, 22718828), 
                (33555659, 32, 1048576, 17, 10, 1105213, 14101769, 18155557, 5893352), 
                (33555383, 16807, 11701571, 11, 20, 447397, 16228604, 28817193, 13965411), 
                (33555617, 243, 14348907, 10, 5, 13845724, 12977014, 30017090, 26275185), 
                (33555817, 3125, 9765625, 8, 23, 7523293, 28614582, 22256958, 3172621)              # input 10
            }

# # expamples
# container = {
#                 (31,26,30,18,11,6,24,6,25),                                                         # 21
#                 (348149, 113459, 185149, 153405, 127561, 208913, 209176, 208913, 217800 ),          # 72729
#                 (4139, 32, 1644, 3782, 2220, 3776, 1722, 2924, 3616)                                # no
#             }

def gcd(a,b):
    if b==0:
        return a
    else:
        return gcd(b,a%b)


def solve(p, g, A, D, D_p, s1, s2, s1_p, s2_p):
    if s1!=s1_p:
        return "no"

    left = (s1 * (s1_p - s2)) % (p-1)
    #right = (s2_p*D - s2*D_p) % (p-1)

    # Shanks
    M = 1 + int(p ** (1/2))
    list1 = []
    list2 = []
    for i in range (M+1):
        # store g^[0...M]
        list1.append(g ** i % p)
        # calculate fermat's little theorem
        s = pow(g, p-2, p)
        t = pow(s, M, p)
        u = pow(t, i, p)
        # store hg^[-iM]
        list2.append(A * u % p)

    if gcd(left,p-1)==1:
        # find matching entries in the lists
        for i in list1:
            if i in list2:
                # calculate x then return
                return list1.index(i) + list2.index(i) * M
    #solutions = gcd(left,p-1)
    # find matching entries in the lists
    for i in list1:
        if i in list2:
            # calculate x then return
            x = list1.index(i) + list2.index(i) * M
            if (pow(g,x) - A) % p == 0:
                return x




# container = generate_input(323)
for x in container:
    p, g, A, D, D_p, s1, s2, s1_p, s2_p = x[0], x[1], x[2],x[3], x[4], x[5],x[6], x[7], x[8]
    print("input: ", p, g, A, D, D_p, s1, s2, s1_p, s2_p)
    print(solve(p, g, A, D, D_p, s1, s2, s1_p, s2_p))