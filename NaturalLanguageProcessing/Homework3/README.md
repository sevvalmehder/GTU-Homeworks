# Language Detection


This program is classifies the languages. This homework is based on ["N-Gram-Based Text Categorization (1994)" paper](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.53.9367) by William B. Cavnar and John M. Trenkle.  

We need top 300 most occurrences ngrams for each language. There are 3 .bat file for English, Spanish and French. For Turkish, charNgrams.json file in Homework2 must be used. Program will keep the 300 most occurrences ngrams for Turkish according to charNgrams.json.
 
## Test

This command will start the program. Program wants an input sentence and predict the language of this sentence in loop. 
```
python test.py
```
