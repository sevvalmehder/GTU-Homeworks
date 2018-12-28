import os
import sys

def spellIt(word, fst, out):
	'''Spell the given word according to fst
	Then write the result at given output file'''
	os.system("echo {} | fst-infl {} >> {}". format(word, fst, out))
	os.system("sed -i '/{}/d' {}".format(word, out))

if __name__ == "__main__":

	if len(sys.argv) != 2:
		print("Usage: python testFst.py yourFST.a")
		exit()
		
	# Output file and fst to use
	outFile = "output.txt"
	fst = sys.argv[1]

	# Open the file and spell every word
	with open("dataset.txt") as fileP:
		for curWord in fileP:
			spellIt(curWord.rstrip(), fst, outFile)
			
