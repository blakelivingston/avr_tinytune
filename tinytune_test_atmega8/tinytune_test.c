/*
 * Created: 1/15/2012 11:34:34 PM
 *  Author: Blake Livingston
 */

#include <avr/io.h>
#include <avr/portpins.h>
#include "tinytune/tinytune.h"

#define TEST_ZELDA

#ifdef TEST_ZELDA
#include "test_songs/zelda.h"
int main(void)
{
  initTinyTune();
  initVoiceTRI(0);
  setBitCrunch(0,4);
  playSong(&zelda);
  while(1)
  {
  }
}
#endif

#ifdef TEST_FAXANADU
#include "test_songs/faxanadu.h"
int main(void)
{
  initTinyTune();
  initVoiceTRI(2);
  setDuty(0,0x80);
  setDuty(0,0x85);
  setBitCrunch(2,4);
  playSong(&faxanadu);
  while(1)
  {
  }
}
#endif

#ifdef TEST_PITCHBEND
#include "test_songs/pitch.h"
int main(void)
{
  initTinyTune();
  playSong(&pitch);
  while(1)
  {
  }
}
#endif

#ifdef TEST_ENV
#include "test_songs/env_test.h"
int main(void)
{
	initTinyTune();
	playSong(&env_test);
	while(1)
	{
	}
}
#endif

#ifdef TEST_DEMO1
#include "test_songs/demo1.h"
int main(void)
{
  initTinyTune();
  initVoiceTRI(4);
  initVoiceTRI(0);
  setDuty(1,0xe0);
  setDuty(2,0xe0);
  setBitCrunch(0,4);
  playSong(&demo1);
  while(1)
  {
  }
}
#endif

#ifdef TEST_NOISE
#include "test_songs/noise.h"
int main(void) {
  initTinyTune();
  initVoiceNOISE(0);
  initVoiceNOISE(1);
  playSong(&noise);
  while (1) {
  }
}
#endif
