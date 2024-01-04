#pragma once

#include "BHW/ecs/Component.hpp"

namespace BHW
{
    typedef uint64_t EntityUUID;

    template <typename TECS>
    struct Entity
    {
        inline Entity(EntityUUID entityUUID, TECS* ecs) : m_entityUUID(entityUUID), m_ecs(ecs) { }

        template <typename TComponent, typename ...TArgs>
        inline TComponent& AddComponent(TArgs&&... args)
        {
            return m_ecs->AddComponent<TComponent>(m_entityUUID, std::forward<TArgs>(args)...);
        }

        template <typename TComponent>
        inline void RemoveComponent()
        {
            m_ecs->RemoveComponent<TComponent>(m_entityUUID);
        }

        template <typename TComponent>
        inline bool HasComponent()
        {
            return m_ecs->HasComponent<TComponent>(m_entityUUID);
        }

        template <typename TComponent>
        inline TComponent& GetComponent()
        {
            return m_ecs->GetComponent<TComponent>(m_entityUUID);
        }

        EntityUUID              m_entityUUID;
        //std::shared_ptr<TECS> m_ecs       ;
        TECS* m_ecs;
    };

    template <typename ...TComponents>
    class EntityComponents
    {
    public:
        using TComponentBitMask = ComponentBitMask<TComponents...>;

        inline EntityComponents(TComponentBitMask componentBitMask) : m_componentBitMask(componentBitMask), m_componentIndices() { }
        inline EntityComponents() : EntityComponents(TComponentBitMask()) { }
    
        template <typename TComponent>
        inline void AddComponent(ComponentIndex componentIndex)
        {
            m_componentIndices[TComponentBitMask::template ComponentTypeUUID<TComponent>()] = componentIndex;

            m_componentBitMask.template Enable<TComponent>();
        }

        template <typename TComponent>
        inline void RemoveComponent(ComponentIndex componentIndex)
        {
            m_componentIndices[TComponentBitMask::template ComponentTypeUUID<TComponent>()] = componentIndex;
            m_componentBitMask.template Disable<TComponent>();
        }

        template <typename TComponent>
        inline bool HasComponent()
        {
            return m_componentBitMask.template IsEnabled<TComponent>();
        }

        template <typename ...TComponents>
        inline bool HasComponents()
        {
            return m_componentBitMask.template IsEnabled<TComponents...>();
        }

        template <typename TComponent>
        inline ComponentIndex GetComponentIndex()
        {
            return m_componentIndices[TComponentBitMask::template ComponentTypeUUID<TComponent>()];
        }
    
    private:
        TComponentBitMask m_componentBitMask;

        std::array<ComponentIndex, sizeof...(TComponents)> m_componentIndices;
    };
}