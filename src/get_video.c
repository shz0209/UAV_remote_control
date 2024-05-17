#include "../include/get_video.h"

void* get_video(void* arg)
{
    
    cv::VideoCapture cap("http://192.168.1.1:8081/");
    // cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        printf("Error: Couldn't open the camera.\n");
        return NULL;
    }
    cv::Mat frame;
    while (1) 
    {
        cap>>frame;
        if (frame.empty()) 
        {
        std::err << "Error: Couldn't read a frame from the camera." << std::endl;
        }

        cv::imshow("Received Image", frame);
        char key = cv::waitKey(10);
        if (key == 27) { // ESC 键的 ASCII 码是 27
            break;
        }
        
    }
    cv::destroyAllWindows();
    cap.release();
    return NULL;
}
