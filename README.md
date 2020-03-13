# GravityPlugin
Custom gravity plugin for BakkesMod. Allows changing gravity in any direction. (Can also change strength)

## Installation

1. Copy `GravityPlugin.dll` to `<steam_directory>/steamapps/common/rocketleague/Binaries/Win32/bakkesmod/plugins`
2. Copy `gravityplugin.set` to `<steam_directory>/steamapps/common/rocketleague/Binaries/Win32/bakkesmod/plugins/settings`
3. Add `plugin load gravityplugin` to `<steam_directory>/steamapps/common/rocketleague/Binaries/Win32/bakkesmod/cfg/plugins.cfg`

## Commands

**gravity_on** [0|1] - turn custom gravity on/off

**gravity_strength** - Set the gravity strength (default: 650)

**gravity_ball_strength** - Multiplier for ball gravity relative to car (default: 1.0)

**gravity_polar** - Set the polar angle for the gravity direction.

**gravity_azimuth** - Set the azimuth angle for the gravity direction.

If you don't understand these angles, check out https://en.wikipedia.org/wiki/Spherical_coordinate_system

