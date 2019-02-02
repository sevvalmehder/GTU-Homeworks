import sys
import train as tr
import json


def getUnigrams(text):
	'''Calculate unigrams'''

	unigrams = []
	for i in range(len(text)):
		unigrams.append(text[i:i+1])
	return unigrams

def calcProbs(unigrams, ngrams):
	'''This function calculates perplexity for unigrams, bigrams.. '''

	ngramProbs = []

	for i in range(len(ngrams)):

		# This is the all probabilities of igram
		probs = []

		for j, gram in enumerate(unigrams):
			# if unigrams calculated
			if i == 0:
				prob = ngrams[i].get(gram) / sum(ngrams[i].values())
				probs.append(prob)

			# We must start i.th element when we calculate igram
			elif j >= i:
				wanted = "".join(unigrams[j-i:j+1])
				given = "".join(unigrams[j-i:j])
				#print("pay: {} / payda: {}".format(wanted, given))
				if wanted not in ngrams[i]:
					ngrams[i][wanted] = 1
		
				prob = ngrams[i].get(wanted) / ngrams[i-1].get(given)

				probs.append(prob)

		ngramProbs.append(probs)
	
	return ngramProbs


def calcPerp(ngramProbs):

	# index i of perps is the perplexity of igram
	perps = []

	for probs in ngramProbs:
		perp = 1
		n = 0
		
		# Multiply 1/probabilities 
		for p in probs:
			n += 1
			perp *= 1/p

		print("Probability: {}".format(1/perp))
		perp = pow(perp, 1/float(n))
		perps.append(perp)

	return perps

if __name__ == '__main__':

	if len(sys.argv) > 1:
		print("Welcome to train mode..")
		testMode = False
		trainObj = tr.ngrams(sys.argv[1])
		trainObj.createCharNgrams()

	else:
		ngrams = []
		# Read the nrams file
		with open("charNgrams.json", "r") as file:
			ngrams = json.load(file)

		while(1):
			# Get the text to test
			testText = input("What do you want to test\n")
			unigrams = getUnigrams(testText)
			probs = calcProbs(unigrams, ngrams)
			perps = calcPerp(probs)
			print(perps)

	