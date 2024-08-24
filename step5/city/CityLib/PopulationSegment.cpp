/**
 * @file PopulationSegment.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PopulationSegment.h"

/**
 * Constructor
 */
PopulationSegment::PopulationSegment()
{
}


/**
 * Determine how many population members are going to be removed in time.
 * @param elapsed Elapsed time that has occured
 * @return Number of removed population members
 */
int PopulationSegment::Remove(double elapsed)
{
    // Apply any loss acceleration
    if(mExponential)
    {
        mLossRate *= pow(mLossAcceleration, elapsed);
    }
    else
    {
        mLossRate += mLossAcceleration * elapsed;
    }

    // Increment the amount of loss and remove the integral part
    mFractionalLoss += mLossRate * elapsed;
    int loss = (int)mFractionalLoss;
    mFractionalLoss -= loss;

    if(loss > mCurrent)
    {
        // Cannot lose more than we have
        loss = mCurrent;
    }

    // And lose them
    mCurrent -= loss;

    return loss;
}

/**
 * Set all parameters of the population
 * @param current Current population
 * @param lossRate Loss rate in people per second
 * @param lossAcceleration Loss acceleration in people per second per second
 * @param exponential If true, acceleration is exponential
 */
void PopulationSegment::Set(int current, double lossRate, double lossAcceleration, bool exponential)
{
    mCurrent = current;
    mLossRate = lossRate;
    mLossAcceleration = lossAcceleration;
    mExponential = exponential;
    mFractionalLoss = 0;
}

/**
 * Add to the population
 * @param add Number of people to add
 */
void PopulationSegment::Add(int add)
{
    mCurrent += add;
}
