#pragma once

#include <thread>

#include "protocolCraft/Handler.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/ConnectionClient.hpp"

namespace Botcraft
{
    class World;
    class InventoryManager;
    class EntityManager;

#if USE_GUI
    namespace Renderer
    {
        class RenderingManager;
    }
#endif
    
    /// @brief A client containing the different managers,
    /// and performing client-side physics.
    /// Can be inherited if you want to handle other packets 
    /// without a need of any behaviour tree stuff.
    class ManagersClient : public ConnectionClient
    {
    public:
        ManagersClient(const bool use_renderer_);
        virtual ~ManagersClient();

        virtual void Disconnect() override;

        void SetSharedWorld(const std::shared_ptr<World> world_);

        const bool GetAutoRespawn() const;
        void SetAutoRespawn(const bool b);

        // Set the right transaction id, add it to the inventory manager,
        // update the next transaction id and send it to the server
        // return the id of the transaction
        const int SendInventoryTransaction(std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> transaction);

        std::shared_ptr<World> GetWorld() const;
        std::shared_ptr<EntityManager> GetEntityManager() const;
        std::shared_ptr<InventoryManager> GetInventoryManager() const;
        const bool GetCreativeMode() const;

    protected:
        void RunSyncPos();
        void Physics(const bool is_in_fluid);

    protected:
        virtual void Handle(ProtocolCraft::Message &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundChangeDifficultyPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket &msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket &msg) override;

    protected:
        std::shared_ptr<World> world;
        std::shared_ptr<EntityManager> entity_manager;
        std::shared_ptr<InventoryManager> inventory_manager;
#if USE_GUI
        // If true, opens a window to display the view
        // from the bot. Only one renderer can be active
        // at the same time
        bool use_renderer;
        std::shared_ptr<Renderer::RenderingManager> rendering_manager;
#endif

        bool auto_respawn;

        GameType game_mode;

        Difficulty difficulty;
#if PROTOCOL_VERSION > 463
        bool difficulty_locked;
#endif
        bool is_hardcore;

        bool allow_flying;
        bool creative_mode; // Instant break

        std::thread m_thread_physics;//Thread running to compute position and send it to the server every 50 ms (20 ticks/s)
    };
} //Botcraft
