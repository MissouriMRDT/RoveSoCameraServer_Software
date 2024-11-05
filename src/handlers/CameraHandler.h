/******************************************************************************
 * @brief Defines the CameraHandler class.
 *
 * @file CameraHandler.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include "../vision/cameras/BasicCam.h"
#include "RecordingHandler.h"

/// \cond
#include <opencv2/core.hpp>

/// \endcond

/******************************************************************************
 * @brief The CameraHandler class is responsible for managing all of the
 *      camera feeds that are collected on the core rover. Whether
 *      it be a USB webcam or a MJPEG stream, this class is responsible
 *      for initializing that camera and configuring it.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
class CameraHandler
{
    private:
        /////////////////////////////////////////
        // Declare private class member variables.
        /////////////////////////////////////////

        BasicCam* m_pDriveCamLeft;
        BasicCam* m_pDriveCamRight;
        BasicCam* m_pGimbalCamLeft;
        BasicCam* m_pGimbalCamRight;
        BasicCam* m_pBackCam;
        BasicCam* m_pAuxCamera1;
        BasicCam* m_pAuxCamera2;
        BasicCam* m_pAuxCamera3;
        BasicCam* m_pAuxCamera4;
        BasicCam* m_pMicroscope;
        RecordingHandler* m_pRecordingHandler;

    public:
        /////////////////////////////////////////
        // Define public enumerators specific to this class.
        /////////////////////////////////////////

        enum class BasicCamName    // Enum for different basic cameras.
        {
            BASICCAM_START,
            eDriveCamLeft,
            eDriveCamRight,
            eGimbalCamLeft,
            eGimbalCamRight,
            eBackCam,
            eAuxCamera1,
            eAuxCamera2,
            eAuxCamera3,
            eAuxCamera4,
            eMicroscope,
            BASICCAM_END
        };

        /////////////////////////////////////////
        // Declare public class methods and variables.
        /////////////////////////////////////////

        CameraHandler();
        ~CameraHandler();
        void StartAllCameras();
        void StartRecording();
        void StopAllCameras();
        void StopRecording();

        /////////////////////////////////////////
        // Accessors.
        /////////////////////////////////////////

        BasicCam* GetBasicCam(BasicCamName eCameraName);
};

#endif    // CAMERA_HANDLER_H
