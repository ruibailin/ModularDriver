a. About usb driver:
All source code is reconstructed according to old 3 files:
1. btr_usb.c  --->usb/core
2. btr_usb_storage.c ---->usb/sto
3. btr_dwc_otg.c ---->usb/otg

b. intrduction for all main directories:
1. usb/usb:
it includes some public fuctions and macros which are used by all usb.
such as:
usb_memcpy, usb_wakeup_init, and functions to minulate ctrlrequest data.

2. usb/otg
directly read and write the reqisters of USB

3.usb/core
an intermter layer driver to manage hardware of USB and provide driver framework for all kinds of USB applications such as storage, etc

4. usb/sto:
an implementation of USB storage.

c. infrastrcture of baremetal USB driver software:
3 layers:
	storage
	    |
	    |
                core
	    |
	    |
	otg
	   |
	   |
	usb hardware

d. about the meaning of driver
You can find driver directory in all 3 main directories. Why?
Driver means there are some user-defined datas to be managed.
These datas include status of USB and endpoint, state of transfer data streams.
All these datas should be recorded and changed in RAM since the USB hardware can't record or keep record all of them.




















