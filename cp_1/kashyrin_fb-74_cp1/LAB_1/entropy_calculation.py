import pickle
from math import log2 as Logarifm
with open('entry.pickle', 'rb') as f:
	freq = pickle.load(f)


def AddToE (first,All):
	return (first/All)*(Logarifm(first/All))


def Find_H(name):
	Sum,H = 0,0
	for i in freq[name].keys():
		Sum += freq[name][i]
	for i in freq[name].keys():
		H -= AddToE(freq[name][i],Sum)
	return H/2

"""
Here you can find comments on variables in the program
H1: counting the entropy of monograms of text with spaces
H2: counting the entropy of monograms of text without spaces
H3: calculation of the entropy of bigrams without spaces with overlaps
H4:	calculation of the entropy of bigrams with overlaps and spaces
H5:	calculation of the entropy of bigrams without overlaps and spaces
H6:	calculation of the entropy of bigrams without overlaps and  with spaces

"""

Sum,H = 0,0
for i in freq['M'].keys():
	Sum += freq['M'][i]
for i in freq['M'].keys():
	H -= AddToE(freq['M'][i],Sum)

print('counting the entropy of monograms of text with spaces:',format(H))


Sum,H = Sum -freq['M'][' '],0
for i in freq['M'].keys():
	if i!= ' ':
		H -= AddToE(freq['M'][i],Sum)	

print('counting the entropy of monograms of text without spaces:',format(H))
print('calculation of the entropy of bigrams without spaces with overlaps:',Find_H('(B#)(!S)'))
print('calculation of the entropy of bigrams with overlaps and spaces:',Find_H('(B#)(S)'))
print('calculation of the entropy of bigrams without overlaps and spaces:',Find_H('(B)(!S)'))
print('calculation of the entropy of bigrams without overlaps and  with spaces:',Find_H('(B)(S)'))
print('redundancy: ',(1-(1.041+1.872)/10))