#include <string>

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

static const size_t COUNT_OF_IMAGES = 20;
static const int TIMEOUT_MS = 1000; // TODO not used currently

static const int DEFAULT_ACQUISITION_RATE = 1000;
static const int DEFAULT_EXPOSURE_TIME = 1000;

static const int ROWS = 256;
static const int COLS = 6144;

using namespace Pylon;
using namespace std;
using namespace cv;

/**
 * Usage:
 * $./capture <exposureTime> <acquisitionRate>
 */
int main(int argc, char* argv[])
{
	int acquisition_rate = DEFAULT_ACQUISITION_RATE;
	int exposure_time = DEFAULT_EXPOSURE_TIME;

	if (argc >= 2)
		exposure_time = stoi(string(argv[1]));
	if (argc >= 3)
		acquisition_rate = stoi(string(argv[2]));

	PylonInitialize();

	try {
		Mat resultImage = Mat(ROWS, COLS, CV_8UC3);
		Mat resizedImage = Mat(ROWS*2, COLS, CV_8UC3);

        	CBaslerGigEInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
		CGrabResultPtr ptrGrabResult;

		cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

		camera.Open();
		camera.Width.SetValue(COLS);
		camera.Height.SetValue(ROWS);
		camera.OffsetX.SetValue(0);
		camera.OffsetY.SetValue(0);

		cout << "Setting exposure time to " << to_string(exposure_time) << endl;
		camera.ExposureTimeRaw.SetValue(exposure_time);
		cout << "Setting Acquisition line rate to " << to_string(acquisition_rate) << endl;
		camera.AcquisitionLineRateAbs.SetValue(acquisition_rate);

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
			cout << "captured" << endl;
		}

		resize(resultImage, resizedImage, Size(COLS*2, ROWS * COUNT_OF_IMAGES));

		imwrite("result.jpg", resizedImage);
		//imwrite("result.jpg", resultImage);

	}
	catch(const GenericException &e)
	{
		cerr << "An exception occured during capturing." << endl
		<< e.GetDescription() << endl;
	}

	PylonTerminate();
}
