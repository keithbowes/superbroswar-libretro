#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#define RNGMAX(rMaxInt) RandomNumberGenerator::generator().getInteger(rMaxInt)
#define RANDOM_BOOL() RandomNumberGenerator::generator().getBoolean()

class RandomNumberGeneratoreratorType {
public:
    virtual void reseed(unsigned seed);
    virtual int getInteger(int min, int max) = 0;

    // generate uniformly distributed random number
    // rMax is not part of the set
    int getInteger(int rMax);

    bool getBoolean();

    // will return true only if 1/scaleMax is verified
    bool getBoolean(int scaleMax);

    // make a decision using 'scaleMax' steps and 'positiveThreshold' as threshold
    // returns true only when random value is above the threshold
    bool getBoolean(int scaleMax, int positiveThreshold);
};

class RandomNumberGenerator {
public:
    static RandomNumberGeneratoreratorType& generator();

private:
    RandomNumberGenerator();
    ~RandomNumberGenerator();
    RandomNumberGenerator(RandomNumberGenerator const&);
    void operator=(RandomNumberGenerator const&);

    RandomNumberGeneratoreratorType* rng;
};

// default random number generator, using system
class SystemRandomNumberGeneratorerator : public RandomNumberGeneratoreratorType {
public:
    int getInteger(int rMin, int rMax);
};


// default random number generator, using system
class Well512RandomNumberGeneratorerator : public RandomNumberGeneratoreratorType {
private:
    /* initialize state to random bits */
    unsigned state[16];
    /* init should also reset this to 0 */
    unsigned index;

    /* return 32 bit random number */
    unsigned getNext();

    void initialize();
    void initialize(unsigned seed);

public:

    Well512RandomNumberGeneratorerator();
    void reseed(unsigned seed);
    int getInteger(int rMin, int rMax);
};

#endif // RANDOMNUMBERGENERATOR_H
