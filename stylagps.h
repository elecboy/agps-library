/*******************************************************************************
 (C) Copyright 2009 Styl Solutions Co., Ltd. , All rights reserved *
 *
 This source code and any compilation or derivative thereof is the sole *
 property of Styl Solutions Co., Ltd. and is provided pursuant to a *
 Software License Agreement. This code is the proprietary information *
 of Styl Solutions Co., Ltd and is confidential in nature. Its use and *
 dissemination by any party other than Styl Solutions Co., Ltd is *
 strictly limited by the confidential information provisions of the *
 Agreement referenced above. *
 ******************************************************************************/

#ifndef libstyl_agps_h
#define libstyl_agps_h

#define MAX_PARAM_NODE			10
#define PARAM_LEN				(255 + 1)		// Supported path name + 1 terminator char
#define BUFFER_LEN				( ( (PARAM_LEN) * 2) * MAX_PARAM_NODE )	// each node has 1 value and 1 key
#define URL_LEN					2083
#define JSON_BUFFER				100000
#define DEFAULT_TIME_SEC		10
#define CONFIG_FILE				"/etc/stylagps/stylagps.conf"
#define GOOGLE_GEOLOCATION_URL	"https://www.googleapis.com/geolocation/v1/geolocate?"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _dict_node {
	char key[PARAM_LEN];
	char value[PARAM_LEN];
} node_t;

int StylAgpsGetLocation(double *longitude, double *latitude, double *accuracy);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* libstyl_agps_h */