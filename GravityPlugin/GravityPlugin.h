#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#pragma comment( lib, "bakkesmod.lib" )

class GravityPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	Vector gravity;
public:
	virtual void onLoad();
	virtual void onUnload();
	void OnChangeActive(std::string oldValue, CVarWrapper cvar);
	void UpdateGravity(std::string oldValue, CVarWrapper cvar);
	void ApplyGravity(std::string eventName);
};