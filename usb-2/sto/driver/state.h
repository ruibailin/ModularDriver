
/*------------------------------------
 * state.h
 * Create:  2021-11-05
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_STO_DRIVER_STATE_H_
#define USB_STO_DRIVER_STATE_H_
/*================================================================*/
enum STO_STATE_E{
    WAITING_FOR_COMMAND,
    SENDING_BLOCKS,
    SENDING_RESULT,
    SENDING_FAILED_RESULT,
    RECEIVING_BLOCKS,
    RECEIVING_TIME,
    WAITING_FOR_CSW_COMPLETION_OR_COMMAND,
    WAITING_FOR_CSW_COMPLETION
};
extern enum STO_STATE_E sto_state ;
/*================================================================*/
#endif
/* end of state.h */
