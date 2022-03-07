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

	(void)gpsd_source_spec(NULL, &gpsd_source);

	flags = WATCH_ENABLE | WATCH_JSON;

	status = gps_open(gpsd_source.server, gpsd_source.port, &gps_info);

	if (status != 0) {
		printf("No GPSD running or network error:%d,%s\n",errno,gps_errstr(errno));
		exit(EXIT_FAILURE);
	}

	(void)gps_stream(&gps_info, flags, gpsd_source.device);

	/* Wait for data from GPSD for a maximum of 5 microseconds */
	while (gps_waiting(&gps_info, 5000000)) {
		if (-1 == gps_read(&gps_info))
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
			printf("Indoor deployment: %s <%d>\n",status_str[gps_info.status],gps_info.status);

			if (LATLON_SET == (LATLON_SET & gps_info.set))
			{
				if (isfinite(gps_info.fix.latitude) && isfinite(gps_info.fix.longitude))
				{
					/* Display data from the GPS receiver if valid */
					printf("Latitude: %.6f Longitude: %.6f\n",
					gps_info.fix.latitude, gps_info.fix.longitude);
				}
				else
				{
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
					printf("Height: %.6f \n",gps_info.fix.altitude);
				}
				else
				{
					printf("Height: Data not found\n");
				}
			}
			else
			{
				printf("Altitude not set\n");
			}
			if (isfinite(gps_info.dop.hdop))
			{
				printf("Major axis: %.1f\n", gps_info.dop.hdop);
			}
			else
			{
				printf("Major axis : Data not found\n");
			}
			if (isfinite(gps_info.dop.pdop))
			{
				printf("Minor axis: %.1f\n", gps_info.dop.pdop);
			}
			else
			{
				printf("Minor axis: Data not found\n");
			}
			if (isfinite(gps_info.dop.vdop))
			{
				printf("Vertical Uncertainty: %.1f\n", gps_info.dop.vdop);
			}
			else
			{
				printf("vertical Uncertainty: Data not found\n");
			}
			if (isfinite(gps_info.fix.track))
			{
				printf("orientation:%f \n", gps_info.fix.track);
			}
			else
			{
				printf("orientation: Data not found\n");
			}
		}
		else
		{
			printf("No data packets received...\n");
		}
	}
	sleep (3);
	flags = WATCH_DISABLE;
	(void)gps_stream(&gps_info, flags, gpsd_source.device);
	(void)gps_close(&gps_info);
	exit(EXIT_SUCCESS);
}

