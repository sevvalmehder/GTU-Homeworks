# Spelling words

This is a program that spells the Turkish words. [SFST](http://www.cis.uni-muenchen.de/~schmid/tools/SFST/) last version was used in this homework. SFST is a toolbox for the implementation of morphological analysers and other tools which are based on finite state transducer technology.
A short manual and a tutorial included in the source code package.

## Quick start
```
$ fst-compiler spelling.fst spelling.a  
$ fst-mor ex.a  
analyze >  
```
## Test
Compile your fst before using this test according to quick start part. Use dataset.txt for test document.  

After execute python test file with your final state transducer:
```
$ python testFST.py yourFST.a
```
there will be an output.txt file for spelled results.