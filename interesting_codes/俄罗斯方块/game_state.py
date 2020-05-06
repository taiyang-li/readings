#!/usr/bin/env python
# coding: utf-8

import pygame
import random
from game_config import GameConfig
from wall import Wall
from piece import Piece

class GameState(object):
    def __init__(self, screen):
        self.screen = screen
        self.score = 0
        self.is_gameover = True
        self.is_paused = False
        self.time_interval = GameConfig.TIMER_INTERVAL
        self.piece = None
        self.next_piece = None
        self.wall = Wall(self.screen)

    def new_piece(self):
        self.piece = self.next_piece
        shape = GameConfig.SHAPES[random.randint(0, len(GameConfig.SHAPES) - 1)]
        self.next_piece = Piece(self.screen, shape, self.wall)

    def add_score(self, elimiate_lines):
        self.score += elimiate_lines * GameConfig.SCORE_PER_LINE

    def start(self):
        self.score = 0
        self.is_gameover = False
        self.is_paused = False
        self.new_piece()
        self.new_piece()
        self.wall.clear()
        self.set_timer()

    def restart(self):
        self.start()

    def gameover(self):
        self.is_gameover = True
        self.clear_timer()

    def pause(self):
        self.is_paused = True
        self.clear_timer()

    def resume(self):
        self.is_paused = False
        self.set_timer()

    def set_timer(self):
        pygame.time.set_timer(pygame.USEREVENT, self.time_interval)

    def clear_timer(self):
        pygame.time.set_timer(pygame.USEREVENT, 0)

    def judge(self):
        elimiate_lines = self.wall.elimiate_lines()
        self.add_score(elimiate_lines)

        for i in range(GameConfig.COLUMN_NUM):
            if self.wall.is_wall(0, i):
                self.gameover()
                return

        self.new_piece()


