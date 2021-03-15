'''
def append_items(lst,new):
    answer = [i.copy() for i in lst]
    for item in answer:
        if new not in item:
            item.append(new)
    return answer



lst1 = [[1,2],[3],[4,5]]
new_lst1 = append_items(lst1,2)
print(new_lst1)
print(lst1)
'''

'''
class Riding:
    
    district = str 
    canVote = dict{social security numbers : True/False}
    voters = List[social security numbers]
    

    def __init__(self,name: str):
        self.district = name
        self.canVote = {}
        self.voters = []

    def add_voters(self,voters: [int]):
        for i in voters:
            if i not in self.voters:
                self.voters.append(i)
                self.canVote[i] = True

    def voted(self,voter:int):
        # voter in Riding 
        self.canVote[voter] = False

    def can_vote(self,voter: int):
        if voter in self.voters:
            return self.canVote[voter]
        else:
            return False

    

r = Riding('Donlands')
r.add_voters([5, 3, 9]) 
r.add_voters([1, 2, 3, 4]) # Adding voter 3 again does nothing and raises no error.
print(r.can_vote(2))
print(r.can_vote(6))
r.voted(2)
print(r.can_vote(2))

'''
from math import sqrt
from itertools import count, islice

def isPrime(n):
    return n > 1 and all(n % i for i in islice(count(2), int(sqrt(n)-1)))


def question4(n):
    if n == 0:
        return []
    else:
        primes = []
        if isPrime(n):
            primes = [n]
        primes += question4(n-1)
    return primes


n = 950
print(len(question4(n)))