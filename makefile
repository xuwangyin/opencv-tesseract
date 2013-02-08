all:
	g++ opencv-tesseract.cpp -o opencv-tesseract `pkg-config --cflags --libs opencv tesseract`
