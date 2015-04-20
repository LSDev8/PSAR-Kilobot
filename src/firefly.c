/*##############################################*/
/*# Kilkobot Firefly - Synchronize kilobot led #*/
/*##############################################*/
#include <kilolib.h>

/* CONSTANTS */
#define PERIOD 32 /* Only 32 possible messages */

/* VARIABLES */
uint8_t Mclock;
message_t mesgs[PERIOD];
uint8_t offsets[PERIOD];
uint8_t total;
uint16_t avg;

/* Transmition Mclock message */
message_t *message_trans()
{
  return &mesgs[Mclock];
}

/* Receiption Mclock message */
void message_receip(message_t *mess, distance_measurement_t *dist)
{
  /* if robot ahead of neighbor... */
  if (Mclock > mess->data[0])
    {
      /* ...by less than half a period */
      if (Mclock - mess->data[0] < PERIOD/2)
	offsets[Mclock - mess->data[0]]++;
    }
  else
    {
      /* ...by more than a half period */
      if (mess->data[0] - Mclock > PERIOD/2)
	offsets[Mclock + (PERIOD - mess->data[0])]++;
    }
}

void setup()
{
  for (int i=0; i<PERIOD; i++)
    {
      mesgs[i].data[0] = i;
      mesgs[i].type = NORMAL;
      mesgs[i].crc = message_crc(&mesgs[i]);
      offsets[i] = 0;
    }

  kilo_ticks += (rand_hard())<<2;
}

void loop()
{
  Mclock = (kilo_ticks>>2)%PERIOD;
  if (!Mclock)
    {
      /* Blink in magenta */
      set_color(RGB(1,0,1));
      delay(100);
      set_color(RGB(0,0,0));
      
      total = 0;
      avg = 0;
      /* Compute average offset */
      for(int i=0; i<PERIOD; i++)
	{
	  avg += i*offsets[i]; /* the total offset amount */
	  total += offsets[i]; /* total number of neighbor offsets recorded */
	  offsets[i] = 0;      /* clear the array for next time */
	}

      /* Adjust clock by average offset */
      if (total>0)
	{
	  avg /= total;
	  kilo_ticks -= (avg<<2);
	}
    }
}

int main()
{
  kilo_init();
  kilo_message_tx = message_trans;
  kilo_message_rx = message_receip;
  kilo_start(setup, loop);
}
