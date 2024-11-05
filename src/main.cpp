/******************************************************************************
 * @brief Main program file. Sets up classes and runs main program functions.
 *
 * @file main.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "./RoveSoCameraServerGlobals.h"
#include "./RoveSoCameraServerLogging.h"
#include "./RoveSoCameraServerNetworking.h"
#include <fstream>

// Create a boolean used to handle a SIGINT and exit gracefully.
volatile sig_atomic_t bMainStop = false;

/******************************************************************************
 * @brief Help function given to the C++ csignal standard library to run when
 *      a CONTROL^C is given from the terminal.
 *
 * @param nSignal - Integer representing the interrupt value.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
void SignalHandler(int nSignal)
{
    // Check signal type.
    if (nSignal == SIGINT || nSignal == SIGTERM)
    {
        // Submit logger message.
        LOG_INFO(logging::g_qSharedLogger, "Ctrl+C or SIGTERM received. Cleaning up...");

        // Update stop signal.
        bMainStop = true;
    }
    // The SIGQUIT signal can be sent to the terminal by pressing CNTL+\.
    else if (nSignal == SIGQUIT)
    {
        // Submit logger message.
        LOG_INFO(logging::g_qSharedLogger, "Quit signal key pressed. Cleaning up...");

        // Update stop signal.
        bMainStop = true;
    }
}

/******************************************************************************
 * @brief Autonomy main function.
 *
 * @return int - Exit status number.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
int main()
{
    // Print Software Header
    std::ifstream fHeaderText("../data/ASCII/v25.txt");
    std::string szHeaderText;
    if (fHeaderText)
    {
        std::ostringstream pHeaderText;
        pHeaderText << fHeaderText.rdbuf();
        szHeaderText = pHeaderText.str();
    }

    std::cout << szHeaderText << std::endl;
    std::cout << "Copyright \u00A9 2024 - Mars Rover Design Team\n" << std::endl;

    // Initialize Loggers
    logging::InitializeLoggers(constants::LOGGING_OUTPUT_PATH_ABSOLUTE);

    // Setup signal interrupt handler.
    struct sigaction stSigBreak;
    stSigBreak.sa_handler = SignalHandler;
    stSigBreak.sa_flags   = 0;
    sigemptyset(&stSigBreak.sa_mask);
    sigaction(SIGINT, &stSigBreak, nullptr);
    sigaction(SIGQUIT, &stSigBreak, nullptr);

    /////////////////////////////////////////
    // Setup global objects.
    /////////////////////////////////////////
    // Initialize RoveComm.
    network::g_pRoveCommUDPNode = new rovecomm::RoveCommUDP();
    network::g_pRoveCommTCPNode = new rovecomm::RoveCommTCP();
    // Start RoveComm instances bound on ports.
    network::g_bRoveCommUDPStatus = network::g_pRoveCommUDPNode->InitUDPSocket(manifest::General::ETHERNET_UDP_PORT);
    network::g_bRoveCommTCPStatus = network::g_pRoveCommTCPNode->InitTCPSocket(constants::ROVECOMM_TCP_INTERFACE_IP.c_str(), manifest::General::ETHERNET_TCP_PORT);
    // Check if RoveComm was successfully initialized.
    if (!network::g_bRoveCommUDPStatus || !network::g_bRoveCommTCPStatus)
    {
        // Submit logger message.
        LOG_CRITICAL(logging::g_qSharedLogger,
                     "RoveComm did not initialize properly! UDPNode Status: {}, TCPNode Status: {}",
                     network::g_bRoveCommUDPStatus,
                     network::g_bRoveCommTCPStatus);

        // Since RoveComm is crucial, stop code.
        bMainStop = true;
    }
    else
    {
        // Submit logger message.
        LOG_INFO(logging::g_qSharedLogger, "RoveComm UDP and TCP nodes successfully initialized.");
    }

    // Initialize callbacks.
    network::g_pRoveCommUDPNode->AddUDPCallback<uint8_t>(logging::SetLoggingLevelsCallback, manifest::Autonomy::COMMANDS.find("SETLOGGINGLEVELS")->second.DATA_ID);
    // Initialize handlers.
    globals::g_pCameraHandler = new CameraHandler();

    // Start camera and detection handlers.
    globals::g_pCameraHandler->StartAllCameras();
    // Enable Recording on Handlers.
    globals::g_pCameraHandler->StartRecording();

    /////////////////////////////////////////
    // Declare local variables used in main loop.
    /////////////////////////////////////////
    // Get Camera pointers.
    BasicCam* pDriveCamLeft   = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eDriveCamLeft);
    BasicCam* pDriveCamRight  = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eDriveCamRight);
    BasicCam* pGimbalCamLeft  = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eGimbalCamLeft);
    BasicCam* pGimbalCamRight = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eGimbalCamRight);
    BasicCam* pBackCam        = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eBackCam);
    BasicCam* pAuxCamera1     = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eAuxCamera1);
    BasicCam* pAuxCamera2     = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eAuxCamera2);
    BasicCam* pAuxCamera3     = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eAuxCamera3);
    BasicCam* pAuxCamera4     = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eAuxCamera4);
    BasicCam* pMicroscope     = globals::g_pCameraHandler->GetBasicCam(CameraHandler::BasicCamName::eMicroscope);

    IPS IterPerSecond         = IPS();

    /*
        This while loop is the main periodic loop for the RoveSoCameraServer program.
        Loop until user sends sigkill or sigterm.
    */
    while (!bMainStop)
    {
        // Create a string to append FPS values to.
        std::string szMainInfo = "";
        // Get FPS of all cameras and detectors and construct the info into a string.
        szMainInfo += "\n--------[ Threads FPS ]--------\n";
        szMainInfo += "Main Process FPS: " + std::to_string(IterPerSecond.GetExactIPS()) + "\n";
        szMainInfo += "DriveCamLeft FPS: " + std::to_string(pDriveCamLeft->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "DriveCamRight FPS: " + std::to_string(pDriveCamRight->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "GimbalCamLeft FPS: " + std::to_string(pGimbalCamLeft->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "GimbalCamRight FPS: " + std::to_string(pGimbalCamRight->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "BackCam FPS: " + std::to_string(pBackCam->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "AuxCamera1 FPS: " + std::to_string(pAuxCamera1->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "AuxCamera2 FPS: " + std::to_string(pAuxCamera2->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "AuxCamera3 FPS: " + std::to_string(pAuxCamera3->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "AuxCamera4 FPS: " + std::to_string(pAuxCamera4->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "Microscope FPS: " + std::to_string(pMicroscope->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "\nRoveCommUDP FPS: " + std::to_string(network::g_pRoveCommTCPNode->GetIPS().GetExactIPS()) + "\n";
        szMainInfo += "RoveCommTCP FPS: " + std::to_string(network::g_pRoveCommTCPNode->GetIPS().GetExactIPS()) + "\n";

        // Submit logger message.
        LOG_DEBUG(logging::g_qSharedLogger, "{}", szMainInfo);

        // Update IPS tick.
        IterPerSecond.Tick();

        // No need to loop as fast as possible. Sleep...
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    /////////////////////////////////////////
    // Cleanup.
    /////////////////////////////////////////

    // Stop RoveComm quill logging or quill will segfault if trying to output logs to RoveComm.
    network::g_bRoveCommUDPStatus = false;
    network::g_bRoveCommTCPStatus = false;

    // Stop handlers.
    globals::g_pCameraHandler->StopAllCameras();
    network::g_pRoveCommUDPNode->CloseUDPSocket();
    network::g_pRoveCommTCPNode->CloseTCPSocket();

    // Delete dynamically allocated objects.
    delete globals::g_pCameraHandler;
    delete network::g_pRoveCommUDPNode;
    delete network::g_pRoveCommTCPNode;

    // Set dangling pointers to null.
    globals::g_pCameraHandler   = nullptr;
    network::g_pRoveCommUDPNode = nullptr;
    network::g_pRoveCommTCPNode = nullptr;

    // Submit logger message that program is done cleaning up and is now exiting.
    LOG_INFO(logging::g_qSharedLogger, "Clean up finished. Exiting...");

    // Successful exit.
    return 0;
}
