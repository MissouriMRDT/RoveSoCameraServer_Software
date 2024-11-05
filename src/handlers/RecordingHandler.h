/******************************************************************************
 * @brief Defines the RecordingHandler class.
 *
 * @file RecordingHandler.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef RECORDING_HANDLER_H
#define RECORDING_HANDLER_H

#include "../vision/cameras/BasicCam.h"

/// \cond
#include <opencv2/opencv.hpp>
#include <vector>

/// \endcond

/******************************************************************************
 * @brief The RecordingHandler class serves to enumerate the cameras available from
 *      the CameraHandler and retrieve and write frames from each camera to the filesystem.
 *      The recording of each camera can be disabled through constants and the framerate
 *      of the recording can be adjusted to save CPU-time and resources.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
class RecordingHandler : public AutonomyThread<void>
{
    public:
        /////////////////////////////////////////
        // Define public enumerators specific to this class.
        /////////////////////////////////////////

        // Enum used to select which mode the recorder should run in.
        enum class RecordingMode
        {
            eCameraHandler    // Record video feeds from the CameraHandler.
        };

        /////////////////////////////////////////
        // Declare public class methods and variables.
        /////////////////////////////////////////

        RecordingHandler(RecordingMode eRecordingMode);
        ~RecordingHandler();

        /////////////////////////////////////////
        // Mutators.
        /////////////////////////////////////////

        void SetRecordingFPS(const int nRecordingFPS);

        /////////////////////////////////////////
        // Accessors.
        /////////////////////////////////////////

        int GetRecordingFPS() const;

    private:
        /////////////////////////////////////////
        // Declare private methods.
        /////////////////////////////////////////

        void ThreadedContinuousCode() override;
        void PooledLinearCode() override;
        void UpdateRecordableCameras();
        void RequestAndWriteCameraFrames();

        /////////////////////////////////////////
        // Declare private class member variables.
        /////////////////////////////////////////

        int m_nTotalVideoFeeds;
        RecordingMode m_eRecordingMode;
        std::vector<BasicCam*> m_vBasicCameras;
        std::vector<cv::VideoWriter> m_vCameraWriters;
        std::vector<bool> m_vRecordingToggles;
        std::vector<cv::Mat> m_vFrames;
        std::vector<cv::cuda::GpuMat> m_vGPUFrames;
        std::vector<std::future<bool>> m_vFrameFutures;
};
#endif
