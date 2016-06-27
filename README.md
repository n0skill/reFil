# reFil
A machine that makes filament suitable for 3D printers out of normally unrecycled plastic parts such as HDPE from bottle caps, failed prints etc.

# Folders
* schematics - All of the schematics made with KiCAD. Including the gerber files, kicad files (schematic, netlist, pcb, etc.)
* src - The source code running on the arduino nano (arduino/C/AVR ASM)
* mechanics - mechanical parts

# Material
The following material is needed for the whole project.

## Mechanical parts
The machine is made of lathed aluminium and brass.
All the plans will be available in the "mechanical" folder. Including 3D models, plans and specs

## Electrical parts
The controller board consists of an arduino nano and a custom board. Using a 24V power supply, a LM7805 regulator is used to drop down the voltage to a usable 5V signal to drive the logic. Since the drop is quite significant and the LM7805 is a simple linear regulator, a decent amount of heat will be produced. This can compromise the functionality of the circuit, so a heat sink has to be appended to it in order to better disipate the heat.

The board will be used to: 
1) display the current temperature
2) drive the motor
3) drive the heating element

### Temperature sensor
The temperature sensor consists of a PT1000 RTD as part of a voltage divider circuit. The conversion from voltage to temperature can be made by either: looking up a table, or using a formula.

Once the temperature is known, the arduino uses BCD encoding to controll the CD4543BE 7 segment display driver, which displays the temperature.

### Motor driver
The motor is a E192.24.246 Micromotors brushed DC thing. It has a 1:246 gearbox that allows it to move things with a high torque (at the expense of a lower rate of rotation. But we don't care about that)

It is using the 24V from the barrel jack and is toggled using a SRD-05VDC-SL-C relay from SONGLE industries.

### Heating element

The heating element is a simple nichrome wire that is also toggled with a relay on the 24V power line.

