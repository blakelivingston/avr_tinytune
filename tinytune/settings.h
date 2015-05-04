// CPU clock rate
#define F_CPU 8000000
// Number of bytes to pre-calculate. Not conclusively shown that this helps much.
#define SAMPLE_BUFFER 32
// Sample clock updates at this rate in Hz
#define SAMPLE_RATE 44000UL
// Max number of voices
#define N_VOICES 5
// Right shift divide for output waveform. Use for course global volume setting
#define OUTPUT_SCALE_SHIFT 4
