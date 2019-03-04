''' Şevval MEHDER - 151044009
Karşılaştırma:

    Repeat-until blokları dolayısıyla Hoare'nin algoritması anlaşılması ve takip edilmesi
    daha zor bir algoritmadır. Hoare bakıldığında Lomuto'ya göre daha az swap işlemi yapmaktadır. Bu özelliği sayesinde
    daha efficient sonuçlar üretir. Yine de anormal durumlar haricinde karşılaştırma ve swap sayıları göz önüne
    alındığında iki liste de benzer performanslar sağlamaktadır. Ancak,

    Bütün elemanları eşit bir liste düşünelim. Pivot ve A[j] karşılaştırmasındaki
    eşitlik durumu sebbeiyle Hoare'nin algoritması karşılaştrma ve swap işlemi
    yaparak verimsizleşmektedir. Bu tarz extrem durumda Lomuto'nun algoritması seçilmelidir.
    Zaten sıralı bir liste de Hoare kötü bir performans sergilemektedir.

'''


def LomutaPartition(arr, left, right):
    pivot = arr[right]  # Last item
    smallest = left

    for j in range(left, right):

        if arr[j] <= pivot:
            smallest += 1
            arr[smallest - 1], arr[j] = arr[j], arr[smallest - 1]

    arr[smallest], arr[right] = arr[right], arr[smallest]
    return smallest


def LomutaHelper(arr, left, right):
    if right > left:
        pivot = LomutaPartition(arr, left, right)

        LomutaHelper(arr, left, pivot - 1)
        LomutaHelper(arr, pivot + 1, right)


def quickSortLomuto(arr):
    LomutaHelper(arr, 0, len(arr) - 1)
    return arr


def HoarePartition(arr, first, last):
    pivot = arr[first]
    up = first
    down = last

    while True:

        while up < last and pivot >= arr[up]:
            up += 1

        while pivot < arr[down]:
            down -= 1

        if up < down:
            arr[up], arr[down] = arr[down], arr[up]

        if up >= down:
            break

    arr[first], arr[down] = arr[down], arr[first]

    return down


def HoareHelper(arr, first, last):
    if last > first:
        pivot = HoarePartition(arr, first, last)

        HoareHelper(arr, first, pivot - 1)
        HoareHelper(arr, pivot + 1, last)


def quickSortHoare(arr):
    HoareHelper(arr, 0, len(arr) - 1)
    return arr


def main():
    arr = [15, 4, 68, 24, 75, 16, 42]
    qsh = quickSortHoare(arr)
    print("mainde:", qsh)
    # Output: [4, 15, 16, 24, 42, 68, 75]
    qsl = quickSortLomuto(arr)
    print(qsl)
    # Output: [4, 15, 16, 24, 42, 68, 75]


main()
