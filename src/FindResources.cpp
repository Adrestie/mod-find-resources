/*
 * This file is part of mod-find-resources.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Find Resources (spell 95000) tracks herbs, minerals and schools of fish on
 * the minimap at once. The spell itself is data (data/sql, installer.json);
 * this script teaches it to the characters who gather, and takes it back from
 * those who no longer do.
 */

#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"

#include <algorithm>

namespace
{
    constexpr uint32 SPELL_FIND_RESOURCES = 95000;

    struct FindResourcesConfig
    {
        bool enable = true;
        uint32 professions = 1;

        void Load()
        {
            enable = sConfigMgr->GetOption<bool>("FindResources.Enable", true);
            professions = std::min<uint32>(sConfigMgr->GetOption<uint32>("FindResources.Professions", 1), 3);
        }
    };

    FindResourcesConfig config;

    bool IsGatheringSkill(uint32 skill)
    {
        return skill == SKILL_HERBALISM || skill == SKILL_MINING || skill == SKILL_FISHING;
    }

    // Teaches or takes back the spell, by the gathering skills the character has.
    void Update(Player* player)
    {
        if (!config.enable)
            return;

        uint32 known = uint32(player->HasSkill(SKILL_HERBALISM)) + uint32(player->HasSkill(SKILL_MINING))
            + uint32(player->HasSkill(SKILL_FISHING));
        bool deserved = known >= config.professions;

        if (deserved && !player->HasSpell(SPELL_FIND_RESOURCES))
            player->learnSpell(SPELL_FIND_RESOURCES);
        else if (!deserved && player->HasSpell(SPELL_FIND_RESOURCES))
        {
            player->removeSpell(SPELL_FIND_RESOURCES, SPEC_MASK_ALL, false);
            player->RemoveAurasDueToSpell(SPELL_FIND_RESOURCES);
        }
    }
}

class FindResourcesWorldScript : public WorldScript
{
public:
    FindResourcesWorldScript() : WorldScript("FindResourcesWorldScript", { WORLDHOOK_ON_AFTER_CONFIG_LOAD }) { }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        config.Load();
    }
};

class FindResourcesPlayerScript : public PlayerScript
{
public:
    FindResourcesPlayerScript() : PlayerScript("FindResourcesPlayerScript", { PLAYERHOOK_ON_LOGIN, PLAYERHOOK_ON_SET_SKILL }) { }

    void OnPlayerLogin(Player* player) override
    {
        Update(player);
    }

    // A gathering profession learned or abandoned. The skills a character
    // loads with are seen at login.
    void OnPlayerSetSkill(Player* player, uint32 skill, uint32 /*value*/, uint32 /*max*/, uint32 /*step*/, uint32 /*newValue*/) override
    {
        if (IsGatheringSkill(skill) && player->IsInWorld())
            Update(player);
    }
};

void AddSC_find_resources()
{
    new FindResourcesWorldScript();
    new FindResourcesPlayerScript();
}
