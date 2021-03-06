#/usr/bin/env python
# coding: utf-8

import pygame
from game_config import GameConfig

class GameDisplay(object):
    @staticmethod
    def draw(screen, game_state):
        # 背景
        screen.fill(GameConfig.BG_COLOR)

        # 游戏区边界
        GameDisplay.draw_game_border(screen)

        # 苹果
        if game_state.fruit:
            GameDisplay.draw_fruit(screen, game_state.fruit)

        # 蛇
        if game_state.snake:
            GameDisplay.draw_snake(screen, game_state.snake)

        # 分数区
        GameDisplay.draw_score(screen, game_state.score)

    @staticmethod
    def draw_cell(screen, x, y, color):
        pygame.draw.rect(screen, color, pygame.Rect(x, y, GameConfig.CELL_WIDTH, GameConfig.CELL_HEIGHT))

    @staticmethod
    def draw_snake(screen, snake):
        snake.draw()

    @staticmethod
    def draw_fruit(screen, fruit):
        fruit.draw()

    @staticmethod
    def draw_game_border(screen):
        x = GameConfig.GAME_AREA_LEFT
        y = GameConfig.GAME_AREA_TOP
        width = GameConfig.GAME_AREA_WIDTH
        height = GameConfig.GAME_AREA_HEIGHT
        color = GameConfig.EDGE_COLOR
        GameDisplay.draw_border(screen, x, y, width, height, color)

    @staticmethod
    def draw_border(screen, x, y, width, height, color):
        lu_x = x - GameConfig.EDGE_WIDTH
        lu_y = y - GameConfig.EDGE_HEIGHT
        ru_x = x + width
        ru_y = y - GameConfig.EDGE_HEIGHT
        ld_x = x - GameConfig.EDGE_WIDTH
        ld_y = y + height
        total_width = width + 2 * GameConfig.EDGE_WIDTH
        total_height = height + 2 * GameConfig.EDGE_HEIGHT
        pygame.draw.rect(screen, color, pygame.Rect(lu_x, lu_y, total_width, GameConfig.EDGE_HEIGHT))
        pygame.draw.rect(screen, color, pygame.Rect(lu_x, lu_y, GameConfig.EDGE_WIDTH, total_height))
        pygame.draw.rect(screen, color, pygame.Rect(ld_x, ld_y, total_width, GameConfig.EDGE_HEIGHT))
        pygame.draw.rect(screen, color, pygame.Rect(ru_x, ru_y, GameConfig.EDGE_WIDTH, total_height))

    @staticmethod
    def draw_score(screen, score):
        score_font = pygame.font.SysFont('Calibri', GameConfig.SCORE_SIZE)
        text = 'score: %d' % (score)
        score_surface = score_font.render(text, True, GameConfig.SCORE_COLOR)
        screen.blit(score_surface, (GameConfig.SCORE_LEFT, GameConfig.SCORE_TOP))

