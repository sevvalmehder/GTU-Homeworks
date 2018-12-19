$cons$ = b|c|ç|d|f|g|ğ|h|j|k|l|m|n|p|r|s|ş|t|v|y|z
$vowel$ = a|e|ı|i|o|ö|u|ü

%
% Syllables with 3 letter
%

% vowel + cons + cons
% For example: "alp", "aşk"
$vcc$ = $vowel$ $cons$ $cons$ 

% cons + vowel + cons
% For example: "huy", "kar", "gir"
$cvc$ = $cons$ $vowel$ $cons$

%
% Syllable with 4 letter
%

% cons + vowel + cons + cons
% For example: "harp", "türk", "mest"
$cvcc$ = $cons$ $vowel$ $cons$ $cons$ 

% Combine all them
$single_syllable$ = $vcc$ | $cvc$ | $cvcc$

% If there is a consonant between two vowels
% the consonant belongs to previous vowel: "a-ra"
$R1$ = ($cons$)? $vowel$ <->:<> $cons$ $vowel$
% There can be sequential R1: "a-ra-ba" , "a-ra-ba-lar"
$R1.1$ = $R1$ (<->:<> $cons$ $vowel$)* ($cons$)?

% Combine them
$Rule1$ = $R1$ | $R1.1$

% If there is two consonant side by side
% first one belongs to previous and the other one belongs to next 
$R2$ = $cons$? $vowel$ $cons$ <->:<> $cons$ $vowel$ ($cons$)?
% There can be sequential R2: "sev-mek-ten", "sev-mek-ten-dir"
$R2.1$ = $R2$ (<->:<> $cons$ $vowel$ ($cons$)?)*

% Combine them
$Rule2$ = $R2$ | $R2.1$

% If there is three consonant side by side 
% First 2 consanant belongs to previous and the other one belongs to next
$R3$ = ($cons$? $vowel$)? $cons$ $cons$ <->:<> $cons$ $vowel$ $cons$?

% There are some words have both r1 and r2
% "kur-ba-ğa", "in-sa-nın", "a-rın-mak", "ba-yın-dır"
$R1+R2$ = $Rule1$ $vowel$? $cons$ <->:<> $cons$ $vowel$ ($cons$)?
$R2+R1$ = ($cons$? $vowel$)? $cons$ <->:<> $cons$ $R1$ $cons$?
$R3+R1$ = $R3$ $R1$

% Combine all of them
$Mixed_rules$ = $R1+R2$ | $R2+R1$ | $R3+R1$

% Special rule for words like as "prog-ram"
$special$ = $cons$ $R2$
% "a-la-fran-ga"
$R1+special$ = $R1$ $special$

% Combine them
$specials$ = $special$ | $R1+special$

%Combine all of them
$Rule1$ | $Rule2$ | $R3$ | $Mixed_rules$ | $specials$ | $single_syllable$ 