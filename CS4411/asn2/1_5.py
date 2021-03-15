import math as m

N = 4000
B = 50

N1 = m.ceil(N/(B))
x = m.ceil(m.log(N1,B-1))+1
print("# of buffer pages: {} \t # of passes:{}".format(B,x))

while x >= 3:
    B+=1
    N1 = m.ceil(N/(B))
    print(N1)
    x = m.ceil(m.log(N1,B-1))+1
    print("# of buffers: {} \t # of passes:{}".format(B,x))