/**
 * @file PopulationSegment.h
 * @author Charles Owen
 *
 * Way to keep track of population segment and move them
 * around over time. This simulates things like
 * a population becoming infected or a population
 * leaving an area.
 */

#ifndef CITY_POPULATIONSEGMENT_H
#define CITY_POPULATIONSEGMENT_H

/**
 * Way to keep track of population segment and move them
 * around over time. This simulates things like
 * a population becoming infected or a population
 * leaving an area.
 */
class PopulationSegment {
private:
    /// The current population
    int mCurrent = 0;

    /// A fractional amount of a person
    /// pending removal.
    double mFractionalLoss = 0;

    /// Population loss rate in people per second
    double mLossRate = 1.0;

    /// Loss rate growth in people per second per second
    double mLossAcceleration = 0;

    /// Is the acceleration exponential?
    bool mExponential = false;

public:
    PopulationSegment();

    void Set(int current=0, double lossRate=1, double lossAcceleration=0,
            bool exponential=false);

    /**
     * Get the current population
     * @return Population (integral amount)
     */
    int GetCount() {return mCurrent;}

    int Remove(double elapsed);

    void Add(int add);
};

#endif //CITY_POPULATIONSEGMENT_H
