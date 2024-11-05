/******************************************************************************
 * @brief Defines functions and objects used for Autonomy Networking
 *
 * @file RoveSoCameraServerNetworking.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

/// \cond
#include <RoveComm/RoveComm.h>
#include <chrono>
#include <ctime>
#include <iostream>

/// \endcond

#ifndef ROVESOCAMERASERVER_NETWORKING_H
#define ROVESOCAMERASERVER_NETWORKING_H

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
    extern rovecomm::RoveCommUDP* g_pRoveCommUDPNode;    // Global RoveComm UDP Instance.
    extern rovecomm::RoveCommTCP* g_pRoveCommTCPNode;    // Global RoveComm TCP Instance.

    // RoveComm Status:
    extern bool g_bRoveCommUDPStatus;
    extern bool g_bRoveCommTCPStatus;
}    // namespace network

#endif    // ROVESOCAMERASERVER_NETWORKING_H