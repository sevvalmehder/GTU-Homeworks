''' Şevval MEHDER

         Bu algoritma en büyük sayıyı bulabilmek adına sayının başına koyabidiği kadar üçer tane 5 koymaktadır. Çünkü 5,
    3ten büyük bir sayıdır ve Greedy algoritma olması gereği seçmesi gerektiğinde o durumda en mantıklı olanı yaparak
    5'i seçer.  Devamına 3 koyabilmek için en az 5 blokluk boşluk bırakmaya çalışır. Bazen 3e gerek duymadan sadece
    5 koyarak bitebilecek sayıları da tespit eder.

'''


def decentNumber(digit):
    if digit == 1:
        return -1

    number = ""
    block5 = "555"
    block3 = "33333"

    while digit - 3 >= 5 or digit - 3 == 0:
        number += block5
        digit -= 3
        if digit == 0:
            return int(number)

    while digit % 5 == 0:
        number += block3
        digit -= 5

        if digit == 0:
            return int(number)

    return -1


def main():
    dn = decentNumber(1)
    print(dn)
    # Output: -1
    dn = decentNumber(3)
    print(dn)
    # Output: 555
    dn = decentNumber(5)
    print(dn)
    # Output: 33333
    dn = decentNumber(11)
    print(dn)
    # Output: 55555533333


main()
