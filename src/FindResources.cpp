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
 * the minimap at once. The spell and the quests that teach it are data
 * (data/sql, installer.json): one quest per gathering profession, given by the
 * profession's trainers in the capitals. Some of those trainers give no quest
 * in the game; this script makes them quest givers while they are in the
 * world, without changing their template in the database.
 */

#include "Creature.h"
#include "ScriptMgr.h"

#include <unordered_set>

namespace
{
    // Herbalism, mining and fishing trainers of the eight capitals; the same
    // list as creature_queststarter in data/sql/world.
    std::unordered_set<uint32> const Trainers =
    {
        5566, 5502, 5137, 4204, 16736, 3404, 3013, 4614, 16644,  // herbalism
        5513, 4254, 16752, 3357, 3001, 4598, 16663,              // mining
        5493, 5161, 4156, 16774, 3332, 3028, 4573, 16780         // fishing
    };
}

class FindResourcesCreatureScript : public AllCreatureScript
{
public:
    FindResourcesCreatureScript() : AllCreatureScript("FindResourcesCreatureScript") { }

    void OnCreatureAddWorld(Creature* creature) override
    {
        if (Trainers.count(creature->GetEntry()) && !creature->HasNpcFlag(UNIT_NPC_FLAG_QUESTGIVER))
            creature->SetNpcFlag(UNIT_NPC_FLAG_QUESTGIVER);
    }
};

void AddSC_find_resources()
{
    new FindResourcesCreatureScript();
}
