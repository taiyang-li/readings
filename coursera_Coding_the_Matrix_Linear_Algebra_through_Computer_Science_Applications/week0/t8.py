#!/usr/bin/python


for i1 in range(1,10):
    for j1 in range(1,10):
        for k1 in range(1,10):
            for i2 in range(1,10):
                for j2 in range(1,10):
                    for k2 in range(1,10):
                        s1 = set()
                        s1.add(i1)
                        s1.add(j1) 
                        s1.add(k1)
                        
                        if len(s1) != 3:
                            break

                        s2 = set()
                        s2.add(i1)
                        s2.add(j2)
                        s2.add(k2)
                        
                        if len(s2) != 3:
                            break
                        
                        p = {x1 * x2 for x1 in s1 for x2 in s2}
                        if len(p) == 5:
                            print s1
                            print s2
                            print "\n"
                           
                        

