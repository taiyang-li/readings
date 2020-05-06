#!/usr/bin/env python
# coding: utf-8

import pygame
from game_config import GameConfig
from game_display import GameDisplay

class Snake(object):
    directions = {'left': (-1, 0), 'right': (1, 0), 'up': (0, -1), 'down': (0, 1)}

    def __init__(self, screen):
        self.screen = screen
        self.direction = Snake.directions['up']
        self.color = GameConfig.SNAKE_COLOR
        self.positions = [(5, 10), (5, 11), (5, 12)]

    def draw(self):
        for position in self.positions:
            x = GameConfig.GAME_AREA_LEFT + GameConfig.CELL_WIDTH * position[0]
            y = GameConfig.GAME_AREA_TOP + GameConfig.CELL_HEIGHT * position[1]
            GameDisplay.draw_cell(self.screen, x, y, self.color)

    def move_up(self, fruit):
        self.direction = Snake.directions['up']
        return self.move(fruit)

    def move_down(self, fruit):
        self.direction = Snake.directions['down']
        return self.move(fruit)

    def move_left(self, fruit):
        self.direction = Snake.directions['left']
        return self.move(fruit)

    def move_right(self, fruit):
        self.direction = Snake.directions['right']
        return self.move(fruit)

    def move(self, fruit):
        new_head = self.direction[0] + self.positions[0][0], self.direction[1] + self.positions[0][1]
        if new_head[0] < 0 or new_head[0] >= GameConfig.COLUMN_NUM or new_head[1] < 0 or new_head[1] >= GameConfig.LINE_NUM or new_head in self.positions:
            return -1

        if new_head == fruit.position:
            self.positions.insert(0, new_head)
            return 1

        self.positions.insert(0, new_head)
        self.positions.pop()
        return 0

