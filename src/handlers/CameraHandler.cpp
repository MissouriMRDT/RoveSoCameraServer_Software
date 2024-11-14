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

    // Initialize streaming handlers for cameras.
    m_pDriveCamLeftStream   = new FFmpegUDPCameraStreamer(m_pDriveCamLeft, "239.0.0.1", 50000);
    m_pDriveCamRightStream  = new FFmpegUDPCameraStreamer(m_pDriveCamRight, "239.0.0.2", 50000);
    m_pGimbalCamLeftStream  = new FFmpegUDPCameraStreamer(m_pGimbalCamLeft, "239.0.0.3", 50000);
    m_pGimbalCamRightStream = new FFmpegUDPCameraStreamer(m_pGimbalCamRight, "239.0.0.4", 50000);
    m_pBackCamStream        = new FFmpegUDPCameraStreamer(m_pBackCam, "239.0.0.5", 50000);
    m_pAuxCamera1Stream     = new FFmpegUDPCameraStreamer(m_pAuxCamera1, "239.0.0.6", 50000);
    m_pAuxCamera2Stream     = new FFmpegUDPCameraStreamer(m_pAuxCamera2, "239.0.0.7", 50000);
    m_pAuxCamera3Stream     = new FFmpegUDPCameraStreamer(m_pAuxCamera3, "239.0.0.8", 50000);
    m_pAuxCamera4Stream     = new FFmpegUDPCameraStreamer(m_pAuxCamera4, "239.0.0.9", 50000);
    m_pMicroscopeStream     = new FFmpegUDPCameraStreamer(m_pMicroscope, "239.0.0.10", 50000);
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

    // Delete streams dynamic memory.
    delete m_pDriveCamLeftStream;
    delete m_pDriveCamRightStream;
    delete m_pGimbalCamLeftStream;
    delete m_pGimbalCamRightStream;
    delete m_pBackCamStream;
    delete m_pAuxCamera1Stream;
    delete m_pAuxCamera2Stream;
    delete m_pAuxCamera3Stream;
    delete m_pAuxCamera4Stream;
    delete m_pMicroscopeStream;

    // Delete recording handler dynamic memory.
    delete m_pRecordingHandler;

    // Delete cameras dynamic memory.
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

    // Set streams dangling pointers to nullptr.
    m_pDriveCamLeftStream   = nullptr;
    m_pDriveCamRightStream  = nullptr;
    m_pGimbalCamLeftStream  = nullptr;
    m_pGimbalCamRightStream = nullptr;
    m_pBackCamStream        = nullptr;
    m_pAuxCamera1Stream     = nullptr;
    m_pAuxCamera2Stream     = nullptr;
    m_pAuxCamera3Stream     = nullptr;
    m_pAuxCamera4Stream     = nullptr;
    m_pMicroscopeStream     = nullptr;

    // Set recording handler dangling pointer to nullptr.
    m_pRecordingHandler = nullptr;

    // Set cameras dangling pointers to nullptr.
    m_pDriveCamLeft   = nullptr;
    m_pDriveCamRight  = nullptr;
    m_pGimbalCamLeft  = nullptr;
    m_pGimbalCamRight = nullptr;
    m_pBackCam        = nullptr;
    m_pAuxCamera1     = nullptr;
    m_pAuxCamera2     = nullptr;
    m_pAuxCamera3     = nullptr;
    m_pAuxCamera4     = nullptr;
    m_pMicroscope     = nullptr;
}

void CameraHandler::StartCameras(bool bDriveCamLeft,
                                 bool bDriveCamRight,
                                 bool bGimbalCamLeft,
                                 bool bGimbalCamRight,
                                 bool bBackCam,
                                 bool bAuxCamera1,
                                 bool bAuxCamera2,
                                 bool bAuxCamera3,
                                 bool bAuxCamera4,
                                 bool bMicroscope)
{
    if (bDriveCamLeft)
    {
        m_pDriveCamLeft->Start();
    }
    if (bDriveCamRight)
    {
        m_pDriveCamRight->Start();
    }
    if (bGimbalCamLeft)
    {
        m_pGimbalCamLeft->Start();
    }
    if (bGimbalCamRight)
    {
        m_pGimbalCamRight->Start();
    }
    if (bBackCam)
    {
        m_pBackCam->Start();
    }
    if (bAuxCamera1)
    {
        m_pAuxCamera1->Start();
    }
    if (bAuxCamera2)
    {
        m_pAuxCamera2->Start();
    }
    if (bAuxCamera3)
    {
        m_pAuxCamera3->Start();
    }
    if (bAuxCamera4)
    {
        m_pAuxCamera4->Start();
    }
    if (bMicroscope)
    {
        m_pMicroscope->Start();
    }
}

/******************************************************************************
 * @brief Signals all cameras to start their threads.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StartAllCameras()
{
    StartCameras();
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
 * @brief Signal the StreamingHandler to start streaming video feeds from the CameraHandler.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
void CameraHandler::StartStreaming(bool bDriveCamLeft,
                                   bool bDriveCamRight,
                                   bool bGimbalCamLeft,
                                   bool bGimbalCamRight,
                                   bool bBackCam,
                                   bool bAuxCamera1,
                                   bool bAuxCamera2,
                                   bool bAuxCamera3,
                                   bool bAuxCamera4,
                                   bool bMicroscope)
{
    // Start streaming handlers.
    if (bDriveCamLeft)
    {
        m_pDriveCamLeftStream->Start();
    }
    if (bDriveCamRight)
    {
        m_pDriveCamRightStream->Start();
    }
    if (bGimbalCamLeft)
    {
        m_pGimbalCamLeftStream->Start();
    }
    if (bGimbalCamRight)
    {
        m_pGimbalCamRightStream->Start();
    }
    if (bBackCam)
    {
        m_pBackCamStream->Start();
    }
    if (bAuxCamera1)
    {
        m_pAuxCamera1Stream->Start();
    }
    if (bAuxCamera2)
    {
        m_pAuxCamera2Stream->Start();
    }
    if (bAuxCamera3)
    {
        m_pAuxCamera3Stream->Start();
    }
    if (bAuxCamera4)
    {
        m_pAuxCamera4Stream->Start();
    }
    if (bMicroscope)
    {
        m_pMicroscopeStream->Start();
    }
}

void CameraHandler::StopCameras(bool bDriveCamLeft,
                                bool bDriveCamRight,
                                bool bGimbalCamLeft,
                                bool bGimbalCamRight,
                                bool bBackCam,
                                bool bAuxCamera1,
                                bool bAuxCamera2,
                                bool bAuxCamera3,
                                bool bAuxCamera4,
                                bool bMicroscope)
{
    if (bDriveCamLeft)
    {
        m_pDriveCamLeft->RequestStop();
        m_pDriveCamLeft->Join();
    }
    if (bDriveCamRight)
    {
        m_pDriveCamRight->RequestStop();
        m_pDriveCamRight->Join();
    }
    if (bGimbalCamLeft)
    {
        m_pGimbalCamLeft->RequestStop();
        m_pGimbalCamLeft->Join();
    }
    if (bGimbalCamRight)
    {
        m_pGimbalCamRight->RequestStop();
        m_pGimbalCamRight->Join();
    }
    if (bBackCam)
    {
        m_pBackCam->RequestStop();
        m_pBackCam->Join();
    }
    if (bAuxCamera1)
    {
        m_pAuxCamera1->RequestStop();
        m_pAuxCamera1->Join();
    }
    if (bAuxCamera2)
    {
        m_pAuxCamera2->RequestStop();
        m_pAuxCamera2->Join();
    }
    if (bAuxCamera3)
    {
        m_pAuxCamera3->RequestStop();
        m_pAuxCamera3->Join();
    }
    if (bAuxCamera4)
    {
        m_pAuxCamera4->RequestStop();
        m_pAuxCamera4->Join();
    }
    if (bMicroscope)
    {
        m_pMicroscope->RequestStop();
        m_pMicroscope->Join();
    }
}

/******************************************************************************
 * @brief Signals all cameras to stop their threads.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void CameraHandler::StopAllCameras()
{
    // Stop streaming handlers.
    StopStreaming();

    // Stop recording handler.
    StopRecording();

    // Stop cameras.
    StopCameras();
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

void CameraHandler::StopStreaming(bool bDriveCamLeft,
                                  bool bDriveCamRight,
                                  bool bGimbalCamLeft,
                                  bool bGimbalCamRight,
                                  bool bBackCam,
                                  bool bAuxCamera1,
                                  bool bAuxCamera2,
                                  bool bAuxCamera3,
                                  bool bAuxCamera4,
                                  bool bMicroscope)
{
    // Stop streaming handlers.
    if (bDriveCamLeft)
    {
        m_pDriveCamLeftStream->RequestStop();
        m_pDriveCamLeftStream->Join();
    }
    if (bDriveCamRight)
    {
        m_pDriveCamRightStream->RequestStop();
        m_pDriveCamRightStream->Join();
    }
    if (bGimbalCamLeft)
    {
        m_pGimbalCamLeftStream->RequestStop();
        m_pGimbalCamLeftStream->Join();
    }
    if (bGimbalCamRight)
    {
        m_pGimbalCamRightStream->RequestStop();
        m_pGimbalCamRightStream->Join();
    }
    if (bBackCam)
    {
        m_pBackCamStream->RequestStop();
        m_pBackCamStream->Join();
    }
    if (bAuxCamera1)
    {
        m_pAuxCamera1Stream->RequestStop();
        m_pAuxCamera1Stream->Join();
    }
    if (bAuxCamera2)
    {
        m_pAuxCamera2Stream->RequestStop();
        m_pAuxCamera2Stream->Join();
    }
    if (bAuxCamera3)
    {
        m_pAuxCamera3Stream->RequestStop();
        m_pAuxCamera3Stream->Join();
    }
    if (bAuxCamera4)
    {
        m_pAuxCamera4Stream->RequestStop();
        m_pAuxCamera4Stream->Join();
    }
    if (bMicroscope)
    {
        m_pMicroscopeStream->RequestStop();
        m_pMicroscopeStream->Join();
    }
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

FFmpegUDPCameraStreamer* CameraHandler::GetFFmpegUDPCameraStreamer(BasicCamName eCameraName)
{
    // Determine which streaming handler should be returned.
    switch (eCameraName)
    {
        case BasicCamName::eDriveCamLeft: return m_pDriveCamLeftStream;        // Return the left drive cam stream.
        case BasicCamName::eDriveCamRight: return m_pDriveCamRightStream;      // Return the right drive cam stream.
        case BasicCamName::eGimbalCamLeft: return m_pGimbalCamLeftStream;      // Return the left gimbal cam stream.
        case BasicCamName::eGimbalCamRight: return m_pGimbalCamRightStream;    // Return the right gimbal cam stream.
        case BasicCamName::eBackCam: return m_pBackCamStream;                  // Return the back cam stream.
        case BasicCamName::eAuxCamera1: return m_pAuxCamera1Stream;            // Return the first auxiliary cam stream.
        case BasicCamName::eAuxCamera2: return m_pAuxCamera2Stream;            // Return the second auxiliary cam stream.
        case BasicCamName::eAuxCamera3: return m_pAuxCamera3Stream;            // Return the third auxiliary cam stream.
        case BasicCamName::eAuxCamera4: return m_pAuxCamera4Stream;            // Return the fourth auxiliary cam stream.
        case BasicCamName::eMicroscope: return m_pMicroscopeStream;            // Return the microscope cam stream.
        default: return m_pDriveCamLeftStream;
    }
}
