/******************************************************************************
 * @brief Sets up functions and classes used project wide.
 *
 * @file RoveSoCameraServerGlobals.cpp
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 *
 * @copyright Copyright Mars Rover Design Team 2024 - All Rights Reserved
 ******************************************************************************/

#include "RoveSoCameraServerGlobals.h"

/******************************************************************************
 * @brief Namespace containing all global types/structs that will be used project
 *      wide and ARE NOT SPECIFIC TO A CERTAIN CLASS.
 *
 * @author Eli Byrd (edbgkk@mst.edu)
 * @date 2024-11-04
 ******************************************************************************/
namespace globals
{
    /////////////////////////////////////////
    // Forward declarations for namespace variables and objects.
    /////////////////////////////////////////

    // Camera Handler:
    CameraHandler* g_pCameraHandler;
}    // namespace globals
