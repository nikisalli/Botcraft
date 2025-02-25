#pragma once

#include "botcraft/Game/ManagersClient.hpp"
#include "botcraft/AI/Blackboard.hpp"

namespace Botcraft
{
    /// @brief A ManagersClient extended with a blackboard that can store any
    /// kind of data and a virtual Yield function.
    /// You should **not** inherit from this class, but from TemplatedBehaviourClient
    /// or SimpleBehaviourClient instead.
    class BehaviourClient : public ManagersClient
    {
    public:
        BehaviourClient(const bool use_renderer_);
        virtual ~BehaviourClient();

        virtual void Yield() = 0;

        Blackboard& GetBlackboard();

    protected:
        Blackboard blackboard;
    };
} // namespace Botcraft
