''' Şevval MEHDER 151044009
    Divide and conquer bir algoritma gerçekleştirmek adına her adımda listeyi ikiye bölerek başladım.
    Listeyi ikiye bölme işleminin daha kolay gerçekleşmesi ve bulunması gereken subarray'in başladığı indexi daha rahat
    takip edebilmek için bir helper fonksiyon yazdım. Bu fonksiyonda,
    önce soldaki liste için bir recursive çağrı, sonra soldaki için bir recursive çağrı yaptım ve elemenlarının
    bir kısmı solda bir kısmı sağda olabilecek bir array için bunu hesaplayan bir kod yazdım.
    Bu kod ortadan sağa ve ortadan sola doğru toplayarak minimum aramaktadır. Sola doğru olan sırasında
    minimum bulunduğu anda o anki indexi başlangıç indexi olarak belirledim. Bu minimum sub array'in başladığı noktayı
    temsil etmektedir. Devam eden bu fonksiyon içerisinde, sol ve sağ ve diğer işlem için bir toplam değer
    ve bir başlangıç noktası belirledim, karşılaştırmalar sırasında bunların da atamasını gerçekleştirdim. Ve fonksiyon
    bu iki değeri return etmektedir.
    Bu fonksiyonu çağırdığım noktada ise return edilen başlangıç noktasından ileriye doğru toplayarak bulunan minimum
    değeri elde ettim ve bu sırada subarray'i de bulmuş oldum.

    Bu algoritma için recurrence relation yazmak istense
    T(n) = 2.T(n/2) + (crosses midpoint problem complexity) şeklinde yazılması gerekir.
    Crosses midpoint olarak bahsedilen sapda ve solda elamanlara sahip olması durumu için en kötü durumda arrayin tüm
    elamanları gezilir ki bu da O(n) zamanda yapılır. O zaman relation şu halini alır:
    T(n) = 2.T(n/2) + n
    Master Theorem baz alındığında bu algoritmanın worst case karmaşıklığına O(nlogn) denebilir.
    '''

import sys


def min_subarray_helper(arr, first, last):
    if first == last:
        return arr[first], first

    middle = (first + last) // 2

    # Recursive call for left
    left_min, start_index_L = min_subarray_helper(arr, first, middle)
    # Recursive call for left
    right_min, start_index_R = min_subarray_helper(arr, middle + 1, last)

    # compare and assign
    if left_min < right_min:
        last_min = left_min
        start_index = start_index_L
    else:
        last_min = right_min
        start_index = start_index_R

    # ------------------------------------------------ #
    # calculate the other possible minimum array such that
    # have element both left and right side
    temp = 0
    minLeft = sys.maxsize
    start_index_O = 0

    for i in range(middle, -1, -1):
        temp += arr[i]
        if temp < minLeft:
            start_index_O = i
            minLeft = temp

    temp = 0
    minRight = sys.maxsize
    for i in range(middle + 1, len(arr)):
        temp += arr[i]
        if temp < minRight:
            minRight = temp

    other_min = minLeft + minRight

    # the other possible minimum sum has been calculated
    # ------------------------------------------------ #

    # compare and assign
    if other_min < last_min:
        last_min = other_min
        start_index = start_index_O

    return last_min, start_index


def min_subarray_finder(arr):
    first = 0  # first index
    last = len(arr) - 1  # last index

    last_min, start_index = min_subarray_helper(arr, first, last)

    sum = 0
    result_list = []
    # Get the subarray that has minimum sum
    for i in range(start_index, len(arr) - 1):
        sum += arr[i]
        result_list.append(arr[i])

        if sum == last_min:
            return result_list


def main():
    inpArr = [1, -4, -7, 5, -13, 9, 23, -1]
    msa = min_subarray_finder(inpArr)
    print(msa)  # Output: [-4, -7, 5, -13]
    print(sum(msa))  # Output: -19


main()
