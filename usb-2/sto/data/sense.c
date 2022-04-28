
/*------------------------------------
 * sense.c
 * Create:  2021-10-29
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "../0ctr.h"
#include "../1imp.h"
/*================================================================*/
struct sense_data_s {
    unsigned char ResponseCode;
    unsigned char Obsolete;
    unsigned char fei_sensekey;
    unsigned char Information[4];
    unsigned char AdditionalSenseLength;
    unsigned int CommandSpecificInformation;
    unsigned char AdditionalSenseCode;
    unsigned char AdditionalSenseCodeQualifier;
    unsigned char FieldReplaceableUnitCode;
    unsigned char SKSV;
    unsigned short SenseKeySpecific;
}__attribute__ ((packed));

static struct current_sense{
    unsigned char sense_key;
    unsigned char information;
    unsigned char asc;
    unsigned char ascq;
};

static struct current_sense cur_sense_data;


#define SENSE_NOT_READY             0x02
#define SENSE_MEDIUM_ERROR          0x03
#define SENSE_ILLEGAL_REQUEST       0x05
#define SENSE_UNIT_ATTENTION        0x06

#define ASC_MEDIUM_NOT_PRESENT      0x3a
#define ASC_INVALID_FIELD_IN_CBD    0x24
#define ASC_LBA_OUT_OF_RANGE        0x21
#define ASC_WRITE_ERROR             0x0C
#define ASC_READ_ERROR              0x11
#define ASC_NOT_READY               0x04
#define ASC_INVALID_COMMAND         0x20
/*================================================================*/
int data_sense_request(void *data);
int data_sense_request(void *data)
{
	struct sense_data_s *sense_data = (struct sense_data_s *)data;
    sense_data->ResponseCode = 0x70;/*current error*/
    sense_data->Obsolete = 0;
    sense_data->fei_sensekey = cur_sense_data.sense_key & 0x0f;
    //sense_data->Information=cur_sense_data.information;
    BTR_USB_MEMSET(sense_data->Information, 0, 4);
    sense_data->Information[0] = cur_sense_data.information;
    sense_data->AdditionalSenseLength = 10;
    sense_data->CommandSpecificInformation = 0;
    sense_data->AdditionalSenseCode = cur_sense_data.asc;
    sense_data->AdditionalSenseCodeQualifier = cur_sense_data.ascq;
    sense_data->FieldReplaceableUnitCode = 0;
    sense_data->SKSV = 0;
    sense_data->SenseKeySpecific = 0;

    return sizeof(struct sense_data_s);
}
/*================================================================*/
void data_sense_cur_init(void);
void data_sense_cur_init()
{
	    cur_sense_data.sense_key = 0;
	    cur_sense_data.information = 0;
	    cur_sense_data.asc = 0;
	    cur_sense_data.ascq = 0;
}

void data_sense_cur_error(void);
void data_sense_cur_error()
{
    cur_sense_data.sense_key=SENSE_MEDIUM_ERROR;
    cur_sense_data.asc=ASC_WRITE_ERROR;
    cur_sense_data.ascq=0;
}

void data_sense_cur_not_ready(void);
void data_sense_cur_not_ready()
{
    cur_sense_data.sense_key = SENSE_NOT_READY;
    cur_sense_data.asc = ASC_MEDIUM_NOT_PRESENT;
    cur_sense_data.ascq = 0;
}

void data_sense_cur_illegal(void);
void data_sense_cur_illegal()
{
    cur_sense_data.sense_key = SENSE_ILLEGAL_REQUEST;
    cur_sense_data.asc = ASC_LBA_OUT_OF_RANGE;
    cur_sense_data.ascq = 0;
}

/*================================================================*/

/* end of sense.c */
