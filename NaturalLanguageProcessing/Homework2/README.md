# Ngrams

This is a program that counts the character and spell ngrams in given corpus. 
Then calculates the probability and perplexity of given sentence.  

wiki_00 can be used as corpus for character ngrams.

## Train

Train the corpus with this command according to characters. After this command executed, charNgrams.json must be created. This json file include the ngrams and their counts.
```
python testChar.py <corpus.txt> 
```

## Test

Test with this command according to characters. Program wants the input firstly then calculates the probability and perplexity of this input.
```
python testChar.py 
```