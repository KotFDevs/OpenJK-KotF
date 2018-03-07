/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

// bg_weapons.c -- part of bg_pmove functionality

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"

// Muzzle point table...
vec3_t WP_MuzzlePoint[WP_NUM_WEAPONS] =
{//	Fwd,	right,	up.
	{0,		0,		0	},	// WP_NONE,
	{0	,	8,		0	},	// WP_STUN_BATON,
	{0	,	8,		0	},	// WP_MELEE,
	{8	,	16,		0	},	// WP_SABER,
	{12,	6,		-6	},	// WP_BRYAR_PISTOL,
	{12,	6,		-6	},	// WP_BLASTER,
	{12,	6,		-6	},	// WP_DISRUPTOR,
	{12,	2,		-6	},	// WP_BOWCASTER,
	{12,	4.5,	-6	},	// WP_REPEATER,
	{12,	6,		-6	},	// WP_DEMP2,
	{12,	6,		-6	},	// WP_FLECHETTE,
	{12,	8,		-4	},	// WP_ROCKET_LAUNCHER,
	{12,	0,		-4	},	// WP_THERMAL,
	{12,	0,		-10	},	// WP_TRIP_MINE,
	{12,	0,		-4	},	// WP_DET_PACK,
	{12,	6,		-6	},	// WP_CONCUSSION
	{12,	6,		-6	},	// WP_BRYAR_OLD,
	{12,	6,		-6	},	// WP_BATTLEDROID,
	{12,	6,		-6	},	// WP_THEFIRSTORDER,
	{12,	6,		-6	},	// WP_CLONECARBINE,
	{12,	6,		-6	},	// WP_REBELBLASTER,
	{12,	6,		-6	},	// WP_CLONERIFLE,
	{12,	6,		-6	},	// WP_CLONECOMMANDO,
	{12,	6,		-6	},	// WP_REBELRIFLE,
	{12,	6,		-6	},	// WP_REY,
	{12,	6,		-6	},	// WP_JANGO,
	{12,	6,		-6	},	// WP_BOBA,
	{12,	6,		-6	},	// WP_CLONEPISTOL,
};

weaponData_t weaponData[WP_NUM_WEAPONS] =
{
	{	// WP_NONE
//		"No Weapon",			//	char	classname[32];		// Spawning name
		AMMO_NONE,				//	int		ammoIndex;			// Index to proper ammo slot
		0,						//	int		ammoLow;			// Count when ammo is low
		0,						//	int		energyPerShot;		// Amount of energy used per shot
		0,						//	int		fireTime;			// Amount of time between firings
		0,						//	int		range;				// Range of weapon
		0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		0,						//	int		altFireTime;		// Amount of time between alt-firings
		0,						//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_STUN_BATON
//		"Stun Baton",			//	char	classname[32];		// Spawning name
		AMMO_NONE,				//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		0,						//	int		energyPerShot;		// Amount of energy used per shot
		350,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		350,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_MELEE
//		"Melee",			//	char	classname[32];		// Spawning name
		AMMO_NONE,				//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		0,						//	int		energyPerShot;		// Amount of energy used per shot
		400,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		400,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_SABER,
//		"Lightsaber",			//	char	classname[32];		// Spawning name
		AMMO_NONE,				//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		0,						//	int		energyPerShot;		// Amount of energy used per shot
		100,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		100,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BRYAR_PISTOL,
//		"Bryar Pistol",				//	char	classname[32];		// Spawning name
		AMMO_BLASTER,				//	int		ammoIndex;			// Index to proper ammo slot
		0,//15,						//	int		ammoLow;			// Count when ammo is low
		0,//2,						//	int		energyPerShot;		// Amount of energy used per shot
		720,//400,					//	int		fireTime;			// Amount of time between firings
		8192,						//	int		range;				// Range of weapon
		0,//2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		660,//400,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,						//	int		altRange;			// Range of alt-fire
		0,							//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,//200,					//	int		altChargeSubTime;	// above for secondary
		0,							//	int		chargeSub;			// amount to subtract during charge on each interval
		0,//1,						//	int		altChargeSub;		// above for secondary
		0,							//	int		maxCharge;			// stop subtracting once charged for this many ms
		0,//1500					//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BLASTER
//		"E11 Blaster Rifle",	//	char	classname[32];		// Spawning name
		AMMO_BLASTER,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		350,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		150,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_DISRUPTOR
//		"Tenloss Disruptor Rifle",//	char	classname[32];		// Spawning name
		AMMO_POWERCELL,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		3,						//	int		energyPerShot;		// Amount of energy used per shot
		840,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		3,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		880,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		200,					//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		3,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		1700					//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BOWCASTER
//		"Wookiee Bowcaster",		//	char	classname[32];		// Spawning name
		AMMO_POWERCELL,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		2,						//	int		energyPerShot;		// Amount of energy used per shot
		390,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		3,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		750,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		400,					//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		5,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		1700,					//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_REPEATER
//		"Imperial Heavy Repeater",//	char	classname[32];		// Spawning name
		AMMO_METAL_BOLTS,		//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		105,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		15,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		1000,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_DEMP2
//		"DEMP2",				//	char	classname[32];		// Spawning name
		AMMO_POWERCELL,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		4,						//	int		energyPerShot;		// Amount of energy used per shot
		500,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		6,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		1000,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		250,					//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		3,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		2100					//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_FLECHETTE
//		"Golan Arms Flechette",	//	char	classname[32];		// Spawning name
		AMMO_METAL_BOLTS,		//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		8,						//	int		energyPerShot;		// Amount of energy used per shot
		650,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		10,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		800,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_ROCKET_LAUNCHER
//		"Merr-Sonn Missile System",	//	char	classname[32];		// Spawning name
		AMMO_ROCKETS,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		1100,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		1,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		1100,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_THERMAL
//		"Thermal Detonator",	//	char	classname[32];		// Spawning name
		AMMO_THERMAL,				//	int		ammoIndex;			// Index to proper ammo slot
		0,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		600,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		1,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		400,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_TRIP_MINE
//		"Trip Mine",			//	char	classname[32];		// Spawning name
		AMMO_TRIPMINE,				//	int		ammoIndex;			// Index to proper ammo slot
		0,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		1000,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		1,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		800,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_DET_PACK
//		"Det Pack",				//	char	classname[32];		// Spawning name
		AMMO_DETPACK,				//	int		ammoIndex;			// Index to proper ammo slot
		0,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		1000,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		300,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_CONCUSSION
//		"Concussion Rifle",		//	char	classname[32];		// Spawning name
		AMMO_METAL_BOLTS,		//	int		ammoIndex;			// Index to proper ammo slot
		40,						//	int		ammoLow;			// Count when ammo is low
		20,						//	int		energyPerShot;		// Amount of energy used per shot
		1000,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		22,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		1000,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BRYAR_OLD,
//		"Bryar Pistol",			//	char	classname[32];		// Spawning name
		AMMO_BLASTER,			//	int		ammoIndex;			// Index to proper ammo slot
		15,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		400,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		1,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		400,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		200,					//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		1,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		1500					//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BATTLEDROID,
//		"E-5 Carbine",			//	char	classname[32];		// Spawning name
		AMMO_BLASTER,			//	int		ammoIndex;			// Index to proper ammo slot
		5,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		300,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		140,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,						//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		0,						//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		0						//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_THEFIRSTORDER,
//		"F-11D",				//	char	classname[32];		// Spawning name
	  AMMO_BLASTER,				//	int		ammoIndex;			// Index to proper ammo slot
	  5,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  330,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  150,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_CLONECARBINE,
	//		"DC-15 Carbine",			//	char	classname[32];		// Spawning name
	  AMMO_METAL_BOLTS,			//	int		ammoIndex;			// Index to proper ammo slot
	  5,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  370,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  170,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_REBELBLASTER,
	//		"DH-17",			//	char	classname[32];		// Spawning name
	  AMMO_BLASTER,				//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  380,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  3,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  200,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_CLONERIFLE,
	//		"DC-15 Rifle",			//	char	classname[32];		// Spawning name
	  AMMO_METAL_BOLTS,			//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  230,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  85,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_CLONECOMMANDO,
	//		"DC-17M",			//	char	classname[32];		// Spawning name
	  AMMO_METAL_BOLTS,			//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  2,						//	int		energyPerShot;		// Amount of energy used per shot
	  280,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  3,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  210,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_REBELRIFLE,
	//		"A280",			//	char	classname[32];		// Spawning name
	  AMMO_POWERCELL,			//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  2,						//	int		energyPerShot;		// Amount of energy used per shot
	  370,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  3,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  240,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_REY,
	//		"LPA NN-14",			//	char	classname[32];		// Spawning name
		AMMO_BLASTER,			//	int		ammoIndex;			// Index to proper ammo slot
		15,						//	int		ammoLow;			// Count when ammo is low
		1,						//	int		energyPerShot;		// Amount of energy used per shot
		600,					//	int		fireTime;			// Amount of time between firings
		8192,					//	int		range;				// Range of weapon
		2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		800,					//	int		altFireTime;		// Amount of time between alt-firings
		8192,					//	int		altRange;			// Range of alt-fire
		0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		200,//200,				//	int		altChargeSubTime;	// above for secondary
		0,						//	int		chargeSub;			// amount to subtract during charge on each interval
		1,//1,					//	int		altChargeSub;		// above for secondary
		0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
		1800,//1500				//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_JANGO,
	//		"Westar 34",			//	char	classname[32];		// Spawning name
	  AMMO_BLASTER,				//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  330,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  200,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  200,//200,				//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  1,//1,					//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  1200,//1500				//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_BOBA,
	//		"EE-3",				//	char	classname[32];		// Spawning name
	  AMMO_POWERCELL,			//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  2,						//	int		energyPerShot;		// Amount of energy used per shot
	  380,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  12,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  950,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  0,						//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  0,						//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_CLONEPISTOL,
	//		"DC-17 Hand Pistol",			//	char	classname[32];		// Spawning name
	  AMMO_METAL_BOLTS,			//	int		ammoIndex;			// Index to proper ammo slot
	  15,						//	int		ammoLow;			// Count when ammo is low
	  1,						//	int		energyPerShot;		// Amount of energy used per shot
	  450,						//	int		fireTime;			// Amount of time between firings
	  8192,						//	int		range;				// Range of weapon
	  2,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
	  600,						//	int		altFireTime;		// Amount of time between alt-firings
	  8192,						//	int		altRange;			// Range of alt-fire
	  0,						//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
	  200,//200,				//	int		altChargeSubTime;	// above for secondary
	  0,						//	int		chargeSub;			// amount to subtract during charge on each interval
	  1,//1,					//	int		altChargeSub;		// above for secondary
	  0,						//	int		maxCharge;			// stop subtracting once charged for this many ms
	  1500,//1500				//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_EMPLCACED_GUN
//		"Emplaced Gun",				//	char	classname[32];		// Spawning name
		/*AMMO_BLASTER*/0,			//	int		ammoIndex;			// Index to proper ammo slot
		/*5*/0,						//	int		ammoLow;			// Count when ammo is low
		/*2*/0,						//	int		energyPerShot;		// Amount of energy used per shot
		100,						//	int		fireTime;			// Amount of time between firings
		8192,						//	int		range;				// Range of weapon
		/*3*/0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		100,						//	int		altFireTime;		// Amount of time between alt-firings
		8192,						//	int		altRange;			// Range of alt-fire
		0,							//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,							//	int		altChargeSubTime;	// above for secondary
		0,							//	int		chargeSub;			// amount to subtract during charge on each interval
		0,							//	int		altChargeSub;		// above for secondary
		0,							//	int		maxCharge;			// stop subtracting once charged for this many ms
		0							//	int		altMaxCharge;		// above for secondary
	},
	{	// WP_TURRET - NOTE NOT ACTUALLY USEABLE BY PLAYER!
//		"Emplaced Gun",			//	char	classname[32];		// Spawning name
		/*AMMO_BLASTER*/0,			//	int		ammoIndex;			// Index to proper ammo slot
		/*5*/0,						//	int		ammoLow;			// Count when ammo is low
		/*2*/0,						//	int		energyPerShot;		// Amount of energy used per shot
		0,							//	int		fireTime;			// Amount of time between firings
		0,							//	int		range;				// Range of weapon
		/*3*/0,						//	int		altEnergyPerShot;	// Amount of energy used for alt-fire
		0,							//	int		altFireTime;		// Amount of time between alt-firings
		0,							//	int		altRange;			// Range of alt-fire
		0,							//	int		chargeSubTime;		// ms interval for subtracting ammo during charge
		0,							//	int		altChargeSubTime;	// above for secondary
		0,							//	int		chargeSub;			// amount to subtract during charge on each interval
		0,							//	int		altChargeSub;		// above for secondary
		0,							//	int		maxCharge;			// stop subtracting once charged for this many ms
		0							//	int		altMaxCharge;		// above for secondary
	}
};

ammoData_t ammoData[AMMO_MAX] =
{
	{	// AMMO_NONE
//		"",				//	char	icon[32];	// Name of ammo icon file
		0				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_FORCE
//		"",				//	char	icon[32];	// Name of ammo icon file
		100				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_BLASTER
//		"",				//	char	icon[32];	// Name of ammo icon file
		300				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_POWERCELL
//		"",				//	char	icon[32];	// Name of ammo icon file
		300				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_METAL_BOLTS
//		"",				//	char	icon[32];	// Name of ammo icon file
		300				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_ROCKETS
//		"",				//	char	icon[32];	// Name of ammo icon file
		25				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_EMPLACED
//		"",				//	char	icon[32];	// Name of ammo icon file
		800				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_THERMAL
//		"",				//	char	icon[32];	// Name of ammo icon file
		10				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_TRIPMINE
//		"",				//	char	icon[32];	// Name of ammo icon file
		10				//	int		max;		// Max amount player can hold of ammo
	},
	{	// AMMO_DETPACK
//		"",				//	char	icon[32];	// Name of ammo icon file
		10				//	int		max;		// Max amount player can hold of ammo
	}
};
