# mod-find-resources

**WORK IN PROGRESS**

Find Resources for AzerothCore 3.3.5a: one tracking spell that shows herbs, mineral veins and schools of fish on the minimap at the same time.

## Key features

- A fourth tracker beside Find Herbs, Find Minerals and Find Fish, in the minimap's tracking menu.
- Learned through the quest *A Nose for Everything*, from the herbalism, mining and fishing trainers of the capitals and of Dalaran.
- Everything shows at once, whatever professions the character has.
- Data only: no C++, nothing to rebuild.
- Texts in English, French, German, Spanish and Russian.

## Dependencies

| Dependency | For |
|---|---|
| [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk) (WotLK 3.3.5a) | the server |
| [WoW-mods-installer](https://github.com/Adrestie/WoW-mods-installer) V1.12 or later | the trainers made quest givers are put back on removal |

## How to install

1. Download `installer.exe` from the [WoW-mods-installer releases](https://github.com/Adrestie/WoW-mods-installer/releases).
2. Stop the worldserver and close the game.
3. Run `installer.exe`, give it this folder and the folders it asks for, click **Check**, then **Install**.
4. Start the worldserver again.
5. The installer writes the game files into `Data\patch-Z.MPQ`: give that archive to the other players.

## How to update

Same steps with the new version's folder, choosing **Update** instead of **Install**. Start the worldserver again.

## How to uninstall

Same steps, choosing **Remove**. The trainers it made quest givers lose that flag again. Start the worldserver again.
