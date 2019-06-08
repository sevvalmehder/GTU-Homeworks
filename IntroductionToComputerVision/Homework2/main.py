import cv2
import numpy as np
import glob
import os
import random

# square size in millimeter
square_size = 0.26


def find_intrinsic_params(width, height, dir_path):
    # termination criteria
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    objp = np.zeros((height * width, 3), np.float32)
    objp[:, :2] = np.mgrid[0:width, 0:height].T.reshape(-1, 2)
    objp = objp * square_size

    # Arrays to store object points and image points from all the images.
    objpoints = []  # 3d point in real world space
    imgpoints = []  # 2d points in image plane.
    images = glob.glob(os.path.join(dir_path, '*.jpg'))

    for image in images:

        img = cv2.imread(image)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # Find the chess board corners
        ret, corners = cv2.findChessboardCorners(gray, (width, height), None)

        # If found, add object points, image points
        if ret:
            objpoints.append(objp)
            corners = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            imgpoints.append(corners)

            '''
            # Draw and display the corners
            img = cv2.drawChessboardCorners(img, (width, height), corners, ret)
            cv2.imshow("Chessboard", img)
            cv2.waitKey(0)
            '''

        else:
            print(image)

    ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

    return mtx, dist


def select_points(objp, corners, randoms, img):
    world_points = np.zeros((len(randoms), 3, 1), np.float32)  # 2d points in image world space
    image_points = np.zeros((len(randoms), 2, 1), np.float32)  # 3d points in real world space

    for i in range(len(randoms)):
        index = randoms[i]
        world_points[i] = [[k] for k in objp[index]]
        image_points[i] = [[z] for z in corners[index][0]]

        # img = cv2.circle(img, tuple(image_points[i]), 2, (0, 255, 0), 2)
        # img = cv2.putText(img, str([world_points[i][k][0] for k in range(3)]), tuple(image_points[i]),
        #                   cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 1)

    # cv2.imshow("Chessboard", img)
    # cv2.waitKey(0)

    return image_points, world_points


def get_projection(imgp, objp, cam_mat, dist_coeffs):
    # Get rotation vector and transition vector
    vectors = cv2.solvePnP(objp, imgp, cam_mat, dist_coeffs)
    rvec, tvec = vectors[1], vectors[2]

    # convert rotation vector to a rotation matrix
    rmat = cv2.Rodrigues(rvec)[0]

    # The joint rotation-translation matrix [R|t] is called
    # a matrix of extrinsic parameters
    extrinsic_params = np.hstack((rmat, tvec))

    projection_mat = np.dot(cam_mat, extrinsic_params)

    return projection_mat


def find_positions(projection_mat, imgp):
    ''' P1 = M1 x P
        P = P1 x inverse(M1)
    '''

    points = []
    for point in imgp:
        point = [point[0], point[1], 0]
        inverse_m1 = np.linalg.pinv(projection_mat)
        p = np.dot(inverse_m1, point)
        points.append(p)

    return points


if __name__ == '__main__':

    width = 9
    height = 6

    camera_mat_l, dist_coeffs_l = find_intrinsic_params(width, height, 'calibration_comp')
    camera_mat_r, dist_coeffs_r = find_intrinsic_params(width, height, 'calibration_logi')

    # Use webcam to get images
    capture = cv2.VideoCapture(0)
    capture2 = cv2.VideoCapture(1)

    while True:

        # Get the current frame
        _, cam_left = capture.read()
        _, cam_right = capture2.read()

        # cam_left = cv2.imread("test_image.jpg")
        # cam_right = cv2.imread("test_image.jpg")

        # Convert grayscale and find the chess board corners for each camera image
        gray_left = cv2.cvtColor(cam_left, cv2.COLOR_BGR2GRAY)
        gray_right = cv2.cvtColor(cam_right, cv2.COLOR_BGR2GRAY)
        ret, corners_left = cv2.findChessboardCorners(gray_left, (width, height), None)
        ret2, corners_right = cv2.findChessboardCorners(gray_right, (width, height), None)

        if ret and ret2:
            # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
            objp = np.zeros((height * width, 3), np.float32)
            objp[:, :2] = np.mgrid[0:width, height:0:-1].T.reshape(-1, 2)
            objp *= square_size

            # Select and draw points
            rand_points = [0, 8, 45, 53]
            imgp_left, objp_left = select_points(objp, corners_left, rand_points, cam_left)
            imgp_right, objp_right = select_points(objp, corners_right, rand_points, cam_right)

            # Get projection matrices
            projection_mat_left = get_projection(imgp_left, objp_left, camera_mat_l, dist_coeffs_l)
            projection_mat_right = get_projection(imgp_right, objp_right, camera_mat_r, dist_coeffs_r)


            # Estimation
            cam1 = find_positions(projection_mat_left, imgp_left)
            cam2 = find_positions(projection_mat_right, imgp_right)

            # Show the estimation
            for k,i in enumerate(rand_points):
                img = cv2.circle(cam_right, tuple(corners_right[i][0]), 2, (0, 255, 0), 2)
                img = cv2.putText(cam_right, "P{}".format(k) + str(cam1[k]), (25, 20*(k+1)),
                                  cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 1)

                img = cv2.circle(cam_left, tuple(corners_left[i][0]), 2, (0, 255, 0), 2)
                img = cv2.putText(cam_left, "P{}".format(k) + str(cam2[k]), (50, 20*(k+1)),
                                  cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 1)

        cv2.imshow("CamRight", cam_right)
        cv2.imshow("CamLeft", cam_left)
        cv2.waitKey(0)


