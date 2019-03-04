# Author : Sevval MEHDER
# CSE 321 - Introduction to Algorithm
# Homework2 - Question 5
# Tower Of Hanoi



def tower_of_hanoi(A, B, C, n, times):
    # Base case
    if n == 1:
        print("Disk ", n, ": ", A, " to ", C)
        times[n - 1] += calc_times(A, C, n)

    else:
        # Move n-1 disks from A to B
        tower_of_hanoi(A, C, B, n - 1, times)
        print("Disk ", n, ": ", A, " to ", C)
        times[n - 1] += calc_times(A, C, n)
        # From B to C
        tower_of_hanoi(B, A, C, n - 1, times)


def calc_times(src, dst, weight):
    def switch(x):
        return {
            'SRC': 0,
            'AUX': 1,
            'DST': 2,
        }[x]

    return abs(switch(src) - switch(dst)) * weight


if __name__ == "__main__":

    input_size = 4
    print("Input size is", input_size)

    # Initialize the weight list
    # This list represent the time takes to move a disk
    times = []
    for i in range(input_size):
        times.append(0)

    # Let the game begin !
    tower_of_hanoi("SRC", "AUX", "DST", input_size, times)

    # Print out
    for i in range(len(times) ):
        print("Elapsed time for dist ", i + 1, ": ", times[i])