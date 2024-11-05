/******************************************************************************
 * @brief Implements the CameraHandler class.
 *
 * @file CameraHandler.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "CameraHandler.h"
#include "../RoveSoCameraServerConstants.h"

/******************************************************************************
 * @brief Construct a new Camera Handler Thread:: Camera Handler Thread object.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
CameraHandler::CameraHandler()
{
    // Initialize left drive camera.
    m_pDriveCamLeft = new BasicCam(constants::BASICCAM_DRIVECAMLEFT_INDEX,
                                   constants::BASICCAM_DRIVECAMLEFT_RESOLUTIONX,
                                   constants::BASICCAM_DRIVECAMLEFT_RESOLUTIONY,
                                   constants::BASICCAM_DRIVECAMLEFT_FPS,
                                   constants::BASICCAM_DRIVECAMLEFT_PIXELTYPE,
                                   constants::BASICCAM_DRIVECAMLEFT_HORIZONTAL_FOV,
                                   constants::BASICCAM_DRIVECAMLEFT_VERTICAL_FOV,
                                   constants::BASICCAM_DRIVECAMLEFT_ENABLE_RECORDING,
                                   constants::BASICCAM_DRIVECAMLEFT_FRAME_RETRIEVAL_THREADS);

    // Initialize right drive camera.
    m_pDriveCamRight = new BasicCam(constants::BASICCAM_DRIVECAMRIGHT_INDEX,
                                    constants::BASICCAM_DRIVECAMRIGHT_RESOLUTIONX,
                                    constants::BASICCAM_DRIVECAMRIGHT_RESOLUTIONY,
                                    constants::BASICCAM_DRIVECAMRIGHT_FPS,
                                    constants::BASICCAM_DRIVECAMRIGHT_PIXELTYPE,
                                    constants::BASICCAM_DRIVECAMRIGHT_HORIZONTAL_FOV,
                                    constants::BASICCAM_DRIVECAMRIGHT_VERTICAL_FOV,
                                    constants::BASICCAM_DRIVECAMRIGHT_ENABLE_RECORDING,
                                    constants::BASICCAM_DRIVECAMRIGHT_FRAME_RETRIEVAL_THREADS);

    // Initialize left gimbal camera.
    m_pGimbalCamLeft = new BasicCam(constants::BASICCAM_GIMBALCAMLEFT_INDEX,
                                    constants::BASICCAM_GIMBALCAMLEFT_RESOLUTIONX,
                                    constants::BASICCAM_GIMBALCAMLEFT_RESOLUTIONY,
                                    constants::BASICCAM_GIMBALCAMLEFT_FPS,
                                    constants::BASICCAM_GIMBALCAMLEFT_PIXELTYPE,
                                    constants::BASICCAM_GIMBALCAMLEFT_HORIZONTAL_FOV,
                                    constants::BASICCAM_GIMBALCAMLEFT_VERTICAL_FOV,
                                    constants::BASICCAM_GIMBALCAMLEFT_ENABLE_RECORDING,
                                    constants::BASICCAM_GIMBALCAMLEFT_FRAME_RETRIEVAL_THREADS);

    // Initialize right gimbal camera.
    m_pGimbalCamRight = new BasicCam(constants::BASICCAM_GIMBALCAMRIGHT_INDEX,
                                     constants::BASICCAM_GIMBALCAMRIGHT_RESOLUTIONX,
                                     constants::BASICCAM_GIMBALCAMRIGHT_RESOLUTIONY,
                                     constants::BASICCAM_GIMBALCAMRIGHT_FPS,
                                     constants::BASICCAM_GIMBALCAMRIGHT_PIXELTYPE,
                                     constants::BASICCAM_GIMBALCAMRIGHT_HORIZONTAL_FOV,
                                     constants::BASICCAM_GIMBALCAMRIGHT_VERTICAL_FOV,
                                     constants::BASICCAM_GIMBALCAMRIGHT_ENABLE_RECORDING,
                                     constants::BASICCAM_GIMBALCAMRIGHT_FRAME_RETRIEVAL_THREADS);

    // Initialize back camera.
    m_pBackCam = new BasicCam(constants::BASICCAM_BACKCAM_INDEX,
                              constants::BASICCAM_BACKCAM_RESOLUTIONX,
                              constants::BASICCAM_BACKCAM_RESOLUTIONY,
                              constants::BASICCAM_BACKCAM_FPS,
                              constants::BASICCAM_BACKCAM_PIXELTYPE,
                              constants::BASICCAM_BACKCAM_HORIZONTAL_FOV,
                              constants::BASICCAM_BACKCAM_VERTICAL_FOV,
                              constants::BASICCAM_BACKCAM_ENABLE_RECORDING,
                              constants::BASICCAM_BACKCAM_FRAME_RETRIEVAL_THREADS);

    // Initialize auxiliary camera 1.
    m_pAuxCamera1 = new BasicCam(constants::BASICCAM_AUXCAM1_INDEX,
                                 constants::BASICCAM_AUXCAM1_RESOLUTIONX,
                                 constants::BASICCAM_AUXCAM1_RESOLUTIONY,
                                 constants::BASICCAM_AUXCAM1_FPS,
                                 constants::BASICCAM_AUXCAM1_PIXELTYPE,
                                 constants::BASICCAM_AUXCAM1_HORIZONTAL_FOV,
                                 constants::BASICCAM_AUXCAM1_VERTICAL_FOV,
                                 constants::BASICCAM_AUXCAM1_ENABLE_RECORDING,
                                 constants::BASICCAM_AUXCAM1_FRAME_RETRIEVAL_THREADS);

    // Initialize auxiliary camera 2.
    m_pAuxCamera2 = new BasicCam(constants::BASICCAM_AUXCAM2_INDEX,
                                 constants::BASICCAM_AUXCAM2_RESOLUTIONX,
                                 constants::BASICCAM_AUXCAM2_RESOLUTIONY,
                                 constants::BASICCAM_AUXCAM2_FPS,
                                 constants::BASICCAM_AUXCAM2_PIXELTYPE,
                                 constants::BASICCAM_AUXCAM2_HORIZONTAL_FOV,
                                 constants::BASICCAM_AUXCAM2_VERTICAL_FOV,
                                 constants::BASICCAM_AUXCAM2_ENABLE_RECORDING,
                                 constants::BASICCAM_AUXCAM2_FRAME_RETRIEVAL_THREADS);

    // Initialize auxiliary camera 3.
    m_pAuxCamera3 = new BasicCam(constants::BASICCAM_AUXCAM3_INDEX,
                                 constants::BASICCAM_AUXCAM3_RESOLUTIONX,
                                 constants::BASICCAM_AUXCAM3_RESOLUTIONY,
                                 constants::BASICCAM_AUXCAM3_FPS,
                                 constants::BASICCAM_AUXCAM3_PIXELTYPE,
                                 constants::BASICCAM_AUXCAM3_HORIZONTAL_FOV,
                                 constants::BASICCAM_AUXCAM3_VERTICAL_FOV,
                                 constants::BASICCAM_AUXCAM3_ENABLE_RECORDING,
                                 constants::BASICCAM_AUXCAM3_FRAME_RETRIEVAL_THREADS);

    // Initialize auxiliary camera 4.
    m_pAuxCamera4 = new BasicCam(constants::BASICCAM_AUXCAM4_INDEX,
                                 constants::BASICCAM_AUXCAM4_RESOLUTIONX,
                                 constants::BASICCAM_AUXCAM4_RESOLUTIONY,
                                 constants::BASICCAM_AUXCAM4_FPS,
                                 constants::BASICCAM_AUXCAM4_PIXELTYPE,
                                 constants::BASICCAM_AUXCAM4_HORIZONTAL_FOV,
                                 constants::BASICCAM_AUXCAM4_VERTICAL_FOV,
                                 constants::BASICCAM_AUXCAM4_ENABLE_RECORDING,
                                 constants::BASICCAM_AUXCAM4_FRAME_RETRIEVAL_THREADS);

    // Initialize microscope camera.
    m_pMicroscope = new BasicCam(constants::BASICCAM_MICROSCOPE_INDEX,
                                 constants::BASICCAM_MICROSCOPE_RESOLUTIONX,
                                 constants::BASICCAM_MICROSCOPE_RESOLUTIONY,
                                 constants::BASICCAM_MICROSCOPE_FPS,
                                 constants::BASICCAM_MICROSCOPE_PIXELTYPE,
                                 constants::BASICCAM_MICROSCOPE_HORIZONTAL_FOV,
                                 constants::BASICCAM_MICROSCOPE_VERTICAL_FOV,
                                 constants::BASICCAM_MICROSCOPE_ENABLE_RECORDING,
                                 constants::BASICCAM_MICROSCOPE_FRAME_RETRIEVAL_THREADS);

    // Initialize recording handler for cameras.
    m_pRecordingHandler = new RecordingHandler(RecordingHandler::RecordingMode::eCameraHandler);
}

/******************************************************************************
 * @brief Destroy the Camera Handler Thread:: Camera Handler Thread object.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
CameraHandler::~CameraHandler()
{
    // Signal and wait for cameras to stop.
    this->StopAllCameras();

    // Delete dynamic memory.
    delete m_pDriveCamLeft;
    delete m_pDriveCamRight;
    delete m_pGimbalCamLeft;
    delete m_pGimbalCamRight;
    delete m_pBackCam;
    delete m_pAuxCamera1;
    delete m_pAuxCamera2;
    delete m_pAuxCamera3;
    delete m_pAuxCamera4;
    delete m_pMicroscope;
    delete m_pRecordingHandler;

    // Set dangling pointers to nullptr.
    m_pDriveCamLeft     = nullptr;
    m_pDriveCamRight    = nullptr;
    m_pGimbalCamLeft    = nullptr;
    m_pGimbalCamRight   = nullptr;
    m_pBackCam          = nullptr;
    m_pAuxCamera1       = nullptr;
    m_pAuxCamera2       = nullptr;
    m_pAuxCamera3       = nullptr;
    m_pAuxCamera4       = nullptr;
    m_pMicroscope       = nullptr;
    m_pRecordingHandler = nullptr;
}

/******************************************************************************
 * @brief Signals all cameras to start their threads.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StartAllCameras()
{
    // Start on-rover cams.
    m_pDriveCamLeft->Start();
    m_pDriveCamRight->Start();
    m_pGimbalCamLeft->Start();
    m_pGimbalCamRight->Start();
    m_pBackCam->Start();

    // Start auxiliary system cams.
    m_pAuxCamera1->Start();
    m_pAuxCamera2->Start();
    m_pAuxCamera3->Start();
    m_pAuxCamera4->Start();
    m_pMicroscope->Start();
}

/******************************************************************************
 * @brief Signal the RecordingHandler to start recording video feeds from the CameraHandler.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StartRecording()
{
    // Start recording handler.
    m_pRecordingHandler->Start();
}

/******************************************************************************
 * @brief Signals all cameras to stop their threads.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StopAllCameras()
{
    // Stop recording handler.
    m_pRecordingHandler->RequestStop();
    m_pRecordingHandler->Join();

    // Stop on-rover cams.
    m_pDriveCamLeft->RequestStop();
    m_pDriveCamLeft->Join();
    m_pDriveCamRight->RequestStop();
    m_pDriveCamRight->Join();
    m_pGimbalCamLeft->RequestStop();
    m_pGimbalCamLeft->Join();
    m_pGimbalCamRight->RequestStop();
    m_pGimbalCamRight->Join();
    m_pBackCam->RequestStop();
    m_pBackCam->Join();

    // Stop auxiliary system cams.
    m_pAuxCamera1->RequestStop();
    m_pAuxCamera1->Join();
    m_pAuxCamera2->RequestStop();
    m_pAuxCamera2->Join();
    m_pAuxCamera3->RequestStop();
    m_pAuxCamera3->Join();
    m_pAuxCamera4->RequestStop();
    m_pAuxCamera4->Join();
    m_pMicroscope->RequestStop();
    m_pMicroscope->Join();
}

/******************************************************************************
 * @brief Signal the RecordingHandler to stop recording video feeds from the CameraHandler.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StopRecording()
{
    // Stop recording handler.
    m_pRecordingHandler->RequestStop();
    m_pRecordingHandler->Join();
}

/******************************************************************************
 * @brief Accessor for Basic cameras.
 *
 * @param eCameraName - The name of the camera to retrieve. An enum defined in and specific to this class.
 * @return BasicCam* - A pointer to the basic camera pertaining to the given name.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
BasicCam* CameraHandler::GetBasicCam(BasicCamName eCameraName)
{
    // Determine which camera should be returned.
    switch (eCameraName)
    {
        case BasicCamName::eDriveCamLeft: return m_pDriveCamLeft;        // Return the left drive cam.
        case BasicCamName::eDriveCamRight: return m_pDriveCamRight;      // Return the right drive cam.
        case BasicCamName::eGimbalCamLeft: return m_pGimbalCamLeft;      // Return the left gimbal cam.
        case BasicCamName::eGimbalCamRight: return m_pGimbalCamRight;    // Return the right gimbal cam.
        case BasicCamName::eBackCam: return m_pBackCam;                  // Return the back cam.
        case BasicCamName::eAuxCamera1: return m_pAuxCamera1;            // Return the first auxiliary cam.
        case BasicCamName::eAuxCamera2: return m_pAuxCamera2;            // Return the second auxiliary cam.
        case BasicCamName::eAuxCamera3: return m_pAuxCamera3;            // Return the third auxiliary cam.
        case BasicCamName::eAuxCamera4: return m_pAuxCamera4;            // Return the fourth auxiliary cam.
        case BasicCamName::eMicroscope: return m_pMicroscope;            // Return the microscope cam.
        default: return m_pDriveCamLeft;
    }
}
