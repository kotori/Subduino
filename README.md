Subduino 
========

Opensource ROV design for underwater exploration.

About
------
The Subduino project aims to make a modular ROV system comprising of several slave Arduino MCUs to do the legwork of the processing while the master MCU can do its own processing idependantly.

Compilation
------------

#### Connect master controller (ATMega644/1284)
```bash
cd master_controller/
vim Makefile
make && make upload
```

#### Connect slave rudder controller (ATMega168/328)
```bash
cd rudder_controller/
vim Makefile
make && make upload
```

#### Connect slave thrust controller (ATMega168/328)
```bash
cd thrust_controller/
vim Makefile
make && make upload
```

#### Connect slave sensor controller (ATMega168/328)
```bash
cd sensor_controller/
vim Makefile
make && make upload
```

#### Connect joystick controller (ATMega644/1284)
```bash
cd joystick_controller/
vim Makefile
make && make upload
```

