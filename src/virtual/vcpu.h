/*
 * The Shadow Simulator
 *
 * Copyright (c) 2010-2011 Rob Jansen <jansen@cs.umn.edu>
 *
 * This file is part of Shadow.
 *
 * Shadow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shadow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shadow.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VCPU_H_
#define VCPU_H_

#include <glib.h>
#include <stddef.h>
#include <stdint.h>

/* this is multiplied by the actual number of bytes processed to artificially increase processing penalty.
 * set to 0 to disable CPU load delays. */
#define VCPU_LOAD_MULTIPLIER 1

/* how long until we block reads and writes? 1 milliseconds */
#define VCPU_DELAY_THRESHOLD_NS 1000000

/* ratio of AES speed to Tor application processing speed as in a PlanetLab experiment */
#define VCPU_AES_TO_TOR_RATIO 24.0
/* estimate of the fraction of time taken to read vs write */
#define VCPU_READ_FRACTION 0.75
#define VCPU_WRITE_FRACTION 1 - VCPU_READ_FRACTION

struct vcpu_s {
	guint64 cpu_speed_Bps;
	gdouble nanos_per_cpu_aes_byte;
	gdouble nanos_per_cpu_proc_byte;
	SimulationTime now;
	SimulationTime timeCPUAvailable;
};

vcpu_tp vcpu_create(guint64 cpu_speed_Bps);
void vcpu_destroy(vcpu_tp vcpu);

void vcpu_add_load_aes(vcpu_tp vcpu, guint32 bytes);
void vcpu_add_load_read(vcpu_tp vcpu, guint32 bytes);
void vcpu_add_load_write(vcpu_tp vcpu, guint32 bytes);
gboolean vcpu_isBlocked(vcpu_tp vcpu);

SimulationTime vcpu_adjustDelay(vcpu_tp vcpu, SimulationTime now);

#endif /* VCPU_H_ */