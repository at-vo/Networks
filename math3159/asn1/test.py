
# number sets given through generate input 
# x1, y1 = (32416188767, 32241382686) 
# x2, y2 = (1050809276997196863379, 32416188127) 
# x3, y3 = (970516904892, 955775357338)

container = [
            # tests
            #(32416190039, 23716567735), (1050809318036091666301, 32416188517), (831018615847, 746527923770), 
            #(32416188839, 20727961657), (1050809325491815514539, 32416189031), (637009706803, 455514560204),
            #323
            (32416188767, 32241382686), (1050809276997196863379, 32416188127) ,(970516904892, 955775357338)
            ]

#   solve function
def solve(m, a):
    u = 1
    g = a
    x = 0
    y = m
    if(m == 1):
        return 1,1,1
    while True:
        if(y == 0):
            v = (g - ( a * u )) / m
            return g, u, v
        else:
            t = g % y 
            q = g//y
            s = u-(q*x)
            u = x 
            g = y
            x = s
            y = t
#test
for i in container:
    m = i[0]
    a = i[1]
    g,u,v = solve(m, a)
    if (u<0):
        u+=m
    if (g==1):
        print("the inverse of {} (mod  {}) is {}".format(a,m,u))
    else:
        print("{} is not invertable (mod {})".format(a,m))

