/* hall-effect-bricklet
 * Copyright (C) 2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * hall-effect.c: Implementation of Hall Effect Bricklet messages
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

#include "hall-effect.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/drivers/adc/adc.h"
#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "config.h"

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_GET_VALUE: {
			get_value(com, (GetValue*)data);
			return;
		}

		case FID_GET_EDGE_COUNT: {
			get_edge_count(com, (GetEdgeCount*)data);
			return;
		}

		case FID_SET_EDGE_COUNT_CONFIG: {
			set_edge_count_config(com, (SetEdgeCountConfig*)data);
			return;
		}

		case FID_GET_EDGE_COUNT_CONFIG: {
			get_edge_count_config(com, (GetEdgeCountConfig*)data);
			return;
		}

		case FID_SET_EDGE_INTERRUPT: {
			set_edge_interrupt(com, (SetEdgeInterrupt*)data);
			return;
		}

		case FID_GET_EDGE_INTERRUPT: {
			get_edge_interrupt(com, (GetEdgeInterrupt*)data);
			return;
		}

		case FID_SET_EDGE_CALLBACK_PERIOD: {
			set_edge_count_callback_period(com, (SetEdgeCountCallbackPeriod*)data);
			return;
		}

		case FID_GET_EDGE_CALLBACK_PERIOD: {
			get_edge_count_callback_period(com, (GetEdgeCountCallbackPeriod*)data);
			return;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			break;
		}
	}
}

void get_value(const ComType com, const GetValue *data) {
	GetValueReturn gvr;
	gvr.header        = data->header;
	gvr.header.length = sizeof(GetValueReturn);
	gvr.value         = BC->current_value; // PIN_HALL_EFFECT.pio->PIO_PDSR & PIN_HALL_EFFECT.mask;

	BA->send_blocking_with_timeout(&gvr,
	                               sizeof(GetValueReturn),
	                               com);
}

void get_edge_count(const ComType com, const GetEdgeCount *data) {
	GetEdgeCountReturn gecr;
	gecr.header        = data->header;
	gecr.header.length = sizeof(GetEdgeCountReturn);
	gecr.count         = BC->edge_count;

	BA->send_blocking_with_timeout(&gecr,
	                               sizeof(GetEdgeCountReturn),
	                               com);

	if(data->reset_counter) {
		BC->edge_count = 0;
	}
}

void set_edge_count_config(const ComType com, const SetEdgeCountConfig *data) {
	if(data->edge_type > EDGE_TYPE_BOTH) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	BC->edge_type = data->edge_type;
	BC->debounce  = data->debounce;

	BC->edge_count = 0;
	BC->edge_interrupt_counter = 0;

	BA->com_return_setter(com, data);
}

void get_edge_count_config(const ComType com, const GetEdgeCountConfig *data) {
	GetEdgeCountConfigReturn geccr;
	geccr.header        = data->header;
	geccr.header.length = sizeof(GetEdgeCountConfigReturn);
	geccr.edge_type     = BC->edge_type;
	geccr.debounce      = BC->debounce;

	BA->send_blocking_with_timeout(&geccr,
	                               sizeof(GetEdgeCountConfigReturn),
	                               com);
}

void set_edge_interrupt(const ComType com, const SetEdgeInterrupt *data) {
	BC->edge_interrupt_count = data->count;
	BC->edge_interrupt_counter = 0;

	BA->com_return_setter(com, data);
}

void get_edge_interrupt(const ComType com, const GetEdgeInterrupt *data) {
	GetEdgeInterruptReturn geir;
	geir.header        = data->header;
	geir.header.length = sizeof(GetEdgeInterruptReturn);
	geir.count         = BC->edge_interrupt_count;

	BA->send_blocking_with_timeout(&geir,
	                               sizeof(GetEdgeInterruptReturn),
	                               com);
}

void set_edge_count_callback_period(const ComType com, const SetEdgeCountCallbackPeriod *data) {
	BC->edge_callback_period = data->period;

	BA->com_return_setter(com, data);
}

void get_edge_count_callback_period(const ComType com, const GetEdgeCountCallbackPeriod *data) {
	GetEdgeCountCallbackPeriodReturn geccpr;
	geccpr.header        = data->header;
	geccpr.header.length = sizeof(GetEdgeCountCallbackPeriodReturn);
	geccpr.period        = BC->edge_callback_period;

	BA->send_blocking_with_timeout(&geccpr,
	                               sizeof(GetEdgeCountCallbackPeriodReturn),
	                               com);
}

void constructor(void) {
	PIN_HALL_EFFECT.type = PIO_INPUT;
	PIN_HALL_EFFECT.attribute = PIO_DEFAULT;
	BA->PIO_Configure(&PIN_HALL_EFFECT, 1);

	BC->current_value = false;
	BC->debounce = 100;
	BC->debounce_counter = 0;
	BC->edge_callback_period = 0;
	BC->edge_count = 0;
	BC->edge_interrupt_count = 0;
	BC->edge_interrupt_counter = 0;
	BC->edge_type = EDGE_TYPE_RISING;
	BC->send_edge_count = false;
	BC->send_edge_interrupt = false;
	BC->tick = 0;
}

void destructor(void) {
	PIN_HALL_EFFECT.type = PIO_INPUT;
	PIN_HALL_EFFECT.attribute = PIO_PULLUP;
	BA->PIO_Configure(&PIN_HALL_EFFECT, 1);
}


void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->debounce_counter == 0) {
			if(PIN_HALL_EFFECT.pio->PIO_PDSR & PIN_HALL_EFFECT.mask) {
				if(!BC->current_value) {
					BC->current_value = true;
					BC->debounce_counter = BC->debounce;
					if(BC->edge_type == EDGE_TYPE_RISING || BC->edge_type == EDGE_TYPE_BOTH) {
						BC->edge_count++;
						BC->edge_interrupt_counter++;
					}
				}
			} else {
				if(BC->current_value) {
					BC->current_value = false;
					BC->debounce_counter = BC->debounce;
					if(BC->edge_type == EDGE_TYPE_FALLING || BC->edge_type == EDGE_TYPE_BOTH) {
						BC->edge_count++;
						BC->edge_interrupt_counter++;
					}
				}
			}
		} else {
			BC->debounce_counter--;
		}

		BC->tick++;
		if(BC->edge_callback_period != 0 && BC->tick >= BC->edge_callback_period) {
			BC->tick = 0;
			BC->send_edge_count = true;
		}

		if(BC->edge_interrupt_count != 0 && BC->edge_interrupt_counter >= BC->edge_interrupt_count) {
			BC->edge_interrupt_counter = 0;
			BC->send_edge_interrupt = true;
		}
	}

	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->send_edge_interrupt) {
			EdgeInterrupt ei;
			BA->com_make_default_header(&ei, BS->uid, sizeof(EdgeInterrupt), FID_EDGE_INTERRUPT);
			ei.count = BC->edge_count;
			ei.value = BC->current_value;

			BA->send_blocking_with_timeout(&ei,
										   sizeof(EdgeInterrupt),
										   *BA->com_current);

			BC->send_edge_interrupt = false;
		}

		if(BC->send_edge_count) {
			EdgeCount ec;
			BA->com_make_default_header(&ec, BS->uid, sizeof(EdgeCount), FID_EDGE_COUNT);
			ec.count = BC->edge_count;
			ec.value = BC->current_value;

			BA->send_blocking_with_timeout(&ec,
										   sizeof(EdgeCount),
										   *BA->com_current);

			BC->send_edge_count = false;
		}
	}
}
