// CPU clock rate
#if defined (__AVR_ATmega8__)
#define F_CPU 8000000
#else
#define F_CPU 16000000
#endif
// Number of bytes to pre-calculate. Not conclusively shown that this helps much.
#define SAMPLE_BUFFER 24
// Sample clock updates at this rate in Hz
#if defined (__AVR_ATmega8__)
#define SAMPLE_RATE 14000UL
#else
#define SAMPLE_RATE 32000UL
#endif
// Max number of voices
#define N_VOICES 5
// Right shift divide for output waveform. Use for course global volume setting
#define OUTPUT_SCALE_SHIFT 3