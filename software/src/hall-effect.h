/* hall-effect-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * hall-effect.h: Implementation of Hall Effect Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef HALL_EFFECT_H
#define HALL_EFFECT_H

#include <stdint.h>
#include "bricklib/com/com_common.h"

#define EDGE_TYPE_RISING  0
#define EDGE_TYPE_FALLING 1
#define EDGE_TYPE_BOTH    2

#define FID_GET_VALUE 1
#define FID_GET_EDGE_COUNT 2
#define FID_SET_EDGE_COUNT_CONFIG 3
#define FID_GET_EDGE_COUNT_CONFIG 4
#define FID_SET_EDGE_INTERRUPT 5
#define FID_GET_EDGE_INTERRUPT 6
#define FID_SET_EDGE_CALLBACK_PERIOD 7
#define FID_GET_EDGE_CALLBACK_PERIOD 8
#define FID_EDGE_INTERRUPT 9
#define FID_EDGE_COUNT 10

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetValue;

typedef struct {
	MessageHeader header;
	bool value;
} __attribute__((__packed__)) GetValueReturn;

typedef struct {
	MessageHeader header;
	bool reset_counter;
} __attribute__((__packed__)) GetEdgeCount;

typedef struct {
	MessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) GetEdgeCountReturn;

typedef struct {
	MessageHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} __attribute__((__packed__)) SetEdgeCountConfig;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetEdgeCountConfig;

typedef struct {
	MessageHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} __attribute__((__packed__)) GetEdgeCountConfigReturn;

typedef struct {
	MessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) SetEdgeInterrupt;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetEdgeInterrupt;

typedef struct {
	MessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) GetEdgeInterruptReturn;

typedef struct {
	MessageHeader header;
	uint32_t period;
} __attribute__((__packed__)) SetEdgeCountCallbackPeriod;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetEdgeCountCallbackPeriod;

typedef struct {
	MessageHeader header;
	uint32_t period;
} __attribute__((__packed__)) GetEdgeCountCallbackPeriodReturn;

typedef struct {
	MessageHeader header;
	uint32_t count;
	bool value;
} __attribute__((__packed__)) EdgeInterrupt;

typedef struct {
	MessageHeader header;
	uint32_t count;
	bool value;
} __attribute__((__packed__)) EdgeCount;

void get_value(const ComType com, const GetValue *data);
void get_edge_count(const ComType com, const GetEdgeCount *data);
void set_edge_count_config(const ComType com, const SetEdgeCountConfig *data);
void get_edge_count_config(const ComType com, const GetEdgeCountConfig *data);
void set_edge_interrupt(const ComType com, const SetEdgeInterrupt *data);
void get_edge_interrupt(const ComType com, const GetEdgeInterrupt *data);
void set_edge_count_callback_period(const ComType com, const SetEdgeCountCallbackPeriod *data);
void get_edge_count_callback_period(const ComType com, const GetEdgeCountCallbackPeriod *data);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
