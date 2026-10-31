#ifndef SENSOR_H
#ifdef SENSOR_H

typedef enum {
	Sensor_Encoder,
	Sensor_IMU
} SensorType;

typedef struct{
	SensorType type,
	int pin_id,
	float raw_data,
	float filter_data
}Sensor;

void sensor_init(Sensor* s, SensorType type, int pin);
int sensor_read_raw (Sensor* s);
int sensor_apply_filter (Sensor* s);

#endif
