haruffa = "абвгдежзийклмнопрстуфхцчшщьыэюя"


from math import gcd
def cTOn(f,s):
	flag1,flag2 = True,True
	number = 0
	for i  in range(0,len(haruffa)):
		if(flag1):
			if haruffa[i] == f:
				number += i*31
				flag1 = False
		if (flag2):
			if haruffa[i] == s:
				number += i
				flag2 = False

	return number



with open('05.txt', 'r') as f:
    record = f.read()

Temp = []
for i in range(0,len(record),2):
	Temp.append(record[i:i+2])


set_of_Temp = set(Temp)


array = [list(set_of_Temp),[0]*len(list(set_of_Temp))]

for i in Temp:
	for j in range(0,len(array[0])):
		if i == array[0][j]:
			array[1][j] += 1
temp = []
CTemp = Temp
def defFind(elem,arr):
	for j in range(0,len(arr)):
		if elem == arr[j]:
			return int(j)

def rev(F_,S_):
	A,B,C,D = 1,0,0,1
	while S_!=0:
		t1,t2 = divmod(F_,S_)
		F_,S_ = S_,t2
		A,B,C,D = C,D,(A - t1 * C),(B - t1 * D)
	return A

for i in [0,1,2,3,4]:
	index = defFind(max(array[1]),array[1])
	temp.append(array[0][index])
	del array[1][index]
	del array[0][index]


def slc(f,s,c):
	final = []
	if (gcd(f,c) != 1):
		if (s%gcd(f,c) == 0):
			temp_arr = [f/gcd(f,c),s/gcd(f,c),c/gcd(f,c)]
			for i in range(0,gcd(f,c)):
				final += [(rev(temp_arr[0],temp_arr[2])*temp_arr[1] + i * c)%c]
	else:
		final += [(rev(f,c)*s)%c]
	return final
def arr_without(elem,arr):
	tempA = []
	for i in arr:
		if i != elem:
			tempA +=[i]
	return tempA

saved = ['ст', 'но', 'то', 'на', 'ен']
saved_pare = []

for index_1 in saved:
	for index_2 in temp:
		for   index_3 in arr_without(index_1,saved):

			for index_4 in arr_without(index_2,temp):
				data = {}
				data['x0'] = cTOn(index_1[0],index_1[1])
				data['x1'] = cTOn(index_3[0],index_3[1])
				data['y0'] = cTOn(index_2[0],index_2[1])
				data['y1']=cTOn(index_4[0],index_4[1])

				e1 = data['x0']-data['x1']
				e2 = data['y0']-data['y1']

				Our = slc(e1,e2,(31**2))

				if len(Our) > 0:
					for i in Our:
						
						j = (data['y0'] - i*data['x0']) % (31**2)
						saved_pare.append([int(i),int(j)])


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

def check(tempSTR):
	print(find_(tempSTR))
	if find_(tempSTR)>0.055:

		return tempSTR
	else:
		return False
def GeTT(A,B,jedex):
	tempY = cTOn(jedex[0],jedex[1])
	AR = rev(A,(31**2))
	tempX = (rev(A,(31**2))*(tempY-B)) % (31**2)
	
	Last = tempX%31
	
	return haruffa[(tempX - Last)//31] + haruffa[Last]


def open(arr_keys,temp):
	for i in arr_keys:
		
		tempSTR,A,B="",i[0],i[1]
		print('\n[',i[0],':',i[1],']')

		for j in temp:
			tempSTR += GeTT(A,B,j)
	
		print(check(tempSTR))
		
		
diction = {}
for i in saved_pare:
	print(i)
	diction[i[0]]=i[1]

ArraY = []
for i in diction.keys():
	ArraY += [[i,diction[i]]]

#ArraY = [[654,777]]
open(ArraY,Temp)
print(saved_pare)