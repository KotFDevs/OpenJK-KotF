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

// Clone Weapon

#include "cg_headers.h"

#include "cg_local.h"
#include "cg_media.h"
#include "FxScheduler.h"

/*
-------------------------
FX_CloneProjectileThink
-------------------------
*/

void FX_CloneProjectileThink(centity_t *cent, const struct weaponInfo_s *weapon)
{
	vec3_t forward;

	if (cent->currentState.eFlags & EF_USE_ANGLEDELTA)
	{
		AngleVectors(cent->currentState.angles, forward, 0, 0);
	}
	else
	{
		if (VectorNormalize2(cent->gent->s.pos.trDelta, forward) == 0.0f)
		{
			if (VectorNormalize2(cent->currentState.pos.trDelta, forward) == 0.0f)
			{
				forward[2] = 1.0f;
			}
		}
	}

	// hack the scale of the forward vector if we were just fired or bounced...this will shorten up the tail for a split second so tails don't clip so harshly
	int dif = cg.time - cent->gent->s.pos.trTime;

	if (dif < 75)
	{
		if (dif < 0)
		{
			dif = 0;
		}

		float scale = (dif / 75.0f) * 0.95f + 0.05f;

		VectorScale(forward, scale, forward);
	}

	theFxScheduler.PlayEffect(cgs.effects.cloneShotEffect, cent->lerpOrigin, forward);

}

/*
-------------------------
FX_CloneAltFireThink
-------------------------
*/
void FX_CloneAltFireThink(centity_t *cent, const struct weaponInfo_s *weapon)
{
	FX_CloneProjectileThink(cent, weapon);
}

/*
-------------------------
FX_CloneWeaponHitWall
-------------------------
*/
void FX_CloneWeaponHitWall(vec3_t origin, vec3_t normal)
{
	theFxScheduler.PlayEffect(cgs.effects.cloneWallImpactEffect, origin, normal);
}

/*
-------------------------
FX_CloneWeaponHitPlayer
-------------------------
*/
void FX_CloneWeaponHitPlayer(gentity_t *hit, vec3_t origin, vec3_t normal, qboolean humanoid)
{
	//temporary? just testing out the damage skin stuff -rww
	if (hit && hit->client && hit->ghoul2.size())
	{
		CG_AddGhoul2Mark(cgs.media.bdecal_burnmark1, flrand(3.5, 4.0), origin, normal, hit->s.number,
			hit->client->ps.origin, hit->client->renderInfo.legsYaw, hit->ghoul2, hit->s.modelScale, Q_irand(10000, 13000));
	}

	theFxScheduler.PlayEffect(cgs.effects.cloneFleshImpactEffect, origin, normal);
}

/*
-------------------------
FX_CloneAltProjectileThink
-------------------------
*/

void FX_CloneAltProjectileThink(centity_t *cent, const struct weaponInfo_s *weapon)
{
	vec3_t forward;

	if (VectorNormalize2(cent->gent->s.pos.trDelta, forward) == 0.0f)
	{
		if (VectorNormalize2(cent->currentState.pos.trDelta, forward) == 0.0f)
		{
			forward[2] = 1.0f;
		}
	}

	// hack the scale of the forward vector if we were just fired or bounced...this will shorten up the tail for a split second so tails don't clip so harshly
	int dif = cg.time - cent->gent->s.pos.trTime;

	if (dif < 75)
	{
		if (dif < 0)
		{
			dif = 0;
		}

		float scale = (dif / 75.0f) * 0.95f + 0.05f;

		VectorScale(forward, scale, forward);
	}

	// see if we have some sort of extra charge going on
	for (int t = 1; t < cent->gent->count; t++)
	{
		// just add ourselves over, and over, and over when we are charged
		theFxScheduler.PlayEffect(cgs.effects.clonePowerupShotEffect, cent->lerpOrigin, forward);
	}

	theFxScheduler.PlayEffect(cgs.effects.cloneShotEffect, cent->lerpOrigin, forward);
}

/*
-------------------------
FX_CloneAltHitWall
-------------------------
*/
void FX_CloneAltHitWall(vec3_t origin, vec3_t normal, int power)
{
	switch (power)
	{
	case 4:
	case 5:
		theFxScheduler.PlayEffect(cgs.effects.cloneWallImpactEffect3, origin, normal);
		break;

	case 2:
	case 3:
		theFxScheduler.PlayEffect(cgs.effects.cloneWallImpactEffect2, origin, normal);
		break;

	default:
		theFxScheduler.PlayEffect(cgs.effects.cloneWallImpactEffect, origin, normal);
		break;
	}
}

/*
-------------------------
FX_CloneAltHitPlayer
-------------------------
*/
void FX_CloneAltHitPlayer(vec3_t origin, vec3_t normal, qboolean humanoid)
{
	theFxScheduler.PlayEffect(cgs.effects.cloneFleshImpactEffect, origin, normal);
}
