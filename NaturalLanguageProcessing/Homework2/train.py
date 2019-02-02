import re, string
import json

class ngrams:

	def __init__(self, filename):
		self.inputFilename = filename
		self.__allNgrams = [{}, {}, {}, {}, {}]

	def clearTrainData(self, noisyText):
		'''This text has some nonlatin characters and XML markup
		Clear the data from this noise'''

		# Delete except ASCII characters and Turkish Characters
		noisyText = re.sub("[^\x00-\x7F\u00E7\u011F\u0131\u015F\u00F6\u00FC\u00C7\u011E\u0130\u015E\u00D6\u00DC]", "", noisyText)
		# Get rid of punctuaiton except period punctuaiton
		unwantedPuncs = "[" + re.sub("\.","",string.punctuation) +"]"
		clearText = re.sub(unwantedPuncs, "", noisyText)
	
		return clearText
		
	def writeToJSON(self, filename):
		'''Export the ngrams to JSON file'''

		with open(filename, "w") as file:
			json.dump(self.__allNgrams, file, 
				ensure_ascii=False, sort_keys=True, indent=4)

	def addOneSmoothing(self):

		for ngram in self.__allNgrams:
			for key in ngram:
				ngram[key] += 1

	def createCharNgrams(self, text = None):
		'''Create Ngrams. If the text and n values are None, this function called from test file
		If they are not None, this is a recursive call'''

		# If this is a call from test file, read the data
		if text is None:
			# Open the file and read
			with open(self.inputFilename, "r") as file:
				data = file.read()

			# Clear the train data
			data = self.clearTrainData(data)

			self.createCharNgrams(data)

			# Apply Laplace Smoothing
			self.addOneSmoothing()
			# Write to file
			self.writeToJSON("charNgrams.json")

		else:

			for i in range( len(text)):

				for n in range(1, 6):

					current = text[i:i+n]

					# If it is already exist in dict increase the frequency
					if current in self.__allNgrams[n-1]:
						self.__allNgrams[n-1][current] += 1
					# Else, add in dict with frequency 1
					else:
						self.__allNgrams[n-1][current] = 1

	def createSpellNgrams(self, data = None):

		if data is None:
			# Open the file and read
			with open(self.inputFilename, "r") as file:
				data = file.read()

			# Clear the train data
			data = data[:-1].split("-")

			self.createSpellNgrams(data)
			
			# Apply Laplace Smoothing
			self.addOneSmoothing()
			# Write to file
			self.writeToJSON("spellNgrams.json")

		else:

			for i in range(len(data)):

				for n in range(1, 6):

					key = str(data[i:i+n])

					# If it is already exist in dict increase the frequency
					if key in self.__allNgrams[n-1]:
						self.__allNgrams[n-1][key] += 1
					# Else, add in dict with frequency 1
					else:
						self.__allNgrams[n-1][key] = 1


		

	

		

