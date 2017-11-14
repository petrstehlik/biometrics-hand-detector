#include <pylon/PylonIncludes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

static const size_t COUNT_OF_IMAGES = 1024;
static const int TIMEOUT_MS = 10000; // TODO not used currently

static const int ROWS = 256;
static const int COLS = 2048;

using namespace Pylon;
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	PylonInitialize();

	try {
		Mat resultImage = Mat(ROWS, COLS, CV_8UC3);
		CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
		CGrabResultPtr ptrGrabResult;

		cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

		camera.StartGrabbing(COUNT_OF_IMAGES);

		CImageFormatConverter formatConverter;
		formatConverter.OutputPixelFormat = PixelType_BGR8packed;

		while(camera.IsGrabbing())
		{
			camera.RetrieveResult(TIMEOUT_MS, ptrGrabResult, TimeoutHandling_ThrowException);
			if (ptrGrabResult->GrabSucceeded()) {
				Mat currentImage;
				CPylonImage pylonImage;
				formatConverter.Convert(pylonImage, ptrGrabResult);
				currentImage = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
				resultImage.push_back(currentImage);
			}
		}

		imwrite("result.jpg", resultImage);

	}
	catch(const GenericException &e)
	{
		cerr << "An exception occured during capturing." << endl
		<< e.GetDescription() << endl;
	}

	PylonTerminate();
}
