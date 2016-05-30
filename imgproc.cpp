#include <QDebug>
#include <QImage>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

#include "imgproc.h"

ImgProc::ImgProc()
{
    path = "C:\\Users\\Joseph dela Pena\\Pictures\\DSC02297.JPG";
    img = cv::imread (path.toStdString());
    new_image = img.clone ();
    out_image = cv::Mat::zeros (img.size(), img.type());

    cvtColor(img, hue, CV_BGR2HSV);
    cvtColor(img, saturation, CV_BGR2HSV);
}

QImage
ImgProc::get ()
{
    return get_image (new_image);
}

/*
 * g (i,j) =  af(x) + b
 * alpha - adjust contrast
 * beta - adjust brightness
 */
QImage
ImgProc::adjust_contrast_brightness (const int & alpha,
                                     const int & beta)
{
    for (int y = 0; y < img.rows; y ++) {
        for (int x = 0; x < img.cols; x ++) {
            for (int c = 0; c < 3; c ++)  {
                out_image.at <cv::Vec3b> (y, x)[c] =
                        cv::saturate_cast <uchar> (alpha * new_image.at<cv::Vec3b> (y, x)[c] + beta);
            }
        }
    }
    //out_image.copyTo (new_image);
    return get_image (out_image);
}

void
ImgProc::for_each_pixel(cv::Mat & image,
                        const uchar & value,
                        int index)
{
    int rows     = image.rows;
    int cols     = image.cols;
    int channels = image.channels ();

    if (image.isContinuous ()) {
        cols = cols * rows;
        rows = 1;
    }

    for (int j=0; j<rows; ++j) {
        auto pixel = image.ptr(j);
        for (int i=0; i < cols; ++ i, pixel += channels) {
            if (pixel[index] <= (255 - value)) {
                pixel[index] += value;
            } else {
                pixel[index] = 255;
            }
        }
    }
}

QImage
ImgProc::adjust_hue (const int & value)
{
    /* hsv - hue index: 0 */
    for_each_pixel (hue, value / 10, 0);
    cvtColor(hue, out_image, CV_HSV2BGR);

    return get_image (out_image);
}

QImage
ImgProc::adjust_saturation (const int & value)
{
    /* hsv - saturation index: 1 */
    for_each_pixel (saturation, value / 10, 1);
    cvtColor(saturation, out_image, CV_HSV2BGR);

    return get_image (out_image);
}

QImage
ImgProc::get_image (const cv::Mat & img)
{
    switch (img.type()) {
         // 8-bit, 4 channel
         case CV_8UC4: {
            QImage image (img.data,
                          img.cols,
                          img.rows,
                          img.step,
                          QImage::Format_RGB32);

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3: {
            QImage image (img.data,
                          img.cols,
                          img.rows,
                          img.step,
                          QImage::Format_RGB888);

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1: {
            static QVector<QRgb>  ctable;

            // only create our color table once
            if (ctable.isEmpty()) {
               for ( int i = 0; i < 256; ++i ) {
                  ctable.push_back (qRgb( i, i, i));
               }
            }

            QImage image (img.data,
                          img.cols,
                          img.rows,
                          img.step,
                          QImage::Format_Indexed8);

            image.setColorTable (ctable);

            return image;
         }

         default:
            qDebug () << "cv::Mat image type not handled in switch:" << img.type();
            break;
    }

    return QImage();
}

