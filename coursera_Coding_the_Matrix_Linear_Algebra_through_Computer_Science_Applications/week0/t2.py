#!/usr/bin/python


# strlist is a list of strs which is a sentence or a word 
def makeInverseIndex(strlist):  
    res = {}
    for i in range(len(strlist)):
        str = strlist[i]
        words = str.split()
        for w in words:
            if w not in res:
                res[w] = {i}
            else:
                res[w].add(i)
    return res


if __name__ == "__main__":
    strs = ['Ask', 'not', 'what', 'you', 'can', 'do', 'for', 'your', 'country', '.']
    print makeInverseIndex(strs)
    
    filename = "stories_small.txt"
    fp = open(filename)
    strs = list(fp)
    res =  makeInverseIndex(strs)
    print res
    fp.close()

    filename = "stories_big.txt"
    fp = open(filename)
    strs = list(fp)
    res =  makeInverseIndex(strs)
    print res
    fp.close()
    

