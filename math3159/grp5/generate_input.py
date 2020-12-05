import sys
import random

p = [32416187567, 32416188191, 32416188127, 32416189987, 32416188691, 32416189079]
A = [100, 54, 19, 1004, 103245, 325]
B = [300, 456, 33, 9998, 992349, 233496]
Px = [27957624436, 27828875679, 16475848216, 21776342460, 8909974598, 6548599300]
Py = [9381314875, 24709261957, 5118271045, 26884854746, 12810966706, 15997014953]
Qx = [4926003430, 4979256242, 19262187694, 22858809622, 17766069436, 12258808117]
Qy = [24870962866, 12312669996,2854205065, 16175884785, 28295926988, 25905354257,]
e = [17242042885, 10269365243, 13332545241, 29713279001, 16789908933, 28582187811]
t1 = [8484016628, 29615329983, 9721955507, 18366438538, 20309635644, 3484632773]

ins = []
for i in range(6):
    ins.append([p[i],A[i],B[i],Px[i],Py[i],Qx[i],Qy[i],e[i],t1[i]])

def generate_input(student_number) :
    random.seed(student_number)
    random.shuffle(ins)
    
    for i in range(3):
        print("Input " + str(i+1))
        print(ins[i])

if __name__ == "__main__":
    if len(sys.argv) == 1 :
        print("    Usage: run\n        python generate_input.py [last three digits of your student number]\n    to obtain six tuples (p,A,B,Px,Py,Qx,Qy,e,t).\n    You must use your own code to determine p and q such that N=pq.")
    else :
        generate_input(int(sys.argv[1]))
