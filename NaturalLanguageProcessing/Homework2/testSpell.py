import sys
import sys
import train as tr
import json

# ---------------------------- Spelling Function ------------------------------
# This function taken from https://github.com/teknokrat-as/heceleme repository

def hypo(x):
    i = 0
    vw = "aeıioöuü"
    cn = "bcçdfgğhjklmnprsştvyz"
    while i < len(x):
        if x[i] in vw:
            if i + 1 < len(x) and x[i+1] in vw:
                return x[0:i+1] + "-" + hypo(x[i+1:len(x)])
            elif i + 2 < len(x) and x[i+2] in vw:
                return x[0:i+1] + "-" + hypo(x[i+1:len(x)])
            elif i + 3 == len(x) and x[i+1] in cn and x[i+2] in cn:
                return x[0:i+3] + "-" + hypo(x[i+3:len(x)])
            elif i + 3 < len(x) and x[i+3] in vw:
                return x[0:i+2] + "-" + hypo(x[i+2:len(x)])
            elif i+3 < len(x) and x[i+1] in cn and x[i+2] in cn and x[i+3] in cn:
                return x[0:i+3] + "-" + hypo(x[i+3:len(x)])
            elif i + 3 < len(x) and x[i:i+3] == 'str' or 'ktr' or 'ntr':
                return x[0:i+2] + "-" + hypo(x[i+2:len(x)])
            else:
                return x[0:i+3] + "-" + hypo(x[i+3:len(x)])

        i += 1

    return x

# ------------------------- End of Spelling Function --------------------------

def getUnigrams(text):
	'''Calculate unigrams'''

	unigrams = []

	for word in text.split():
		spelled = hypo(word)
		for spell in spelled[:-1].split("-"):
			unigrams.append(spell)
		unigrams.append(" ")

	# Delete the last whitespace
	return unigrams[:-1]


def calcProbs(unigrams, ngrams):
	'''This function calculates perplexity for unigrams, bigrams.. '''

	ngramProbs = []

	for i in range(len(ngrams)):

		# This is the all probabilities of igram
		probs = []

		
		for j, g in enumerate(unigrams):

			gram = str([g])

			# if unigrams calculated
			if i == 0:
				prob = ngrams[i].get(gram) / sum(ngrams[i].values())
				probs.append(prob)

			# We must start i.th element when we calculate igram
			elif j >= i:
				wanted = str(unigrams[j-i:j+1])
				given = str(unigrams[j-i:j])
				#print("pay: {} / payda: {}".format(wanted, given))
				if wanted not in ngrams[i]:
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
		trainObj.createSpellNgrams()

	else:
		ngrams = []
		# Read the nrams file
		with open("spellNgrams.json", "r") as file:
			ngrams = json.load(file)

		while(1):
			# Get the text to test
			testText = input("What do you wanna test\n")
			unigrams = getUnigrams(testText)
			probs = calcProbs(unigrams, ngrams)
			perps = calcPerp(probs)
			print(perps)