#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <vector>
#include <ostream>

#include "Vector.hpp"

struct Particle {
    Vector r; // Radius-vector
    Vector v; // Velocity
    double m; // Mass
    double bornTime;
    Particle *next; // For Particle system
};

class ParticleSystem {
    Particle *first;
    int count;

    double timeQuantum;
    double t;
    double accumulatedTime;
    double accumulatedParticles;
    double genVelocity;

    void removeParticle(Particle *p);
    void addParticle(Particle *p);
    void clearList();
    void copyList(Particle *p);
    void copyAll(const ParticleSystem &sys);

    virtual Particle* createParticle() const = 0;
    virtual bool processParticle(Particle *p) const = 0; // To remove or not to remove a particle

  protected:
    static const double G = 6.673e-11; // N*(m/s)^2
    static const double earthRadius = 6.4e6; // m
    static const double earthMass = 5.9742e24; // kg

  public:
    ParticleSystem(double timeQuantum, double genVelocity);
    ParticleSystem(const ParticleSystem &sys);
    ~ParticleSystem();

    ParticleSystem& operator =(const ParticleSystem &sys);

    void process(double dt);
    std::vector <Vector> getCoordinates() const;
    std::vector <Vector> getVelocities() const;
    double getTime() const;
    double getQuant() const;
    int getCount() const;

    friend std::ostream& operator <<(std::ostream &out, const ParticleSystem &sys);
};

std::ostream& operator <<(std::ostream &out, const ParticleSystem &sys);

#endif
