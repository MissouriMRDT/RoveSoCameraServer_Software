/******************************************************************************
 * @brief The constants header for Autonomy Software
 *
 * @file RoveSoCameraServerConstants.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef ROVESOCAMERASERVERCONSTANTS_H
#define ROVESOCAMERASERVERCONSTANTS_H

#include "./interfaces/Camera.hpp"

/// \cond
#include <opencv2/opencv.hpp>
#include <quill/core/LogLevel.h>

/// \endcond

/******************************************************************************
 * @brief Namespace containing all constants for RoveSoCamera Server software.
 *        Including RoveSoCameraServerGlobals.h will also include this namespace.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
namespace constants
{
    ///////////////////////////////////////////////////////////////////////////
    //// General Constants.
    ///////////////////////////////////////////////////////////////////////////

    // Logging constants.
    const std::string LOGGING_OUTPUT_PATH_ABSOLUTE = "../logs/";                  // The absolute to write output logging and video files to.
    const quill::LogLevel CONSOLE_MIN_LEVEL        = quill::LogLevel::TraceL3;    // The minimum logging level that is allowed to send to the console log stream.
    const quill::LogLevel FILE_MIN_LEVEL           = quill::LogLevel::TraceL3;    // The minimum logging level that is allowed to send to the file log streams.
    const quill::LogLevel ROVECOMM_MIN_LEVEL       = quill::LogLevel::Info;       // The minimum logging level that is allowed to send to the RoveComm log stream.
    const quill::LogLevel CONSOLE_DEFAULT_LEVEL    = quill::LogLevel::TraceL3;    // The default logging level for console stream.
    const quill::LogLevel FILE_DEFAULT_LEVEL       = quill::LogLevel::TraceL3;    // The default logging level for file streams.
    const quill::LogLevel ROVECOMM_DEFAULT_LEVEL   = quill::LogLevel::Info;       // The default logging level for RoveComm stream.

    // Logging color constants.
    const std::string szTraceL3Color   = "\033[30m";           // Standard Grey
    const std::string szTraceL2Color   = "\033[30m";           // Standard Grey
    const std::string szTraceL1Color   = "\033[30m";           // Standard Grey
    const std::string szDebugColor     = "\033[36m";           // Standard Cyan
    const std::string szInfoColor      = "\033[32m";           // Standard Green
    const std::string szNoticeColor    = "\033[97m\033[1m";    // Bright Bold White
    const std::string szWarningColor   = "\033[93m\033[1m";    // Bright Bold Yellow
    const std::string szErrorColor     = "\033[91m\033[1m";    // Bright Bold Red
    const std::string szCriticalColor  = "\033[95m\033[1m";    // Bright Bold Magenta
    const std::string szBacktraceColor = "\033[30m";           // Standard Grey

    // RoveComm constants.
    const int ROVECOMM_OUTGOING_UDP_PORT        = 11000;    // The UDP socket port to use for the main UDP RoveComm instance.
    const int ROVECOMM_OUTGOING_TCP_PORT        = 12000;    // The UDP socket port to use for the main UDP RoveComm instance.
    const std::string ROVECOMM_TCP_INTERFACE_IP = "";       // The IP address to bind the socket to. If set to "", the socket will be bound to all available interfaces.
    ///////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////.;'//////////////////
    //// Recording Handler Adjustments.
    ///////////////////////////////////////////////////////////////////////////

    // Recording adjustments.
    const int RECORDER_FPS = 15;    // The FPS all recordings should run at.
    // Camera recording toggles.
    const bool BASICCAM_DRIVECAMLEFT_ENABLE_RECORDING   = true;    // Whether or not to record the left drive camera.
    const bool BASICCAM_DRIVECAMRIGHT_ENABLE_RECORDING  = true;    // Whether or not to record the right drive camera.
    const bool BASICCAM_GIMBALCAMLEFT_ENABLE_RECORDING  = true;    // Whether or not to record the left gimbal camera.
    const bool BASICCAM_GIMBALCAMRIGHT_ENABLE_RECORDING = true;    // Whether or not to record the right gimbal camera.
    const bool BASICCAM_BACKCAM_ENABLE_RECORDING        = true;    // Whether or not to record the back camera.
    const bool BASICCAM_AUXCAM1_ENABLE_RECORDING        = true;    // Whether or not to record the first auxiliary camera.
    const bool BASICCAM_AUXCAM2_ENABLE_RECORDING        = true;    // Whether or not to record the second auxiliary camera.
    const bool BASICCAM_AUXCAM3_ENABLE_RECORDING        = true;    // Whether or not to record the third auxiliary camera.
    const bool BASICCAM_AUXCAM4_ENABLE_RECORDING        = true;    // Whether or not to record the fourth auxiliary camera.
    const bool BASICCAM_MICROSCOPE_ENABLE_RECORDING     = true;    // Whether or not to record the microscope camera.
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //// Camera Constants.
    ///////////////////////////////////////////////////////////////////////////

    // BasicCam Basic Config.
    const cv::InterpolationFlags BASICCAM_RESIZE_INTERPOLATION_METHOD = cv::InterpolationFlags::INTER_LINEAR;    // The algorithm used to fill in pixels when resizing.
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //// Camera Handler Adjustments.
    ///////////////////////////////////////////////////////////////////////////

    // Drive Left Camera.
    const int BASICCAM_DRIVECAMLEFT_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_DRIVECAMLEFT_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_DRIVECAMLEFT_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_DRIVECAMLEFT_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_DRIVECAMLEFT_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_DRIVECAMLEFT_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_DRIVECAMLEFT_INDEX                   = 0;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_DRIVECAMLEFT_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Drive Right Camera.
    const int BASICCAM_DRIVECAMRIGHT_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_DRIVECAMRIGHT_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_DRIVECAMRIGHT_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_DRIVECAMRIGHT_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_DRIVECAMRIGHT_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_DRIVECAMRIGHT_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_DRIVECAMRIGHT_INDEX                   = 1;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_DRIVECAMRIGHT_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Gimbal Left Camera.
    const int BASICCAM_GIMBALCAMLEFT_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_GIMBALCAMLEFT_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_GIMBALCAMLEFT_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_GIMBALCAMLEFT_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_GIMBALCAMLEFT_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_GIMBALCAMLEFT_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_GIMBALCAMLEFT_INDEX                   = 2;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_GIMBALCAMLEFT_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Gimbal Right Camera.
    const int BASICCAM_GIMBALCAMRIGHT_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_GIMBALCAMRIGHT_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_GIMBALCAMRIGHT_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_GIMBALCAMRIGHT_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_GIMBALCAMRIGHT_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_GIMBALCAMRIGHT_FRAME_RETRIEVAL_THREADS = 5;    // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_GIMBALCAMRIGHT_INDEX                   = 3;    // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_GIMBALCAMRIGHT_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Back Camera.
    const int BASICCAM_BACKCAM_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_BACKCAM_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_BACKCAM_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_BACKCAM_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_BACKCAM_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_BACKCAM_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_BACKCAM_INDEX                   = 4;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_BACKCAM_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Aux Camera 1.
    const int BASICCAM_AUXCAM1_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM1_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM1_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_AUXCAM1_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM1_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM1_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_AUXCAM1_INDEX                   = 5;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_AUXCAM1_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Aux Camera 2.
    const int BASICCAM_AUXCAM2_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM2_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM2_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_AUXCAM2_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM2_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM2_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_AUXCAM2_INDEX                   = 6;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_AUXCAM2_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Aux Camera 3.
    const int BASICCAM_AUXCAM3_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM3_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM3_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_AUXCAM3_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM3_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM3_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_AUXCAM3_INDEX                   = 7;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_AUXCAM3_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Aux Camera 4.
    const int BASICCAM_AUXCAM4_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM4_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_AUXCAM4_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_AUXCAM4_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM4_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_AUXCAM4_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_AUXCAM4_INDEX                   = 8;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_AUXCAM4_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.

    // Microscope Camera.
    const int BASICCAM_MICROSCOPE_RESOLUTIONX             = 1280;    // The horizontal pixel resolution to resize the basiccam images to.
    const int BASICCAM_MICROSCOPE_RESOLUTIONY             = 720;     // The vertical pixel resolution to resize the basiccam images to.
    const int BASICCAM_MICROSCOPE_FPS                     = 30;      // The FPS to use for the basiccam.
    const int BASICCAM_MICROSCOPE_HORIZONTAL_FOV          = 110;     // The horizontal FOV of the camera. Useful for future calculations.
    const int BASICCAM_MICROSCOPE_VERTICAL_FOV            = 70;      // The vertical FOV of the camera. Useful for future calculations.
    const int BASICCAM_MICROSCOPE_FRAME_RETRIEVAL_THREADS = 5;       // The number of threads allocated to the threadpool for performing frame copies to other threads.
    const int BASICCAM_MICROSCOPE_INDEX                   = 9;       // The /dev/video index of the camera.
    const PIXEL_FORMATS BASICCAM_MICROSCOPE_PIXELTYPE     = PIXEL_FORMATS::eBGR;    // The pixel layout of the camera.
    ///////////////////////////////////////////////////////////////////////////

}    // namespace constants

#endif    // ROVESOCAMERASERVERCONSTANTS_H
