
/*------------------------------------
 * class.h
 * Create:  2021-11-14
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#ifndef USB_CORE_DRIVER_CLASS_H_
#define USB_CORE_DRIVER_CLASS_H_
/*================================================================*/
/* Common api, implemented by all class drivers */

struct usb_class_driver {
    /* First some runtime data */
    int enabled;
    int first_interface;
    int last_interface;

    /* Driver api starts here */

    /* Set this to true if the driver needs exclusive disk access (e.g. usb storage) */
    int needs_exclusive_storage;

    /* Let the driver request endpoints it need. Returns zero on success */
    int (*request_endpoints)(void *req);

    /* Tells the driver what its first interface number will be. The driver
     returns the number of the first available interface for the next driver
     (i.e. a driver with one interface will return interface+1)
     A driver must have at least one interface
     Mandatory function */
    int (*set_first_interface)(int interface);

    /* Asks the driver to put the interface descriptor and all other
     needed descriptor for this driver at dest.
     Returns the number of bytes taken by these descriptors.
     Mandatory function */
    int (*get_config_descriptor)(unsigned char *dest, int max_packet_size);

    /* Tells the driver that a usb connection has been set up and is now
     ready to use.
     Optional function */
    void (*init_connection)(void);

    /* Initialises the driver. This can be called multiple times,
     and should not perform any action that can disturb other threads
     (like getting the audio buffer)
     Optional function */
    void (*init)(void);

    /* Tells the driver that the usb connection is no longer active
     Optional function */
    void (*disconnect)(void);

    /* Tells the driver that a usb transfer has been completed. Note that "dir"
     is relative to the host
     Optional function */
    void (*transfer_complete)(int ep, int dir, int status, int length);

    /* Tells the driver that a control request has come in. If the driver is
     able to handle it, it should ack the request, and return true. Otherwise
     it should return false.struct usb_ctrlrequest
     Optional function */
    int (*control_request)(void* req, unsigned char *dest);

    /* Tells the driver that a hotswappable disk/card was inserted or
     extracted
     Optional function */
    void (*notify_hotswap)(int volume, int inserted);
};

/*================================================================*/
#endif
/* end of class.h */
