import re
import string
import collections

#Fuction that opens file, creates dictionary, and counts items
def ItemCounter():
	with open('CS210_Project_Three_Input_File.txt') as file:
		groceryItems = collections.Counter(line.strip() for line in file)
#for loop that prints contents of dictionary
	for key in groceryItems:
		print('%s %d' % (key, groceryItems[key]))

	file.close()

#Function that returns the number of times of a user-input search item
def CountInstances(s):
	s = s.capitalize()
#Open the file to read and uses the built-in count function
	with open('CS210_Project_Three_Input_File.txt') as file:
		data = file.read()
		occurences = data.count(s)
	return occurences

	file.close()

#Function that creates file with each grocery item and the number of occurence
def DataWriter():
	with open('frequency.dat', "w") as writeFile: 
		with open('CS210_Project_Three_Input_File.txt') as file:
			groceryItems = collections.Counter(line.strip() for line in file)
#For loop that writes the item and counts to the output file
			for key in groceryItems:
				writeFile.write('%s %d\n' % (key, groceryItems[key]))

	file.close()
	writeFile.close()