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
