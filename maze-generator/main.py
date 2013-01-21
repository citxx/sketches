#!/usr/bin/python

import pygame
from pygame.locals import *
import sys
from random import choice, randrange

class DSU:
    def __init__(self, elements):
        self._dsu = {x : x for x in elements}
        self._count = len(elements)

    def get(self, x):
        if x in self._dsu:
            if self._dsu[x] == x:
                return x
            else:
                self._dsu[x] = self.get(self._dsu[x])
                return self._dsu[x]
        else:
            return None

    def join(self, a, b):
        a = self.get(a)
        b = self.get(b)
        if a == None or b == None:
            raise "Wrong sets"

        if a != b:
            self._count -= 1
            if choice([True, False]):
                self._dsu[a] = b
            else:
                self._dsu[b] = a

    def count(self):
        return self._count

class Cell:
    def __init__(self):
        self._walls = {"left" : True, "right" : True, "top" : True, "bottom" : True}

    def get(self, direction):
        if direction in self._walls:
            return self._walls[direction]
        else:
            return None

    def create(self, direction):
        if direction in self._walls:
            self._walls[direction] = True
        else:
            raise BaseException()

    def destroy(self, direction):
        if direction in self._walls:
            self._walls[direction] = False
        else:
            raise BaseException()

class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.maze = [[Cell() for y in range(self.height)] for x in range(self.width)]

        link = DSU([(x, y) for x in range(self.width) for y in range(self.height)])
        while link.count() > 1:
            # Choose random wall
            x = randrange(width)
            y = randrange(height)
            dirs = ["right", "top", "left", "bottom"]
            direction = choice(dirs)

            pos2 = self.getPos((x, y), direction)
            if pos2 == None:
                continue
            pos1 = (x, y)

            if link.get(pos1) == link.get(pos2):
                continue

            link.join(pos1, pos2)

            self.maze[x][y].destroy(direction)
            self.maze[pos2[0]][pos2[1]].destroy(dirs[(dirs.index(direction) + 2) % 4])

    def getPos(self, pos, direction):
        shift = {"right" : (1, 0), "top" : (0, 1), "left" : (-1, 0), "bottom" : (0, -1)}
        if direction in shift:
            sh = shift[direction]
            (x, y) = (pos[0] + sh[0], pos[1] + sh[1])
            if x < 0 or self.width <= x:
                return None
            if y < 0 or self.height <= y:
                return None
            return (x, y)
        else:
            return None


pygame.init()

width, height = 650, 650

screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Maze")

mWidth, mHeight = 40, 40

m = Maze(mWidth, mHeight)

def makeTurn(humanPos, direction):
    (hx, hy) = humanPos
    if (m.maze[hx][hy].get(direction)):
        return humanPos
    return m.getPos(humanPos, direction)


humanPos = (0, 0)
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            sys.exit()
        elif event.type == KEYDOWN:
            if event.key == K_ESCAPE:
                sys.exit()
            elif event.key == K_n:
                m = Maze(mWidth, mHeight)
                humanPos = (0, 0)
            elif event.key == K_UP:
                humanPos = makeTurn(humanPos, "bottom")
            elif event.key == K_LEFT:
                humanPos = makeTurn(humanPos, "left")
            elif event.key == K_DOWN:
                humanPos = makeTurn(humanPos, "top")
            elif event.key == K_RIGHT:
                humanPos = makeTurn(humanPos, "right")
            else:
                pass
        else:
            pass

    start = (10, 10)
    end = (width - 10, height - 10)
    step = (1.0 * (end[0] - start[0]) / mWidth,
            1.0 * (end[1] - start[1]) / mHeight)

    (startX, startY) = start
    (endX, endY) = end
    (stepX, stepY) = step

    screen.fill((255, 255, 255))

    left =   int(startX + stepX * humanPos[0])
    top =    int(startY + stepY * humanPos[1])

    pygame.draw.rect(screen, (20, 200, 20), pygame.Rect(left, top, stepX, stepY))

    for i in xrange(mWidth):
        for j in xrange(mHeight):
            left =   int(startX + stepX * i)
            right =  int(startX + stepX * (i + 1) - 1)
            bottom = int(startY + stepY * j)
            top =    int(startY + stepY * (j + 1) - 1)

            lb = (left, bottom)
            lt = (left, top)
            rb = (right, bottom)
            rt = (right, top)
            if (m.maze[i][j].get("right")):
                pygame.draw.line(screen, (0, 0, 0), rb, rt, 1)
            if (m.maze[i][j].get("top")):
                pygame.draw.line(screen, (0, 0, 0), lt, rt, 1)
            if (m.maze[i][j].get("left")):
                pygame.draw.line(screen, (0, 0, 0), lb, lt, 1)
            if (m.maze[i][j].get("bottom")):
                pygame.draw.line(screen, (0, 0, 0), rb, lb, 1)

    pygame.display.flip()

