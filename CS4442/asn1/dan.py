import numpy as np
import matplotlib.pyplot as plt

#Used for formatting prints
regs = ["Linear", "2nd Order", "3rd Order", "4th Order"]

#Adds a scatter plot to the current graph with a marker
def add_plot(x_values, y_values, marker="o"):
    plt.scatter(x_values, y_values, marker=marker)

#Recursive function to expand a x vector into x: x->[x^N ... x : 1]. ie When 1 x:x->[x | 1]
def augment_array(orig_data, order = 1):
    if order == 1:
        return np.concatenate((orig_data.reshape((-1, 1)), orig_data.reshape((-1, 1))**0 ), axis=1)
    else:
        return np.concatenate((orig_data.reshape((-1,1))**order, augment_array(orig_data, order-1)), axis=1)

#Returns a function f(x) to compute errors with respect to some y_data
def err_func(y_data):
    return lambda data: np.sum((data - y_data)**2)/len(y_data)

#Returns a function f(x) to compute w for some data x using y_data
def w_func(y_data, lm = 0, i_hat = 0):
    return lambda data: np.linalg.inv(data.T @ data + lm*i_hat) @ data.T @ y_data

#Takes weight vector and x vector and computes their inner product
#ie returns w0*x0+w1*x1+...+wNxN
def compute_y(w, x):
    return w.T @ x

#Computes the N-degree regression on the training data
def regression(training_x, training_y, test_x, test_y, degree=1, lm=0, graph=True):
    #Extend training/test x data into the desired order
    train_data_x = augment_array(training_x, degree)
    test_data_x = augment_array(test_x, degree)

    #Set up error functions wrt their y data
    err_train_f = err_func(training_y)
    err_test_f = err_func(test_y)

    #Set up the training w_func wrt to its y_data (This cond may be removed)
    if lm == 0:
        w_train_f = w_func(training_y)
    else:
        i_hat = np.identity(degree + 1)
        i_hat[0,0] = 0
        w_train_f = w_func(training_y, lm, i_hat)
    
    #Compute the weights using training data and the w_fuc
    weights = w_train_f(train_data_x)

    #Compute the predicted y values using the weights for both training and test data
    train_weights_y = [compute_y(weights, x) for x in train_data_x]
    test_weights_y = [compute_y(weights, x) for x in test_data_x]

    #Compute the errors on the training and test data
    train_err = err_train_f(train_weights_y)
    test_err = err_test_f(test_weights_y)

    #Graph the training and test data wrt to their the computed values
    if graph:
        print("Average error ("+regs[degree-1]+" Regression):\n\tTraining Set: ",train_err, "\n\tTest Set", test_err)
        add_plot(training_x, training_y)
        plt.plot(training_x, train_weights_y)
        plt.title(regs[degree - 1]+" Regression vs Training Data")
        plt.show()

        add_plot(test_x, test_y)
        plt.plot(test_x, test_weights_y)
        plt.title(regs[degree - 1]+" Regression vs Test Data")
        plt.show()

    #Return a dictionary storing the weights, computed values and errors
    return {"weights": weights, "tr_y": train_weights_y, "te_y": test_weights_y, "tr_err": train_err, "te_err": test_err}

#Computes K fold cross validation for an M-polynomial regression on a set of lambdas
def k_fold_cross_validation(k, order, training_x, training_y, lambda_const = [0]):
    #Randomly Split the training data
    nt = np.random.permutation(training_x)
    #Compute the order of the permuted array wrt to the sorted values
    ord_arr = [np.asscalar(np.where(nt[val] == training_x)[0]) for val in range(len(nt))]
    
    #Re-order the sorted arrays wrt the permutation above
    new_training = training_x[ord_arr]
    new_training_y = training_y[ord_arr]

    #Split the data into k-groups
    t_set_x = np.split(new_training, k)
    t_set_y = np.split(new_training_y, k)

    #array of cross validation errors for all trials K
    cross_val_errors = []

    for i in range(k):
        #Leave the i-th set of K groups as the validation set
        validation_set_x = t_set_x[i]
        validation_set_y = t_set_y[i]
        #Regroup the remaining K-1 groups as the testing set and flatten them
        t_x = np.asarray(t_set_x[:i] + t_set_x[i+1:]).reshape(-1)
        t_y = np.asarray(t_set_y[:i] + t_set_y[i+1:]).reshape(-1)

        # Will run a regression for each lambda, so len(w_set) = len(lambda_const)
        #and len(w_set[x]["weights"]) for any x = order
        w_set = [regression(t_x, t_y, validation_set_x, validation_set_y, 4, lm, False) for lm in lambda_const]
        #For this trial K, errors store the testing error wrt to the lambdas
        errors = [n["te_err"] for n in w_set]
        #store the individual lambda errors for this trial
        cross_val_errors.append(errors)

    avg_err = []
    #The length of cross_val_errors is K where cross_val_errors[k] is all the individual testing errors for each lambda i
    for x in range(len(lambda_const)):
        tmp_sum = 0
        #add the error for lambda_const[x] for trial y 
        for y in range(len(cross_val_errors)):
            tmp_sum += cross_val_errors[y][x]
        #Put the average of errors for K trials into avg_err
        avg_err.append(tmp_sum/(len(cross_val_errors)))

    return (avg_err, lambda_const[avg_err.index(min(avg_err))])
    
#This function servers to load data from a file into a sorted np array
def load_data():
    test_x = np.fromfile("data/hw1xte.dat", sep=" ")
    test_y = np.fromfile("data/hw1yte.dat", sep=" ")

    #Load training data for plot
    training_x = np.fromfile("data/hw1xtr.dat", sep=" ")
    training_y = np.fromfile("data/hw1ytr.dat", sep=" ")

    #Sort the data into increasing x order
    training_y = training_y[np.argsort(training_x)]
    training_x = np.sort(training_x)

    test_y = test_y[np.argsort(test_x)]
    test_x = np.sort(test_x)

    return (training_x, training_y, test_x, test_y)

def main():
    #load the data from the files
    training_x, training_y, test_x, test_y = load_data()
    lambda_const = [0.01, 0.1, 1, 10, 100, 1000, 10000]

    #Plot the original training and test data
    add_plot(training_x, training_y)
    plt.title("Training Data")
    plt.show()

    add_plot(test_x, test_y, "^")
    plt.title("Test Data")
    plt.show()

    #Compute the regressions for 1, 2, 3, 4 -> Linear to 4th Order polynomial 
    regression_set = [regression(training_x, training_y, test_x, test_y, order,False) for order in range(1, 5)]
    #Pull out all the testing set errors from the computed regressions
    errors = [err["te_err"] for err in regression_set]
    
    #The data with the smallest testing set errors 
    print("The best order for fitting the data based on test error is: ", errors.index(min(errors)) + 1)

    #Compute the 4-th Order polyninomial regression on the data using various lambda constants
    lm_reg = [regression(training_x, training_y, test_x, test_y, 4, lm, False) for lm in lambda_const]
    
    #Extract the training and testing errors from the regressions (respectively)
    lm_reg_errors_tr = [x["tr_err"] for x in lm_reg]
    lm_reg_errors_te = [x["te_err"] for x in lm_reg]
    
    #The best lambda to use should have resulted in the lowest error on the testing data
    print("Best lambda (Q3 A): ", lambda_const[lm_reg_errors_te.index(min(lm_reg_errors_te))])

    #Plot Training/Testing errors vs Lambda Constant
    plt.plot(lambda_const,lm_reg_errors_tr, label="Training Error")
    plt.plot(lambda_const, lm_reg_errors_te, label="Test Error")
    plt.xscale("log")
    plt.title("Errors vs Lambda")
    plt.legend()
    plt.show()
    
    #Extract all the wN generated by the different lambdas into an array such that [[w0L0, w0L1...w0LI], ... ,[wNL0, ... wNLI]]
    #where N is the order of the polynomial and I the index of the lambda used to generate wN
    w_from_lm_reg = [[lm_reg[x]["weights"][y] for x in range(len(lambda_const))] for y in range(len(lm_reg[0]["weights"]))]

    #loop through the array to create plots of Weights vs Lambda
    for i in range(len(w_from_lm_reg)):
        plt.plot(lambda_const, w_from_lm_reg[i], label="w"+str(i))
    plt.title("Weight Parameters vs Lambda")
    plt.xscale("log")
    plt.legend()    
    plt.show()

    #Compute k-fold cross validation on our training data for each lambda and extract the avg_error array and best lambda to use
    avg_error, lm = k_fold_cross_validation(5, 4, training_x, training_y, lambda_const)
    print("Best lambda (Q3 C): ", lm)

    #Plot the avg error vs lambda constants
    plt.plot(lambda_const, avg_error)
    plt.title("Cross Validation Average Error vs Lambda Const")
    plt.xscale("log")
    plt.show()

    #Compute the 4th order polynomial regression for the best lambda above
    best_fit = regression(training_x, training_y, test_x, test_y, 4, lm, False)
    #Plot the test data and the regression line
    add_plot(test_x, test_y)
    plt.plot(test_x, best_fit["te_y"])
    plt.title("Best Fit Cross Validation vs Testing Data")
    plt.show()
 
main()

