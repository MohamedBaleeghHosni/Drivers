/******************************************************************************
 *
 * Module: Flame Sensor
 *
 * File Name: flame_sensor.h
 *
 * Description: Header file for the Flame Sensor driver
 *
 * Author: Mohamed Baleegh
 *
 *******************************************************************************/

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Flame sensor pin configeration */
#define FLAME_SENSOR_PORT_ID     PORTD_ID
#define FLAME_SENSOR_PIN_ID      PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void FlameSensor_init(void);

/*
 * Read the flame sensor value.
 * if
 *  Flame detected ->1
 *        No flame ->0
 */
uint8 FlameSensor_getValue(void);

#endif
