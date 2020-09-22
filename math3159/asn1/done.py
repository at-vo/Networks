
# number sets given through generate input 
# (32416188767, 32241382686) 
# x2, y2 = (1050809276997196863379, 32416188127) 
# x3, y3 = (970516904892, 955775357338)

container = [   
                (56,15), 
                #(32416188767, 32241382686), 
                #(1050809276997196863379, 32416188127) ,
                #(970516904892, 955775357338)
            ]

#   solve function
def solve(m, a):
    trackA = 0                              # init reference to a
    result = 1                              # init result
    mod = m                                 # keep reference to original m

    if m == 1: 
        return 0
  
    while a > 1:     
        floor = a // m                      # calculate floor

        temp = m                            # begin switching m and a
        m = a % m                           # m is now remainder
        a = temp                            # a is now m for next iteration   

        temp = trackA                       # temp is new a
        trackA = result - (trackA * floor)  # calculate a used for next iteration
        result = temp                       # result is now new a


    if result < 0 : 
        result += mod                       # make result positive
  
    return result 

#test
for i in container:
    m = i[0]
    a = i[1]
    try:
        print("the inverse of {} (mod  {}) is {}".format(a,m,solve(m, a)))
    except ZeroDivisionError as ex:
        print("{} is not invertable (mod {})".format(a,m))