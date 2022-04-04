/*
 *Copyright (c) 2022, Qualcomm Innovation Center, Inc. All rights reserved.
 *
 *Permission to use, copy, modify, and/or distribute this software for any
 *purpose with or without fee is hereby granted, provided that the above
 *copyright notice and this permission notice appear in all copies.
 *
 *THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE
 */

#include <gps.h>
#include <gpsdclient.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define MODE_STRING_COUNT 4
#define STATUS_STRING_COUNT 3

static char *status_str[STATUS_STRING_COUNT] =
{
	"status_no_fix",
	"status_fix",
	"status_dgps_fix"
};

int main(void)
{
	struct gps_data_t gps_info;
	struct fixsource_t gpsd_source;
	int status,flags;
	bool latlon_set = false, alti_set = false, hdop_set = false, pdop_set = false, vdop_set = false, orientation_set = false, is_data_valid = false;
	(void)gpsd_source_spec(NULL, &gpsd_source);

	flags = WATCH_ENABLE | WATCH_JSON;

	status = gps_open(gpsd_source.server, gpsd_source.port, &gps_info);

	if (status != 0) {
		printf("No GPSD running or network error:%d,%s\n",errno,gps_errstr(errno));
		exit(EXIT_FAILURE);
	}

	(void)gps_stream(&gps_info, flags, gpsd_source.device);
	//printf("\nWaiting for GPS data!!\n");
	/* Wait for data from GPSD for a maximum of 10 seconds */
	while ((gps_waiting(&gps_info, 10000000)) && (is_data_valid == false)) {
		if (-1 == gps_read(&gps_info, NULL, 0))
		{
			printf("Read failure!\n");
			exit(EXIT_FAILURE);
		}
		if (PACKET_SET == (PACKET_SET & gps_info.set))
		{
			if (MODE_SET != (MODE_SET & gps_info.set)) {
				continue;
			}
		/* Checking if the mode is within the range */
			if (gps_info.fix.mode < 0 ||
			 gps_info.fix.mode >= MODE_STRING_COUNT)
			{
				gps_info.fix.mode = 0;
			}
			printf("\nIndoor deployment: %s <%d>\n",status_str[gps_info.fix.status],gps_info.fix.status);

			if (LATLON_SET == (LATLON_SET & gps_info.set))
			{
				if (isfinite(gps_info.fix.latitude) && isfinite(gps_info.fix.longitude))
				{
					latlon_set = true;
					/* Display data from the GPS receiver if valid */
					printf("Latitude: %.6f Longitude: %.6f\n",
					gps_info.fix.latitude, gps_info.fix.longitude);
				}
				else
				{
					latlon_set = false;
					printf("Latitude and Longitude: Data not found\n");
				}
			}
			else
			{
				printf("LatLon not set!\n");
			}
			if (ALTITUDE_SET == (ALTITUDE_SET & gps_info.set))
			{
				if (isfinite(gps_info.fix.altitude))
				{
					alti_set = true;
					printf("Height: %.6f \n",gps_info.fix.altMSL);
				}
				else
				{
					alti_set = false;
					printf("Height: Data not found\n");
				}
			}
			else
			{
				printf("Altitude not set\n");
			}
			if (isfinite(gps_info.dop.hdop))
			{
				hdop_set = true;
				printf("Major axis: %.1f\n", gps_info.dop.hdop);
			}
			else
			{
				hdop_set = false;
				printf("Major axis : Data not found\n");
			}
			if (isfinite(gps_info.dop.pdop))
			{
				pdop_set = true;
				printf("Minor axis: %.1f\n", gps_info.dop.pdop);
			}
			else
			{
				pdop_set = false;
				printf("Minor axis: Data not found\n");
			}
			if (isfinite(gps_info.dop.vdop))
			{
				vdop_set = true;
				printf("Vertical Uncertainty: %.1f\n", gps_info.dop.vdop);
			}
			else
			{
				vdop_set = false;
				printf("vertical Uncertainty: Data not found\n");
			}
			if (isfinite(gps_info.fix.track))
			{
				orientation_set = true;
				printf("orientation:%f \n", gps_info.fix.track);
			}
			else
			{
				orientation_set = false;
				printf("orientation: Data not found\n");
			}
			if ((latlon_set == true) && (alti_set == true) && (hdop_set == true) && (pdop_set == true) && (vdop_set == true) && (orientation_set == true))
			{
				is_data_valid = true;
			}
		}
		else
		{
			printf("No data packets received...\n");
		}
	}
	sleep(1);
	flags = WATCH_DISABLE;
	(void)gps_stream(&gps_info, flags, gpsd_source.device);
	(void)gps_close(&gps_info);
	if (is_data_valid == true)
	{
		printf("GPS Data fields are set...Exiting!!\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("GPS Wait timed out..Retrying!!\n");
		exit(EXIT_FAILURE);
	}
}

