/**
 * This file is part of RagEmu.
 * http://ragemu.org - https://github.com/RagEmu/Renewal
 *
 * Copyright (C) 2016  RagEmu Dev Team
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
#ifndef CONFIG_CONSTANTS_H
#define CONFIG_CONSTANTS_H

/**
 * Hercules configuration file (http://herc.ws)
 * For detailed guidance on these check http://herc.ws/wiki/SRC/config/
 **/

/**
 * @INFO: This file holds constants that aims at making code smoother and more efficient
 */

/**
 * "Sane Checks" to save you from compiling with cool bugs
 **/
#if SECURE_NPCTIMEOUT_INTERVAL <= 0
	#error SECURE_NPCTIMEOUT_INTERVAL should be at least 1 (1s)
#endif
#if NPC_SECURE_TIMEOUT_INPUT < 0
	#error NPC_SECURE_TIMEOUT_INPUT cannot be lower than 0
#endif
#if NPC_SECURE_TIMEOUT_MENU < 0
	#error NPC_SECURE_TIMEOUT_MENU cannot be lower than 0
#endif
#if NPC_SECURE_TIMEOUT_NEXT < 0
	#error NPC_SECURE_TIMEOUT_NEXT cannot be lower than 0
#endif

/**
 * DefType
 **/
typedef short defType;
#define DEFTYPE_MIN SHRT_MIN
#define DEFTYPE_MAX SHRT_MAX

/* ATCMD_FUNC(mobinfo) HIT, FLEE, ATK, ATK2, MATK and MATK2 calculations */
#define MOB_FLEE(mobdata) ( (mobdata)->lv + (mobdata)->status.agi + 100 )
#define MOB_HIT(mobdata)  ( (mobdata)->lv + (mobdata)->status.dex + 150 )
#define MOB_ATK1(mobdata) ( ((mobdata)->lv + (mobdata)->status.str) + (mobdata)->status.rhw.atk * 8 / 10 )
#define MOB_ATK2(mobdata) ( ((mobdata)->lv + (mobdata)->status.str) + (mobdata)->status.rhw.atk * 12 / 10 )
#define MOB_MATK1(mobdata)( ((mobdata)->lv + (mobdata)->status.int_) + (mobdata)->status.rhw.atk2 * 7 / 10 )
#define MOB_MATK2(mobdata)( ((mobdata)->lv + (mobdata)->status.int_) + (mobdata)->status.rhw.atk2 * 13 / 10 )
#define RE_SKILL_REDUCTION() do { \
	wd.damage = battle->calc_elefix(src, target, skill_id, skill_lv, battle->calc_cardfix(BF_WEAPON, src, target, nk, s_ele, s_ele_, wd.damage, 0, wd.flag), nk, n_ele, s_ele, s_ele_, false, flag.arrow); \
	if( flag.lh ) \
		wd.damage2 = battle->calc_elefix(src, target, skill_id, skill_lv, battle->calc_cardfix(BF_WEAPON, src, target, nk, s_ele, s_ele_, wd.damage2, 1, wd.flag), nk, n_ele, s_ele, s_ele_, true, flag.arrow); \
} while(0)

/* Renewal's dmg level modifier, used as a macro for a easy way to turn off. */
#define RE_LVL_DMOD(val) do { \
	if( (val) > 0 ) \
		skillratio = skillratio * status->get_lv(src) / (val); \
} while(0)
#define RE_LVL_MDMOD(val) do { \
	if ( (val) > 0 ) \
		md.damage = md.damage * status->get_lv(src) / (val); \
} while(0)
/* ranger traps special */
#define RE_LVL_TMDMOD() do { \
	md.damage = md.damage * 150 / 100 + md.damage * status->get_lv(src) / 100; \
} while(0)

#define VARCAST_REDUCTION(val) do { \
	if( (varcast_r += (val)) != 0 && varcast_r >= 0 ) \
		time = time * (1 - (float)min((val), 100) / 100); \
} while(0)

/* console_input doesn't go well with minicore */
#ifdef MINICORE
	#undef CONSOLE_INPUT
#endif

/**
 * End of File
 **/
#endif /* CONFIG_CONSTANTS_H */
