# Author : Sevval MEHDER
# CSE 321 - Introduction to Algorithm
# Homework2 - Question 4
# Find Rotten Walnut recursive problem


def find_rotten(weight_list):
    # Find the middle element
    middle = len(weight_list) // 2

    # Find the right and the left scale list
    # If list has odd element don't include middle
    left_scale = weight_list[:middle]
    right_scale = weight_list[middle:] if len(weight_list) % 2 == 0 else weight_list[(middle + 1):]

    # If the rotten one is the middle
    if compareScales(left_scale, right_scale) == 0:
        return middle if weight_list[middle] != 1 else -1


    # If the rotten one is on the left
    elif compareScales(left_scale, right_scale) == 1:
        return find_rotten(left_scale)

    # If the rotten one is on the right
    # If list has odd element count the middle
    else:
        if len(weight_list) % 2 == 0:
            return len(left_scale) + find_rotten(right_scale)
        else:
            return len(left_scale) + 1 + find_rotten(right_scale)


# The Python function which compares two set of walnuts
# You will assume that this function executes in constant time (O (1)).
def compareScales(leftScaleList, rightScaleList):
    result = sum(leftScaleList) - sum(rightScaleList)
    if result < 0:
        return 1
    elif result > 0:
        return -1
    else:
        return 0

# The test main with some test case
if __name__ == "__main__":

    # Call function for test with some case
    print(find_rotten([1, 1, 1, 1, 1, 1]))
    print(find_rotten([1, 1, 1, 1, 1, 1, 1]))
    print(find_rotten([0.5, 1]))
    print(find_rotten([1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1]))
    print(find_rotten([1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1]))
    print(find_rotten([1, 1, 1, 1, 1, 1, 1, 1, 0.5]))
    print(find_rotten([0.5, 1, 1, 1, 1, 1, 1, 1, 1]))
    print(find_rotten([1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1]))

