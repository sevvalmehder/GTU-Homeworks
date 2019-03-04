''' Şevval MEHDER

        Maksimum cost a ulaşmak için X listesine koyacağımız elemanlar ya 1e eşit olmalı ya da listedeki elemanlara.
    İki satırdan oluşan bir tablo oluşturduğumuzda bu iki durumdan birini seçtiğimizde oluşacak toplamı kaydedebiliriz.
    Bu yüzden iki 2xn boyutunda bir array oluşturup her n. adım için değerlendirilecek 2 değer, tablodaki önceden
    hesaplanılan değerler kullanılarak hesaplandı ve en sonunda oluşaan satır sonundaki toplamlardan en büyüğü seçildi.

    Verilen Y dizisinin eleman sayısı n olmak üzere, 2xn kadarlık bir tabloyu doldurarak işlem yaptık.
    Bu tablonun her bir hücresini doldurmak, karşılaştırmayla yani O(1) zamanda olur. 2n tane hücre olduğu düşünülürse
    karmaşıklık O(2n) yani O(n) olmaktadır.

'''


def find_maximum_cost(Y):
    # Make empty 2d list with 0s
    values = [[0 for _ in range(2)] for _ in range(len(Y))]

    i = 1
    # Try 1 and Y[i] in every step in while.
    # Go on with adding
    while i < len(Y):
        # Added 0 for change from None to int
        values[i][0] = max(values[i - 1][0] + 0, values[i - 1][1] + Y[i - 1] - 1)
        values[i][1] = max(values[i - 1][1] + abs(Y[i] - Y[i - 1]), values[i - 1][0] + Y[i] - 1)
        i += 1
        print(values)

    return max(values[len(Y) - 1][0], values[len(Y) - 1][1])


def main():
    Y = [5, 6, 8, 13, 9]
    cost = find_maximum_cost(Y)
    print(cost)
    '''# Output: 52
    Y = [1, 9, 11, 7, 3]
    cost = find_maximum_cost(Y)
    print(cost)
    # Output: 28
    Y = [50,28,1,1,13,7]
    cost = find_maximum_cost(Y)
    print(cost) #Output: 78'''


main()
