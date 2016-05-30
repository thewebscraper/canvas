#ifndef IMGPROC_H
#define IMGPROC_H

#include <QImage>
#include <QString>

#include <opencv/cv.h>
#include <opencv2/core/mat.hpp>

class ImgProc
{
public:
    ImgProc();
    QImage adjust_contrast_brightness (const int & alpha,
                                       const int & beta);

    QImage adjust_saturation (const int & value);
    QImage adjust_hue        (const int & value);
    QImage get               ();

private:

    void for_each_pixel (cv::Mat & image,
                         const uchar & value,
                         int index);

    QImage get_image (const cv::Mat & img);

    QString path;
    cv::Mat img;
    cv::Mat new_image;
    cv::Mat out_image;
    cv::Mat hue;
    cv::Mat saturation;
};

#endif // IMGPROC_H
