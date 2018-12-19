# Syllabify words

This is a program that syllabifies the Turkish words. [SFST](http://www.cis.uni-muenchen.de/~schmid/tools/SFST/) last version was used in this homework. SFST is a toolbox for the implementation of morphological analysers and other tools which are based on finite state transducer technology.
A short manual and a tutorial included in the source code package.

## Quick start

$ fst-compiler syllabify.fst syllabify.a  
$ fst-mor syllabify.a  
analyze >  