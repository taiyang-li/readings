#!/usr/bin/python

def inv_dict(d):
    return {v:k for (k,v) in d.items()}


d = {'thank you':'merci', 'goodbye':'au revior'}
inv_d = inv_dict(d)
print inv_d
