#include "RainSystem.hpp"

#include <iostream> // TO REMOVE
#include <cstdlib>

RainSystem::RainSystem(double timeQuantum, double genVelocity, Vector cloudBegin, Vector cloudEnd, Vector wind):
    ParticleSystem(timeQuantum, genVelocity),
    cloudBegin(cloudBegin),
    cloudEnd(cloudEnd),
    wind(wind) {
}

Particle* RainSystem::createParticle() const {
    double r1 = (double)rand()/RAND_MAX;
    double r2 = (double)rand()/RAND_MAX;
    double r3 = (double)rand()/RAND_MAX;
    Vector diff = this->cloudEnd - this->cloudBegin;
    Vector position =  this->cloudBegin + Vector(r1*diff.x, r2*diff.y, r3*diff.z);

    Particle *result = new Particle;
    result->r = position;
    result->v = Vector();
    result->m = RainSystem::dropMass*(1.00 + 0.5*((double)rand()/RAND_MAX - 0.5)); // kg
    result->bornTime = this->getTime();
    return result;
}

bool RainSystem::processParticle(Particle *p) const {
    if (p->r.z < 0) {
        return true;
    }
    else {
        double G = ParticleSystem::G;
        double M = ParticleSystem::earthMass;
        double R = ParticleSystem::earthRadius;
        Vector aGrav = Vector(0, 0, -G*M/(R*R));

        Vector v = p->v - this->wind;
        double k = RainSystem::dropK;
        Vector aAir = -k/p->m * v;

        Vector a = aGrav + aAir;

        p->v += this->getQuant()*a;
        p->r += this->getQuant()*p->v;

        return false;
    }
}

void RainSystem::moveCloud(const Vector &dr) {
    this->cloudBegin += dr;
    this->cloudEnd   += dr;
}
