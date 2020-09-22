
# number sets given through generate input 323
# x1, y1 (32416188767, 32241382686) 
# x2, y2 = (1050809276997196863379, 32416188127) 
# x3, y3 = (970516904892, 955775357338)

container = [   
            # tests
            (32416190039, 23716567735), (1050809318036091666301, 32416188517), (831018615847, 746527923770), 
            (32416188839, 20727961657), (1050809325491815514539, 32416189031), (637009706803, 455514560204),
            #323
            (32416188767, 32241382686), (1050809276997196863379, 32416188127) ,(970516904892, 955775357338)
            ]

#   solve function
def solve(m, a):
    trackA = 0                              # init reference to a
    result = 1                              # init result
    mod = m                                 # keep reference to original m
  
    while True:     
        floor = a // m                      # calculate floor

        temp = m                            # begin switching m and a
        m = a % m                           # m is now remainder
        a = temp                            # a is now m for next iteration   

        temp = trackA                       # temp is new a
        trackA = result - (temp * floor)    # calculate a used for next iteration
        result = temp                       # result is now new a

        if a == 1:
            break                           # finish when a is one

    if result < 0 : 
        result += mod                       # make result positive
  
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