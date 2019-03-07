import sys
import cv2
import numpy as np
import time

# Define colors
GREEN = (0, 255, 0)
BLUE = (255, 0, 0)


def find_spots(frame, kernel_size):
    # Get the height and width value of image
    width, height = frame.shape[0], frame.shape[1]

    # initialize the min and max values
    min = 255
    max = -1

    # initialize the brightest and darkest points with origin
    darkest, brightest = (0, 0, 0), (0, 0, 0)

    # Slide the window kernel_size/2 times instead of looking all pixels
    deviation = int((kernel_size + 1) / 2)

    # Find the sliding windows
    for i in range(0, width - kernel_size, deviation):
        for j in range(0, height - kernel_size, deviation):
            window = frame[i:i + kernel_size, j:j + kernel_size]

            # calculate the mean value of window
            mean = np.mean(window)
            if mean < min:
                min = mean;
                darkest = (i, j)
            if mean > max:
                max = mean;
                brightest = (i, j)

    # Brightest and darkest points are the left corner of window
    # We must return the middle point of window
    # Remember kernel size must be odd number
    addition = int((kernel_size - 1) / 2)
    return (brightest[1] + addition, brightest[0] + addition), (darkest[1] + addition, darkest[0] + addition)


def main():
    if len(sys.argv) != 2:
        print("Usage: python main.py kernelSize")
        exit(-1)

    # Set the kernel size
    kernel_size = int(sys.argv[1])
    if kernel_size % 2 == 0:
        print("Kernel size must be an odd number")
        exit(-1)

    # Use webcam to get images
    capture = cv2.VideoCapture(0)

    while True:
        # Get the current frame
        ret, cam_frame = capture.read()

        start_time = time.time()

        # Convert image to grayscale
        gray_frame = cv2.cvtColor(cam_frame, cv2.COLOR_BGR2GRAY)

        # Find brightest and darkest
        brightest, darkest = find_spots(gray_frame, kernel_size)

        # Draw the results
        cur_frame = cv2.circle(cam_frame, brightest, kernel_size, GREEN, 2)
        cur_frame = cv2.putText(cur_frame, "Brightest", brightest, cv2.FONT_HERSHEY_SIMPLEX, 1, GREEN, 2)
        cur_frame = cv2.circle(cur_frame, darkest, kernel_size, BLUE, 2)
        cur_frame = cv2.putText(cur_frame, "Darkest", darkest, cv2.FONT_HERSHEY_SIMPLEX, 1, BLUE, 2)

        cv2.imshow("Show results", cur_frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        finish_time = time.time()
        print("Elapsed time : {}".format(finish_time - start_time))

    # When everything done, release the capture
    capture.release()


# Call main
main()
