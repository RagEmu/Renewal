/**
 * This file is part of RagEmu.
 * http://ragemu.org - https://github.com/RagEmu/Renewal
 *
 * Copyright (C) 2016  RagEmu Dev Team
 * Copyright (C) 2012-2015  Hercules Dev Team
 * Copyright (C)  Athena Dev Teams
 *
 * RagEmu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define RAGEMU_CORE

#include "random.h"

#include "common/cbasetypes.h" // for WIN32
#include "common/showmsg.h"
#include "common/timer.h" // gettick

#include <mt19937ar/mt19937ar.h> // init_genrand, genrand_int32, genrand_res53

#if defined(WIN32)
#	include "common/winapi.h"
#elif defined(HAVE_GETPID) || defined(HAVE_GETTID)
#	include <sys/types.h>
#	include <unistd.h>
#endif


/// Initializes the random number generator with an appropriate seed.
void rnd_init(void)
{
	unsigned long seed = (unsigned long)timer->gettick();
	seed += (unsigned long)time(NULL);
#if defined(WIN32)
	seed += (unsigned long)GetCurrentProcessId();
	seed += (unsigned long)GetCurrentThreadId();
#else
#if defined(HAVE_GETPID)
	seed += (unsigned long)getpid();
#endif // HAVE_GETPID
#if defined(HAVE_GETTID)
	seed += (unsigned long)gettid();
#endif // HAVE_GETTID
#endif
	init_genrand(seed);
}


/// Initializes the random number generator.
void rnd_seed(uint32 seed)
{
	init_genrand(seed);
}


/// Generates a random number in the interval [0, SINT32_MAX]
int32 rnd(void)
{
	return (int32)genrand_int31();
}


/// Generates a random number in the interval [0, dice_faces)
/// NOTE: interval is open ended, so dice_faces is excluded (unless it's 0)
uint32 rnd_roll(uint32 dice_faces)
{
	return (uint32)(rnd_uniform()*dice_faces);
}


/// Generates a random number in the interval [min, max]
/// Returns min if range is invalid.
int32 rnd_value(int32 min, int32 max)
{
	if( min >= max )
		return min;
	return min + (int32)(rnd_uniform()*(max-min+1));
}


/// Generates a random number in the interval [0.0, 1.0)
/// NOTE: interval is open ended, so 1.0 is excluded
double rnd_uniform(void)
{
	return ((uint32)genrand_int32())*(1.0/4294967296.0);// divided by 2^32
}


/// Generates a random number in the interval [0.0, 1.0) with 53-bit resolution
/// NOTE: interval is open ended, so 1.0 is excluded
/// NOTE: 53 bits is the maximum precision of a double
double rnd_uniform53(void)
{
	return genrand_res53();
}
