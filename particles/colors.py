#!/usr/bin/python

import random

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

def get_random(min_intensity=0, max_intensity=765):
    #return (255, 0, 0)
    return (random.randrange(256), random.randrange(256), random.randrange(256))
