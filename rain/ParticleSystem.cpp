#include "ParticleSystem.hpp"
#include <cmath>

ParticleSystem::ParticleSystem(double timeQuantum, double genVelocity):
    first(new Particle),
    count(0),
    timeQuantum(timeQuantum),
    t(0.0),
    accumulatedTime(0.0),
    accumulatedParticles(0.0),
    genVelocity(genVelocity) {
}

ParticleSystem::ParticleSystem(const ParticleSystem &sys) {
    copyAll(sys);
}

ParticleSystem::~ParticleSystem() {
    this->clearList();
}

void ParticleSystem::copyList(Particle *p) {
    if (p == NULL) {
        this->first = NULL;
    }
    else {
        this->first = new Particle(*p);
        Particle *src = p;
        Particle *dst = first;
        while (src->next != NULL) {
            src = src->next;
            dst->next = new Particle(*src);
            dst = dst->next;
        }
    }
}

void ParticleSystem::removeParticle(Particle *p) {
    if (p->next != NULL) {
        Particle *tmp = p->next;
        *p = *p->next;
        delete tmp;
        this->count -= 1;
    }
}

void ParticleSystem::addParticle(Particle *p) {
    p->next = this->first;
    this->first = p;
    this->count += 1;
}

void ParticleSystem::clearList() {
    Particle *p = this->first;
    while (p->next != NULL) {
        removeParticle(p);
    }
    delete p;
}

void ParticleSystem::copyAll(const ParticleSystem &sys) {
    this->timeQuantum = sys.timeQuantum;
    this->t = sys.t;
    this->accumulatedTime = sys.accumulatedTime;
    this->accumulatedParticles = sys.accumulatedParticles;
    this->genVelocity = sys.genVelocity;
    this->copyList(sys.first);
    this->count = sys.count;
}

ParticleSystem& ParticleSystem::operator =(const ParticleSystem &sys) {
    this->clearList();
    this->copyAll(sys);
    return *this;
}

void ParticleSystem::process(double dt) {
    this->accumulatedTime += dt;
    this->t += dt;

    while (this->accumulatedTime > this->timeQuantum) {
        this->accumulatedTime -= this->timeQuantum;
        this->accumulatedParticles += this->timeQuantum * this->genVelocity;

        while (this->accumulatedParticles >= 1.0) {
            this->accumulatedParticles -= 1.0;
            this->addParticle(this->createParticle());
        }

        Particle *p = this->first;
        while (p->next != NULL) {
            bool rem = this->processParticle(p);
            if (rem) {
                this->removeParticle(p);
            }
            else {
                p = p->next;
            }
        }
    }
}

std::vector <Vector> ParticleSystem::getCoordinates() const {
    std::vector <Vector> result;
    for (Particle *p = this->first; p != NULL; p = p->next) {
        result.push_back(p->r);
    }
    return result;
}

std::vector <Vector> ParticleSystem::getVelocities() const {
    std::vector <Vector> result;
    for (Particle *p = this->first; p != NULL; p = p->next) {
        result.push_back(p->v);
    }
    return result;
}

double ParticleSystem::getTime() const {
    return this->t;
}

double ParticleSystem::getQuant() const {
    return this->timeQuantum;
}

int ParticleSystem::getCount() const {
    return this->count;
}

std::ostream& operator <<(std::ostream &out, const ParticleSystem &sys) {
    int n = 0;
    if (sys.first->next == NULL) {
        out << "The particle system is empty" << std::endl;
    }
    else {
        for (Particle *p = sys.first; p->next != NULL; p = p->next) {
            out << "Particle #" << n++ << ": r=" << p->r << " v=" << p->v << std::endl;
        }
    }
    return out;
}
