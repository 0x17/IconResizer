#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <boost/filesystem.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

void enforceDirectoryExists(const string &path);
void writeResizedIcons(const string &outPath, const Mat &inputImage);
void writeEmptyBlackLaunchImages(const string &outPath);

int main(int argc, char** argv)  {
	string homePath = getenv("HOME");

	string defaultSrc = homePath + "/SourceImage.png";
	string defaultOutPath = homePath + "/Desktop/Conversions";

	string sourceImage = argc > 1 ? argv[1] : defaultSrc;
	string outPath = argc > 2 ? argv[2] : defaultOutPath;

	path parentOutPath = path(outPath).parent_path();
	if(!is_directory(parentOutPath))
		throw runtime_error("Output parent directory does not exist!");

	enforceDirectoryExists(outPath);

	Mat inputImage = imread(sourceImage.c_str(), IMREAD_COLOR);
	if(inputImage.empty())
		throw runtime_error("Could not open or find the image!");

	writeResizedIcons(outPath, inputImage);
	writeEmptyBlackLaunchImages(outPath);

	return 0;
}

void enforceDirectoryExists(const string &path) {
	if(!exists(path)) {
		create_directory(path);
	}
}

void writeResizedQuadImage(const Mat &src, int wh, const string& out) {
	Size destSize(wh, wh);
	Mat outputImage;
	resize(src, outputImage, destSize);
	imwrite(out, outputImage);
}

void writeBlackImage(const Size s, const string &out) {
	Mat img(s, CV_8UC3, Scalar(0, 0, 0));
	imwrite(out, img);
}

void writeResizedIcons(const string &outPath, const Mat &inputImage) {
	list<pair<int, string>> sizes = {
			{20, "20pt@1x"},
			{29, "29pt@1x"},
			{40, "20pt@2x_40pt@1x"},
			{58, "29pt@2x"},
			{60, "20pt@3x"},
			{80, "40pt@2x"},
			{87, "29pt@3x"},
			{120, "40pt@3x"},
			{152, "76pt@2x"},
			{167, "83_5pt@2x"},
			{180, "60pt@3x"}
	};

	for(auto size : sizes) {
		writeResizedQuadImage(inputImage, size.first, outPath + "/scaled" + to_string(size.first) + "_" + size.second+ ".png");
	}
}

void writeEmptyBlackLaunchImages(const string &outPath) {
	list<pair<Size, string>> launchSizes = {
			{{2208, 1242}, "iPhone6s7Plus"},
			{{1334, 750}, "iPhone6s7"},
			{{1136, 640}, "iPhoneSE"},
			{{2732, 2048}, "12_9iPadPro2x"},
			{{1366, 1024}, "12_9iPadPro1x"},
			{{2048, 1536}, "9_7iPadProAirMini2x"},
			{{1024, 768}, "9_7iPadProAirMini"}
	};

	for(auto launchSize : launchSizes) {
		writeBlackImage(launchSize.first, outPath + "/launchImage_" + launchSize.second + ".png");
	}
}