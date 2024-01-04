#pragma once

#include <array>
#include <vector>
#include <unordered_map>
#include <functional>

#include "BHW/utils/event/EventSystem.hpp"

#include "BHW/utils/data/Data.hpp"
#include "BHW/ecs/Entity.hpp"
#include "BHW/ecs/Component.hpp"
#include "BHW/ecs/ComponentBitMask.hpp"
#include "BHW/ecs/EventSystem.hpp"

#include "BHW/utils/random/Random.hpp"

namespace BHW
{
    template <typename TEventSystem, typename ...TComponents>
    class ECS : public ECSSystem<ECS<TEventSystem, TComponents...>, TEventSystem>
    {
    public:
        using TComponentBitMask = typename ComponentBitMask<TComponents...>;

        using TEntity           = Entity          <ECS<TEventSystem, TComponents...>>;
        using TEntityComponents = EntityComponents<TComponents...                   >;

    public:
        inline ECS() :
            ECSSystem<ECS<TEventSystem, TComponents...>, TEventSystem>(),
            m_components           (),  
            m_entityComponents     (), 
            m_componentEntityOwners(), 
            m_random               ()
        {
            // too much? noooo this is fine, the more the merrier :)
            (std::get<std::vector<TComponents>>(m_components).reserve(1000), ...);
            m_entityComponents                               .reserve(1000);
            m_componentEntityOwners                          .reserve(1000);
        }

    public:
        inline bool EntityExists(EntityUUID entityUUID)
        {
            return m_entityComponents.find(entityUUID) != m_entityComponents.end();
        }

        inline EntityUUID CreateEntity()
        {
            EntityUUID entityUUID = m_random.UInt64();

            m_entityComponents.emplace(entityUUID, TEntityComponents(TComponentBitMask()));

            return entityUUID;
        }

        template <typename TComponent, typename ...TArgs>
        inline TComponent& AddComponent(EntityUUID entityUUID, TArgs... args)
        {
            if (!EntityExists            (entityUUID)) return AddComponent<TComponent>(CreateEntity(), args...);
            if ( HasComponent<TComponent>(entityUUID)) return GetComponent<TComponent>(entityUUID);

            std::vector<TComponent>& components = std::get<std::vector<TComponent>>(m_components);

            ComponentIndex componentIndex = components.size();
            ComponentUUID  componentUUID  = TComponentBitMask::template ComponentUUID<TComponent>(componentIndex);

            components.emplace_back(args...);

            m_entityComponents[entityUUID].AddComponent<TComponent>(componentIndex);

            m_componentEntityOwners[componentUUID] = entityUUID;

            return components[componentIndex];
        }

        template <typename TComponent>
        inline TComponent& GetComponent(EntityUUID entityUUID)
        {
            if (!EntityExists            (entityUUID)) throw std::runtime_error("Entity does not exist");
            if (!HasComponent<TComponent>(entityUUID)) throw std::runtime_error("Entity does not have component");

            std::vector<TComponent>& components = std::get<std::vector<TComponent>>(m_components);

            ComponentIndex componentIndex = m_entityComponents[entityUUID].GetComponentIndex<TComponent>();

            return components[componentIndex];
        }

        template <typename TComponent>
        inline bool HasComponent(EntityUUID entityUUID)
        {
            if (!EntityExists(entityUUID)) return false;

            return m_entityComponents[entityUUID].HasComponent<TComponent>();
        }

        template <typename TComponent>
        inline bool RemoveComponent(EntityUUID entityUUID)
        {
            if (!EntityExists            (entityUUID)) return false;
            if (!HasComponent<TComponent>(entityUUID)) return false;

            std::vector<TComponent>& components = std::get<std::vector<TComponent>>(m_components);

            ComponentIndex componentIndex = m_entityComponents[entityUUID].GetComponentIndex<TComponent>();
            ComponentUUID  componentUUID  = TComponentBitMask::template ComponentUUID<TComponent>(componentIndex);

            components[componentIndex] = components.back();
            components.emplace_back();

            m_entityComponents[entityUUID].RemoveComponent<TComponent>(componentIndex);

            m_componentEntityOwners.erase(componentUUID);

            return true;
        }

        template <typename ...TComponents>
        inline void ForEachEntity(std::function<void(EntityUUID, TComponents&...)> function)
        {
            // TODO: this could be optimized by using m_components
            for (auto& [entityUUID, entityComponents] : m_entityComponents)
            {
                if (entityComponents.HasComponents<TComponents...>())
                {
                    function(entityUUID, GetComponent<TComponents>(entityUUID)...);
                }
            }
        }

        template <typename TComponent>
        inline void ForEachComponent(std::function<void(EntityUUID, TComponent&)> function)
        {
            std::vector<TComponent>& components = std::get<std::vector<TComponent>>(m_components);

            for (ComponentIndex componentIndex = 0; componentIndex < components.size(); componentIndex++)
            {
                ComponentUUID componentUUID = TComponentBitMask::template ComponentUUID<TComponent>(componentIndex);

                if (m_componentEntityOwners.find(componentUUID) != m_componentEntityOwners.end())
                {
                    EntityUUID entityUUID = m_componentEntityOwners[componentUUID];

                    function(entityUUID, components[componentIndex]);
                }
            }
        }

        inline TEntity GetEntity(EntityUUID entityUUID)
        {
            return TEntity(entityUUID, this);
        }

        inline void Reset()
        {
            m_components           = std::tuple<std::vector<TComponents>...>();
            m_entityComponents     .clear();
            m_componentEntityOwners.clear();
        }

    private:
        Random m_random;

        std::tuple        <std::vector<TComponents  >...   > m_components           ;

        std::unordered_map<EntityUUID   , TEntityComponents> m_entityComponents     ;
        std::unordered_map<ComponentUUID, EntityUUID       > m_componentEntityOwners;
    };
}