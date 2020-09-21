def modInverse(a, m) : 
    m0 = m 
    y = 0
    x = 1
  
    if (m == 1) : 
        return 0
  
    while (a > 1) : 

        # q is quotient 
        q = a // m 
        t = m 
  
        # m is remainder now, process 
        # same as Euclid's algo 
        m = a % m 
        a = t 
        t = y 
  
        # Update x and y 
        y = x - q * y 
        x = t 

        print(a)
  
    # Make x positive 
    if (x < 0) : 
        x = x + m0 
  
    return x 
  
  
# Driver program to test above function 
a = 15
m = 56

print("Modular multiplicative inverse is", modInverse(a, m)) 

