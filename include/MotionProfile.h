#ifndef __BNS_MOTION_PROFILE_H
#define __BNS_MOTION_PROFILE_H

#include "main.h"
#include "math.h"
#include <stdbool.h>

typedef struct MotionProfile
{
	float acceleration;
	float deceleration;

	float startVelocity;
	float maxVelocity;
	float endVelocity;

	float distance;
} MotionProfile;

// MotionProfileInit(...)
// Initate defaults for the motion profile
void MotionProfileInit(struct MotionProfile *profile);

// MotionProfileEasyParams(...)
// Initiate simple params for the motion params
void MotionProfileEasyParams(struct MotionProfile* profile, float accel, float speed, float distance);

// MotionProfileSetDistance(...)
// Sets the desired distance for the motion controller
void MotionProfileSetDistance(struct MotionProfile *profile, float distance);

// MotionProfileSetAccel(...)
// Sets the desired acceleration/deceleration for the motion controller
void MotionProfileSetAccel(struct MotionProfile *profile, float accel, float decel);

// MotionProfileSetVelocity(...)
// Sets the desired velocities for the motion controller
void MotionProfileSetVelocity(struct MotionProfile *profile, float enterVel, float maxVel, float exitVel);

// MotionProfileIsComplete(...)
// Returns true if the motion profile is complete at a given time variable
bool MotionProfileIsComplete(struct MotionProfile *profile, float time);

// MotionProfileCompute(...)
// Given a time input, return the appropriate speed
// Units are entirely arbritrary and should be determined by the user
// This should be used in a loop with a variable that relates to the real world time
float MotionProfileCompute(struct MotionProfile *profile, float time);

// MotionProfilePrint(...)
// Prints to the debug stream what the profile is going to do.
// Set dt to however detailed you want your profile to print as
// For instance, if you are running the profile at 25 times a second
//  set dt to 1/25, or 0.04 to see what it will return
// Note: This function will take a long time to print, only use it for
//  debugging
void MotionProfilePrint(struct MotionProfile* profile, float dt);

float _MotionProfileCheckParameters(struct MotionProfile* profile);

float _MotionProfileDetermineExchangeTime(struct MotionProfile *profile);

float _MotionProfileGetVelocityWithoutMaxVelocity(struct MotionProfile *profile, float time, bool *isComplete);

float _MotionProfileGetVelocityWithMaxVelocity(struct MotionProfile *profile, float time, bool *isComplete);

#endif
