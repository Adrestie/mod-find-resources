# mod-find-resources

Find Resources for AzerothCore 3.3.5a: one tracking spell that shows nearby
herbs, mineral veins and schools of fish on the minimap at the same time,
where the game lets a gatherer track only one kind at once.

**Written, not yet built nor tried in game.** See
[What to check in game](#what-to-check-in-game).

## What it does

The game lets a gatherer track one kind of resource at a time, with Find
Herbs, Find Minerals or Find Fish. This module adds a fourth tracking spell, **Find Resources**, that shows all three at once on the minimap: herbs,
mineral veins and schools of fish.

- **Learned from a trainer, by a quest.** The herbalism, mining and fishing
  trainers of the eight capitals (Stormwind, Ironforge, Darnassus, the Exodar,
  Orgrimmar, Thunder Bluff, the Undercity, Silvermoon) and of Dalaran offer
  the quest *A Nose for Everything* to the characters who have their
  profession. It completes as soon as it is accepted, after a few lines from
  the trainer, and teaches the spell. One quest is enough: once it is done at
  one trainer, the others no longer offer it.
- **A tracker like the others.** It sits in the minimap's tracking menu and in
  the General tab of the spellbook, is instant, lasts until cancelled and
  shares the trackers' cooldown. Casting it ends Find Herbs, Find Minerals,
  Find Fish or a hunter's tracking; casting one of them ends it.
- **Everything at once.** Herbs, veins and schools of fish all show, whatever
  professions the character has.

| Language | Spell | Quest |
|---|---|---|
| enUS | Find Resources | A Nose for Everything |
| frFR | Découverte de ressources | Du flair pour tout |
| deDE | Ressourcensuche | Ein Riecher für alles |
| esES, esMX | Encontrar recursos | Olfato para todo |
| ruRU | Поиск ресурсов | Нюх на всё |

## How it works

Spell 95000 (tranche 95 of the [WoW-mods registry](https://github.com/Adrestie/WoW-mods/blob/main/ID_RANGES.md))
is Find Herbs with three effects instead of one, each applying the trackers'
aura (`SPELL_AURA_TRACK_RESOURCES`) for one lock type: herbs (2), minerals (3),
schools of fish (19). The core sets one bit of `PLAYER_TRACK_RESOURCES` per
effect and the client draws every kind whose bit is set. Spell 95001 is the
quests' reward: the player casts it and learns 95000.

Both spells are data on both sides: the `spell_dbc` rows of
`data/sql/world/find_resources_01_spell.sql` for the server, the same rows in
the client's `Spell.dbc`, written by the installer (`installer.json`).
`find_resources_02_quests.sql` holds the three quests (95000 herbalism, 95001
mining, 95002 fishing), each with `RequiredSkillID` and the same exclusive
group, and the trainers that give and take them back. Darnassus has no mining
trainer, Shattrath no gathering trainer at all.

Some of those trainers give no quest in the game: the SQL makes them quest
givers (`npcflag` 2). The flag stays if the module is removed; on a creature
with no quest it does nothing.

The module is data only: no C++, nothing to rebuild.

## Requirements

| | |
|---|---|
| [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk) | 3.3.5a |
| Game client | the two spells' rows in `DBFilesClient\Spell.dbc` (the installer writes them) |

## Installing

Stop the world server, then run `installer.exe`, the WoW-mods installer
([WoW-mods-installer releases](https://github.com/Adrestie/WoW-mods-installer/releases)),
and give it this folder, the game folder, the world server's folder and MySQL.
It applies the SQL to the world database and adds the spells to the game's
`Spell.dbc`; start the world server again. Every player needs the client part.

By hand: apply `data/sql/world` to the world database, and add the rows of
`installer.json` (`dbc`) to the client's `Spell.dbc` in a patch archive.

## What to check in game

- A character with Herbalism talks to the herbalism trainer of a capital: the
  quest is offered, completes at once and teaches the spell.
- The mining and fishing trainers no longer offer it to that character; a
  character without any of the three professions is not offered it.
- The trainers that were not quest givers (Ironforge's herbalist, Stormwind's
  miner and fisherman, the Exodar's and Silvermoon's) show the quest.
- Cast it: herbs, veins and schools of fish all show on the minimap.
- Cast Find Herbs: Find Resources ends, only herbs show; and the other way.
- The texts of the spell and of the quest in each language of the client.

## Licence

GNU General Public License, version 2 or later, like AzerothCore.
