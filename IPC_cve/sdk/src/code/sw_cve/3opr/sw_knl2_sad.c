/*---------------------------
 * sw_knl2_sad.c
 *  Created on: Jun 19, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#include "../../code/sw_cve/3opr/c_share.h"
/**************************************************/
#define	BLK4_SIZE	4
#define	BLK4_SHIFT	4
static void knl2_sad4(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height);
static void knl2_sad4(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height)
{
	int i, j, m, n;
	int xPos, yPos;
	int value;

	for (i = 0; i < height; i += BLK4_SIZE)
	{
		for (j = 0; j < width; j += BLK4_SIZE)
		{
			value = 0;
			for (m = 0; m < BLK4_SIZE; m++)
			{
				for (n = 0; n < BLK4_SIZE; n++)
				{
					yPos = i + m;
					xPos = j + n;

					value += ABS(in0[yPos*width + xPos] - in1[yPos*width + xPos]);
				}
			}

			yPos = i / BLK4_SIZE;
			xPos = j / BLK4_SIZE;
			out[yPos*(width / BLK4_SIZE) + xPos] = value >> BLK4_SHIFT;
		}
	}
}
/**************************************************/
#define	BLK8_SIZE	8
#define	BLK8_SHIFT	6
static void knl2_sad8(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height);
static void knl2_sad8(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height)
{
	int i, j, m, n;
	int xPos, yPos;
	int value;

	for (i = 0; i < height; i += BLK8_SIZE)
	{
		for (j = 0; j < width; j += BLK8_SIZE)
		{
			value = 0;
			for (m = 0; m < BLK8_SIZE; m++)
			{
				for (n = 0; n < BLK8_SIZE; n++)
				{
					yPos = i + m;
					xPos = j + n;

					value += ABS(in0[yPos*width + xPos] - in1[yPos*width + xPos]);
				}
			}

			yPos = i / BLK8_SIZE;
			xPos = j / BLK8_SIZE;
            out[yPos*(width / BLK8_SIZE) + xPos] = value >> BLK8_SHIFT;
		}
	}
}
/**************************************************/
#define	BLK16_SIZE		16
#define	BLK16_SHIFT		8
static void knl2_sad16(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height);
static void knl2_sad16(UINT8 *out, UINT8 *in0, UINT8 *in1, int width, int height)
{
	int i, j, m, n;
	int xPos, yPos;
	int value;

	for (i = 0; i < height; i += BLK16_SIZE)
	{
		for (j = 0; j < width; j += BLK16_SIZE)
		{
			value = 0;
			for (m = 0; m < BLK16_SIZE; m++)
			{
				for (n = 0; n < BLK16_SIZE; n++)
				{
					yPos = i + m;
					xPos = j + n;

					value += ABS(in0[yPos*width + xPos] - in1[yPos*width + xPos]);
				}
			}

			yPos = i / BLK16_SIZE;
			xPos = j / BLK16_SIZE;
            out[yPos*(width / BLK16_SIZE) + xPos] = value >> BLK16_SHIFT;
		}
	}
}

/**************************************************/
void sw_knl2_SAD(char *out, char *in0, char *in1, int width, int height,int ctrl);
void sw_knl2_SAD(char *out, char *in0, char *in1, int width, int height,int ctrl)
{
	ctrl &= 0x03;

	switch (ctrl)
	{
	case 0:
		knl2_sad4(out, in0, in1, width, height);
		break;
	case 1:
		knl2_sad8(out, in0, in1, width, height);
		break;
	case 2:
		knl2_sad16(out, in0, in1, width, height);
		break;
	default:

		break;
	}

}
/* end of sw_knl2_sad.c */
