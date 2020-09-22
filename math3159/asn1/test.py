
# number sets given through generate input 
# x1, y1 = (32416188767, 32241382686) 
# x2, y2 = (1050809276997196863379, 32416188127) 
# x3, y3 = (970516904892, 955775357338)

container = [(56,15), (651161546456454643531,456456454664), (32416188767, 32241382686), (1050809276997196863379, 32416188127) ,(970516904892, 955775357338)
            ]

#   solve function
def solve(m, a):
    u = 1
    g = a
    x=0
    y=m
    if(m==1):
        return 1,1,1
    while True:
        if(y==0):
            v = (g-(a*u))/m
            return g, u, v
        else:
            t = g % y 
            q = g//y
            s=u-(q*x)
            u = x 
            g=y
            x=s
            y=t

    

#test


for i in container:
    m = i[0]
    a = i[1]
    g,u,v = solve(m, a)
    if (u<0):
        u+=m
    if (#u!=1 #and v!=1 and v>0
    ):
        #print("the inverse of {} (mod  {}) is {}".format(a,m,u))
        print("g: {} u: {} v: {}".format(g,u,v))

    else:
        print("g: {} u: {} v: {}".format(g,u,v))

        #print("{} is not invertable (mod {})".format(a,m))

