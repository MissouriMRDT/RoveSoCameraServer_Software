/******************************************************************************
 * @brief Defines the BasicCam class.
 *
 * @file BasicCam.h
 * @author ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-08-17
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#ifndef BASICCAM_H
#define BASICCAM_H

#include "../../interfaces/AutonomyThread.hpp"
#include "../../interfaces/Camera.hpp"

/// \cond
#include <opencv2/opencv.hpp>

/// \endcond

/******************************************************************************
 * @brief This class implements and interfaces with the most common USB cameras
 *  and features. It is designed in such a way that multiple other classes/threads
 *  can safely call any method of an object of this class withing resource corruption
 *  or slowdown of the camera.
 *
 *
 * @author clayjay3 (claytonraycowen@gmail.com)
 * @date 2023-09-21
 ******************************************************************************/
class BasicCam : public Camera<cv::Mat>
{
    public:
        /////////////////////////////////////////
        // Declare public methods and member variables.
        /////////////////////////////////////////

        BasicCam(const std::string szCameraPath,
                 const int nPropResolutionX,
                 const int nPropResolutionY,
                 const int nPropFramesPerSecond,
                 const PIXEL_FORMATS ePropPixelFormat,
                 const double dPropHorizontalFOV,
                 const double dPropVerticalFOV,
                 const bool bEnableRecordingFlag,
                 const int nNumFrameRetrievalThreads = 10);
        BasicCam(const int nCameraIndex,
                 const int nPropResolutionX,
                 const int nPropResolutionY,
                 const int nPropFramesPerSecond,
                 const PIXEL_FORMATS ePropPixelFormat,
                 const double dPropHorizontalFOV,
                 const double dPropVerticalFOV,
                 const bool bEnableRecordingFlag,
                 const int nNumFrameRetrievalThreads = 10);
        ~BasicCam();
        std::future<bool> RequestFrameCopy(cv::Mat& cvFrame) override;

        /////////////////////////////////////////
        // Getters.
        /////////////////////////////////////////

        std::string GetCameraLocation() const;
        bool GetCameraIsOpen() override;

    private:
        /////////////////////////////////////////
        // Declare private member variables.
        /////////////////////////////////////////
        // Basic Camera specific.
        cv::VideoCapture m_cvCamera;
        std::string m_szCameraPath;
        bool m_bCameraIsConnectedOnVideoIndex;
        int m_nCameraIndex;
        int m_nNumFrameRetrievalThreads;

        // Mats for storing frames.
        cv::Mat m_cvFrame;

        /////////////////////////////////////////
        // Declare private methods.
        /////////////////////////////////////////
        void ThreadedContinuousCode() override;
        void PooledLinearCode() override;
};
#endif
