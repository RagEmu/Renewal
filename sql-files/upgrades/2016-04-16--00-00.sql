#1460764800

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

ALTER TABLE `elemental` 
 CHANGE COLUMN `atk1` `atk` MEDIUMINT(6) UNSIGNED NOT NULL DEFAULT '0',
 DROP COLUMN `atk2`,
 CHANGE COLUMN `class` `kind` SMALLINT(1) NOT NULL,
 CHANGE COLUMN `mode` `scale` SMALLINT(1) NOT NULL;

--
-- Table structure for table `elemental_sc`
--

CREATE TABLE IF NOT EXISTS `elemental_sc` (
  `ele_id` INT(11) UNSIGNED NOT NULL,
  `char_id` INT(11) UNSIGNED NOT NULL,
  `type` SMALLINT(11) UNSIGNED NOT NULL,
  `tick` INT(11) NOT NULL,
  `val1` INT(11) NOT NULL DEFAULT '0',
  `val2` INT(11) NOT NULL DEFAULT '0',
  `val3` INT(11) NOT NULL DEFAULT '0',
  `val4` INT(11) NOT NULL DEFAULT '0',
  KEY (`ele_id`),
  KEY (`char_id`),
  PRIMARY KEY (`ele_id`,`char_id`, `type`)
)ENGINE=MyISAM;

INSERT INTO `sql_updates` (`timestamp`) VALUES (1460764800);
