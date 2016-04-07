/**
 * This file is part of RagEmu.
 * http://ragemu.org - https://github.com/RagEmu/Renewal
 *
 * Copyright (C) 2016  RagEmu Dev Team
 * Copyright (C) 2013-2015  Hercules Dev Team
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

/**
 * Base Author: shennetsind @ http://herc.ws
 */
#ifndef MAP_IRC_BOT_H
#define MAP_IRC_BOT_H

#include "common/ragemu.h"

#define IRC_NICK_LENGTH 40
#define IRC_IDENT_LENGTH 40
#define IRC_HOST_LENGTH 63
#define IRC_FUNC_LENGTH 30
#define IRC_MESSAGE_LENGTH 500

struct channel_data;

struct irc_func {
	char name[IRC_FUNC_LENGTH];
	void (*func)(int, char*, char*, char*, char*);
};

struct irc_bot_interface {
	int fd;
	bool isIn, isOn;
	int64 last_try;
	unsigned char fails;
	uint32 ip;
	unsigned short port;
	/* */
	struct channel_data *channel;
	/* */
	struct {
		struct irc_func **list;
		unsigned int size;
	} funcs;
	/* */
	void (*init) (bool minimal);
	void (*final) (void);
	/* */
	int (*parse) (int fd);
	void (*parse_sub) (int fd, char *str);
	void (*parse_source) (char *source, char *nick, char *ident, char *host);
	/* */
	struct irc_func* (*func_search) (char* function_name);
	/* */
	int (*connect_timer) (int tid, int64 tick, int id, intptr_t data);
	int (*identify_timer) (int tid, int64 tick, int id, intptr_t data);
	int (*join_timer) (int tid, int64 tick, int id, intptr_t data);
	/* */
	void (*send)(char *str);
	void (*relay) (const char *name, const char *msg);
	/* */
	void (*pong) (int fd, char *cmd, char *source, char *target, char *msg);
	void (*privmsg) (int fd, char *cmd, char *source, char *target, char *msg);
	void (*userjoin) (int fd, char *cmd, char *source, char *target, char *msg);
	void (*userleave) (int fd, char *cmd, char *source, char *target, char *msg);
	void (*usernick) (int fd, char *cmd, char *source, char *target, char *msg);
};

#ifdef RAGEMU_CORE
void ircbot_defaults(void);
#endif // RAGEMU_CORE

HPShared struct irc_bot_interface *ircbot;

#endif /* MAP_IRC_BOT_H */
