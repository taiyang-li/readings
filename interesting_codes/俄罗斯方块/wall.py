#!/usr/bin/env python
# coding: utf-8

import pygame
from game_config import GameConfig
from game_display import GameDisplay

class Wall(object):
    def __init__(self, screen):
        self.screen = screen
        self.grid = [[GameConfig.BLANK_LABEL for i in range(GameConfig.COLUMN_NUM)] for j in range(GameConfig.LINE_NUM)]

    def draw(self):
        for i in range(len(self.grid)):
            for j in range(len(self.grid[0])):
                if self.grid[i][j] != GameConfig.BLANK_LABEL:
                    x = GameConfig.GAME_AREA_LEFT + GameConfig.CELL_WIDTH * j
                    y = GameConfig.GAME_AREA_TOP + GameConfig.CELL_HEIGHT * i
                    color = GameConfig.PIECE_COLORS[self.grid[i][j]]
                    GameDisplay.draw_cell(self.screen, x, y, color)

    def set_cell(self, row, col, label):
        self.grid[row][col] = label

    def elimiate_lines(self):
        full_lines = []
        for i in range(len(self.grid)):
            if self.is_full(self.grid[i]):
                full_lines.append(i)

        for line_no in full_lines:
            self.copy_down(line_no)
        return len(full_lines)

    def clear(self):
        for i in range(len(self.grid)):
            for j in range(len(self.grid[0])):
                self.grid[i][j] = GameConfig.BLANK_LABEL

    def is_wall(self, row, col):
        return self.grid[row][col] != GameConfig.BLANK_LABEL

    def is_full(self, line):
        for i in range(len(line)):
            if line[i] == GameConfig.BLANK_LABEL:
                return False
        return True

    def copy_down(self, line_no):
        for i in range(line_no, 0, -1):
            self.grid[i] = self.grid[i-1]
        self.grid[0] = [GameConfig.BLANK_LABEL for x in range(GameConfig.COLUMN_NUM)]

if __name__ == '__main__':
    screen = 1
    wall = Wall(screen)
