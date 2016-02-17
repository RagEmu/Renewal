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
#ifndef COMMON_DES_H
#define COMMON_DES_H

#include "common/ragemu.h"

/// One 64-bit block.
typedef struct BIT64 { uint8_t b[8]; } BIT64;

struct des_interface {
	void (*decrypt_block) (BIT64* block);
	void (*decrypt) (unsigned char* data, size_t size);
};

#ifdef RAGEMU_CORE
void des_defaults(void);
#endif // RAGEMU_CORE

HPShared struct des_interface *des;

#endif // COMMON_DES_H
