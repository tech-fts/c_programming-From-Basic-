#include "sensor.h"
#include <stdio.h>

void sensor_init (Sensor* s, SensorType type, int pin)
{
	s->type = type;
	s->pin_id = pin;
	s->raw_data = 0.0f;
	s->filter_data = 0.0f;
}

void sensor_read_raw (Sensor* s)
{
	int base = s->type == Sensor_Encoder ? 100.0f : 9.8f;
	int noise = ((rand() % 100) - 50) / 100.0f;
	s->raw_data = base + noise;
}

void sensor_apply_filter (Sensor* s)
{
	float alpha = 2.0f;
	s->filter_data = (alpha * s->raw_data) + ((1.0f - alpha)* s->filter_data);
}
