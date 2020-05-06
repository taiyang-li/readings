#!/usr/bin/python


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

def orSearch(inverseIndex, query):
    res = set()
    for w in query:
        res = res | inverseIndex[w]
    return res


def andSearch(inverseIndex, query):
    for i in range(len(query)):
        if i == 0:
            res = inverseIndex[query[i]]
        else:
            res = res & inverseIndex[query[i]]
    return res



if __name__ == "__main__":
    strs = ['Johann Sebastian Bach', 'Johannes Brahms', 'Johann Strauss the Younger', 'Johann Strauss the Elder', ' Johann Christian Bach',  'Carl Philipp Emanuel Bach']
    idx =  makeInverseIndex(strs)
    print  orSearch(idx, ['Bach','the']) == {0, 2, 3, 4, 5} 
    print  orSearch(idx, ['Johann', 'Carl']) == {0, 2, 3, 4, 5}
    print  andSearch(idx, ['Johann', 'the']) == {2, 3}
    print  andSearch(idx, ['Johann', 'Bach']) == {0, 4}
   

