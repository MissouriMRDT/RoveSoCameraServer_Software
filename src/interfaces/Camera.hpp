/******************************************************************************
 * @brief Defines the Camera base interface class.
 *
 * @file Camera.hpp
 * @author ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-08-17
 *
 * @copyright Copyright Mars Rover Design Team 2023 - All Rights Reserved
 ******************************************************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../util/vision/FetchContainers.hpp"
#include "./AutonomyThread.hpp"

/// \cond
#include <atomic>
#include <future>
#include <shared_mutex>

/// \endcond

/******************************************************************************
 * @brief This interface class serves as a base for all other classes that will
 *      implement and interface with a type of camera.
 *
 *
 * @author ClayJay3 (claytonraycowen@gmail.com)
 * @date 2023-08-17
 ******************************************************************************/
template<class T>
class Camera : public AutonomyThread<void>
{
    public:
        // Declare public methods and member variables.
        /******************************************************************************
         * @brief Construct a new Camera object.
         *
         * @param nPropResolutionX - X res of camera.
         * @param nPropResolutionY - Y res of camera.
         * @param nPropFramesPerSecond - FPS camera is running at.
         * @param ePropPixelFormat - The pixel layout/format of the image.
         * @param dPropHorizontalFOV - The horizontal field of view.
         * @param dPropVerticalFOV - The vertical field of view.
         * @param bEnableRecordingFlag - Whether or not this camera should be recorded.
         *
         * @author ClayJay3 (claytonraycowen@gmail.com)
         * @date 2023-08-18
         ******************************************************************************/
        Camera(const int nPropResolutionX,
               const int nPropResolutionY,
               const int nPropFramesPerSecond,
               const PIXEL_FORMATS ePropPixelFormat,
               const double dPropHorizontalFOV,
               const double dPropVerticalFOV,
               const bool bEnableRecordingFlag)
        {
            // Initialize member variables.
            m_nPropResolutionX     = nPropResolutionX;
            m_nPropResolutionY     = nPropResolutionY;
            m_nPropFramesPerSecond = nPropFramesPerSecond;
            m_ePropPixelFormat     = ePropPixelFormat;
            m_dPropHorizontalFOV   = dPropHorizontalFOV;
            m_dPropVerticalFOV     = dPropVerticalFOV;
            m_bEnableRecordingFlag = bEnableRecordingFlag;
        }

        /******************************************************************************
         * @brief Destroy the Camera object.
         *
         *
         * @author ClayJay3 (claytonraycowen@gmail.com)
         * @date 2023-08-18
         ******************************************************************************/
        virtual ~Camera() {}

        /******************************************************************************
         * @brief Accessor for the Prop Resolution private member.
         *
         * @return cv::Size - The resolution of the camera stored in OpenCV's cv::Size.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-08-19
         ******************************************************************************/
        cv::Size GetPropResolution() const { return cv::Size(m_nPropResolutionX, m_nPropResolutionY); }

        /******************************************************************************
         * @brief Accessor for the Prop Frames Per Second private member.
         *
         * @return int - The FPS of the camera.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-08-19
         ******************************************************************************/
        int GetPropFramesPerSecond() const { return m_nPropFramesPerSecond; }

        /******************************************************************************
         * @brief Accessor for the Prop Pixel Format private member.
         *
         * @return PIXEL_FORMATS - The layout/pixel format of the image returned from
         *                      the camera.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-08-19
         ******************************************************************************/
        PIXEL_FORMATS GetPropPixelFormat() const { return m_ePropPixelFormat; }

        /******************************************************************************
         * @brief Accessor for the Prop Horizontal FOV private member.
         *
         * @return double - The horizontal field of view of the camera.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-08-19
         ******************************************************************************/
        double GetPropHorizontalFOV() const { return m_dPropHorizontalFOV; }

        /******************************************************************************
         * @brief Accessor for the Prop Vertical FOV private member.
         *
         * @return double - The vertical field of view of the camera.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-08-19
         ******************************************************************************/
        double GetPropVerticalFOV() const { return m_dPropVerticalFOV; }

        /******************************************************************************
         * @brief Accessor for the Enable Recording Flag private member.
         *
         * @return true - Recording for this camera has been requested/flagged.
         * @return false - This camera should not be recorded.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-12-26
         ******************************************************************************/
        bool GetEnableRecordingFlag() const { return m_bEnableRecordingFlag; }

        /******************************************************************************
         * @brief Mutator for the Enable Recording Flag private member
         *
         * @param bEnableRecordingFlag - Whether or not recording should be enabled for this camera.
         *
         * @author clayjay3 (claytonraycowen@gmail.com)
         * @date 2023-12-26
         ******************************************************************************/
        void SetEnableRecordingFlag(const bool bEnableRecordingFlag) { m_bEnableRecordingFlag = bEnableRecordingFlag; }

    protected:
        // Declare protected methods and member variables.
        int m_nPropResolutionX;
        int m_nPropResolutionY;
        int m_nPropFramesPerSecond;
        PIXEL_FORMATS m_ePropPixelFormat;
        double m_dPropHorizontalFOV;
        double m_dPropVerticalFOV;
        std::atomic_bool m_bEnableRecordingFlag;

        // Queues and mutexes for scheduling and copying camera frames and data to other threads.
        std::queue<containers::FrameFetchContainer<T>> m_qFrameCopySchedule;
        std::shared_mutex m_muPoolScheduleMutex;
        std::shared_mutex m_muFrameCopyMutex;

        // Declare interface class pure virtual functions. (These must be overriden by inheritor.)
        virtual std::future<bool> RequestFrameCopy(T& tFrame) = 0;    // This is where the code to retrieve an image from the camera is put.
        virtual bool GetCameraIsOpen()                        = 0;    // This is where the code to check if the camera is current open goes.

    private:
        // Declare private methods and member variables.
};

#endif
