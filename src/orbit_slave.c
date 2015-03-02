//Kilobot slave - Orbit around the master.

#include <kilolib.h>

static const uint8_t MIN_DISTANCE = 40;
static const uint8_t DISTANCE = 60;

uint8_t cur_dist = 0;
uint8_t new_msg = 0;
distance_measurement_t dist;

void message_rx(message_t *m, distance_measurement_t *d)
{
  new_msg = 1;
  dist = *d;
}

void loop()
{
  //New message receive ?
  if(new_msg)
    {
      new_msg = 0;
      //Blink led.
      set_color(RGB(0,1,0));
      delay(20);
      set_color(RGB(0,0,0));
      cur_dist = estimate_distance(&dist);

      //Too far.
      if(cur_dist >= DISTANCE)
	{
	  spinup_motors();
	  //Go right.
	  set_motors(0, kilo_turn_right);
	}
      //Too close.
      else if(cur_dist <= MIN_DISTANCE)
	{
	  spinup_motors();
	  //Go left.
	  set_motors(kilo_turn_left, 0);
	}
      //Distance ok.
      else
	{
	  spinup_motors();
	  //Go straight;
	  set_motors(kilo_straight_left, kilo_straight_right);
	}
    }
}

void setup() { }

int main()
{
  kilo_init();
  kilo_message_rx = message_rx;
  kilo_start(setup, loop);
  
  return 0;
}
