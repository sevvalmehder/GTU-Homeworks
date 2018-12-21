$cons$ = b|c|ç|d|f|g|ğ|h|j|k|l|m|n|p|r|s|ş|t|v|y|z
$vowel$ = a|e|ı|i|o|ö|u|ü

%
% Syllables with 3 or 4 letters
% For ex: "alp", "kar", "türk"
%
$single_syllable$ = $vowel$ $cons$ $cons$ | $cons$ $vowel$ $cons$| $cons$ $vowel$ $cons$ $cons$

% If there is a consonant between two vowels the consonant belongs to previous vowel: "a-ra"
% It could be a recursive "a-ra-ba-lar-ım"
$R1$ = $cons$? $vowel$ <->:<> $cons$ $vowel$ $cons$? (<->:<> $cons$ $vowel$ $cons$?)* $cons$?

% If there is two consonant side by side first one belongs to previous and the other one belongs to next
% "sev-mek", "sev-mek-ten"
$R2$ = ($cons$? $vowel$)? $cons$ <->:<> $cons$ $vowel$ ($cons$ <->:<> $cons$ $vowel$ )* (<->:<> $cons$ $vowel$ $cons$?)* $cons$?

% If there is three consonant side by side 
% First 2 consonant belongs to previous and the other one belongs to next
$R3$ = ($cons$? $vowel$)? $cons$ $cons$ <->:<> $cons$ $vowel$ $cons$? (<->:<> $cons$ $vowel$ $cons$?)* $cons$?

% R3 follows R1 for example "u-çurt-ma"
$R1R3$ = $R1$ $R3$ 

% R3 follows R2 for example "ab-dest-ha-ne"
$R2R3$ = $vowel$ $cons$ <->:<> $cons$ $R3$

% Combine them
$Rules$ = $R1$ | $R2$ | $R3$ | $R1R3$ | $R2R3$

%Combine all of them
$Rules$ | $single_syllable$  