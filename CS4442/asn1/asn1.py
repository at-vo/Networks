'''
        DAT VO
        250983323
        CS 4442 ASN 1
        BOYU WANG
'''

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

degreeList = ["Linear", "2nd Order", "3rd Order", "4th Order"]

def readfile(predict,expect):
    xdata = np.fromfile(predict, sep=" ")
    ydata = np.fromfile(expect, sep=" ")

    # sort data
    ydata = ydata[np.argsort(xdata)]
    xdata = np.sort(xdata)

    return xdata, ydata


def hypothesis(w,x):
    return w.T @ x

def errorfn(y):
    return lambda y1: np.sum(pow((y1 - y),2))/len(y)

def gradient(y):
    return lambda x: np.linalg.inv(x.T @ x) @ x.T @ y


def regression(xtrData,ytrData,xteData,yteData,degree=1):

    # create training dataFrame
    trdataobject = {'x':xtrData,'y':ytrData}
    trData = pd.DataFrame(trdataobject)
    trData = pd.concat([pd.Series(1., index=trData.index, name='bias'), trData], axis=1)
    ytr = trData['y']
    xtr = trData.drop(columns='y')


    # create testing dataFrame
    tedataobject = {'x':xteData,'y':yteData}
    teData = pd.DataFrame(tedataobject)
    teData = pd.concat([pd.Series(1., index=teData.index, name='bias'), teData], axis=1)
    yte = teData['y']
    xte = teData.drop(columns='y')

    if degree > 1:
        exp = 2
        # add the next exponents 
        while exp <= degree:
            xte[exp] = xte['x']**exp
            xtr[exp] = xtr['x']**exp
            exp+=1

    # convert to numpy
    xte = xte.to_numpy()
    xtr = xtr.to_numpy()
    yte = yte.to_numpy()
    ytr = ytr.to_numpy()
    
    # gradient function on y training 
    wTr = gradient(ytr)
    # weights on x training 
    weights = wTr(xtr)

    # compute y1 values for weights
    y1Tr = [hypothesis(weights,x) for x in xtr]
    y1Te = [hypothesis(weights,x) for x in xte]

    # error functions
    errTrfn = errorfn(ytr)
    errTefn = errorfn(yte)

    # compute training errors 
    errTr = errTrfn(y1Tr)
    errTe = errTefn(y1Te)

    # graph training 
    fig,axs = plt.subplots(2)
    fig.tight_layout()
    axs[0].scatter(xtrData, ytrData)
    axs[0].set_title(degreeList[degree - 1] + " Regression vs Training Data")
    axs[0].plot(xtrData, y1Tr,color="yellow")

    # graph testing
    axs[1].scatter(xteData, yteData)
    axs[1].set_title(degreeList[degree - 1] + " Regression vs Test Data")
    axs[1].plot(xteData, y1Te,color="yellow")
    plt.show()

    # report average error
    print("\nRegression Model: ", degreeList[degree-1])
    print("Average error of Training: ", errTr)
    print("Average error of Testing: ", errTe)

    # return dict of values
    return {"ws": weights, "y1tr": y1Tr, "y1te": y1Te, "errTr": errTr, "errTe": errTe}

def kfold():
    
    return

def main():
    # PATH variables for data
    pathXTR = "data\hw1xtr.dat"
    pathYTR = "data\hw1ytr.dat"
    pathXTE = "data\hw1xte.dat"
    pathYTE = "data\hw1yte.dat"

    # generate arrays for data
    xtrData, ytrData = readfile(pathXTR,pathYTR)
    xteData, yteData = readfile(pathXTE,pathYTE)

    #Plot the original training and test data
    fig,axs = plt.subplots(2)
    fig.tight_layout()
    axs[0].scatter(xtrData, ytrData)
    axs[0].set_title("Training Data")

    axs[1].scatter(xteData, yteData)
    axs[1].set_title("Test Data")
    plt.show()

    regressions = [regression(xtrData, ytrData, xteData, yteData, i) for i in range(1,5)]


    return 0

    



if __name__ == '__main__':
    main()
    


