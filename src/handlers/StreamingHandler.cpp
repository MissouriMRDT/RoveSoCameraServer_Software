/******************************************************************************
 * @brief
 *
 * @file StreamingHandler.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "StreamingHandler.h"
#include "../RoveSoCameraServerLogging.h"

/******************************************************************************
 * @brief Construct a new Streaming Handler:: Streaming Handler object.
 *
 * @param pCamera -
 * @param outputBitRate -
 * @param maxBitRate -
 * @param bufferSize -
 * @param streamWidth -
 * @param streamHeight -
 * @param frameRate -
 * @param port -
 * @param brightness -
 * @param contrast -
 * @param saturation -
 * @param sharpness -
 * @param gamma -
 * @param gain -
 * @param exposure -
 * @param whiteBalance -
 * @param ipAddress -
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
StreamingHandler::StreamingHandler(BasicCam* pCamera,
                                   const std::string& ipAddress,
                                   int port,
                                   int outputBitRate,
                                   int maxBitRate,
                                   int bufferSize,
                                   int streamWidth,
                                   int streamHeight,
                                   int frameRate,
                                   double brightness,
                                   double contrast,
                                   double saturation,
                                   double sharpness,
                                   double gamma,
                                   double gain,
                                   double exposure,
                                   double whiteBalance)
{
    /////////////////////////////////////////
    // Variable Initialization
    /////////////////////////////////////////
    m_pCamera           = pCamera;

    m_nOutputBitRate    = outputBitRate;
    m_nOutputMaxBitRate = maxBitRate;
    m_nBufferSize       = bufferSize;
    m_nStreamWidth      = streamWidth;
    m_nStreamHeight     = streamHeight;
    m_nFrameRate        = frameRate;
    m_nPort             = port;
    m_nPoints           = 0;

    m_dBrightness       = brightness;
    m_dContrast         = contrast;
    m_dSaturation       = saturation;
    m_dSharpness        = sharpness;
    m_dGamma            = gamma;
    m_dGain             = gain;
    m_dExposure         = exposure;
    m_dWhiteBalance     = whiteBalance;

    m_szIPAddress       = ipAddress;
    m_szUDPAddress      = "udp://" + m_szIPAddress + ":" + std::to_string(m_nPort);

    m_pPacket           = av_packet_alloc();

    /////////////////////////////////////////
    // FFmpeg setup
    /////////////////////////////////////////
    avformat_network_init();

    m_pFormatCtx = nullptr;
    avformat_alloc_output_context2(&m_pFormatCtx, nullptr, "mpegts", m_szUDPAddress.c_str());
    if (!m_pFormatCtx)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not allocate output context.");
        return;
    }

    const AVCodec* pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!pCodec)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Codec not found.");
        return;
    }

    m_pStream = avformat_new_stream(m_pFormatCtx, nullptr);
    if (!m_pStream)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not create stream.");
        return;
    }

    m_pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!m_pCodecCtx)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not allocate codec context.");
        return;
    }

    m_pCodecCtx->codec_id     = AV_CODEC_ID_H264;
    m_pCodecCtx->bit_rate     = m_nOutputBitRate;    // Use constant for bitrate
    m_pCodecCtx->width        = m_nStreamWidth;      // Use constant for video width
    m_pCodecCtx->height       = m_nStreamHeight;     // Use constant for video height
    AVRational time_base      = {1, 30};
    m_pCodecCtx->time_base    = time_base;
    m_pCodecCtx->framerate    = {30, 1};
    m_pCodecCtx->gop_size     = 10;
    m_pCodecCtx->max_b_frames = 1;
    m_pCodecCtx->pix_fmt      = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(m_pCodecCtx, pCodec, nullptr) < 0)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not open codec.");
        avcodec_free_context(&m_pCodecCtx);
        return;
    }

    if (avcodec_parameters_from_context(m_pStream->codecpar, m_pCodecCtx) < 0)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not copy codec parameters to stream.");
        return;
    }

    if (avio_open(&m_pFormatCtx->pb, m_szUDPAddress.c_str(), AVIO_FLAG_WRITE) < 0)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not open output URL.");
        return;
    }

    if (avformat_write_header(m_pFormatCtx, nullptr) < 0)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Failed to write header.");
        return;
    }

    m_swsCtx = sws_getContext(m_nStreamWidth,
                              m_nStreamHeight,
                              AV_PIX_FMT_BGR24,
                              m_pCodecCtx->width,
                              m_pCodecCtx->height,
                              m_pCodecCtx->pix_fmt,
                              SWS_BICUBIC,
                              nullptr,
                              nullptr,
                              nullptr);
    if (!m_swsCtx)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not initialize swsContext.");
        return;
    }

    m_pFrameYUV         = av_frame_alloc();
    m_pFrameYUV->format = m_pCodecCtx->pix_fmt;
    m_pFrameYUV->width  = m_pCodecCtx->width;
    m_pFrameYUV->height = m_pCodecCtx->height;
    if (av_image_alloc(m_pFrameYUV->data, m_pFrameYUV->linesize, m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, 32) < 0)
    {
        LOG_CRITICAL(logging::g_qSharedLogger, "Error: Could not allocate picture buffer.");
        return;
    }

    this->SetMainThreadIPSLimit(120);
}

/******************************************************************************
 * @brief
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
void StreamingHandler::ThreadedContinuousCode()
{
    cv::Mat cvNormalFrame1;

    std::future<bool> fuCopyStatus1 = m_pCamera->RequestFrameCopy(cvNormalFrame1);

    if (fuCopyStatus1.get() && !cvNormalFrame1.empty())
    {
        // Apply brightness and contrast adjustment
        cv::Mat adjustedFrame = cvNormalFrame1;
        // cvNormalFrame1.convertTo(adjustedFrame, -1, m_dContrast, m_dBrightness);

        // Check and adjust channels to ensure compatibility with the encoder
        if (adjustedFrame.channels() == 1)
        {
            cv::cvtColor(adjustedFrame, adjustedFrame, cv::COLOR_GRAY2BGR);
        }
        else if (adjustedFrame.channels() == 4)
        {
            cv::cvtColor(adjustedFrame, adjustedFrame, cv::COLOR_BGRA2BGR);
        }

        // Log frame details for debugging
        // LOG_DEBUG(logging::g_qSharedLogger, "Captured frame size: {}x{}, channels: {}", adjustedFrame.cols, adjustedFrame.rows, adjustedFrame.channels());

        // Ensure the frame is resized to the expected dimensions
        if (adjustedFrame.cols != m_nStreamWidth || adjustedFrame.rows != m_nStreamHeight)
        {
            // LOG_WARNING(logging::g_qSharedLogger, "Resizing frame from {}x{} to {}x{}", adjustedFrame.cols, adjustedFrame.rows, m_nStreamWidth, m_nStreamHeight);
            cv::resize(adjustedFrame, adjustedFrame, cv::Size(m_nStreamWidth, m_nStreamHeight));
        }

        // Ensure the frame has 3 channels (BGR)
        if (adjustedFrame.channels() != 3)
        {
            // LOG_WARNING(logging::g_qSharedLogger, "Converting frame to 3-channel BGR format.");
            if (adjustedFrame.channels() == 1)
            {
                cv::cvtColor(adjustedFrame, adjustedFrame, cv::COLOR_GRAY2BGR);
            }
            else if (adjustedFrame.channels() == 4)
            {
                cv::cvtColor(adjustedFrame, adjustedFrame, cv::COLOR_BGRA2BGR);
            }
        }

        uint8_t* inData[1] = {adjustedFrame.data};
        int inLinesize[1]  = {static_cast<int>(adjustedFrame.step)};

        int scaledHeight   = sws_scale(m_swsCtx, inData, inLinesize, 0, m_nStreamHeight, m_pFrameYUV->data, m_pFrameYUV->linesize);
        if (scaledHeight <= 0)
        {
            LOG_ERROR(logging::g_qSharedLogger,
                      "Error: sws_scale failed or returned invalid height. Frame size: {}x{}, input linesize: {}",
                      adjustedFrame.cols,
                      adjustedFrame.rows,
                      inLinesize[0]);
            return;
        }

        m_pFrameYUV->pts = m_nPoints++;

        if (avcodec_send_frame(m_pCodecCtx, m_pFrameYUV) >= 0)
        {
            while (avcodec_receive_packet(m_pCodecCtx, m_pPacket) >= 0)
            {
                m_pPacket->stream_index = m_pStream->index;
                av_interleaved_write_frame(m_pFormatCtx, m_pPacket);
                av_packet_unref(m_pPacket);
            }
        }
    }
}

/******************************************************************************
 * @brief
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
void StreamingHandler::PooledLinearCode() {}

/******************************************************************************
 * @brief Destroy the Streaming Handler:: Streaming Handler object.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-10
 ******************************************************************************/
StreamingHandler::~StreamingHandler()
{
    // Signal and wait for recording thread to stop.
    this->RequestStop();
    this->Join();

    // Write trailer and clean up
    av_write_trailer(m_pFormatCtx);
    av_packet_free(&m_pPacket);
    avcodec_free_context(&m_pCodecCtx);
    av_frame_free(&m_pFrameYUV);
    sws_freeContext(m_swsCtx);
    avformat_free_context(m_pFormatCtx);
}
