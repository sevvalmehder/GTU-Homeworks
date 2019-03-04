import sys


# This function returns x length permutations of inp_list.
def heap_perm(list_inp, size, x, out):

    # the last element is stabil and the others can change
    if size == 1:
        temp = []
        for i in range(x):
            temp.append(list_inp[i])

        out.append(temp)

    # Change the last
    for i in range(size):
        heap_perm(list_inp, size - 1, x, out)

        if size % 2 == 1:
            # swap the last and first
            list_inp[0], list_inp[size - 1] = list_inp[size - 1], list_inp[0]

        else:
            # swap the ith element and last
            list_inp[i], list_inp[size - 1] = list_inp[size - 1], list_inp[i]

    return out


def findOptimalAssistantship(inp_table):
    # Rows are represent number of assistant
    ass_number = len(inputTable)
    # Columns are represent number of course
    course_number = len(inputTable[0])

    # ret_asst[i] will hold the number of the course that R.A. i will be its assistant
    # and -1 if it is doing another department stuff.
    ret_asst = []

    # minimum total time spent per week
    optimal = sys.maxsize

    # Error case
    if ass_number < course_number:
        return

    # If number of courses (n) is less than the number of R.A.’s (r)
    # Add a column with 6 to make rxr matrix
    if ass_number > course_number:
        for i in range(ass_number):
            diff = ass_number - course_number
            while diff > 0:
                inp_table[i].append(6)
                diff -= 1

    # r x r new matrix
    new_asst_number = len(inputTable)
    new_course_number = len(inputTable[0])

    # Calculate all permutations for brute force algorithm
    inp_list = list(range(new_course_number))
    all_perm = heap_perm(inp_list, len(inp_list), new_asst_number, [])

    # Try all permutations one by one
    for perm in all_perm:
        # The ret_asst list for one step
        temp = []
        # total time spent per week for one step
        count = 0

        # Calculate time spent per week
        j = 0  # j is the index for rows
        for i in perm:
            count += inp_table[j][i]

            # If this index is added later(in line 60)
            if i >= course_number:
                temp.append(-1)
            else:
                temp.append(i)

            j += 1

        # If count is minimal
        if count < optimal:
            optimal = count
            ret_asst = temp

    return ret_asst, optimal


if __name__ == '__main__':
    inputTable = [[5, 8, 7],
                  [8, 12, 7],
                  [4, 8, 5]]

    asst, time = findOptimalAssistantship(inputTable)
    print(asst)
    print(time)
