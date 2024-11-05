/******************************************************************************
 * @brief Defines functions and objects used project wide.
 *
 * @file RoveSoCameraServerGlobals.h
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#ifndef AUTONOMY_GLOBALS_H
#define AUTONOMY_GLOBALS_H

#include "handlers/CameraHandler.h"

/// \cond
#include <chrono>
#include <ctime>
#include <iostream>

/// \endcond

/******************************************************************************
 * @brief Namespace containing all global types/structs that will be used project
 *      wide and ARE NOT SPECIFIC TO A CERTAIN CLASS.
 *
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
namespace globals
{
    /////////////////////////////////////////
    // Declare namespace external variables and objects.
    /////////////////////////////////////////
    // Camera Handler:
    extern CameraHandler* g_pCameraHandler;    // Global Camera Handler
}    // namespace globals

#endif    // AUTONOMY_GLOBALS_H