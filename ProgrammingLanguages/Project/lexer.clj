; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Sevval MEHDER                    *
; *  Student ID: 151044009                    *
; *********************************************
; Some notes:
; This code print all the tokens, types and locations in any case
; Lexer function returns the token list

(defn read-file
  "Read the file character by character"
  [filename]

  ; Read the file
  (def characters
    (clojure.string/split
      (slurp filename)
      #""
      )
    )

  ;Return the characters
  characters
  )

(defn is-it-letter
  "check the given character is letter"
  [ch]

  ; use ascii code
  (if (or (and (>= ch 65) (<= ch 90)) (and (>= ch 97) (<= ch 122)) )
    true
    false
    )

  )

(defn is-it-operator
  "check the given character is operator"
  [ch]

  ; use ascii code
  (if (or (= ch 45) (= ch 47) (and (>= ch 40) (<= ch 43) ) )
    true
    false
    )

  )

(defn is-it-number
  "check the given character is number"
  [ch]

  ; use ascii code
  (if (and (>= ch 48) (<= ch 57))
    true
    false
    )

  )

(defn op-process
  "Find the given operator type"
  [op char file line pos]

  ;condition - action
  (cond
    (= op 40) (print "l_paranthesis")
    (= op 41) (print "r_parenthesis")
    (= op 42) (print "star")
    (= op 43) (print "plus")
    (= op 45) (print "minus")
    (= op 47) (print "slash")
    )

  ; write the token and its location
  (print (str " '" char "' Location=<" file ":" line ":" pos ">\n"))
  )

(defn const-process
  "Find the given constant"
  [char file line pos]

  ; write the token and its location
  (println (str "numeric_constant '" char "' Location=<" file ":" line ":" pos ">"))

  )

(defn linear_search
  "search the list for given element"
  [list element]

  (loop [i 0
         last (- (count list) 1)]
    (when (<= i last)
      (if (= element (nth list i))
        true
        (recur (+ i 1) last)
        )
      )
    )

  )
(defn get-keywords
  "get all of the keywords"
  []

  ; all keywords
  (list "and" "or" "not" "equal" "append" "concat" "set" "deffun"
        "for" "while" "if" "then" "else" "true" "false")
  )

(defn get-binary-values
  "get the binary values"
  []

  ; all binary values
  (list "true" "false")

  )

(defn string-process
  "Find the string and then decide it is keyword or identifier"
  [all-file filename line pos, cur_pos]

  ; pos is the final position of the string
  ; Go back until the next element is not letter then find the string
  (loop [i (- pos 1)
         first 0
         str-temp []]
    (if (and (not= i -1) (is-it-letter (int (get (nth all-file i) 0))) )
      (recur (- i 1), first, (conj str-temp (nth all-file i)))
      (def string (clojure.string/join "" (reverse str-temp)))
      )

    )

  ; Find the string type
  ; Is it keywords, binary_value or identifier

  (cond

    (linear_search (get-keywords) string) (print "keyword")
    (linear_search (get-binary-values) string) (print "binary_value")
    :else (print "identifier")
    )

  ; write the token and its location
  (print (str " '" string "' Location=<" filename ":" line ":" (- (+ cur_pos 1) (count string)) ">\n"))

  string
  )

(defn connector
  "connect the lexer and other helpers"
  [all-file nth i filename line pos]

  (let [element (int (get nth 0))]

    ;conditions - actions
    (cond

      ; if it is a number
      (is-it-number element) (const-process nth filename line pos)
      ; if it is a operator
      (is-it-operator element) (op-process element nth filename line pos)
      ; if it is a letter
      (is-it-letter element) (def return (string-process all-file filename line (+ i 1) pos))

      :else "nothing important"
    )

    ; Return the current token
    (if (is-it-letter element)
      return
      nth
    )

  )


)
(defn lexer
  "Perform lexical analysis of the program contained within given file"
  [filename]

  ;Read all characters in file
  (def content (read-file filename))

  ; Travel in file content character by character
  (loop [i 0
         last (- (count content) 1)
         line 1
         pos 1
         the-list []]

    (def token-list (apply list the-list))

    (when (<= i last)

      ; convert integer to use ascii
      (let [element (int (get (nth content i) 0)) ]

        ; if the current element is newline or any token
        (if (or (= element 10) (is-it-number element) (is-it-operator element)
                (and (is-it-letter element) (not= i last) (not (is-it-letter (int (get (nth content (+ i 1)) 0)))) ) )


          (if (or (= element 10) )
            ; if it is newline update the line and position info and dont add any token
            (recur (+ i 1), last, (+ line 1), 1, the-list)
            ; if it is not newline this is a token
            ; update pos info and add this token
            (recur (+ i 1), last, line, (+ pos 1),
                   (conj the-list (connector  content (nth content i) i filename line pos)))
          )

          ; If it is not newkine or any token, it must be space
          ; update pos information and dont add any token
          (recur (+ i 1), last, line, (+ pos 1), the-list)
        )
      )
    )
  )

  ; Return the token list
  token-list
)


;(lexer "CoffeeSample.coffee")

; Show the token list
(println (lexer "CoffeeSample.coffee"))