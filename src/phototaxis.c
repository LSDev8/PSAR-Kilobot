/*###############################################*/
/*# Kilkobot Phototaxis - Move kilobot to light #*/
/*###############################################*/
#include <kilolib.h>

#define RIGHT 0
#define LEFT 1

/* CONSTANTS */
static const uint16_t HI_BARRIER = 600; /* These constants are to avoid ambient light noise */
static const uint16_t LO_BARRIER = 300;

/* VARIABLES */
uint8_t currentDir;
int16_t currentLight = 0;

/* Track the light */
void lightTrack()
{
  int16_t number = 0;
  long avg = 0;

  /* until we are under the noise barrier */
  while (number < 300)
    {
      int16_t sample = get_ambientlight();
      if (sample != -1)
	{
	  avg += sample;
	  number++;
	}
    }

  currentLight = avg / 300;
}

void turnRight()
{
  spinup_motors();               /* kilobot's motor at full speed */
  set_motors(0,kilo_turn_right);
  set_color(RGB(0,1,0));         /* GREEN LIGHT */
}

void turnLeft()
{
  spinup_motors();
  set_motors(kilo_turn_left,0);
  set_color(RGB(1,0,0));         /* RED LIGHT */
}

/* This setup is at your convenience */
void setup()
{
  currentDir = LEFT;
  turnLeft();
}

void loop()
{
  lightTrack();
  
  /* RIGHT */
  if (currentLight > HI_BARRIER)
    {
      currentDir = RIGHT;
      turnRight();
    }
  
  /* LEFT */
  if (currentLight < LO_BARRIER)
    {
      currentDir = LEFT;
      turnLeft();
    }  
}

int main()
{
  kilo_init();
  kilo_start(setup, loop);
}
