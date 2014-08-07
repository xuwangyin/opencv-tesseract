/*
  a simple program demonstrating the use of Tesseract OCR engine with OpenCV,
  adopted from http://www.sk-spell.sk.cx/simple-example-how-to-call-use-tesseract-library
 */

#include <baseapi.h>
// #include <allheaders.h>
#include <sys/time.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char* argv[]) {

  // initilize tesseract OCR engine
  tesseract::TessBaseAPI *myOCR =
    new tesseract::TessBaseAPI();

  printf("Tesseract-ocr version: %s\n",
         myOCR->Version());
  // printf("Leptonica version: %s\n",
  //        getLeptonicaVersion());

  if (myOCR->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    exit(1);
  }

  tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7); // treat the image as a single text line
  myOCR->SetPageSegMode(pagesegmode);

  // read iamge
  namedWindow("tesseract-opencv", 0);
  Mat image = imread("sample.png", 0);

  // set region of interest (ROI), i.e. regions that contain text
  Rect text1ROI(80, 50, 800, 110);
  Rect text2ROI(190, 200, 550, 50);

  // recognize text
  myOCR->TesseractRect( image.data, 1, image.step1(), text1ROI.x, text1ROI.y, text1ROI.width, text1ROI.height);
  const char *text1 = myOCR->GetUTF8Text();

  myOCR->TesseractRect( image.data, 1, image.step1(), text2ROI.x, text2ROI.y, text2ROI.width, text2ROI.height);
  const char *text2 = myOCR->GetUTF8Text();

  // remove "newline"
  string t1(text1);
  t1.erase(std::remove(t1.begin(), t1.end(), '\n'), t1.end());

  string t2(text2);
  t2.erase(std::remove(t2.begin(), t2.end(), '\n'), t2.end());

  // print found text
  printf("found text1: \n");
  printf(t1.c_str());
  printf("\n");

  printf("found text2: \n");
  printf(t2.c_str());
  printf("\n");

  // draw text on original image
  Mat scratch = imread("sample.png");

  int fontFace = FONT_HERSHEY_PLAIN;
  double fontScale = 2;
  int thickness = 2;
  putText(scratch, t1, Point(text1ROI.x, text1ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);
  putText(scratch, t2, Point(text2ROI.x, text2ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);

  rectangle(scratch, text1ROI, Scalar(0, 0, 255), 2, 8, 0);
  rectangle(scratch, text2ROI, Scalar(0, 0, 255), 2, 8, 0);

  imshow("tesseract-opencv", scratch);
  waitKey(0);

  delete [] text1;
  delete [] text2;

  // destroy tesseract OCR engine
  myOCR->Clear();
  myOCR->End();

  return 0;
}
