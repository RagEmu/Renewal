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
#ifndef MAP_BUYINGSTORE_H
#define MAP_BUYINGSTORE_H

#include "common/ragemu.h"
#include "common/mmo.h" // MAX_SLOTS
#include "map/map.h"

struct map_session_data;

/**
 * Declarations
 **/
struct s_search_store_search;

/**
 * Defines
 **/
#define MAX_BUYINGSTORE_SLOTS 5

/// constants (client-side restrictions)
#define BUYINGSTORE_MAX_PRICE 99990000
#define BUYINGSTORE_MAX_AMOUNT 9999

/**
 * Enumerations
 **/
/// failure constants for clif functions
enum e_buyingstore_failure {
	BUYINGSTORE_CREATE               = 1,  // "Failed to open buying store."
	BUYINGSTORE_CREATE_OVERWEIGHT    = 2,  // "Total amount of then possessed items exceeds the weight limit by %d. Please re-enter."
	BUYINGSTORE_TRADE_BUYER_ZENY     = 3,  // "All items within the buy limit were purchased."
	BUYINGSTORE_TRADE_BUYER_NO_ITEMS = 4,  // "All items were purchased."
	BUYINGSTORE_TRADE_SELLER_FAILED  = 5,  // "The deal has failed."
	BUYINGSTORE_TRADE_SELLER_COUNT   = 6,  // "The trade failed, because the entered amount of item %s is higher, than the buyer is willing to buy."
	BUYINGSTORE_TRADE_SELLER_ZENY    = 7,  // "The trade failed, because the buyer is lacking required balance."
	BUYINGSTORE_CREATE_NO_INFO       = 8,  // "No sale (purchase) information available."
};

/**
 * Structures
 **/
struct s_buyingstore_item {
	int price;
	unsigned short amount;
	unsigned short nameid;
};

struct s_buyingstore {
	struct s_buyingstore_item items[MAX_BUYINGSTORE_SLOTS];
	int zenylimit;
	unsigned char slots;
};

///buyingstore entry of autotrader
struct s_bs_autotrade_entry {
	uint16 amount;
	int price;
	uint16 item_id;
};

/// buyingstore merchant data
struct s_bs_autotrade {
	int account_id;
	int char_id;
	int buyer_id;
	int m;
	uint16 x, y;
	unsigned char sex;
	char title[MESSAGE_SIZE];
	int limit;
	uint16 count;
	struct s_bs_autotrade_entry **entries;
	struct map_session_data *sd;
};

/**
 * Interface
 **/
struct buyingstore_interface {
	unsigned int nextid;
	short blankslots[MAX_SLOTS];  // used when checking whether or not an item's card slots are blank
	/// BuyingStore Autotrader
	struct s_bs_autotrade **autotraders; /// Autotraders Storage
	uint16 autotrader_count; /// Autotrader count
	/* */
	bool (*setup) (struct map_session_data* sd, unsigned char slots);
	bool (*create) (struct map_session_data* sd, int zenylimit, unsigned char result, const char* storename, const uint8* itemlist, unsigned int count);
	void (*close) (struct map_session_data* sd);
	void (*open) (struct map_session_data* sd, int account_id);
	void (*trade) (struct map_session_data* sd, int account_id, unsigned int buyer_id, const uint8* itemlist, unsigned int count);
	bool (*search) (struct map_session_data* sd, unsigned short nameid);
	bool (*searchall) (struct map_session_data* sd, const struct s_search_store_search* s);
	unsigned int (*getuid) (void);
	
	// BuyingStore Persistence
	int (*autotrade_final) (union DBKey key, struct DBData *data, va_list ap);
	void (*autotrade_update) (struct map_session_data *sd, enum e_pc_autotrade_update_action action);

	void(*autotrade_populate) (struct map_session_data *sd);
	void(*autotrade_start) (struct map_session_data *sd);
	void(*autotrade_load) (void);
};

#ifdef RAGEMU_CORE
void buyingstore_defaults (void);
#endif // RAGEMU_CORE

HPShared struct buyingstore_interface *buyingstore;

#endif  // MAP_BUYINGSTORE_H
