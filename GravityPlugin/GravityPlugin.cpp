#include "GravityPlugin.h"
#define _USE_MATH_DEFINES
#include <math.h>

BAKKESMOD_PLUGIN(GravityPlugin, "Custom gravity plugin", "1.0", PLUGINTYPE_FREEPLAY)

void GravityPlugin::onLoad()
{
	cvarManager->registerCvar("gravity_on", "0", "Determines if the custom gravity is turned on.", true, true, 0, true, 1, false).addOnValueChanged(std::bind(&GravityPlugin::OnChangeActive, this, std::placeholders::_1, std::placeholders::_2));
	cvarManager->registerCvar("gravity_strength", "650", "Determines the strength of custom gravity.", true, true, 0.0f, true, 5000.0f, true).addOnValueChanged(std::bind(&GravityPlugin::UpdateGravity, this, std::placeholders::_1, std::placeholders::_2));
	cvarManager->registerCvar("gravity_ball_strength", "1", "Determines the strength multiplier of custom gravity effect on the ball only.", true, true, 0.0f, true, 10.0f, true).addOnValueChanged(std::bind(&GravityPlugin::UpdateGravity, this, std::placeholders::_1, std::placeholders::_2));
	cvarManager->registerCvar("gravity_azimuth", "0", "Gravity direction azimuth angle.", true, true, 0.0f, true, 360.0f, true).addOnValueChanged(std::bind(&GravityPlugin::UpdateGravity, this, std::placeholders::_1, std::placeholders::_2));
	cvarManager->registerCvar("gravity_polar", "180", "Gravity direction polar angle.", true, true, 0.0f, true, 180.0f, true).addOnValueChanged(std::bind(&GravityPlugin::UpdateGravity, this, std::placeholders::_1, std::placeholders::_2));
	cvarManager->getCvar("gravity_strength").notify();
}

void GravityPlugin::onUnload()
{
}

void GravityPlugin::OnChangeActive(std::string oldValue, CVarWrapper cvar)
{
	if (oldValue.compare("0") == 0 && cvar.getBoolValue())
	{
		gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", bind(&GravityPlugin::ApplyGravity, this, std::placeholders::_1));
		cvarManager->getCvar("sv_soccar_gravity").setValue(0.000001f);
	}
	else if (oldValue.compare("1") == 0 && !cvar.getBoolValue())
	{
		gameWrapper->UnhookEvent("Function TAGame.Car_TA.SetVehicleInput");
		cvarManager->getCvar("sv_soccar_gravity").setValue(-650.f);
	}
}

void GravityPlugin::UpdateGravity(std::string oldValue, CVarWrapper cvar)
{
	float tickrate = 120.0f;
	float r = cvarManager->getCvar("gravity_strength").getFloatValue() / tickrate;
	float theta = cvarManager->getCvar("gravity_polar").getFloatValue() * M_PI / 180.0f;
	float phi = cvarManager->getCvar("gravity_azimuth").getFloatValue() * M_PI / 180.0f;
	float x = r * sin(theta) * cos(phi);
	float y = r * sin(theta) * sin(phi);
	float z = r * cos(theta);
	gravity = { x, y, z };
	float ball_mult = cvarManager->getCvar("gravity_ball_strength").getFloatValue();
	gravity_ball = { x * ball_mult, y * ball_mult, z * ball_mult };
}

void GravityPlugin::ApplyGravity(std::string eventName)
{
	if (!gameWrapper->IsInGame())
		return;
	auto server = gameWrapper->GetGameEventAsServer();

	auto cars = server.GetCars();
	auto car = cars.Get(0);

	auto velocity = car.GetVelocity();
	car.AddVelocity(gravity);
	auto ball = server.GetBall();
	if (ball.IsNull())
		return;
	ball.AddVelocity(gravity_ball);
}
