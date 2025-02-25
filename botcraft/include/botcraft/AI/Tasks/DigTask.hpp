#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// @brief Dig a block at a given location. If too far, will try to pathfind toward it
    /// @param c The client performing the action
    /// @param pos Location of block to dig
    /// @param face Digging direction
    /// @return Success if the block is broken, Failure otherwise
    Status Dig(BehaviourClient& c, const Position& pos, const PlayerDiggingFace face = PlayerDiggingFace::Top);
        
    /// @brief Same thing as Dig, but reads its parameters from the blackboard
    /// @param c The client performing the action
    /// @return Success if the block is broken, Failure otherwise
    Status DigBlackboard(BehaviourClient& c);
}