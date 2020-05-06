#!/usr/bin/env python
# coding: utf-8

import pygame
import random
from game_config import GameConfig
from fruit import Fruit
from snake import Snake

class GameState(object):
    def __init__(self, screen):
        self.screen = screen
        self.score = 0
        self.is_gameover = True
        self.is_paused = False
        self.time_interval = GameConfig.TIMER_INTERVAL
        self.snake = None
        self.fruit = None

    def new_fruit(self):
        self.fruit = Fruit.new_fruit(self.screen, self.snake)

    def add_score(self, fruit = 1):
        self.score += fruit * GameConfig.SCORE_PER_FRUIT

    def start(self):
        self.score = 0
        self.is_gameover = False
        self.is_paused = False
        self.snake = Snake(self.screen)
        self.new_fruit()
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

    def judge(self, code):
        if code == 0:
            return
        elif code == 1:
            self.add_score()
            self.new_fruit()
        elif code == -1:
            self.gameover()
        else:
            print "unknown code"


