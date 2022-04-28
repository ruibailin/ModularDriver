
/*---------------------------
 * lane.c
 *  Created on: May 1, 2019
 *      Author: Steve Rui
 *---------------------------
 *
 *
 *
 *
 *
 *---------------------------
 */

#include "01import.h"
/**************************************************/
#include "reg.h"
/**************************************************/
static struct reg_value isl79987_default[]={
{0xFF,0x00},{0x03,0x00},{0x0D,0xC9},{0x0E,0xC9},
            {0x10,0x01},{0x11,0x03},{0x12,0x00},{0x13,0x00},{0x14,0x00},
{0xFF,0x05},{0x00,0x02},{0x01,0x85},{0x02,0xa0},{0x03,0x18},
            {0x04,0xE4},{0x05,0x40},{0x06,0x40},
            {0x10,0x05},{0x11,0xa0},
            {0x20,0x00},{0x21,0x0C},{0x22,0x00},{0x23,0x00},
            {0x24,0x00},{0x25,0xF0},{0x26,0x00},{0x27,0x00},
            {0x2A,0x00},{0x2B,0x19},
            {0x2C,0x18},{0x2D,0xF1},{0x2E,0x00},{0x2F,0xF1},
            {0x30,0x00},{0x31,0x00},{0x32,0x00},{0x33,0xC0},
            {0x34,0x18},{0x35,0x00},{0x36,0x00}
};

static struct reg_value isl79987_4Ch1Lane[]={
{0xFF, 0x0},{0x07,0x12},{0x08,0x1f},{0x09,0x43},{0x0A,0x4f},{0x0B,0x40},
{0xFF, 0x5},{0x00,0x01},{0x01,0x25},{0x02,0xA0},{0x03,0x10},
            {0x04,0xE4},{0x05,0x00},{0x06,0x00},{0x07,0x2B},
            {0x08,0x00},{0x09,0x00},{0x0A,0x62},{0x0B,0x02},
            {0x0C,0x36},{0x0D,0x00},{0x0E,0x6C},{0x0F,0x00},
            {0x10,0x05},{0x11,0xA0},{0x12,0x78},{0x13,0x17},
            {0x14,0x07},{0x15,0x36},{0x16,0x10},{0x17,0xF6},
            {0x18,0x00},{0x19,0x17},{0x1A,0x0A},{0x1B,0x71},
            {0x1C,0x7A},{0x1D,0x0F},{0x1E,0x8C},
            {0x23,0x0A},{0x26,0x07},
            {0x28,0x01},{0x29,0x0E},{0x2A,0x00},{0x2B,0x00},
            {0x38,0x03},{0x39,0xC0},{0x3A,0x06},{0x3B,0xB3},
            {0x3C,0x00},{0x3D,0xF1}
};

static struct reg_value isl79987_4Ch2Lane[]={
{0xFF,0x00},{0x07,0x12},{0x08,0x1f},{0x09,0x43},{0x0A,0x4f},{0x0B,0x41},
{0xFF,0x05},{0x00,0x02},{0x01,0x25},{0x02,0xA0},{0x03,0x10},
            {0x04,0xE4},{0x05,0x00},{0x06,0x00},{0x07,0x2B},
            {0x08,0x02},{0x09,0x00},{0x0A,0x62},{0x0B,0x02},
            {0x0C,0x36},{0x0D,0x00},{0x0E,0x6C},{0x0F,0x00},
            {0x10,0x05},{0x11,0xA0},{0x12,0x77},{0x13,0x17},
            {0x14,0x08},{0x15,0x38},{0x16,0x14},{0x17,0xF6},
            {0x18,0x00},{0x19,0x17},{0x1A,0x0A},{0x1B,0x71},
            {0x1C,0x7A},{0x1D,0x0F},{0x1E,0x8C},
            {0x23,0x0A},{0x26,0x08},
            {0x28,0x01},{0x29,0x0E},{0x2A,0x00},{0x2B,0x00},
            {0x38,0x03},{0x39,0xC0},{0x3A,0x06},{0x3B,0xB3},
            {0x3C,0x00},{0x3D,0xF1},
};

static struct reg_value isl79987_2Ch1Lane[]={
{0xFF, 0x0},{0x07,0x11},{0x08,0x1f},{0x09,0x47},{0x0A,0x4f},{0x0B,0x41},
{0xFF, 0x5},{0x00,0x01},{0x01,0x25},{0x02,0xA0},{0x03,0x10},
            {0x04,0xE4},{0x05,0x00},{0x06,0x00},{0x07,0x1B},
            {0x08,0x02},{0x09,0x00},{0x0A,0x62},{0x0B,0x02},
            {0x0C,0x36},{0x0D,0x00},{0x0E,0x36},{0x0F,0x00},
            {0x10,0x05},{0x11,0xA0},{0x12,0x34},{0x13,0x07},
            {0x14,0x02},{0x15,0x1E},{0x16,0x0A},{0x17,0x70},
            {0x18,0x00},{0x19,0x17},{0x1A,0x06},{0x1B,0x31},
            {0x1C,0x43},{0x1D,0x08},{0x1E,0x77},
            {0x23,0x03},{0x26,0x02},
            {0x28,0x00},{0x29,0xB4},{0x2A,0x00},{0x2B,0x00},
            {0x38,0x01},{0x39,0xE0},{0x3A,0x06},{0x3B,0xB3},
            {0x3C,0x00},{0x3D,0xF1}
};

static struct reg_value isl79987_2Ch2Lane[]={
{0xFF, 0x0},{0x07,0x11},{0x08,0x1f},{0x09,0x47},{0x0A,0x4f},{0x0B,0x42},
{0xFF, 0x5},{0x00,0x02},{0x01,0x25},{0x02,0xA0},{0x03,0x10},
            {0x04,0xE4},{0x05,0x00},{0x06,0x00},{0x07,0x24},
            {0x08,0x02},{0x09,0x00},{0x0A,0x62},{0x0B,0x02},
            {0x0C,0x36},{0x0D,0x00},{0x0E,0x36},{0x0F,0x00},
            {0x10,0x05},{0x11,0xA0},{0x12,0x34},{0x13,0x0F},
            {0x14,0x06},{0x15,0x24},{0x16,0x11},{0x17,0x70},
            {0x18,0x00},{0x19,0x17},{0x1A,0x06},{0x1B,0x31},
            {0x1C,0x46},{0x1D,0x08},{0x1E,0x57},
            {0x23,0x06},{0x26,0x06},
            {0x28,0x01},{0x29,0x69},{0x2A,0x00},{0x2B,0x00},
            {0x38,0x01},{0x39,0xE0},{0x3A,0x06},{0x3B,0xB3},
            {0x3C,0x00},{0x3D,0xF1}
};

static struct reg_value isl79987_1Ch1Lane[]={
{0xFF, 0x0},{0x07,0x00}, {0x08,0x1f},{0x09,0x4f},{0x0A,0x4f},{0x0B,0x42},
{0xFF, 0x5},{0x00,0x01},{0x01,0x25},{0x02,0xA0},{0x03,0x10},
            {0x04,0xE4},{0x05,0x00},{0x06,0x00},{0x07,0x17},
            {0x08,0x00},{0x09,0x00},{0x0A,0x62},{0x0B,0x02},
            {0x0C,0x36},{0x0D,0x00},{0x0E,0x1B},{0x0F,0x00},
            {0x10,0x05},{0x11,0xA0},{0x12,0x12},{0x13,0x05},
            {0x14,0x02},{0x15,0x0E},{0x16,0x08},{0x17,0x37},
            {0x18,0x00},{0x19,0x00},{0x1A,0x02},{0x1B,0x11},
            {0x1C,0x22},{0x1D,0x03},{0x1E,0x22},
            {0x23,0x02},{0x26,0x02},
            {0x28,0x01},{0x29,0x0E},{0x2A,0x00},{0x2B,0x00},
            {0x38,0x00},{0x39,0xF0},{0x3A,0x06},{0x3B,0xB3},
            {0x3C,0x00},{0x3D,0xF1}
};
/**************************************************/
void csi_lane_write_channel(struct i2c_client_data *sensor,int channel,int lane);
void csi_lane_write_channel(struct i2c_client_data *sensor,int channel,int lane)
{
	switch (channel)
	{
	case	0:
        WriteTW88S(sensor,isl79987_default, ARRAY_SIZE(isl79987_default));
		break;
	case	1:
        WriteTW88S(sensor,isl79987_1Ch1Lane, ARRAY_SIZE(isl79987_1Ch1Lane));
		break;
	case	2:
		if(lane == 1)
            WriteTW88S(sensor,isl79987_2Ch1Lane, ARRAY_SIZE(isl79987_2Ch1Lane));
		else
            WriteTW88S(sensor,isl79987_2Ch1Lane, ARRAY_SIZE(isl79987_2Ch2Lane));
		break;
	case	4:
		if(channel == 1)
	          WriteTW88S(sensor,isl79987_4Ch1Lane, ARRAY_SIZE(isl79987_4Ch1Lane));
		if(channel == 2)
	          WriteTW88S(sensor,isl79987_4Ch2Lane, ARRAY_SIZE(isl79987_4Ch2Lane));
		if(channel == 4)
		       WriteTW88S(sensor,isl79987_default, ARRAY_SIZE(isl79987_default));
		break;
	default:
		break;
	}
}

/**************************************************/
/* end of lane.c */
