'''
        DAT VO
        250983323
        CS 4442
        BOYU WANG
'''

import matplotlib.pyplot as plt
import numpy as np
from numpy.lib.shape_base import column_stack
import pandas as pd

def readfile(predict,expect):
    dataX = []
    dataY = []
    xfile = open(predict,"r")
    yfile = open(expect,"r")
        
    for xread in xfile:
        yread = yfile.readline()
        dataX.append(float(xread.strip('\n'))) 
        dataY.append(float(yread.strip('\n')))

    xfile.close()
    yfile.close()

    return dataX, dataY

def hypothesis(x,theta):
    y1 = theta*x
    return np.sum(y1, axis=1)

def error(x,y,theta,m):
    y1 = hypothesis(x, theta)
    return sum(np.sqrt((y1-y)**2))/(2*m)

def gradient(x, y, theta, alpha, epoch,m):
    J=[]
    k=0
    while k < epoch:
        y1 = hypothesis(x, theta)
        for c in range(0, len(x.columns)):
            theta[c] = theta[c] - alpha*sum((y1-y)* x.iloc[:, c])/m
        j = error(x, y, theta,m)
        J.append(j)
        k += 1
    return J, theta


def main():
    # PATH variables for data
    pathXTR = "data\hw1xtr.dat"
    pathYTR = "data\hw1ytr.dat"
    pathXTE = "data\hw1xte.dat"
    pathYTE = "data\hw1yte.dat"

    # generate arrays for data
    xtrData, ytrData = readfile(pathXTR,pathYTR)
    xteData, yteData = readfile(pathXTE,pathYTE)

    data = {'bias':[1. for i in range(len(xtrData))],'x':xtrData,'y':ytrData}
    trData = pd.DataFrame(data)
    y = trData['y']
    x = trData.drop(columns='y')

    x['x^2'] = x['x']**2
    x['x^3'] = x['x']**3
    print(x.head())



    # fig, axs = plt.subplots(2)
    # fig.suptitle("TR AND TE DATA")
    # axs[0].scatter(xtrData, ytrData,None,"red")
    # axs[1].scatter(xteData, yteData)
    # plt.show()

if __name__ == '__main__':
    main()
    


