# def fib(n):
#     if (n==1):
#         return 1
#     elif (n==0):
#         return 0
#     return fib(n-1)+fib(n-2)

# for i in range(0,11):
#     print(fib(i*5))


# def fibB(n):
#     arr=[0,1]
#     for i in range(2,n+1):
#         arr.append(arr[i-1]+arr[i-2])
#     return arr
# for i in range(0,31):
#     z = fibB(i*10)
#     print("fibonacci for %d is %d "%(i*10, z[i*10]))


def fib(n):
    if (n==1):
        return 1
    elif (n==0):
        return 0
    a = fib(n-1)
    b = fib(n-2)
    c=a+b
    return c

for i in range(0,31):
    a = fib(i*10)
    print("fibonacci for %d is %d "%(i*10, a))
