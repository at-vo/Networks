from generate_input import generate_input

def mr(n, e, d):

    top = [5,7,13]
    p = 1
    q = 1
    found = False
    i = 0
    while not found and i<len(top):
        a = top[i]
        ed = e * d
        if 1 < gcd(a, n) < n:
            p = a
            q = int(n/a)
            if q!=1:
                found = True
                break
        k = 1
        while (ed - 1) % (pow(2,k)) == 0:
            k = k + 1
        k = k - 1

        m = (ed - 1) // pow(2,k)
        a = pow(a,m,n)
    
        seq = []

        for i in range(k):
            seq.append(a % n)
            a = pow(a,2,n)

        for x in seq:
            if gcd (n,x-1) > 1:
                p = gcd (n,x-1)
                q = int(n / p)
                if q!=1:
                    found=True
                    break
        i+=1
    return p, q


def gcd(a, b):
    if (b == 0):
        return a
    else:
        return gcd(b, a % b)

l = generate_input("323")
for x in l:
    N, e, d = x[0], x[1], x[2]
    print("input: ", N, e, d)
    print(mr(N, e, d))
