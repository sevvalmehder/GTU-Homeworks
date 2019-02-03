import classifier as cl

if __name__ == '__main__':

	categorizer = cl.textCategorizer()

	# Load ngram frequencies for Turkish Language
	turkishFreqs = categorizer.calculateFreq("charNgrams.json")

	while(1):
		# Get an input
		unknownText = input("What do you want to test\n")
		unknownFreq = categorizer.countNgrams(unknownText)

		categorizer.compareWithTr(turkishFreqs, unknownFreq)
		categorizer.compareWithOthers(unknownFreq)

		print(categorizer._languages_dist)
		print("This predicted language is: {}".format(min(categorizer._languages_dist, key = categorizer._languages_dist.get)))