#include "../include/get_video.h"

int get_video()
{
    printf("get video successfully");
    cv::VideoCapture cap;
    cap.open(0);

    if (!cap.isOpened()) {
        printf("Error: Couldn't open the camera.\n");
        return -1;
    }
    // cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    while (1) 
    {
        cv::Mat frame;
        // cap >> frame;
        // cap.read(frame);
        do
        {
            cap>>frame;
            if (frame.empty()) {
            std::cerr << "Error: Couldn't read a frame from the camera." << std::endl;
            }
        }while(frame.empty());

        

        cv::imshow("Received Image", frame);
        char key = cv::waitKey(10);
        if (key == 27) { // ESC 键的 ASCII 码是 27
            break;
        }
        
        
        // 获取图像数据大小
    }
    cv::destroyAllWindows();
    cap.release();
}
