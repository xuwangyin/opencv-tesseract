/*
  a simple program demonstrating the use of Tesseract OCR engine with OpenCV,
  adopted from http://www.sk-spell.sk.cx/simple-example-how-to-call-use-tesseract-library
 */

#include <baseapi.h>
#include <allheaders.h>
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
  printf("Leptonica version: %s\n",
         getLeptonicaVersion());

  if (myOCR->Init(NULL, "eng")) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    exit(1);
  }

  // read iamge
  namedWindow("testocr", 0);
  Mat image = imread("sample.png", 0);

  // set region of interest (ROI), i.e. regions that contain text
  Rect text1ROI(80, 50, 800, 110);
  Rect text2ROI(190, 200, 550, 50);

  // create ROI images that contain text
  Mat text1Img = image(text1ROI);
  Mat text2Img = image(text2ROI);

  // recognize text
  myOCR->TesseractRect( text1Img.data, 1, text1Img.step1(), 0, 0, text1Img.cols, text1Img.rows);
  const char *text1 = myOCR->GetUTF8Text();

  myOCR->TesseractRect( text2Img.data, 1, text2Img.step1(), 0, 0, text2Img.cols, text2Img.rows);
  const char *text2 = myOCR->GetUTF8Text();

  // print found text
  printf("found text: \n");
  printf(text1);
  printf(text2);

  // remove "newline"
  string t1(text1);
  t1.erase(std::remove(t1.begin(), t1.end(), '\n'), t1.end());

  string t2(text2);
  t2.erase(std::remove(t2.begin(), t2.end(), '\n'), t2.end());

  // draw text on original image
  Mat scratch = imread("sample.png");

  int fontFace = FONT_HERSHEY_PLAIN;
  double fontScale = 2;
  int thickness = 2;
  putText(scratch, t1, Point(text1ROI.x, text1ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);
  putText(scratch, t2, Point(text2ROI.x, text2ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);

  rectangle(scratch, text1ROI, Scalar(0, 0, 255), 2, 8, 0);
  rectangle(scratch, text2ROI, Scalar(0, 0, 255), 2, 8, 0);

  imshow("testocr", scratch);
  waitKey(0);

  delete [] text1;
  delete [] text2;

  // as a comparation, apply tesseract OCR to the whole image
  Pix *pix = pixRead("sample.png");
  myOCR->SetImage(pix);
  char* outText = myOCR->GetUTF8Text();

  // print found text
  printf("Whole Image OCR output:\n\n");
  printf(outText);

  // destroy text and image
  delete [] outText;
  pixDestroy(&pix);

  // destroy tesseract OCR engine
  myOCR->Clear();
  myOCR->End();

  return 0;
}
