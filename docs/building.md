Building the Code and Programming the Chip
===
This package contains Atmel Studio 6.2 project files as well as a Makefile for
building the demonstration executable.

This guide is written assuming some experience in working with AVR Microcontrollers and C. Check online for "hello world" style educational tutorials if desired.

Sound output settings can be customized with tinytune/settings.h if you have a different clock speed or wish to change the number of voices/sample rate.

Running the Demo
---
### General Setup
The demo, tinytune_test.c builds several song files, and can be modified to play specific ones by changing the #define test_[SONGNAME] line of the file.

	// Adding this line should play a bit of music familiar to those who have played
	// the NES game Faxanadu, this one is the default for no particular reason.
	#define TEST_FAXANADU

	// This will play the familiar dungeon theme from the Legend of Zelda.
	#define TEST_ZELDA
	
	// And so forth, see tinytune_test.c for more defined songs.
	

### Makefile based build, on Linux
On Debian based distros such as Mint or Ubuntu, the Arduino development package
covers all dependencies, so I recommend installing it if you do not have a dev environment
set up already.

	sudo apt-get install arduino

First, edit the Makefile to specify your MCU programming device, so that [AVRDude](http://www.nongnu.org/avrdude/)
can program your chip. Mine's an AVRISP Mkii.

This documentation assumes that you have UDEV set up for non-root access to your programming device. If not, run _make program_fuses_ and _make program_ with sudo.

There are threads online [documenting this](http://www.avrfreaks.net/forum/tut-hard-use-avr-dragon-linux-without-being-root?skey=avr%20isp%20udev) but be aware that UDEV rules have
changed a bit on newer distros.

On Linux Mint 17, I am using this udev rule:

	...
	
It is likely that it would work on ubuntu as well.

Near the top, find the AVRDUDE_PROGRAMMER definition. E.g.

	AVRDUDE_PROGRAMMER = avrisp2
	AVRDUDE_PORT = usb
	
Change these to match your particular hardware and save. See the [AVRDude documentation](http://www.nongnu.org/avrdude/user-manual/avrdude_4.html) for
programmer types.

From the tinytune_test path, run:

	make clean&& make program_fuses&& make program

If all goes well, this should convert the demo songs to code, build the project,
and program the fuses and image onto your device. make program_fuses need only be done
once per chip, unless you've changed the fuse settings. 

At this point, your device should also be outputing some sound on Pin 3.

### Atmel Studio 6.2 based build on Windows

#### Prerequisites
[Atmel Studio 6.2] (http://www.atmel.com/tools/atmelstudio.aspx) must be installed, as well as Python (I'm using 2.7.8, not sure if Python 3.x works).

For the Renoise song importer to work, [Python] (https://www.python.org/download) must be installed and [included in the PATH environment variable for windows] (http://superuser.com/questions/143119/how-to-add-python-to-the-windows-path).


Open tinytune_test/tinytune_test.atsln in Atmel Studio.

Make sure the build type is set to Release.

Build the project (F7)

Under the Tools menu, open the Device Programming dialog.



Program your device's fuses (optionally), under the Fuses tab.

These are the settings that I'm using:
 
	SELFPRGEN = [ ]
	RSTDISBL = [ ]
	DWEN = [ ]
	SPIEN = [X]
	WDTON = [ ]
	EESAVE = [ ]
	BODLEVEL = DISABLED
	CKDIV8 = [ ]
	CKOUT = [ ]
	SUT_CKSEL = PLLCLK_16KCK_14CK_4MS
	
	EXTENDED = 0xFF (valid)
	HIGH = 0xDF (valid)
	LOW = 0xD1 (valid)

The important thing is to have:

	SUT_CKSEL = PLLCLK_16KCK_14CK_4MS

Which enables the 16MHz cpu clock and the fast 64MHz PLL clock.

Continue to the Production File tab on the device programming dialog. Select avr_tinytune\tinytune_test\Release\tinytune_test.elf and program the device.

At this point, there should be PWM audio playing on Pin 3.