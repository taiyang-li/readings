#!/usr/bin/env python
# coding: utf-8

import pygame
from game_config import GameConfig
from game_display import GameDisplay
from snake import Snake
from random import randint

class Fruit(object):
    def __init__(self, screen, position):
        self.screen = screen
        self.color = GameConfig.FRUIT_COLOR
        self.position = position

    def draw(self):
        x = GameConfig.GAME_AREA_LEFT + GameConfig.CELL_WIDTH * self.position[0]
        y = GameConfig.GAME_AREA_TOP + GameConfig.CELL_HEIGHT * self.position[1]
        GameDisplay.draw_cell(self.screen, x, y, self.color)

    @staticmethod
    def new_fruit(screen, snake):
        cont = True
        while cont:
            position = randint(0, GameConfig.COLUMN_NUM-1), randint(0, GameConfig.LINE_NUM-1)
            cont = position in snake.positions
        return Fruit(screen, position)


