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
#ifndef LOGIN_IPBAN_H
#define LOGIN_IPBAN_H

#include "common/cbasetypes.h"

#ifdef RAGEMU_CORE
// TODO: Interface
// initialize
void ipban_init(void);

// finalize
void ipban_final(void);

// check ip against ban list
bool ipban_check(uint32 ip);

// increases failure count for the specified IP
void ipban_log(uint32 ip);

// parses configuration option
bool ipban_config_read(const char *key, const char* value);
#endif // RAGEMU_CORE

#endif /* LOGIN_IPBAN_H */
