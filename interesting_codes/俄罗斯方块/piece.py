#!/usr/bin/env python
# coding: utf-8

from game_config import GameConfig
from game_display import GameDisplay

class Piece(object):
    def __init__(self, screen, shape, wall):
        self.screen = screen
        self.row = 0
        self.col = 3
        self.turn = 0
        self.shape = shape
        self.shape_template = GameConfig.PIECES[shape]
        self.color = GameConfig.PIECE_COLORS[shape]
        self.wall = wall

    def draw(self):
        shape = self.shape_template[self.turn]
        for i in range(len(shape)):
            for j in range(len(shape[0])):
                if shape[i][j] == 'O':
                    x = GameConfig.GAME_AREA_LEFT + GameConfig.CELL_WIDTH * (self.col + j)
                    y = GameConfig.GAME_AREA_TOP + GameConfig.CELL_HEIGHT * (self.row + i)
                    GameDisplay.draw_cell(self.screen, x, y, self.color)

    def can_move_left(self):
        curr_shape = self.shape_template[self.turn]
        for i in range(len(curr_shape)):
            for j in range(len(curr_shape[0])):
                if curr_shape[i][j] == 'O':
                    new_row = self.row + i
                    new_col = self.col + j - 1
                    if new_col == -1:
                        return False
                    if self.wall.is_wall(new_row, new_col):
                        return False
        return True

    def move_left(self):
        if self.can_move_left():
            self.col -= 1

    def can_move_right(self):
        curr_shape = self.shape_template[self.turn]
        for i in range(len(curr_shape)):
            for j in range(len(curr_shape[0])):
                if curr_shape[i][j] == 'O':
                    new_row = self.row + i
                    new_col = self.col + j + 1
                    if new_col == GameConfig.COLUMN_NUM:
                        return False
                    if self.wall.is_wall(new_row, new_col):
                        return False
        return True

    def move_right(self):
        if self.can_move_right():
            self.col += 1

    def can_move_down(self):
        curr_shape = self.shape_template[self.turn]
        for i in range(len(curr_shape)):
            for j in range(len(curr_shape[0])):
                if curr_shape[i][j] == 'O':
                    new_row = self.row + i + 1
                    new_col = self.col + j
                    if new_row == GameConfig.LINE_NUM:
                        return False
                    if self.wall.is_wall(new_row, new_col):
                        return False
        return True

    def move_down(self):
        if self.can_move_down():
            self.row += 1
            return False
        else:
            self.insert_into_wall()
            return True

    def can_turn(self):
        new_shape = self.shape_template[(self.turn + 1) % len(self.shape_template)]
        for i in range(len(new_shape)):
            for j in range(len(new_shape[0])):
                if new_shape[i][j] == 'O':
                    new_row = self.row + i
                    new_col = self.col + j
                    if new_row < 0 or new_row >= GameConfig.LINE_NUM or new_col < 0 or new_col >= GameConfig.COLUMN_NUM:
                        return False
                    if self.wall.is_wall(new_row, new_col):
                        return False
        return True

    def turn_once(self):
        if self.can_turn():
            self.turn = (self.turn + 1) % len(self.shape_template)

    def goto_bottom(self):
        while self.can_move_down():
            self.row += 1
        self.insert_into_wall()

    def insert_into_wall(self):
        shape = self.shape_template[self.turn]
        for i in range(len(shape)):
            for j in range(len(shape[0])):
                if shape[i][j] == 'O':
                    self.wall.set_cell(self.row + i, self.col + j, self.shape)

