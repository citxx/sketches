#ifndef RAIN_SYSTEM_HPP
#define RAIN_SYSTEM_HPP

#include "ParticleSystem.hpp"

class RainSystem: public ParticleSystem {
    Vector cloudBegin, cloudEnd;
    Vector wind;

    Particle* createParticle() const;
    bool processParticle(Particle *p) const;

    static const double dropK = 1.08889e-4; // kg/s
    static const double dropMass = 0.0004; // kg

  public:
    RainSystem(double timeQuantum, double genVelocity, Vector cloudBegin, Vector cloudEnd, Vector wind = Vector());

    void moveCloud(const Vector &dr);
};

#endif
