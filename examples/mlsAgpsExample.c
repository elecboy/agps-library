/*******************************************************************************
 *  (C) Copyright 2009 STYL Solutions Co., Ltd. , All rights reserved          *
 *                                                                             *
 *  This source code and any compilation or derivative thereof is the sole     *
 *  property of STYL Solutions Co., Ltd. and is provided pursuant to a         *
 *  Software License Agreement.  This code is the proprietary information      *
 *  of STYL Solutions Co., Ltd and is confidential in nature.  Its use and     *
 *  dissemination by any party other than STYL Solutions Co., Ltd is           *
 *  strictly limited by the confidential information provisions of the         *
 *  Agreement referenced above.                                                *
 ******************************************************************************/
/**
 * @file    mlsAgpsExample.c
 * @brief   C code - Implement example application for A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib-object.h>
#include <unistd.h>
#include <signal.h>

#include <mlsAgps.h>
#include "mlsAgpsExample_Common.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
#define TIME_SLEEP 3

/********** Local (static) variable definition ********************************/
static gint LOOP_COUNT = 10000;
static gint run = 1;

/********** Local (static) function declaration section ***********************/
static void HandleSignal(gint sig);

/********** Local function definition section *********************************/
static void HandleSignal(gint sig)
{
    if (sig == SIGINT)
    {
        STYL_INFO_1("\nStop stylagps_demo. Thank you for using STYL demos!\n");
        run = 0;
    }
}

/********** Global function definition section ********************************/
gint main(int argc, const char * argv[])
{
    gdouble longitude = 0;
    gdouble latitude = 0;
    gdouble accuracy = 0;
    gint ret = EXIT_FAILURE;

    signal(SIGINT, HandleSignal);

    GObject * nm_client = mlsAgps_Init();

    STYL_SHOW("** Version: %s **", mlsAgps_GetVersion());

    g_return_val_if_fail(nm_client, EXIT_FAILURE);

    while(LOOP_COUNT)
    {
        if(run==0)
            break;

        STYL_SHOW_1("Running [#%d]...", LOOP_COUNT);

        ret = mlsAgps_GetLocation(nm_client, &latitude, &longitude, &accuracy);

        if (EXIT_SUCCESS == ret)
        {
            STYL_SHOW_2(" => AGPS location: \n        Latitude: %.8f Longitude: %.8f Accuracy: %.8f \t",
                                latitude, longitude, accuracy);
        }
        else
        {
            STYL_ERROR("Cannot query locaion. Retry with debug option to get more information.");
        }
        sleep(TIME_SLEEP);
        LOOP_COUNT--;
    }

    mlsAgps_Finalize(nm_client);

    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
/*@}*/
