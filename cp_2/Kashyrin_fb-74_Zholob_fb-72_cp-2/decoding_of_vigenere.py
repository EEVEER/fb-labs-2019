haruffa = "абвгдежзийклмнопрстуфхцчшщъыьэюя"


with open('5',encoding='utf-8') as f:
    record = f.read()


def addToInd(curr,All):
	return (curr)*(curr-1)/(All*(All-1))


def find_(temp):
	Temp,Len = {},len(temp)

	while len(temp)>0:
		if temp[0] in Temp.keys():
			Temp[temp[0]] += 1
		else:
			Temp[temp[0]] = 1
		temp = temp[1:]
	Index = 0
	for i in Temp.keys():
		Index += addToInd(Temp[i],Len)

		

	return Index

def get_Len(temp):

	j,i = 2,[0,0]

	while j < 20:
		print(find_(temp[::j]),j)
		if i[0]<find_(temp[::j]):
			i[0],i[1]=find_(temp[::j]),j
		j +=1
	return i 


def segmentation(temp,L):


	arr = []
	for i in range(0,L):
		arr.append("")
	
	for i in range(0,len(temp)):
		arr[i%L]+=(temp[i])
	return arr
def Gett(array,elem):
	for i in range(0,len(array)):
		if elem == array[i]:
			return i


def find_freq(temp):
	Temp,Len = {},len(temp)

	while len(temp)>0:
		if temp[0] in Temp.keys():
			Temp[temp[0]] += 1
		else:
			Temp[temp[0]] = 1
		temp = temp[1:]
	
	arr = [[],[]]
	for i in Temp.keys():
		arr[0].append(i)
		arr[1].append(Temp[i])

	
	most_freq = []
	for i in [0,1,2]:
		index = Gett(arr[1],max(arr[1]))
	
		
		elem_ind = (haruffa.find((arr[0])[index]) - haruffa.find('о') )%32
		most_freq.append(haruffa[elem_ind])
		del arr[0][index]
		del arr[1][index]
 
	
	return(most_freq)

def open(KEY,text,Lkey):
	z,clearTXT=0,""


	while z < len(text):

		first = haruffa.find(KEY[z%Lkey])
		second = haruffa.find(text[z])
		current = (- first + second)%len(haruffa)
		clearTXT += haruffa[current]
		z +=1
	return clearTXT

Lkey = get_Len(record)[1]

split_text = segmentation(record,Lkey)

for I in range(0,Lkey):

	print(find_freq(split_text[I]))


KEY = str(input ('Input your key: '))
#KEY = "делолисоборотней"
print(KEY)
print(Lkey)

print(open(KEY,record,Lkey))







