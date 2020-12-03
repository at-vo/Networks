
container = [7,97,2357421]
for i in container:
    a = i
    s = ''
    while a > 0:
        s += str(a % 10)
        a = int(a / 100)
    print(s)
    
num_times = 2
value = 3
result = 0
for i in range(num_times):
    result+=value
    value+=1
print(result)