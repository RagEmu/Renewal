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

#include "int_elemental.h"

#include "char/char.h"
#include "char/inter.h"
#include "char/mapif.h"
#include "common/memmgr.h"
#include "common/mmo.h"
#include "common/nullpo.h"
#include "common/showmsg.h"
#include "common/socket.h"
#include "common/sql.h"
#include "common/strlib.h"
#include "common/utils.h"

#include <stdio.h>
#include <stdlib.h>

struct inter_elemental_interface inter_elemental_s;
struct inter_elemental_interface *inter_elemental;

/**
 * Creates a new elemental with the given data.
 *
 * @remark
 *   The elemental ID is expected to be 0, and will be filled with the newly
 *   assigned ID.
 *
 * @param[in,out] ele The new elemental's data.
 * @retval false in case of errors.
 */
bool mapif_elemental_create(struct s_elemental *ele)
{
	nullpo_retr(false, ele);
	Assert_retr(false, ele->elemental_id == 0);

	if (SQL_ERROR == SQL->Query(inter->sql_handle,
		"INSERT INTO `%s` (`char_id`,`kind`,`scale`,`hp`,`sp`,`max_hp`,`max_sp`,`atk`,`matk`,`aspd`,`def`,`mdef`,`flee`,`hit`,`life_time`)"
		"VALUES ('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
		elemental_db, ele->char_id, (int)ele->kind, ele->scale, ele->hp, ele->sp, ele->max_hp, ele->max_sp, ele->atk, ele->matk, ele->amotion,
		ele->def, ele->mdef, ele->flee, ele->hit, ele->life_time)) {
		Sql_ShowDebug(inter->sql_handle);
		return false;
	}
	ele->elemental_id = (int)SQL->LastInsertId(inter->sql_handle);
	return true;
}

/**
 * Saves an existing elemental.
 *
 * @param ele The elemental's data.
 * @retval false in case of errors.
 */
bool mapif_elemental_save(const struct s_elemental *ele)
{
	nullpo_retr(false, ele);
	Assert_retr(false, ele->elemental_id > 0);

	if (SQL_ERROR == SQL->Query(inter->sql_handle,
		"UPDATE `%s` SET `char_id` = '%d', `kind` = '%d', `scale` = '%d', `hp` = '%d', `sp` = '%d',"
		"`max_hp` = '%d', `max_sp` = '%d', `atk` = '%d', `matk` = '%d', `aspd` = '%d', `def` = '%d',"
		"`mdef` = '%d', `flee` = '%d', `hit` = '%d', `life_time` = '%d' WHERE `ele_id` = '%d'",
		elemental_db, ele->char_id, (int)ele->kind, ele->scale, ele->hp, ele->sp, ele->max_hp, ele->max_sp, ele->atk,
		ele->matk, ele->amotion, ele->def, ele->mdef, ele->flee, ele->hit, ele->life_time, ele->elemental_id)){
		Sql_ShowDebug(inter->sql_handle);
		return false;
	}
	return true;
}

/**
 * Loads the elemental data
 * @param ele_id ElementalID to load
 * @param char_id CharacterID for which elemental is requested
 * @param[in,out] ele The elemental's data.
 * @retval false in case of errors.
 */
bool mapif_elemental_load(int ele_id, int char_id, struct s_elemental *ele)
{
	char* data;

	nullpo_retr(false, ele);
	memset(ele, 0, sizeof(struct s_elemental));
	ele->elemental_id = ele_id;
	ele->char_id = char_id;

	if (SQL_ERROR == SQL->Query(inter->sql_handle,
		"SELECT `kind`, `scale`, `hp`, `sp`, `max_hp`, `max_sp`, `atk`, `matk`, `aspd`,"
		"`def`, `mdef`, `flee`, `hit`, `life_time` FROM `%s` WHERE `ele_id` = '%d' AND `char_id` = '%d'",
		elemental_db, ele_id, char_id)) {
		Sql_ShowDebug(inter->sql_handle);
		return false;
	}

	if (SQL_SUCCESS != SQL->NextRow(inter->sql_handle)) {
		SQL->FreeResult(inter->sql_handle);
		return false;
	}

	SQL->GetData(inter->sql_handle,  0, &data, NULL); ele->kind = atoi(data);
	SQL->GetData(inter->sql_handle,  1, &data, NULL); ele->scale = atoi(data);
	SQL->GetData(inter->sql_handle,  2, &data, NULL); ele->hp = atoi(data);
	SQL->GetData(inter->sql_handle,  3, &data, NULL); ele->sp = atoi(data);
	SQL->GetData(inter->sql_handle,  4, &data, NULL); ele->max_hp = atoi(data);
	SQL->GetData(inter->sql_handle,  5, &data, NULL); ele->max_sp = atoi(data);
	SQL->GetData(inter->sql_handle,  6, &data, NULL); ele->atk = atoi(data);
	SQL->GetData(inter->sql_handle,  7, &data, NULL); ele->matk = atoi(data);
	SQL->GetData(inter->sql_handle,  8, &data, NULL); ele->amotion = atoi(data);
	SQL->GetData(inter->sql_handle,  9, &data, NULL); ele->def = atoi(data);
	SQL->GetData(inter->sql_handle, 10, &data, NULL); ele->mdef = atoi(data);
	SQL->GetData(inter->sql_handle, 11, &data, NULL); ele->flee = atoi(data);
	SQL->GetData(inter->sql_handle, 12, &data, NULL); ele->hit = atoi(data);
	SQL->GetData(inter->sql_handle, 13, &data, NULL); ele->life_time = atoi(data);
	SQL->FreeResult(inter->sql_handle);
	if (save_log)
		ShowInfo("Elemental loaded (%d - %d).\n", ele->elemental_id, ele->char_id);

	return true;
}

/**
 * Saves the elemental data
 * @param fd target fd which requested to save data
 */
void mapif_elemental_request_sc_save(int fd)
{
#ifdef ENABLE_SC_SAVING
	int cid = RFIFOL(fd, 4);
	int eid = RFIFOL(fd, 8);
	int count = RFIFOW(fd, 12);

	if (SQL_ERROR == SQL->Query(inter->sql_handle, "DELETE FROM `%s` WHERE `char_id` = '%d' AND `ele_id`='%d'", elemental_scdata_db, cid, eid))
		Sql_ShowDebug(inter->sql_handle);

	if (count > 0) {
		struct status_change_data data;
		StringBuf buf;
		int i;
		StrBuf->Init(&buf);
		StrBuf->Printf(&buf, "INSERT INTO `%s` (`char_id`, `ele_id`, `type`, `tick`, `val1`, `val2`, `val3`, `val4`) VALUES ", elemental_scdata_db);
		for (i = 0; i < count; ++i) {
			memcpy(&data, RFIFOP(fd, 14 + i*sizeof(struct status_change_data)), sizeof(struct status_change_data));
			if (i > 0)
				StrBuf->AppendStr(&buf, ", ");
			StrBuf->Printf(&buf, "('%d','%d','%hu','%d','%d','%d','%d','%d')", cid, eid,
				data.type, data.tick, data.val1, data.val2, data.val3, data.val4);
		}
		if (SQL_ERROR == SQL->QueryStr(inter->sql_handle, StrBuf->Value(&buf)))
			Sql_ShowDebug(inter->sql_handle);
		StrBuf->Destroy(&buf);
	}
#endif
}

/**
 * Request to load the elemental data
 * @param fd target fd which requested to save data
 * @param char_id CharacterID for which elemental is requested
 * @param ele_id ElementalID to load
 */
void mapif_elemental_request_sc_load(int fd, int char_id, int ele_id)
{
#ifdef ENABLE_SC_SAVING
	if (SQL_ERROR == SQL->Query(inter->sql_handle,
		"SELECT `type`, `tick`, `val1`, `val2`, `val3`, `val4` FROM `%s` WHERE `char_id` = '%d' AND `ele_id` = '%d'",
		elemental_scdata_db, char_id, ele_id)) {
		Sql_ShowDebug(inter->sql_handle);
		return;
	}
	if (SQL->NumRows(inter->sql_handle) > 0) {
		struct status_change_data scdata;
		int count;
		char* data;

		memset(&scdata, 0, sizeof(scdata));
		WFIFOHEAD(fd, 14 + 50 * sizeof(struct status_change_data));
		WFIFOW(fd, 0) = 0x3894;
		WFIFOL(fd, 4) = char_id;
		WFIFOL(fd, 8) = ele_id;
		for (count = 0; count < 50 && SQL_SUCCESS == SQL->NextRow(inter->sql_handle); ++count) {
			SQL->GetData(inter->sql_handle, 0, &data, NULL); scdata.type = atoi(data);
			SQL->GetData(inter->sql_handle, 1, &data, NULL); scdata.tick = atoi(data);
			SQL->GetData(inter->sql_handle, 2, &data, NULL); scdata.val1 = atoi(data);
			SQL->GetData(inter->sql_handle, 3, &data, NULL); scdata.val2 = atoi(data);
			SQL->GetData(inter->sql_handle, 4, &data, NULL); scdata.val3 = atoi(data);
			SQL->GetData(inter->sql_handle, 5, &data, NULL); scdata.val4 = atoi(data);
			memcpy(WFIFOP(fd, 14 + count*sizeof(struct status_change_data)), &scdata, sizeof(struct status_change_data));
		}
		if (count >= 50)
			ShowWarning("Too many status changes for %d:%d, some of them were not loaded.\n", char_id, ele_id);
		if (count > 0) {
			WFIFOW(fd, 2) = 14 + count*sizeof(struct status_change_data);
			WFIFOW(fd, 12) = count;
			WFIFOSET(fd, WFIFOW(fd, 2));

			//Clear the data once loaded.
			if ( SQL_ERROR == SQL->Query(inter->sql_handle, "DELETE FROM `%s` WHERE `char_id` = '%d' AND `ele_id`='%d'", elemental_scdata_db, char_id, ele_id) )
				Sql_ShowDebug(inter->sql_handle);
		}
	} else { //no sc (needs a response)
		WFIFOHEAD(fd, 14);
		WFIFOW(fd, 0) = 0x3894;
		WFIFOW(fd, 2) = 14;
		WFIFOL(fd, 4) = char_id;
		WFIFOL(fd, 8) = ele_id;
		WFIFOW(fd, 12) = 0;
		WFIFOSET(fd, WFIFOW(fd, 2));
	}
	SQL->FreeResult(inter->sql_handle);
#endif
}

bool mapif_elemental_delete(int ele_id)
{
	if (SQL_ERROR == SQL->Query(inter->sql_handle, "DELETE FROM `%s` WHERE `ele_id` = '%d'", elemental_db, ele_id)) {
		Sql_ShowDebug(inter->sql_handle);
		return false;
	}
#ifdef ENABLE_SC_SAVING
	if (SQL_ERROR == SQL->Query(inter->sql_handle, "DELETE FROM `%s` WHERE `ele_id` = '%d'", elemental_scdata_db, ele_id)) {
		Sql_ShowDebug(inter->sql_handle);
		return false;
	}
#endif
	return true;
}

void mapif_elemental_send(int fd, struct s_elemental *ele, unsigned char flag)
{
	int size = sizeof(struct s_elemental) + 5;

	nullpo_retv(ele);
	WFIFOHEAD(fd,size);
	WFIFOW(fd,0) = 0x387c;
	WFIFOW(fd,2) = size;
	WFIFOB(fd,4) = flag;
	memcpy(WFIFOP(fd,5),ele,sizeof(struct s_elemental));
	WFIFOSET(fd,size);
}

void mapif_parse_elemental_create(int fd, const struct s_elemental *ele)
{
	struct s_elemental ele_;
	bool result;

	memcpy(&ele_, ele, sizeof(ele_));

	result = mapif->elemental_create(&ele_);
	mapif->elemental_send(fd, &ele_, result);
}

void mapif_parse_elemental_load(int fd, int ele_id, int char_id)
{
	struct s_elemental ele;
	bool result = mapif->elemental_load(ele_id, char_id, &ele);
	mapif->elemental_send(fd, &ele, result);
}

void mapif_elemental_deleted(int fd, unsigned char flag)
{
	WFIFOHEAD(fd,3);
	WFIFOW(fd,0) = 0x387d;
	WFIFOB(fd,2) = flag;
	WFIFOSET(fd,3);
}

void mapif_parse_elemental_delete(int fd, int ele_id)
{
	bool result = mapif->elemental_delete(ele_id);
	mapif->elemental_deleted(fd, result);
}

void mapif_elemental_saved(int fd, unsigned char flag)
{
	WFIFOHEAD(fd,3);
	WFIFOW(fd,0) = 0x387e;
	WFIFOB(fd,2) = flag;
	WFIFOSET(fd,3);
}

void mapif_parse_elemental_save(int fd, const struct s_elemental *ele)
{
	bool result = mapif->elemental_save(ele);
	mapif->elemental_saved(fd, result);
}

void inter_elemental_sql_init(void)
{
	return;
}

void inter_elemental_sql_final(void)
{
	return;
}

/*==========================================
 * Inter Packets
 *------------------------------------------*/
int inter_elemental_parse_frommap(int fd)
{
	unsigned short cmd = RFIFOW(fd,0);
	switch (cmd) {
		case 0x307a: mapif->parse_elemental_request_sc_save(fd); break;
		case 0x307b: mapif->parse_elemental_request_sc_load(fd, (int)RFIFOL(fd, 4), (int)RFIFOL(fd, 8)); break;
		case 0x307c: mapif->parse_elemental_create(fd, (const struct s_elemental*)RFIFOP(fd,4)); break;
		case 0x307d: mapif->parse_elemental_load(fd, (int)RFIFOL(fd,2), (int)RFIFOL(fd,6)); break;
		case 0x307e: mapif->parse_elemental_delete(fd, (int)RFIFOL(fd,2)); break;
		case 0x307f: mapif->parse_elemental_save(fd, (const struct s_elemental*)RFIFOP(fd, 4)); break;
		default:
			return 0;
	}
	return 1;
}

void inter_elemental_defaults(void)
{
	inter_elemental = &inter_elemental_s;

	inter_elemental->sql_init = inter_elemental_sql_init;
	inter_elemental->sql_final = inter_elemental_sql_final;
	inter_elemental->parse_frommap = inter_elemental_parse_frommap;
}
