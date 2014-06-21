#include <cassert>
#include <climits>
#include <cstdlib>
#include <ctime>

#include "RandomNumberGenerator.h"

//
// ABSTRACT RNG CLASS
//

void RandomNumberGeneratoreratorType::reseed(unsigned seed)
{
    srand(seed);
}

// generate uniformly distributed random number
// rMax is not part of the set
int RandomNumberGeneratoreratorType::getInteger(int rMax)
{
    return getInteger(0, rMax);
}

bool RandomNumberGeneratoreratorType::getBoolean()
{
    return getBoolean(2);
}

// will return true only if 1/scaleMax is verified
bool RandomNumberGeneratoreratorType::getBoolean(int scaleMax)
{
    // maybe we shall match center of range, like (scaleMax/2 - 1) ?
    return 0 == getInteger(scaleMax);
}

// make a decision using 'scaleMax' steps and 'positiveThreshold' as threshold
// returns true only when random value is above the threshold
bool RandomNumberGeneratoreratorType::getBoolean(int scaleMax, int positiveThreshold)
{
    assert(positiveThreshold < scaleMax && positiveThreshold >= 0);
    return getInteger(scaleMax) > positiveThreshold;
}

//
// GLOBAL ACCESS
//

RandomNumberGenerator::RandomNumberGenerator() {
    rng = new Well512RandomNumberGeneratorerator();
}

RandomNumberGenerator::~RandomNumberGenerator() {
    delete rng;
}

RandomNumberGeneratoreratorType& RandomNumberGenerator::generator() {
    static RandomNumberGenerator grng;
    return *(grng.rng);
}

//
// SYSTEM RNG
//

// default random number generator, using system
int SystemRandomNumberGeneratorerator::getInteger(int rMin, int rMax)
{
    assert(rMax > rMin);
    int rVal = ((double) rand() / (((float)RAND_MAX)+1)) * (rMax-rMin) + rMin;
    assert(rVal < rMax && rVal >= rMin);
    return rVal;
}

//
// WELL512 RNG
//

// we initialize the state with (supposedly) true random numbers coming from the system
// this constitutes a good enough seed
unsigned Well512RandomNumberGeneratorerator::getNext()
{
   unsigned a, b, c, d;
   a = state[index];
   c = state[(index+13)&15];
   b = a^c^(a<<16)^(c<<15);
   c = state[(index+9)&15];
   c ^= (c>>11);
   a = state[index] = b^c;
   d = a^((a<<5)&0xDA442D20UL);
   index = (index + 15)&15;
   a = state[index];
   state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
   return state[index];
}

void Well512RandomNumberGeneratorerator::initialize()
{
    index = 0;
    srand(time(0));
    for (int i =0; i < 16; i++) {
        state[i] = rand();
    }
}

void Well512RandomNumberGeneratorerator::initialize(unsigned seed)
{
    assert(sizeof(unsigned) == 4);

    index = 0;
    state[0] = seed;
    for (int i = 1; i < 16; i++)
        // see Linear congruential generator
        state[i] = ((state[i-1] * 1103515245) + 12345) & 0x7fffffff;
}

// we initialize the state with (supposedly) true random numbers coming from the system
// this constitutes a good enough seed
Well512RandomNumberGeneratorerator::Well512RandomNumberGeneratorerator()
{
    initialize();
}

void Well512RandomNumberGeneratorerator::reseed(unsigned seed)
{
    initialize(seed);
}

int Well512RandomNumberGeneratorerator::getInteger(int rMin, int rMax)
{
    assert(rMax > rMin);
    int rVal = ((double) getNext() / (((float)UINT_MAX)+1)) * (rMax-rMin) + rMin;
    assert(rVal < rMax && rVal >= rMin);
    return rVal;
}
