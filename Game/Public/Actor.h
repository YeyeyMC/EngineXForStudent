#pragma once
#include <type_traits>
#include <memory>
#include "LifetimeInterface.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/ComponentTypes.h"

class Actor : public ILifetimeInterface, public std::enable_shared_from_this<Actor>
{
public:

	Actor();
	virtual ~Actor();
#pragma region ILifeTimeInterface
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Tick(const float DeltaSeconds) override;
#pragma endregion

	

private:

	// Stores all the components
	ComponentList mComponents;

#pragma region TemplateRegion
public:

	//template function that takes any data type that inherits from Component
	template<std::derived_from<Component> ComponentType, typename ...Args>
	//this function returns multiple data types, that's why it returns a tuple
	//...Args is an arbitrary number of arguments
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType(Args... Arguments)
	{
		//this is a raw pointer that references the component we want to add to the actor,
		// that component takes a weak pointer to this actor
		// we use a raw pointer and then a shared pointer because Template functions don't do well with nested
		// data types
		ComponentType* ComponentPtr = new ComponentType(weak_from_this(), Arguments...);
		
		
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*ComponentPtr);
		delete ComponentPtr;

		if (NewComponent->CanAddComponent())
		{
			NewComponent->BeginPlay();
			mComponents.emplace_back(NewComponent);
			return {NewComponent, true, "Component was created successfuly"};
		}
		return { nullptr, false, "Failed to add component" };
	}

	template<std::derived_from<Component> ComponentType>
	std::shared_ptr<ComponentType> GetComponentOfType()
	{
		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			if (std::shared_ptr<ComponentType> FoundComponent = std::dynamic_pointer_cast<ComponentType>(ComponentIterator))
			{
				return FoundComponent;
			}
		}

		return nullptr;
	}

	// TODO: spawn actor class if you want to :p

#pragma endregion
};
