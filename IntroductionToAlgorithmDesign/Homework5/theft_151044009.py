''' Şevval MEHDER

    theft_helper fonksiyonuna values isminde boş olarak gönderdiğim çift boyutlu array sağ en alt hücreden başlayarak ve
    amountOfMoney tablosundaki para miktarlatını kullanarak,
    - en son kolona gelmiş olan bütün değerlerin daha önceki kolondan sol alt, sol üst ve sol yanı kontrol ederek
    en yüksek değerin hangisinden gelebileceğini, yani herbir hücreye maksimum ne kadar parayla gelinebilecğeini
    hesaplar.

    theft fonksiyonu da bu hesaplanan values hesaplamaları sonucu her satırdaki son hücreleri kontrol eder.
    son hücrelerden en yüksek miktarda olan hangisiyle onun miktarı return edilir.

    n tane satır ve m tane sütunumuz var. Yani tabloda doldurulmak üzeren n.m tane boşluk var.
    Her bi bloğu doldurmak constant time zaman alır. O(1)
    Dolayısıyla worst case O(n.m) halini alır.

'''


def theft(amountOfMoney):
    # First values
    f_row = len(amountOfMoney)
    f_col = len(amountOfMoney[0])

    # Make a empty 2d list like amountOfMoney
    values = [[None for _ in range(f_col)] for _ in range(f_row)]

    # Fill the new values array
    for col in range(f_col):
        for row in range(f_row):

            if col == 0:
                values[row][col] = amountOfMoney[row][col]

            elif row == 0:
                values[row][col] = amountOfMoney[row][col] + max(values[row][col - 1],
                                                                 values[row + 1][col - 1])

            elif row == f_row - 1:
                values[row][col] = amountOfMoney[row][col] + max(values[row - 1][col - 1],
                                                                 values[row][col - 1])

            else:
                values[row][col] = amountOfMoney[row][col] + max(values[row - 1][col - 1],
                                                                 values[row][col - 1],
                                                                 values[row + 1][col - 1])
    print(values)
    return max([values[i][-1] for i in range(len(amountOfMoney))])


def main():
    amountOfMoneyInLand = [[1, 3, 33, 5],
                           [5, 8, 17, 1],
                           [23, 10, 7, 8],
                           [14, 10, 9, 7]]

    res = theft(amountOfMoneyInLand)
    print(res)
    # Output: 16

    amountOfMoneyInLand = [[10, 33, 13, 15], [22, 21, 4, 1], [5, 0, 2, 3], [0, 6, 14, 2]]
    res = theft(amountOfMoneyInLand)
    print(res)
    # Output: 83


main()
