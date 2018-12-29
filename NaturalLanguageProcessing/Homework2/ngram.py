# Load in all the modules we are going to need
import re, string
import sys

def getTrainData(filename):
	with open(filename, "r") as file:
		text = file.read()

	# Delete except ASCII characters and Turkish Characters
	text = re.sub("[^\x00-\x7F\u00E7\u011F\u0131\u015F\u00F6\u00FC\u00C7\u011E\u0130\u015E\u00D6\u00DC]", "", text)
	# Get rid of punctuaiton except period punctuaiton
	unwantedPuncs = "[" + re.sub("\.","",string.punctuation) +"]"
	text = re.sub(unwantedPuncs, "", text)
	
	return text

def createNgrams(n):
	'''Find all ngrams and their frequency'''

	# Create an emoty dict for ngrams
	ngrams = {}
	
	for i in range(len(text)-n+1):
		current = text[i:i+n]
		# If it is already exist in dict increase the frequency
		if current in ngrams:
			ngrams[current] += 1;
		# Else, add in dict with frequency 1
		else:
			ngrams[current] = 1;
	
	return ngrams

def calcTotal(ngram):
	''' Calculate the values of ngram dict'''
	total = 0
	for val in ngram.values():
		total += val
	return total

if __name__ == "__main__":

	# Check the console arguments then get the n
	if len(sys.argv) != 3:
		print("Usage: python ngram.py filename n")
		exit()
	else:
		filename = sys.argv[1]
		n = int(sys.argv[2])
	
	# Check the n value
	if n > 5:
		print("I am sorry, I can't handle over than 5grams")
		exit()

	# Read train data and get rid of unneccessary things
	text = getTrainData(filename)

	# Create ngrams with given n 
	ngrams = createNgrams(n)
	
	allNgrams = []
	for i in range(n):
		allNgrams.append(createNgrams(i+1))

	## TEST ##
	test = getTrainData("deneme.txt")
	
	markov = True
	prob = 1
	for i in range(len(test)-n+1):
		currentNgram = test[i:i+n]
		prevNgram = test[i:i+n-1]
		if n == 1:
			prob = allNgrams[n-1][currentNgram]/calcTotal(allNgrams[n-1])
		else:
			prob *= allNgrams[n-1][currentNgram]/allNgrams[n-2][prevNgram]

		if markov and i == 2:
			print("result: {}".format(prob))
			exit()

	print("result: {}".format(prob))