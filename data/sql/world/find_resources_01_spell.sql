-- mod-find-resources: the spell Find Resources (95000, tranche 95 of the
-- WoW-mods registry).
--
-- Server side: AzerothCore completes Spell.dbc from `spell_dbc` at startup;
-- the client has the same row (installer.json, DBC Spell.dbc). Three effects
-- apply the aura of the gathering trackers (SPELL_AURA_TRACK_RESOURCES), one
-- per lock type: herbs (2), minerals (3), schools of fish (19). The core sets
-- one bit of PLAYER_TRACK_RESOURCES per effect, so the minimap shows the three
-- at once. Like Find Herbs, the spell is a tracker: casting it ends the other
-- tracking spells, and casting one of them ends it.
--
-- Idempotent: the row is deleted before being written again.

DELETE FROM `spell_dbc` WHERE `ID` = 95000;
INSERT INTO `spell_dbc` (`ID`, `Category`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx6`, `CastingTimeIndex`, `CategoryRecoveryTime`, `ProcChance`, `DurationIndex`, `RangeIndex`, `EquippedItemClass`, `Effect_1`, `Effect_2`, `Effect_3`, `EffectDieSides_3`, `EffectBasePoints_3`, `ImplicitTargetA_1`, `ImplicitTargetA_2`, `ImplicitTargetA_3`, `EffectAura_1`, `EffectAura_2`, `EffectAura_3`, `EffectMiscValue_1`, `EffectMiscValue_2`, `EffectMiscValue_3`, `SpellIconID`, `ActiveIconID`, `Name_Lang_enUS`, `Name_Lang_koKR`, `Name_Lang_frFR`, `Name_Lang_zhCN`, `Name_Lang_enTW`, `Name_Lang_zhTW`, `Name_Lang_Mask`, `NameSubtext_Lang_Mask`, `Description_Lang_enUS`, `Description_Lang_koKR`, `Description_Lang_frFR`, `Description_Lang_zhCN`, `Description_Lang_enTW`, `Description_Lang_zhTW`, `Description_Lang_Mask`, `AuraDescription_Lang_enUS`, `AuraDescription_Lang_koKR`, `AuraDescription_Lang_frFR`, `AuraDescription_Lang_zhCN`, `AuraDescription_Lang_enTW`, `AuraDescription_Lang_zhTW`, `AuraDescription_Lang_Mask`, `DefenseType`, `EffectChainAmplitude_1`, `EffectChainAmplitude_2`, `EffectChainAmplitude_3`, `SchoolMask`)
VALUES (95000, 1238, 687865872, 268566560, 268959744, 1048576, 4096, 1, 1500, 101, 21, 1, -1, 6, 6, 6, 1, -1, 1, 1, 1, 45, 45, 45, 2, 3, 19, 171, 171, 'Find Resources', 'Découverte de ressources', 'Ressourcensuche', 'Encontrar recursos', 'Encontrar recursos', 'Поиск ресурсов', 16712190, 16712190, 'Shows nearby herbs, mineral veins and schools of fish on the minimap.', 'Les herbes, les filons de minerai et les bancs de poissons des environs apparaissent sur la minicarte.', 'Zeigt Kräuter, Erzvorkommen und Fischschwärme in der Nähe auf der Minikarte an.', 'Muestra en el minimapa las hierbas, los filones de mineral y los bancos de peces cercanos.', 'Muestra en el minimapa las hierbas, los filones de mineral y los bancos de peces cercanos.', 'Отображает на миникарте травы, рудные жилы и косяки рыбы поблизости.', 16712190, 'Tracking herbs, minerals and fish.', 'Repère les herbes, les gisements et les bancs de poissons.', 'Sucht nach Kräutern, Mineralien und Fischen.', 'Rastreando hierbas, minerales y peces.', 'Rastreando hierbas, minerales y peces.', 'Поиск трав, минералов и рыбы.', 16712190, 1, 1.0, 1.0, 1.0, 1);
