/******************************************************************************
 * @brief Implements the RecordingHandler class.
 *
 * @file RecordingHandler.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "RecordingHandler.h"
#include "../RoveSoCameraServerConstants.h"
#include "../RoveSoCameraServerGlobals.h"
#include "../RoveSoCameraServerLogging.h"

/// \cond
#include <filesystem>

/// \endcond

/******************************************************************************
 * @brief Construct a new Recording Handler:: Recording Handler object.
 *
 * @param eRecordingMode - The mode the recorder should run in.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
RecordingHandler::RecordingHandler(RecordingMode eRecordingMode)
{
    // Initialize member variables.
    m_eRecordingMode = eRecordingMode;
    // Set max FPS of the ThreadedContinuousCode method.
    this->SetMainThreadIPSLimit(constants::RECORDER_FPS);

    // Resize vectors to match number of video feeds.
    switch (eRecordingMode)
    {
        // RecordingHandler was initialized to record feeds from the CameraHandler.
        case RecordingMode::eCameraHandler:
            // Initialize member variables.
            m_nTotalVideoFeeds = int(CameraHandler::BasicCamName::BASICCAM_END) - 1;
            // Resize member vectors to match number of total video feeds to record.
            m_vBasicCameras.resize(m_nTotalVideoFeeds);
            m_vCameraWriters.resize(m_nTotalVideoFeeds);
            m_vRecordingToggles.resize(m_nTotalVideoFeeds);
            m_vFrames.resize(m_nTotalVideoFeeds);
            m_vGPUFrames.resize(m_nTotalVideoFeeds);
            m_vFrameFutures.resize(m_nTotalVideoFeeds);
            break;

        default:
            // Do nothing.
            break;
    }
}

/******************************************************************************
 * @brief Destroy the Recording Handler:: Recording Handler object.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
RecordingHandler::~RecordingHandler()
{
    // Signal and wait for recording thread to stop.
    this->RequestStop();
    this->Join();

    // Loop through and close video writers.
    for (cv::VideoWriter cvCameraWriter : m_vCameraWriters)
    {
        // Release video writer.
        cvCameraWriter.release();
    }
}

/******************************************************************************
 * @brief This code will run continuously in a separate thread. New frames from
 *      the cameras that have recording enabled are grabbed and the images are
 *      written to the filesystem.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void RecordingHandler::ThreadedContinuousCode()
{
    // Check what mode recorder was initialized with.
    switch (m_eRecordingMode)
    {
        // Record video feeds from the CameraHandler.
        case RecordingMode::eCameraHandler:
            // Update recordable cameras.
            this->UpdateRecordableCameras();
            // Grab and write frames to VideoWriters.
            this->RequestAndWriteCameraFrames();
            break;

        // Shutdown recording handler.
        default:
            // Submit logger message.
            LOG_ERROR(logging::g_qSharedLogger,
                      "The RecordingHandler was initialized with a RecordingMode enum value that doesn't make sense! Thread is shutting down...");
            // Request main thread stop.
            this->RequestStop();
            break;
    }
}

/******************************************************************************
 * @brief This method holds the code that is ran in the thread pool started by
 *      the ThreadedLinearCode() method. It currently does nothing and is not
 *      needed in the current implementation of the RecordingHandler.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void RecordingHandler::PooledLinearCode() {}

/******************************************************************************
 * @brief This method is used internally by the class to update the number of cameras
 *      that have recording enabled from the camera handler.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void RecordingHandler::UpdateRecordableCameras()
{
    // Loop through all Basic cameras from the CameraHandler.
    for (int nCamera = int(CameraHandler::BasicCamName::BASICCAM_START) + 1; nCamera != int(CameraHandler::BasicCamName::BASICCAM_END); ++nCamera)
    {
        // Get pointer to camera.
        BasicCam* pBasicCamera = globals::g_pCameraHandler->GetBasicCam(static_cast<CameraHandler::BasicCamName>(nCamera));
        // Store camera pointer in vector so we can get images later.
        m_vBasicCameras[nCamera - 1] = pBasicCamera;

        // Check if recording for this camera is enabled.
        if (pBasicCamera->GetEnableRecordingFlag() && pBasicCamera->GetCameraIsOpen())
        {
            // Set recording toggle.
            m_vRecordingToggles[nCamera - 1] = true;
            // Setup VideoWriter if needed.
            if (!m_vCameraWriters[nCamera - 1].isOpened())
            {
                // Assemble filepath string.
                std::filesystem::path szFilePath;
                std::filesystem::path szFilenameWithExtension;
                szFilePath = constants::LOGGING_OUTPUT_PATH_ABSOLUTE;                    // Main location for all recordings.
                szFilePath += logging::g_szProgramStartTimeString + "/cameras";          // Folder for each program run.
                szFilenameWithExtension = pBasicCamera->GetCameraLocation() + ".mkv";    // Folder for each camera index or name.

                // Check if directory exists.
                if (!std::filesystem::exists(szFilePath))
                {
                    // Create directory.
                    if (!std::filesystem::create_directories(szFilePath))
                    {
                        // Submit logger message.
                        LOG_ERROR(logging::g_qSharedLogger,
                                  "Unable to create the VideoWriter output directory: {} for camera {}",
                                  szFilePath.string(),
                                  pBasicCamera->GetCameraLocation());
                    }
                }

                // Construct the full output path.
                std::filesystem::path szFullOutputPath = szFilePath / szFilenameWithExtension;

                // Open writer.
                bool bWriterOpened = m_vCameraWriters[nCamera - 1].open(szFullOutputPath.string(),
                                                                        cv::VideoWriter::fourcc('H', '2', '6', '4'),
                                                                        constants::RECORDER_FPS,
                                                                        pBasicCamera->GetPropResolution());

                // Check writer opened status.
                if (!bWriterOpened)
                {
                    // Submit logger message.
                    LOG_WARNING(logging::g_qSharedLogger,
                                "RecordingHandler: Failed to open cv::VideoWriter for basic camera at path/index {}",
                                pBasicCamera->GetCameraLocation());
                }
            }
        }
        else
        {
            // Set recording toggle.
            m_vRecordingToggles[nCamera - 1] = false;
        }
    }
}

/******************************************************************************
 * @brief This method is used internally by the RecordingHandler to request and write
 *      frames to from the cameras stored in the member variable vectors.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void RecordingHandler::RequestAndWriteCameraFrames()
{
    // Loop through total number of cameras and request frames.
    for (int nIter = 0; nIter < m_nTotalVideoFeeds; ++nIter)
    {
        // Check if recording for the camera at this index is enabled.
        if (m_vRecordingToggles[nIter])
        {
            // Check if the camera at the current index is a BasicCam or ZEDCam.
            if (m_vBasicCameras[nIter] != nullptr)
            {
                // Request frame.
                m_vFrameFutures[nIter] = m_vBasicCameras[nIter]->RequestFrameCopy(m_vFrames[nIter]);
            }
        }
    }

    // Loop through cameras and wait for frame requests to be fulfilled.
    for (int nIter = 0; nIter < m_nTotalVideoFeeds; ++nIter)
    {
        // Check if recording for the camera at this index is enabled.
        if (m_vRecordingToggles[nIter])
        {
            // Check if the camera at the current index is a BasicCam or ZEDCam.
            if (m_vBasicCameras[nIter] != nullptr)
            {
                // Wait for future to be fulfilled.
                if (m_vFrameFutures[nIter].get() && !m_vFrames[nIter].empty())
                {
                    // Check if this is a grayscale or color image.
                    if (m_vFrames[nIter].channels() == 1)
                    {
                        // Convert frame from 1 channel grayscale to 3 channel BGR.
                        cv::cvtColor(m_vFrames[nIter], m_vFrames[nIter], cv::COLOR_GRAY2BGR);
                    }
                    // Check if this has an alpha channel.
                    else if (m_vFrames[nIter].channels() == 4)
                    {
                        // Convert from from 4 channels to 3 channels.
                        cv::cvtColor(m_vFrames[nIter], m_vFrames[nIter], cv::COLOR_BGRA2BGR);
                    }

                    // Write frame to OpenCV video writer.
                    m_vCameraWriters[nIter].write(m_vFrames[nIter]);
                }
            }
        }
    }
}

/******************************************************************************
 * @brief Mutator for the desired FPS for all camera recordings.
 *
 * @param nRecordingFPS - The frames per second to record all cameras at.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void RecordingHandler::SetRecordingFPS(const int nRecordingFPS)
{
    // Set the max iterations per second of the recording handler.
    this->SetMainThreadIPSLimit(nRecordingFPS);
}

/******************************************************************************
 * @brief Accessor for the desired FPS for all camera recordings.
 *
 * @return int - The FPS of all camera recordings.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
int RecordingHandler::GetRecordingFPS() const
{
    // Return member variable value.
    return this->GetMainThreadMaxIPS();
}
