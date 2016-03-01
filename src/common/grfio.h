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
#ifndef COMMON_GRFIO_H
#define COMMON_GRFIO_H

#include "common/ragemu.h"

struct grfio_interface {
	void (*init) (const char *fname);
	void (*final) (void);
	void *(*reads) (const char *fname, int *size);
	char *(*find_file) (const char *fname);

	unsigned long (*crc32) (const unsigned char *buf, unsigned int len);
	int (*decode_zip) (void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen);
	int (*encode_zip) (void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen);
};

#define grfio_read(fn) grfio->reads((fn), NULL)

#ifdef RAGEMU_CORE
void grfio_defaults(void);
#endif // RAGEMU_CORE

HPShared struct grfio_interface *grfio;
#endif /* COMMON_GRFIO_H */
