#1460630460

-- This file is part of RagEmu.
-- http://ragemu.org - https://github.com/RagEmu/Renewal
--
-- Copyright (C) 2016  RagEmu Dev Team
--
-- RagEmu is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.

--
-- Table structure for table `buyingstore_merchants`
--

CREATE TABLE IF NOT EXISTS `buyingstore_merchants` (
  `account_id` INT(11) UNSIGNED NOT NULL,
  `char_id` INT(10) UNSIGNED NOT NULL,
  `sex` ENUM('F','M') NOT NULL DEFAULT 'M',
  `title` VARCHAR(80) NOT NULL DEFAULT 'Sell To Me!',
  `limit` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`account_id`, `char_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `buyingstore_data`
--

CREATE TABLE IF NOT EXISTS `buyingstore_data` (
  `char_id` INT(10) UNSIGNED NOT NULL,
  `item_id` INT(10) UNSIGNED NOT NULL,
  `amount` SMALLINT(5) UNSIGNED NOT NULL,
  `price` INT(10) UNSIGNED NOT NULL,
  INDEX (`char_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

INSERT INTO `sql_updates` (`timestamp`) VALUES (1460630460);
