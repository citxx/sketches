#!/usr/bin/python

import sys
import random
import pygame
from pygame.locals import *

import colors

FPS = 60
fps_clock = pygame.time.Clock()

default_window_size = (1200, 200)

class Particle:
    def __init__(self, radius, color, position, velocity):
        self.radius = radius
        self.color = color
        self.position = position
        self.velocity = velocity  # In px per second

    def get_left_bound(self):
        return self.position[0] - self.radius

    def get_right_bound(self):
        return self.position[0] + self.radius

    def get_position(self):
        return (int(self.position[0]), int(self.position[1]))

    def update(self):
        if self.position[0] - self.radius <= 0 or default_window_size[0] <= self.position[0] + self.radius:
            self.velocity = (-self.velocity[0], self.velocity[1])
        if self.position[1] - self.radius <= 1 or default_window_size[1] <= self.position[1] + self.radius:
            self.velocity = (self.velocity[0], -self.velocity[1])
        self.position = (self.position[0] + self.velocity[0] / FPS, self.position[1] + self.velocity[1] / FPS)

def intersect(a, b):
    m1 = a.radius ** 2
    v1x, v1y = a.velocity

    m2 = b.radius ** 2
    v2x, v2y = b.velocity

    dx = b.position[0] - a.position[0]
    dy = b.position[1] - a.position[1]

    if dx ** 2 + dy ** 2 <= (a.radius + b.radius) ** 2 and (v1x - v2x) * dx + (v1y - v2y) * dy > 0:
        tv1x = dx * v1x + dy * v1y
        tv1y = dy * v1x - dx * v1y
        tv2x = dx * v2x + dy * v2y
        tv2y = dy * v2x - dx * v2y

#        print '(', tv1x, tv1y, '), (', tv2x, tv2y, ')'

        tsv1x = ((m1 - m2) * tv1x + 2 * m2 * tv2x) / (m1 + m2)
        tsv1y = tv1y

        tsv2x = (2 * m1 * tv1x + (m2 - m1) * tv2x) / (m1 + m2)
        tsv2y = tv2y

#        print '[', tsv1x, tsv1y, '], [', tsv2x, tsv2y, ']'

        d2 = dx ** 2 + dy ** 2
        sv1x = (dx * tsv1x + dy * tsv1y) / d2
        sv1y = (dy * tsv1x - dx * tsv1y) / d2

        sv2x = (dx * tsv2x + dy * tsv2y) / d2
        sv2y = (dy * tsv2x - dx * tsv2y) / d2

        a.velocity = (sv1x, sv1y)
        b.velocity = (sv2x, sv2y)


screen = pygame.display.set_mode(default_window_size)
pygame.display.set_caption('Sweep and Prune')

particles = [
    Particle(
        random.randint(4, 6),
        colors.get_random(),
        (float(x), float(y)),
        (- (x - 600.0) / 2.0 , - (random.random() - 0.5) * 10.0)
    )
    for x in xrange(50, 1151, 15) for y in xrange(30, 171, 15)
]


#particles = [
#    Particle(
#        random.randint(4, 6),
#        colors.get_random(),
#        (float(x), float(y)),
#        (random.random() * 300 , (random.random() - 0.5) * 50))
#    for x in xrange(50, 250, 15) for y in xrange(30, 171, 15)
#]

#particles = [
#    Particle(60, colors.get_random(), (300.0, 200.0), (10.0, 10.0)),
#    Particle(60, colors.get_random(), (500.0, 400.0), (-10.0, -10.0))
#]

particles.sort(key=lambda x: x.get_left_bound())

iter_num = 0
while True:
#    iter_num += 1
#    print 'Iteration number', iter_num
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

    screen.fill(colors.WHITE)

    particles.sort(key=lambda x: x.get_left_bound())
    for i in xrange(len(particles)):
        right = particles[i].get_right_bound()
        j = i + 1
        while j < len(particles) and particles[j].get_left_bound() <= right:
            intersect(particles[i], particles[j])
            j += 1

    for p in particles:
        p.update()

    for particle in particles:
        pygame.draw.circle(screen, particle.color, particle.get_position(), particle.radius, 0)
        pygame.draw.circle(screen, colors.BLACK, particle.get_position(), particle.radius, 1)

    pygame.display.flip()
    fps_clock.tick(FPS)
