#pragma once

#include <chrono>
#include "System/Macros.h"
#include "App/GlobalStates.h"

// Base interface for app components.
class IAppComponent
{
protected:
	std::chrono::milliseconds DeltaTime = std::chrono::milliseconds(TICK_MS);

public:
	virtual std::chrono::milliseconds GetDeltaTime() const { return DeltaTime; }
	virtual void SetDeltaTime(std::chrono::milliseconds deltaTime) { DeltaTime = deltaTime; }

public:
	virtual void Tick() = 0;
	virtual void Start() = 0;

public:
	virtual AppState GetCorrespondingAppState() const = 0;
};