/******************************************************************************
 * @brief The FFmpegUDPCameraStreamer class is responsible for streaming camera
 *        feeds to a specified IP address and port using the FFmpeg library.
 *
 * @file FFmpegUDPCameraStreamer.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef FFMPEG_UDPCAMERA_STREAMER_H
#define FFMPEG_UDPCAMERA_STREAMER_H

#include "../cameras/BasicCam.h"

/// \cond
#include <opencv2/opencv.hpp>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

/// \endcond

/******************************************************************************
 * @brief The FFmpegUDPCameraStreamer class is responsible for streaming camera
 *        feeds to a specified IP address and port using the FFmpeg library.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
class FFmpegUDPCameraStreamer : public AutonomyThread<void>
{
    private:
        int m_nOutputBitRate;
        int m_nOutputMaxBitRate;
        int m_nBufferSize;
        int m_nStreamWidth;
        int m_nStreamHeight;
        int m_nFrameRate;
        int m_nPort;
        int64_t m_nPoints;
        double m_dBrightness;
        double m_dContrast;
        double m_dSaturation;
        double m_dSharpness;
        double m_dGamma;
        double m_dGain;
        double m_dExposure;
        double m_dWhiteBalance;
        std::string m_szIPAddress;
        std::string m_szUDPAddress;
        BasicCam* m_pCamera;
        AVPacket* m_pPacket;
        SwsContext* m_swsCtx;
        AVFrame* m_pFrameYUV;
        AVStream* m_pStream;
        AVCodecContext* m_pCodecCtx;
        AVFormatContext* m_pFormatCtx;

        void ThreadedContinuousCode() override;

        void PooledLinearCode() override;

    public:
        FFmpegUDPCameraStreamer(BasicCam* pCamera,
                                const std::string& ipAddress = "127.0.0.1",
                                int port                     = 1234,
                                int outputBitRate            = 512000,
                                int maxBitRate               = 524000,
                                int bufferSize               = 524000,
                                int streamWidth              = 480,
                                int streamHeight             = 320,
                                int frameRate                = 30,
                                double brightness            = 0.0,
                                double contrast              = 0.0,
                                double saturation            = 0.0,
                                double sharpness             = 0.0,
                                double gamma                 = 0.0,
                                double gain                  = 0.0,
                                double exposure              = 0.0,
                                double whiteBalance          = 0.0);

        ~FFmpegUDPCameraStreamer();
};

#endif    // FFMPEG_UDPCAMERA_STREAMER_H
