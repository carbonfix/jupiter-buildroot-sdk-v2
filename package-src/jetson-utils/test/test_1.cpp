#include "test_1.hpp"
#include <stdio.h>
#include "glib.h"
#include <glib.h>

#include "opencv2/opencv.hpp"
#include "../sensors/include/get_sensor_data.h"

int test_opencv_function()
{
    // 加载图片
    cv::Mat img = cv::imread("/root/my_image.jpg");

    // 检查图片是否成功加载
    if (img.empty()) {
        std::cerr << "图片加载失败，请检查路径！" << std::endl;
        return -1;
    }

    // 创建窗口
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);

    // 显示图片
    cv::imshow("Display window", img);

    // 等待用户按键
    int k = cv::waitKey(0);

    // 如果用户按下'q'键，则退出
    if (k == 'q' || k == 27) {
        return 0;
    }

    // 销毁所有OpenCV创建的窗口
    cv::destroyAllWindows();

    return 0;
}

int test_sensor_function()
{
    int tick = 0;
    USER_INFO_T *pUserInfo;
    get_sensor_data_init();
    while (1)
    {
        sleep(1);
        tick++;

        if (tick == 5)
        {
            pUserInfo = get_sensor_buffer();
            printf("111====index[%d]=add[%p]==[%d]x[%d]==format[%d]==\n",
                   pUserInfo->bufferIndex, pUserInfo->dataBufferAddr,
                   pUserInfo->width, pUserInfo->height, pUserInfo->format);
        }
        if (tick == 10)
        {
            pUserInfo = get_sensor_buffer();
            printf("222====index[%d]=add[%p]==[%d]x[%d]==format[%d]==\n",
                   pUserInfo->bufferIndex, pUserInfo->dataBufferAddr,
                   pUserInfo->width, pUserInfo->height, pUserInfo->format);
        }

        if (tick == 12)
        {
            pUserInfo = get_sensor_buffer();
            printf("333====index[%d]=add[%p]==[%d]x[%d]==format[%d]==\n",
                   pUserInfo->bufferIndex, pUserInfo->dataBufferAddr,
                   pUserInfo->width, pUserInfo->height, pUserInfo->format);
        }
        if (tick == 15)
        {
            release_sensor_buffer(1);
            printf("444=----------------------------15---------------\n");
        }
        if (tick == 18)
        {
            release_sensor_buffer(0);
            printf("555=----------------------------18---------------\n");
        }
        if (tick == 20)
        {
            pUserInfo = get_sensor_buffer();
            printf("666====index[%d]=add[%p]==[%d]x[%d]==format[%d]==\n",
                   pUserInfo->bufferIndex, pUserInfo->dataBufferAddr,
                   pUserInfo->width, pUserInfo->height, pUserInfo->format);
        }
    }

    return 0;
}

int main() {
    //test_opencv_function();

    test_sensor_function();

    return 0;
}
