; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Yakup Genc                       *
; *  Author: Şevval MEHDER - 151044009        *
; *********************************************


;Spell checkers and the read-as-list function are completed
;There is an algorithm about Gen-Decoder-A
;There is a code for test the spell checkers in test_on_test_data function


;; utility functions 
(load-file "include.clj") ;; "c2i and "i2c"


(use 'clojure.java.io)



(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]

  (def words (clojure.string/split (slurp filename) #"\s+"))

  (def major

    (loop [i 0 major []]
      (if (>= i (count words))
        (apply list major)
        (do
          (let [letters (clojure.string/split (words i) #"")]
            (def temp
              (loop [j 0 sub-list []]
                (if (>= j (count letters))
                  (apply list sub-list)
                  (do
                    (recur (inc j) (conj sub-list (symbol (letters, j) )))
                    )
                )
              )
            )
            (recur (inc i) (conj major temp))
          )
        )
      )
    )
  )


  major

)




;; -----------------------------------------------------
;; HELPERS
;; *** PLACE YOUR HELPER FUNCTIONS BELOW ***

(defn search
  [list to-search]

  (if (= to-search (nth list 0))
    true
    (if (= 1 (count list))
      false
      (recur (pop list) to-search)
    )

  )

)

;This permutations code's source is: https://stackoverflow.com/questions/26076077/clojure-list-all-permutations-of-a-list
;Calculate all of the permutation
(defn permutations [s]
  (lazy-seq
    (if (seq (rest s))
      (apply concat (for [x s]
                      (map #(cons x %) (permutations (remove #{x} s)))))
      [s]
    )
  )
)

(defn test-decode [word alphabet]

  ;  This function will decode the given word
  ;  and return the decoded word
  "decoded"
)

(defn spell-checker-0 
	[word]

  ;Get all words in test dictionary
  (def  words-list  (read-as-list "dictionary2.txt"))

  ;Divide by letter and convert to symbol
  (def to-be-search

    (let [letters (clojure.string/split word #"")]
      (loop [i 0 to-be-search []]
        (if (>= i (count letters))
          (apply list to-be-search)
          (do
            (recur (inc i) (conj to-be-search (symbol (letters, i) )))
          )
        )
      )
    )
  )

  ;Compare all elements in dictionary
  (search words-list to-be-search)

)



(defn spell-checker-1
	[word]

  ;Get all words in test dictionary
  (def  words-list  (read-as-list "dictionary2.txt"))

  ;Divide by letter and convert to symbol
  (def to-be-search

    (let [letters (clojure.string/split word #"")]
      (loop [i 0 to-be-search []]
        (if (>= i (count letters))
          (apply list to-be-search)
          (do
            (recur (inc i) (conj to-be-search (symbol (letters, i) )))
          )
        )
      )
    )
  )

  ;Check dictionary for the word
  (.contains words-list to-be-search)

)


;; -----------------------------------------------------
;; DECODE FUNCTIONS


(defn Gen-Decoder-A 
	[paragraph]
	;you should implement this function
  ;(def alphabet (list 'a 'b 'c 'd 'e 'f 'g 'h 'i 'j 'k 'l 'm 'n 'o 'p 'r 's 't 'u 'v 'w 'x 'y 'z))
  (def alphabet (list 'a 'b 'c 'd 'e 'f ))

  (loop [i 0 counter 0 ]
    (if (>= i (count paragraph))
      false
      (do
        ;Get the decoded word
        (def decoded (test-decode (nth paragraph i) (nth (permutations alphabet) 0) ))
        ;Check the decoded word
        (if (= (spell-checker-0 decoded) true)
        ;  If the decoded word in dictionary
          (- 1 counter)
        )
        (recur (inc i) (inc counter) )
        )
      )
  )

)

(defn Gen-Decoder-B-0 
	[paragraph]
  	;you should implement this function
)

(defn Gen-Decoder-B-1 
	[paragraph]
  	;you should implement this function
)

(defn Code-Breaker 
	[document decoder]
  	;you should implement this function
)

;; -----------------------------------------------------
;; Test code...

(defn test_on_test_data
	[]
	(let [doc (read-as-list "document1.txt")]
		(println doc)
	)


;  My test
  (println (spell-checker-0 "hello"))
  (println (spell-checker-1 "asdasdfsdf"))
)


;; test code...
(test_on_test_data)


