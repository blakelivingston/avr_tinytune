Avr TinyTune
===

Avr Tinytune is a multi-voice, mult-timbral audio synthesis and song playback library targeting the [Atmel ATtiny85 microcontroller](http://www.atmel.com/devices/attiny85.aspx), requiring minimal additional electronic components for use in projects.

What Exactly Does It Do?
---

The C library consists of two somewhat independent parts; A multi-voice synthesizer that uses Fast PWM to simulate 8-bit analog output, and an interrupt driven background-song playback system that plays note and controller data out of chip Flash memory (progmem).

There is also an import utility that generates embeddable code representations of songs, using the save files of the [Renoise](http://www.renoise.com/) tracker-based music composition program as input. Renoise offers a demo version that is usable with this project; though I heartily encourage supporting their excellent software if you find it useful.

Example video, running into an oscilloscope: <a href="https://www.youtube.com/watch?v=PtxxCKs822M">https://www.youtube.com/watch?v=PtxxCKs822M</a>

Update
---
* Now with much more stable playback in the face of occasional buffer under-runs. Sounds like circuit-bent mayhem at 65000hz.
	* Song `TEST_ENV` at `#define SAMPLE_BUFFER 30` and `#define SAMPLE_RATE 78930UL` in settings is  kind of bonkers.

* Renoise 3.01 or better is required for song import. If updating a song from an older version of Renoise, the volume envelopes in the song need to be "Upgraded" in the envelope editing UI. The importer won't pick them up otherwise.

* Atmega8 support added via a patch contributed by <a href="https://github.com/lberezy">Lucas Berezy</a>! Output is on PB3, or pin 17.

Atmega8 support added via a patch contributed by <a href="https://github.com/lberezy">Lucas Berezy</a>! Output is on PB3, or pin 17.

Features
---

### Hardware

* **No** external crystal or oscillator required, though they can probably be used (untested). The ATtiny line of microcontrollers include a fast PLL peripheral clock (PCK) that runs at 64MHz, providing a cpu clock of 16MHz, and an 8-bit duty-cycle resolution PWM period of 250KHz.
	* Quality wise, this is especially nice since the PLL-generated high PWM frequency is easier to filter and introduces less acoustic distortion.
	* The cpu clock may potentially be able to be boosted to 20MHz, for more polyphony or higher sample rate, with no additional components, by setting the OSCCAL register to its maximum of 0xFF _(I have not tested this and it is not directly supported in code settings yet)_

* Requires only an external resistor for very basic use, e.g. driving small headphones _badly_ (since they act as a sort of physical low pass filter).  _Against **all** better judgment, even this can be skipped if you don't mind blowing up your chip (by output current overload) or your eardrum every now and then._

* A resistor capacitor lowpass filter can be used to smooth the PWM output into a reasonably clean audio signal, suitable for driving small headphones or input into an amplifier circuit.

### Synthesis
* Can play as many simultaneous voices as the MCU speed and RAM can accommodate
* Offers the following voice types:
	* PWM (square wave), with adjustable duty cycle
	* Triangle/Saw wave, continuously adjustable between the two waveforms
	* Noise channel. This is currently usable, but slow. Improvements are planned
* Adjustable playback volume
* Interrupt based, and can run in the background
* Bit Crush
	* Reduces output waveform bit depth. Makes most sense on triangle waves. Try a BitCrush of 4 on a TRI wave for that old-school NES tri sound.

### Song playback
* Arbitrary envelopes, including sustain and release
* Portamento and pitch-glides
* Pattern based playback, for space efficiency
	*repeated patterns of music do not take much additional Flash ram
* Song size limited mostly by Flash capacity
* Interrupt based, and can run in the background

### Renoise import
* Supports arbitrary pattern lengths
* Instrument envelope import
* Imports pitch glide and bend commands

Limitations
---
* Noise channel only supports 4-bit volume (life is hard without hardware multiply)
* Not all envelope parameters are supported (no loops)
* There are still some bugs in synthesis
* Output pin is hard-coded to Pin 3 (OC1B) It should be changeable, but it is untested.
* Importer does not set waveform types per instrument yet. They must be set manually when song playback begins (or after if you want).
	* There is no technical limitation preventing this, it just hasn't been done yet
	* I would envision setting special Renoise instrument names that represent the voice type, e.g. "PWM duty:64" that the importer interprets into song data.
* There are some parts of code, particularly in the importer, that I am not especially proud of. A refactoring sweep, knowing what the implementation process had to teach, would do the code base well
* It should be possible to have this run with an external crystal resonator for predictable sound tuning, but I have not tried it yet. The output would also need to be moved to a different pin, since it overlaps one the ATtiny85's resonator pins. Patches welcome.
* Envelopes and pitch bends will only function while a 'song' is playing, initiated by playSong(). For non-song audio synthesis, the caller will have to change volumes and pitches as needed.
	* This would be a reasonable feature for addition


Documentation and Demos
---
* See the tinytune_test directory for an example of song playback and conversion.
* See the docs directory for further information.
* See [tinytune/tinytune.h](tinytune/tinytune.h) for per-function comments.

Hacking
---
This is a hobby project, and my MCU and electronics experience could always use input. Feel free to make suggestions, point out document errors and unclearness, and, best still, submit patches or feature additions to the project.

Also feel free to drop me a line if you use this library! I'm always curious to see how it 
comes in handy. My original intent was to augment [one of these guys](http://www.otamatone.com/) with super enhanced sound, but I still haven't gotten around to it.

License
---
This project is provided under an [MIT License](LICENSE)
