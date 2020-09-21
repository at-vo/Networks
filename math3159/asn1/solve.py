
# number sets given through generate input 
# (32416188767, 32241382686) 
# x2, y2 = (1050809276997196863379, 32416188127) 
# x3, y3 = (970516904892, 955775357338)

container = [(56,15), #(32416188767, 32241382686), (1050809276997196863379, 32416188127) ,(970516904892, 955775357338)
            ]

#   solve function
def solve(m, a):
    mod = m
    y = 0
    result = 1
  
    if (m == 1) : 
        return 0
  
    while (a > 1) : 
        print("a is {}".format(a))
        # q is quotient 
        floor = a // m 
        t = m 
  
        # m is remainder now, process 
        # same as Euclid's algo 
        m = a % m 
        print("m is {}".format(m))
        a = t 
        t = y 
        # Update result and y 
        y = result - floor * y 
        result = t 

    # Make result positive 
    if (result < 0) : 
        result += mod 
  
    return result 

#test


for i in container:
    m = i[0]
    a = i[1]
    try:
        solution = solve(m, a)
        print("the inverse of {} (mod  {}) is {}".format(a,m,solution))
    except ZeroDivisionError as ex:
        print("{} is not invertable (mod {})".format(a,m))

