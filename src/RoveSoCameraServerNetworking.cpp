/******************************************************************************
 * @brief Defines functions and objects used for Autonomy Networking
 *
 * @file RoveSoCameraServerNetworking.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "RoveSoCameraServerNetworking.h"

/******************************************************************************
 * @brief Namespace containing all networking types/structs that will be used
 *        project wide.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
namespace network
{
    // RoveComm Instances:
    rovecomm::RoveCommUDP* g_pRoveCommUDPNode;
    rovecomm::RoveCommTCP* g_pRoveCommTCPNode;

    // RoveComm Status:
    bool g_bRoveCommUDPStatus = false;
    bool g_bRoveCommTCPStatus = false;
}    // namespace network