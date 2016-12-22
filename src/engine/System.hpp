#pragma once

#include "Types.hpp"
#include "NonCopyable.hpp"
#include "Entity.hpp"

#include <cassert>
#include <utility>
#include <unordered_map>

namespace lp {

  class SystemManager;
  class BaseSystem : NonCopyable {
    public:
      typedef int32 Type;

      virtual ~BaseSystem() {}

      virtual void awake() {}
      virtual void update(float dt, float sec) {}
      virtual void render(float dt, float sec) {}
      virtual void freeze() {}

      virtual void onEntitySpawn(Entity* ent) {}
      virtual void onEntityRemove(Entity* ent) {}

      static Type nextType;
  };

  template <typename Derived>
  class System : public BaseSystem {
    public:
      virtual ~System() {}

    private:
      friend class SystemManager;

      static Type type() {
        static Type type = nextType++;
        return type;
      }
  };

  class SystemManager : NonCopyable {
    public:
      virtual ~SystemManager() {
        for (auto p: this->systems) {
          delete p.second;
        }
        this->systems.clear();
      }

      template <typename S>
      S* system() {
        auto it = systems.find(S::type());
        assert(it != systems.end());
        return it == systems.end() ? nullptr : static_cast<S*>(it->second);
      }

      template <typename S>
      SystemManager& addSystem(S* system) {
        this->systems.insert(std::make_pair(S::type(), system));

        return *this;
      }

      template <typename S, typename ... Args>
      SystemManager& addSystem(Args && ... args) {
        return this->addSystem(new S(std::forward<Args>(args) ...));
      }

    protected:
      std::unordered_map<BaseSystem::Type, BaseSystem*> systems;
  };

}
