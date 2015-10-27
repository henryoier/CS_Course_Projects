#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int n_boards = 0; //Will be set by input list
const int board_dt = 10;
int board_w = 12;
int board_h = 12;

int Birds_eye()
{

	//INPUT PARAMETERS:
	int board_n = board_w * board_h;
	CvSize board_sz = cvSize(board_w, board_h);
	CvMat *intrinsic = (CvMat*)cvLoad("Intrinsics.xml");
	CvMat *distortion = (CvMat*)cvLoad("Distortion.xml");
	IplImage *image = 0, *gray_image = 0;
	if ((image = cvLoadImage("view.jpg")) == 0){
		cout << "Error: Couldn't load view.jpg" << endl;
		return 0;
	}
	gray_image = cvCreateImage(cvGetSize(image), 8, 1);
	cvCvtColor(image, gray_image, CV_BGR2GRAY);

	//UNDISTORT OUR IMAGE
	IplImage* mapx = cvCreateImage(cvGetSize(image), IPL_DEPTH_32F, 1);
	IplImage* mapy = cvCreateImage(cvGetSize(image), IPL_DEPTH_32F, 1);
	cvInitUndistortMap(
		intrinsic,
		distortion,
		mapx,
		mapy
		);
	IplImage *t = cvCloneImage(image);
	cvRemap(t, image, mapx, mapy);

	//GET THE CHECKERBOARD ON THE PLANE
	cvNamedWindow("Checkers");
	CvPoint2D32f* corners = new CvPoint2D32f[board_n];
	int corner_count = 0;
	int found = cvFindChessboardCorners(
		image,
		board_sz,
		corners,
		&corner_count,
		CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
		);
	if (!found){
		return -1;
	}
	//Get Subpixel accuracy on those corners
	cvFindCornerSubPix(gray_image, corners, corner_count,
		cvSize(11, 11), cvSize(-1, -1),
		cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

	//GET THE IMAGE AND OBJECT POINTS:
	//Object points are at (r,c): (0,0), (board_w-1,0), (0,board_h-1), (board_w-1,board_h-1)
	//That means corners are at: corners[r*board_w + c]
	CvPoint2D32f objPts[4], imgPts[4];
	objPts[0].x = 0;         objPts[0].y = 0;
	objPts[1].x = board_w - 1; objPts[1].y = 0;
	objPts[2].x = 0;         objPts[2].y = board_h - 1;
	objPts[3].x = board_w - 1; objPts[3].y = board_h - 1;
	imgPts[0] = corners[0];
	imgPts[1] = corners[board_w - 1];
	imgPts[2] = corners[(board_h - 1)*board_w];
	imgPts[3] = corners[(board_h - 1)*board_w + board_w - 1];

	//DRAW THE POINTS in order: B,G,R,YELLOW
	cvCircle(image, cvPointFrom32f(imgPts[0]), 9, CV_RGB(0, 0, 255), 3);
	cvCircle(image, cvPointFrom32f(imgPts[1]), 9, CV_RGB(0, 255, 0), 3);
	cvCircle(image, cvPointFrom32f(imgPts[2]), 9, CV_RGB(255, 0, 0), 3);
	cvCircle(image, cvPointFrom32f(imgPts[3]), 9, CV_RGB(255, 255, 0), 3);

	//DRAW THE FOUND CHECKERBOARD
	cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
	cvShowImage("Checkers", image);

	//FIND THE HOMOGRAPHY
	CvMat *H = cvCreateMat(3, 3, CV_32F);
	CvMat *H_invt = cvCreateMat(3, 3, CV_32F);
	cvGetPerspectiveTransform(objPts, imgPts, H);

	//LET THE USER ADJUST THE Z HEIGHT OF THE VIEW
	float Z = 25;
	int key = 0;
	IplImage *birds_image = cvCloneImage(image);
	cvNamedWindow("Birds_Eye");
	while (key != 27) {//escape key stops
		CV_MAT_ELEM(*H, float, 2, 2) = Z;
		//	   cvInvert(H,H_invt); //If you want to invert the homography directly
		//	   cvWarpPerspective(image,birds_image,H_invt,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
		//USE HOMOGRAPHY TO REMAP THE VIEW
		cvWarpPerspective(image, birds_image, H,
			CV_INTER_LINEAR + CV_WARP_INVERSE_MAP + CV_WARP_FILL_OUTLIERS);
		cvShowImage("Birds_Eye", birds_image);
		key = cvWaitKey();
		if (key == 'u') Z += 0.5;
		if (key == 'd') Z -= 0.5;
	}

	//SHOW ROTATION AND TRANSLATION VECTORS
	CvMat* image_points = cvCreateMat(4, 1, CV_32FC2);
	CvMat* object_points = cvCreateMat(4, 1, CV_32FC3);
	for (int i = 0; i<4; ++i){
		CV_MAT_ELEM(*image_points, CvPoint2D32f, i, 0) = imgPts[i];
		CV_MAT_ELEM(*object_points, CvPoint3D32f, i, 0) = cvPoint3D32f(objPts[i].x, objPts[i].y, 0);
	}

	CvMat *RotRodrigues = cvCreateMat(3, 1, CV_32F);
	CvMat *Rot = cvCreateMat(3, 3, CV_32F);
	CvMat *Trans = cvCreateMat(3, 1, CV_32F);
	cvFindExtrinsicCameraParams2(object_points, image_points,
		intrinsic, distortion,
		RotRodrigues, Trans);
	cvRodrigues2(RotRodrigues, Rot);

	//SAVE AND EXIT
	cvSave("Rot.xml", Rot);
	cvSave("Trans.xml", Trans);
	cvSave("H.xml", H);
	cvInvert(H, H_invt);
	cvSave("H_invt.xml", H_invt); //Bottom row of H invert is horizon line
	cvSaveImage("bird_eye.jpg", birds_image);
}


int main(int argc, char* argv[]) {

	int board_n = board_w * board_h;
	CvSize board_sz = cvSize(board_w, board_h);
	FILE *fptr = fopen("lists.txt", "r");
	char names[2048];
	//COUNT THE NUMBER OF IMAGES:
	while (fscanf(fptr, "%s ", names) == 1){
		n_boards++;
	}
	rewind(fptr);

	//ALLOCATE STORAGE
	CvMat* image_points = cvCreateMat(n_boards*board_n, 2, CV_32FC1);
	CvMat* object_points = cvCreateMat(n_boards*board_n, 3, CV_32FC1);
	CvMat* point_counts = cvCreateMat(n_boards, 1, CV_32SC1);

	///  CvMat * image_points	= cvCreateMat(1, n_boards*board_n, CV_32FC2);
	///  CvMat * object_points = cvCreateMat(1, n_boards*board_n, CV_32FC3);
	///  CvMat * point_counts  = cvCreateMat(1, n_boards, CV_32SC1);

	CvMat* intrinsic_matrix = cvCreateMat(3, 3, CV_32FC1);
	CvMat* distortion_coeffs = cvCreateMat(5, 1, CV_32FC1);


	IplImage* image = 0;// = cvQueryFrame( capture );
	IplImage* gray_image = 0; //for subpixel
	CvPoint2D32f* corners = new CvPoint2D32f[board_n];
	int corner_count;
	int successes = 0;
	int step;

	for (int frame = 0; frame<n_boards; frame++) {
		fscanf(fptr, "%s ", names);

		if (image){
			cvReleaseImage(&image);
			image = 0;
		}
		if (gray_image){
			cvReleaseImage(&gray_image);
			gray_image = 0;
		}
		image = cvLoadImage(names);
		if (gray_image == 0 && image) //We'll need this for subpixel accurate stuff
			gray_image = cvCreateImage(cvGetSize(image), 8, 1);

		if (!image)
			printf("null image\n");

		int found = cvFindChessboardCorners(
			image,
			board_sz,
			corners,
			&corner_count,
			CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
			);

		//Get Subpixel accuracy on those corners
		cvCvtColor(image, gray_image, CV_BGR2GRAY);
		cvFindCornerSubPix(gray_image, corners, corner_count,
			cvSize(11, 11), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		//Draw it
		/*cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
		cvShowImage("Calibration", image);
		*/
		// If we got a good board, add it to our data
		//
		if (corner_count == board_n) {
			step = successes*board_n;
			//	printf("Found = %d for %s\n",found,names);
			for (int i = step, j = 0; j<board_n; ++i, ++j) {
				///         CV_MAT_ELEM(*image_points, CvPoint2D32f,0,i) = cvPoint2D32f(corners[j].x,corners[j].y);
				///         CV_MAT_ELEM(*object_points,CvPoint3D32f,0,i) = cvPoint3D32f(j/board_w, j%board_w, 0.0f);
				CV_MAT_ELEM(*image_points, float, i, 0) = corners[j].x;
				CV_MAT_ELEM(*image_points, float, i, 1) = corners[j].y;
				CV_MAT_ELEM(*object_points, float, i, 0) = j / board_w;
				CV_MAT_ELEM(*object_points, float, i, 1) = j%board_w;
				CV_MAT_ELEM(*object_points, float, i, 2) = 0.0f;

			}
			//        CV_MAT_ELEM(*point_counts, int,0,successes) = board_n;
			CV_MAT_ELEM(*point_counts, int, successes, 0) = board_n;
			successes++;
		}

		//    if( successes == n_boards ) break;

	}
	//ALLOCATE MATRICES ACCORDING TO HOW MANY IMAGES WE FOUND CHESSBOARDS ON
	///  CvMat* image_points2      = cvCreateMat(1,successes*board_n,CV_32FC2);
	///  CvMat* object_points2     = cvCreateMat(1,successes*board_n,CV_32FC3);
	///  CvMat* point_counts2      = cvCreateMat(1,successes,CV_32SC1);
	CvMat* object_points2 = cvCreateMat(successes*board_n, 3, CV_32FC1);
	CvMat* image_points2 = cvCreateMat(successes*board_n, 2, CV_32FC1);
	CvMat* point_counts2 = cvCreateMat(successes, 1, CV_32SC1);
	//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
	for (int i = 0; i<successes*board_n; ++i){
		///      CV_MAT_ELEM(*image_points2, CvPoint2D32f,0,i)  = CV_MAT_ELEM(*image_points, CvPoint2D32f,0,i);
		///      CV_MAT_ELEM(*object_points2,CvPoint3D32f,0,i)  = CV_MAT_ELEM(*object_points,CvPoint3D32f,0,i);
		CV_MAT_ELEM(*image_points2, float, i, 0) = CV_MAT_ELEM(*image_points, float, i, 0);
		CV_MAT_ELEM(*image_points2, float, i, 1) = CV_MAT_ELEM(*image_points, float, i, 1);
		CV_MAT_ELEM(*object_points2, float, i, 0) = CV_MAT_ELEM(*object_points, float, i, 0);
		CV_MAT_ELEM(*object_points2, float, i, 1) = CV_MAT_ELEM(*object_points, float, i, 1);
		CV_MAT_ELEM(*object_points2, float, i, 2) = CV_MAT_ELEM(*object_points, float, i, 2);

	}
	for (int i = 0; i<successes; ++i){
		///		CV_MAT_ELEM(*point_counts2,int,0, i) = CV_MAT_ELEM(*point_counts, int,0,i);
		CV_MAT_ELEM(*point_counts2, int, i, 0) = CV_MAT_ELEM(*point_counts, int, i, 0);
	}
	cvReleaseMat(&object_points);
	cvReleaseMat(&image_points);
	cvReleaseMat(&point_counts);

	// cvWaitKey();//Now we have to reallocate the matrices
	// return 0;
	// At this point we have all of the chessboard corners we need.
	//

	// Initialize the intrinsic matrix such that the two focal
	// lengths have a ratio of 1.0
	//
	CV_MAT_ELEM(*intrinsic_matrix, float, 0, 0) = 1.0f;
	CV_MAT_ELEM(*intrinsic_matrix, float, 1, 1) = 1.0f;
	cvCalibrateCamera2(
		object_points2,
		image_points2,
		point_counts2,
		cvGetSize(image),
		intrinsic_matrix,
		distortion_coeffs,
		NULL,
		NULL,
		0//CV_CALIB_FIX_ASPECT_RATIO
		);
	// Save our work
	cvSave("Intrinsics.xml", intrinsic_matrix);
	cvSave("Distortion.xml", distortion_coeffs);
	// Load test

	cout << "内参矩阵形式如下:" <<endl;
	cout << "fx , 0  , cx" << endl;
	cout << "0  , fy , cy" << endl;
	cout << "0  , 0  ,  1 = " << endl;
	for (int i = 0; i < intrinsic_matrix->rows; i++){
		for (int j = 0; j < intrinsic_matrix->cols; j++){
			cout << setw(8) << CV_MAT_ELEM(*intrinsic_matrix, float, i, j) <<',';
		}
		cout << endl;
	}

	cout << "畸变参数如下:" << endl;
	cout << "k1, k2, k3, p1, p2 =" << endl;
	for (int i = 0; i < distortion_coeffs->rows; i++){
		for (int j = 0; j < distortion_coeffs->cols; j++){
			cout << setw(8) << CV_MAT_ELEM(*distortion_coeffs, float, i, j) << ',';
		}
	}
	cout << endl;

	Birds_eye();

	return 0;
}
