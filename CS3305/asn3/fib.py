'''
Dat Vo 
250983323
'''

'''Part A'''
def fib(n):
    if (n==1):                  # base case =1 
        return 1
    elif (n==0):                # base case =10
        return 0
    return fib(n-1)+fib(n-2)    #return current frame 
# function call
for i in range(0,11):
    at = fib(i*5)               # every 5 fibonaccis
    print("fibonacci at %d is %d"%(i*5,at))

'''Part B'''
def fibonacci(n,fib):
    if (n==1):                  # base case =1 
        return [0,1]
    elif(n==0):                 # base case =0
        return [0,0]
    fib = fibonacci(n-1,fib)    # decrease n and call again
    nextFib = fib[0]+fib[1]     # add fibonacci 
    fib[0]=fib[1]               # assign last fibonacci
    fib[1] = nextFib            # assign next fibonacci
    return fib

# function call
for i in range(0,31):
    fib = [0,0]
    fib = fibonacci(i*10,fib)   # every 10 fibonaccis
    print("fibonacci at %d is %d"%(i*10,fib[1]))
