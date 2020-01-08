import pickle
with open('record', 'r') as f:
    record = f.read()


def frequency_count(OurStr):
	freq= {}
	freq['(B#)(!S)'],freq['(B#)(S)'],freq['(B)(!S)'],freq['(B)(S)'] = {},{},{},{}
	Temp1,Temp2,Temp3,Temp4 = OurStr.replace(' ',''),OurStr,OurStr.replace(' ',''),OurStr
	freq['M'] = {}
	Temp0 = OurStr
	while len(Temp0)>0:
		if Temp0[0] in freq['M'].keys():
			freq['M'][Temp0[0]] += 1
		else:
			freq['M'][Temp0[0]] = 1
		Temp0 = Temp0[1:]
		

	while(len(Temp1)>1):
		if Temp1[0:2] in freq['(B#)(!S)'].keys():
			freq['(B#)(!S)'][Temp1[0:2]] += 1
		else:
			freq['(B#)(!S)'][Temp1[0:2]] = 1
		Temp1 = Temp1[1:]

	#while(len(Temp2)>1):
		if Temp2[0:2] in freq['(B#)(S)'].keys():
			freq['(B#)(S)'][Temp2[0:2]] += 1
		else:
			freq['(B#)(S)'][Temp2[0:2]] = 1
		Temp2 = Temp2[1:]

	#while(len(Temp3)>1):
		if Temp3[0:2] in freq['(B)(!S)'].keys():
			freq['(B)(!S)'][Temp3[0:2]] += 1
		else:
			freq['(B)(!S)'][Temp3[0:2]] = 1
		Temp3 = Temp3[2:]

	#while(len(Temp4)>1):
		if Temp4[0:2] in freq['(B)(S)'].keys():
			freq['(B)(S)'][Temp4[0:2]] += 1
		else:
			freq['(B)(S)'][Temp4[0:2]] = 1
		Temp4 = Temp4[2:]

	with open('entry.pickle', 'wb') as f:
		pickle.dump(freq, f)

frequency_count(record)
