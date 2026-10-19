# mod-find-resources

Find Resources for AzerothCore 3.3.5a: one tracking spell that shows nearby
herbs, mineral veins and schools of fish on the minimap at the same time,
where the game lets a gatherer track only one kind at once.

**Written, not yet built nor tried in game.** See
[What to check in game](#what-to-check-in-game).

| Language | Name |
|---|---|
| enUS | Find Resources |
| frFR | Découverte de ressources |
| deDE | Ressourcensuche |
| esES, esMX | Encontrar recursos |
| ruRU | Поиск ресурсов |

## How it behaves

- **Learned by gathering.** A character with Herbalism, Mining or Fishing
  learns the spell, at login or as soon as the profession is learned; one who
  abandons the last of them loses it. `FindResources.Professions` sets how
  many of the three are needed (0: every character).
- **A tracker like the others.** It sits in the minimap's tracking menu and in
  the General tab of the spellbook, is instant, lasts until cancelled and
  shares the trackers' cooldown. Casting it ends Find Herbs, Find Minerals,
  Find Fish or a hunter's tracking; casting one of them ends it.
- **Everything at once.** Herbs, veins and schools of fish all show, whatever
  professions the character has.

## How it works

Spell 95000 (tranche 95 of the [WoW-mods registry](https://github.com/Adrestie/WoW-mods/blob/main/ID_RANGES.md))
is Find Herbs with three effects instead of one, each applying the trackers'
aura (`SPELL_AURA_TRACK_RESOURCES`) for one lock type: herbs (2), minerals (3),
schools of fish (19). The core sets one bit of `PLAYER_TRACK_RESOURCES` per
effect and the client draws every kind whose bit is set.

The spell is data on both sides: the `spell_dbc` row of
`data/sql/world/find_resources_01_spell.sql` for the server, the same row in
the client's `Spell.dbc`, written by the installer (`installer.json`). The
script (`src/FindResources.cpp`) only teaches and takes back the spell.

## Requirements

| | |
|---|---|
| [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk) | 3.3.5a, built with the module in `modules/` |
| Game client | the spell's row in `DBFilesClient\Spell.dbc` (the installer writes it) |

## Installing

Stop the world server, then run `installer.exe`, the WoW-mods installer
([WoW-mods-installer releases](https://github.com/Adrestie/WoW-mods-installer/releases)),
and give it this folder, the game folder and the server's folders. It copies
the module into `modules/` and the configuration into `configs/modules/`, and
adds the spell to the game's `Spell.dbc`. Then rebuild the core; the world
server applies the SQL at its next start. Every player needs the client part.

By hand: copy the module into `modules/`, copy
`conf/mod-find-resources.conf.dist` to `configs/modules/mod-find-resources.conf`,
rebuild the core, and add the row of `installer.json` (`dbc`) to the client's
`Spell.dbc` in a patch archive.

## Configuration

`mod-find-resources.conf`:

| Setting | Default | |
|---|---|---|
| `FindResources.Enable` | 1 | the module teaches and takes back the spell |
| `FindResources.Professions` | 1 | gathering skills needed, out of Herbalism, Mining and Fishing (0 to 3) |

## What to check in game

- A character with Herbalism only logs in: the spell is in the General tab and
  in the tracking menu.
- Cast it: herbs, veins and schools of fish all show on the minimap.
- Cast Find Herbs: Find Resources ends, only herbs show; and the other way.
- Abandon the last gathering profession: the spell and its aura go.
- The name and the tooltip in each language of the client.

## Licence

GNU General Public License, version 2 or later, like AzerothCore.
