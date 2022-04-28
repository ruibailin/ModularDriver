# ModularDriver
Example for how to write modularized Linux and baremental driver.

As a team leader for software project, I always take care of quality and maintainability of software.
But Linux's gurus have done very bad examples for most of young engineers.Their code has bad modularization and is very hard to understand.
To make things worse, most of Linux code can't be debugged and tested in IDE, it leads very poor efficiency to the whole R&D team.
A modularized driver code means that you can debug most parts of driver code in IDE easily.
In order to debug linux driver in IDE like a hello word program, we need to cut or encapsulate the head and foot of linux driver:
1. Head: declaration and framework of Linux driver.
2. Foot: directly read and write registers of hardware.
Also we need to encapsulate all Linux kernel API.

There are four modularized Linux or baremental driver:
1. IPC_cve: CVE(computor vision engine) is a module for image recognition. In order to test the driver, i wrote a software CVE which can be implemented in kernel or user mode.
2. ISL79987: This is a V4L2 driver for ISL79987 
3. Reg_IO: a driver to read and write register on the SOC board, according to the command comes from up computor. So I include driver and app.
4. usb-2: a driver rewriten or reconstructed according to the old synopsys usb2.0 baremental driver.
