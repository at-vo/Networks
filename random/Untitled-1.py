for key1,items1 in totals.items():
        for key2,items2 in totals.items():
            # check key against used and each other
            broken = False
            if key1!=key2 and key1 not in used and key2 not in used:
                # iterate through
                for i in items1:
                    if broken == False:
                        for j in items2:
                            temp = {i[0],i[1],j[0],j[1]}
                            if len(temp)==4:
                                if temp.difference(sub) not in sub:
                                    # add a new value to 
                                    sub.add(i[0])
                                    sub.add(i[1])
                                    sub.add(j[0])
                                    sub.add(j[1])
                                    used.append(key1)
                                    used.append(key2)
                                    if len(sub)==n:
                                        return sub
                                    broken = True
                                    break

                    if broken == True:
                        break



temp = sub.copy()
removed = False
for index1, a in enumerate(temp,0):
    for index2, b in enumerate(temp,1):
        for index3, c in enumerate(temp,2):
            for index4, d in enumerate(temp,3):
                if len({a,b,c,d}) == 4 and a+b==c+d:
                    sub.remove(j)
                    removed = True
                    break
            if removed == True:
                break
        if removed == True:
            break
    if removed == True:
        break