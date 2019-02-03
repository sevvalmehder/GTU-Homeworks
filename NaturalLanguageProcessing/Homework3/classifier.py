import os
import json, operator

class textCategorizer:
    
    def __init__(self):
        """Constructor"""
        self._languages = ["english.dat", "french.dat", "spanish.dat"]
        self._languages_statistics = {}
        self._languages_dist = {}

    def loadLanguages(self):

        for language_file in self._languages:
            
            # Keep the name of language (english, french, spanish)
            language = language_file[:-4]

            ngram_statistics = open(language_file, mode='r', encoding = "ISO-8859-1").readlines()
            # Get ngrams without freqs
            ngram_statistics = [x.rstrip() for x in ngram_statistics]
            
            # The dictionary as like this: {language:most freq ngrams}
            self._languages_statistics.update({language:ngram_statistics})

        
    def calculateFreq(self, filename):
        '''If the language file is in the .json file without .bat file
        Get in them together in one dictionary and calculate most frequent items'''

        with open(filename, "r") as file:
            ngrams = json.load(file)

        ngramFreq = {}
        for ngram in ngrams:

            for gram in ngram:

                ngramFreq.update({gram:ngram[gram]})


        ngramsSorted =  sorted(ngramFreq.items(), key=operator.itemgetter(1), reverse = True)[0:300]

        return ngramsSorted

    def countNgrams(self, text):
        '''Find and count the most frequent ngrams in the given text'''
        inputNgrams = {}
        for i in range( len(text)):
                for n in range(1, 6):

                    current = text[i:i+n]

                    # If it is already exist in dict increase the frequency
                    if current in inputNgrams:
                        count = inputNgrams[current]
                        inputNgrams.update({current:count+1})
                    # Else, add in dict with frequency 1
                    else:
                        inputNgrams.update({current:1})

        sortedNgrams =  sorted(inputNgrams.items(), key=operator.itemgetter(1), reverse = True)[0:300]
        return sortedNgrams

    def compareWithTr(self, trFreq, unkFreq):
        '''Compare turkish most freq words with given text most freqs'''
        
        # Get the ngrams without values
        trNg = [ng[0] for ng in trFreq]
        unkNg = [ng[0] for ng in unkFreq]
        
        # If there is a item in unknown text but isnt in tr
        maxVal = 300

        tr_dist = 0
        # Compare most freq. item in the unknown word with
        # most freq. item in the language turkish
        for n in unkNg:
            try:
                unkIndex = unkNg.index(n)
                trIndex = trNg.index(n)
            except ValueError:
                trIndex = maxVal

            tr_dist += abs(trIndex - unkIndex)
        
        self._languages_dist.update({"turkish":tr_dist})

    def compareWithOthers(self, unkFreq):

        # Get the ngrams without values
        unkNg = [ng[0] for ng in unkFreq]
        # If there is a item in unknown text but isnt in tr
        maxVal = 300

        # Load the other languages
        self.loadLanguages()

        for lang, mostFreqNg in self._languages_statistics.items():

            # Get the ngrams without values
            mostNgs = [ng.split("\t")[0] for ng in mostFreqNg]

            lang_dist = 0
            for n in unkNg:
                try:
                    unkIndex = unkNg.index(n)
                    langIndex = mostNgs.index(n)
                    #print("unkIndex {}, other {}".format(unkIndex, langIndex))
                except ValueError:
                    langIndex = maxVal

                lang_dist += abs(langIndex - unkIndex)

                self._languages_dist.update({lang:lang_dist})
