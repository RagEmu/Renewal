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
#ifndef CHAR_PINCODE_H
#define CHAR_PINCODE_H

#include "common/ragemu.h"

/* Forward Declarations */
struct char_session_data;
struct config_t; // common/conf.h

enum PincodeResponseCode {
	PINCODE_OK      = 0,
	PINCODE_ASK     = 1,
	PINCODE_NOTSET  = 2,
	PINCODE_EXPIRED = 3,
	PINCODE_UNUSED  = 7,
	PINCODE_WRONG   = 8,
};

/**
 * pincode interface
 **/
struct pincode_interface {
	/* vars */
	int enabled;
	int changetime;
	int maxtry;
	int charselect;
	unsigned int multiplier;
	unsigned int baseSeed;
	/* handler */
	void (*handle) (int fd, struct char_session_data* sd);
	void (*decrypt) (unsigned int userSeed, char* pin);
	void (*error) (int account_id);
	void (*update) (int account_id, char* pin);
	void (*sendstate) (int fd, struct char_session_data* sd, uint16 state);
	void (*setnew) (int fd, struct char_session_data* sd);
	void (*change) (int fd, struct char_session_data* sd);
	int  (*compare) (int fd, struct char_session_data* sd, char* pin);
	void (*check) (int fd, struct char_session_data* sd);
	bool (*config_read) (const char *filename, const struct config_t *config, bool imported);
};

#ifdef RAGEMU_CORE
void pincode_defaults(void);
#endif // RAGEMU_CORE

HPShared struct pincode_interface *pincode;

#endif /* CHAR_PINCODE_H */
