''' Şevval MEHDER
    Verilen string listesini ikiye bölüp,
    - sağdakiler için bir ortak tekrar eden string,
    - soldakiler için ortak tekrar eden bir string bulan bir fonksiyon
    ve ardından bulunan bu iki stringi karşılaştırıp önce o çağrıdaki liste için ve sonuç olarak da
    tüm liste için ortak tekrar eden stringi elde ettim.

    Bu algoritma için:
    T(n) = 2.T(n/2) + (compeare proccess complexity) yazılabilir. Compare işleminde worst case için maksimum, listedeki
    en uzun elemanın uzunluğu kadar dönen bir for döngüsü vardır. Bu da lineer zamana denk gelir. Relation,
    T(n) = 2.T(n/2) + n halini alır.
    Master Theorem baz alındığında bu algoritmanın worst case karmaşıklığına O(nlogn) denebilir.
    '''


def compare(left, right):
    l = len(left) - 1
    r = len(right) - 1

    # if l == -1 or r == -1:
    #     return " "

    while left[l] == right[r] and l >= 0 and r >= 0:
        l -= 1
        r -= 1

    return right[(r + 1):]


def longest_common_postfix(inpStrings):
    if len(inpStrings) == 1:
        return inpStrings[0]

    # According to divide and conquer approach
    # find the middle for divide the list
    middle = len(inpStrings) // 2

    # Research the left of the middle with recursive call
    left_strings = longest_common_postfix(inpStrings[:middle])

    # Research the right of the middle with recursive call
    right_strings = longest_common_postfix(inpStrings[middle:])

    # If there is no common
    if not left_strings or not right_strings:
        return " "
    else:
        return compare(left_strings, right_strings)


def main():
    inpStrings = ["absorptivity", "circularity", "electricity", "importunity", "humanity"]
    # inpStrings = ["relativity", "freedom", "religion"]
    lcp = longest_common_postfix(inpStrings)
    print(lcp)


main()
