#include "kinectcamera.h"
#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include <QPainter>
#include <QImage>
#include <vector>
#include <stdio.h>
using namespace std;
using namespace cv;
openni::VideoFrameRef  mColorFrame;
openni::VideoStream mColorStream;
openni::VideoFrameRef  mDepthFrame;
openni::VideoStream mDepthStream;
openni::Device mDevice;
QImage KinectDepthImage;
QImage KinectColorImage;
static bool kinectstartconfig =0;//设置kinectstartconfig来判断设备是否打开
KinectCamera::KinectCamera(QQuickItem *parent)
    : QQuickPaintedItem(parent),m_streamsource("color")
{
}

void KinectCamera::startcamera(void)
{
    // 1. Initial OpenNI
    if(openni::OpenNI::initialize() != openni::STATUS_OK )
    {
      cerr << "OpenNI Initial Error: "
           <<openni::OpenNI::getExtendedError() << endl;
    }


    // 2. Open Device
    //  Device mDevice;//already defined in globle varable
    if( mDevice.open(openni:: ANY_DEVICE ) != openni::STATUS_OK )
    {
      cerr << "Can't Open Device: "
           <<openni:: OpenNI::getExtendedError() << endl;
    }


    // 3. Create depth stream
    //  VideoStream mDepthStream;//already defined in globle varable
    if( mDepthStream.create( mDevice, openni::SENSOR_DEPTH ) == openni::STATUS_OK )
    {
      // 3a. set video mode
      openni:: VideoMode mMode;
      mMode.setResolution( 640, 480 );
      mMode.setFps( 30 );
      mMode.setPixelFormat( openni:: PIXEL_FORMAT_DEPTH_1_MM );

      if( mDepthStream.setVideoMode( mMode) != openni::STATUS_OK )
      {
        cout << "Can't apply VideoMode: "
             << openni:: OpenNI::getExtendedError() << endl;
      }
    }
    else
    {
      cerr << "Can't create depth stream on device: "
           << openni:: OpenNI::getExtendedError() << endl;
    }


    // 4. Create color stream
    //  VideoStream mColorStream;//already defined in globle varable
      if( mColorStream.create( mDevice, openni::SENSOR_COLOR ) == openni::STATUS_OK )
      {
        // 4a. set video mode
        openni:: VideoMode mMode;
        mMode.setResolution( 640, 480 );
        mMode.setFps( 30 );
        mMode.setPixelFormat(openni::  PIXEL_FORMAT_RGB888 );

        if( mColorStream.setVideoMode( mMode) != openni::STATUS_OK )
        {
          cout << "Can't apply VideoMode: "
               << openni:: OpenNI::getExtendedError() << endl;
        }

        // 4b. image registration//corresponding the color to depth
        if( mDevice.isImageRegistrationModeSupported(
               openni::  IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
        {
          mDevice.setImageRegistrationMode(openni:: IMAGE_REGISTRATION_DEPTH_TO_COLOR );
        }
      }
      else
      {
        cerr << "Can't create color stream on device: "
             << openni:: OpenNI::getExtendedError() << endl;
      }


    //5. Start stream
    mColorStream.start();//开启颜色数据流
    mDepthStream.start();//开启深度数据流
    kinectstartconfig=1;
}

void KinectCamera::closecamera(void)
{
    mColorStream.destroy();
    mDepthStream.destroy();
    mDevice.close();
    openni:: OpenNI::shutdown();
}

void KinectCamera::updatecamera(void)
{
    update();
}

void KinectCamera::paint(QPainter *painter)
{

    if (!kinectstartconfig)//如果设备未打开，先执行startcamera
    {
        startcamera();//打开设备
        if(m_streamsource=="depth")
        {
            if( mDepthStream.isValid() )
            {
                if( mDepthStream.readFrame( &mDepthFrame ) == openni::STATUS_OK )
                {
                    const cv::Mat mImageDepth(
                                mDepthFrame.getHeight(), mDepthFrame.getWidth(),
                                CV_16UC1, (void*)mDepthFrame.getData() );
                    //??????????????????????????????????????????????????1.使用1时可以mask掉深度0点，但是不知道何原因，在qml里必须先paint colorimage
                    Mat minMaxmask;//define mask to mask the point where depth =0
                    mImageDepth.convertTo( minMaxmask, CV_8U);//the mask must be 8U

                    double minPixelValue, maxPixelValue;//define the min and max value of the depth
                    int *mindepthindex1, *maxdepthindex1;//define the index of min and max value of the depth

                    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue,mindepthindex1,maxdepthindex1,minMaxmask);

                    //??????????????????????????????????????????????????2.使用2时不可以mask掉深度0点，但是可以任意paint，可能是 mImageDepth.convertTo( mask1, CV_8U);的问题，如果是规定好最大最小值，可以写成函数形式，使用此方法
                    //    double minPixelValue, maxPixelValue;
                    //    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue);

                    cv::Mat mScaledDepth;
                    mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / (maxPixelValue-minPixelValue),-255.0*minPixelValue/(maxPixelValue-minPixelValue));//深度映射到[0,255]
                    QVector<QRgb>  colorTable;
                    for(int k=0;k<256;++k)
                    {
                        colorTable.push_back( qRgb(k,k,k) );
                    }
                    KinectDepthImage= QImage((const unsigned char*)mScaledDepth.data,mDepthFrame.getWidth(), mDepthFrame.getHeight(),QImage::Format_Indexed8);
                    KinectDepthImage.setColorTable(colorTable);
                    painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),KinectDepthImage);
                }
            }
        }
        else
        {
            if( mColorStream.readFrame( &mColorFrame ) == openni::STATUS_OK )
            {
                KinectColorImage= QImage((const unsigned char*)mColorFrame.getData(),mColorFrame.getWidth(), mColorFrame.getHeight(),QImage::Format_RGB888);
                painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),KinectColorImage);
            }
        }
    }
    else//如果设备以打开，直接执行
    {
        if(m_streamsource=="depth")
        {
            if( mDepthStream.isValid() )
            {
                if( mDepthStream.readFrame( &mDepthFrame ) == openni::STATUS_OK )
                {
                    const cv::Mat mImageDepth(
                                mDepthFrame.getHeight(), mDepthFrame.getWidth(),
                                CV_16UC1, (void*)mDepthFrame.getData() );

                    //??????????????????????????????????????????????????1.使用1时可以mask掉深度0点，但是不知道何原因，在qml里必须先paint colorimage
                    Mat minMaxmask;//define mask to mask the point where depth =0
                    mImageDepth.convertTo( minMaxmask, CV_8U);//the mask must be 8U

                    double minPixelValue, maxPixelValue;//define the min and max value of the depth
                    int *minindexdepth, *maxindexdepth;//define the index of min and max value of the depth

                    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue,minindexdepth,maxindexdepth,minMaxmask);

                    //??????????????????????????????????????????????????2.使用12时不可以mask掉深度0点，但是可以任意paint，可能是 mImageDepth.convertTo( mask1, CV_8U);的为题
                    //    double minPixelValue, maxPixelValue;
                    //    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue);

                    cv::Mat mScaledDepth;
                    mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / (maxPixelValue-minPixelValue),-255.0*minPixelValue/(maxPixelValue-minPixelValue));
                    QVector<QRgb>  colorTable;
                    for(int k=0;k<256;++k)
                    {
                        colorTable.push_back( qRgb(k,k,k) );
                    }
                    KinectDepthImage= QImage((const unsigned char*)mScaledDepth.data,mDepthFrame.getWidth(), mDepthFrame.getHeight(),QImage::Format_Indexed8);
                    KinectDepthImage.setColorTable(colorTable);
                    painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),KinectDepthImage);
                }
            }
        }
        else
        {
            if( mColorStream.readFrame( &mColorFrame ) == openni::STATUS_OK )
            {
                KinectColorImage= QImage((const unsigned char*)mColorFrame.getData(),mColorFrame.getWidth(), mColorFrame.getHeight(),QImage::Format_RGB888);
                painter->drawImage(boundingRect().adjusted(1, 1, -1, -1),KinectColorImage);
            }
        }
    }
}

//void KinectCamera::depthprocess(void)
//{
//    const cv::Mat mImageDepth(
//                mDepthFrame.getHeight(), mDepthFrame.getWidth(),
//                CV_16UC1, (void*)mDepthFrame.getData() );
//////??????????????????????????????????????????????????1.
////    Mat mask1;
////    mImageDepth.convertTo( mask1, CV_8U);
////    double minPixelValue, maxPixelValue;
////    int *aa, *bb;
////    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue,aa,bb,mask1);

////????????????????????????????????????????????????2.使用2时，不能将深度0点mask掉，只有这时才能用process函数
//    double minPixelValue, maxPixelValue;
//    cv::minMaxIdx(mImageDepth, &minPixelValue, &maxPixelValue);


//    cv::Mat mScaledDepth;
//    mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / (maxPixelValue-minPixelValue),-255.0*minPixelValue/(maxPixelValue-minPixelValue));
//    QVector<QRgb>  colorTable;
//    for(int k=0;k<256;++k)
//    {
//        colorTable.push_back( qRgb(k,k,k) );
//    }
//    KinectDepthImage= QImage((const unsigned char*)mScaledDepth.data,mDepthFrame.getWidth(), mDepthFrame.getHeight(),QImage::Format_Indexed8);
//    KinectDepthImage.setColorTable(colorTable);
//}

QString KinectCamera::getstreamsource(void) const
{
    return m_streamsource;
}
void KinectCamera::setstreamsource(const QString streamsource)
{
   m_streamsource=streamsource;
   emit streamsourceChanged();
}

