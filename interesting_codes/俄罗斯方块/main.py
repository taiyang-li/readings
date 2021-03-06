#!/usr/bin/env python
# coding: utf-8

import sys
import pygame
from game_config import GameConfig
from game_state import GameState
from game_display import GameDisplay

def main():
    pygame.init()
    screen = pygame.display.set_mode([GameConfig.SCREEN_WIDTH, GameConfig.SCREEN_HEIGHT])
    pygame.display.set_caption("fangkuai")
    pygame.key.set_repeat(10, 100)  #一直按下某个键，每过100毫秒就引发一个KEYDOWN事件
    game_state = GameState(screen)

    while True:
        process_events(game_state)
        GameDisplay.draw(screen, game_state)
        pygame.display.flip()

def process_events(game_state):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit(0)
        elif event.type == pygame.KEYDOWN:
            process_keydown(game_state, event)
        elif event.type == pygame.USEREVENT:
            touch_bottom = game_state.piece.move_down()
            if touch_bottom:
                game_state.judge()

def process_keydown(game_state, event):
    # 启动游戏
    if game_state.is_gameover and event.key == pygame.K_s:
        game_state.start()
    # 重启游戏
    elif event.key == pygame.K_r:
        game_state.restart()
    # 退出游戏
    elif event.key == pygame.K_q:
        sys.exit(0)
    # 暂停游戏
    elif not game_state.is_paused and event.key == pygame.K_p:
        game_state.pause()
    # 取消暂停
    elif game_state.is_paused and event.key == pygame.K_p:
        game_state.resume()
    # 左移
    elif not game_state.is_paused and not game_state.is_gameover and event.key == pygame.K_LEFT:
        game_state.piece.move_left()
    # 右移
    elif not game_state.is_paused and not game_state.is_gameover and event.key == pygame.K_RIGHT:
        game_state.piece.move_right()
    # 下移
    elif not game_state.is_paused and not game_state.is_gameover and event.key == pygame.K_DOWN:
        touch_bottom = game_state.piece.move_down()
        if touch_bottom:
            game_state.judge()
    # 翻转
    elif not game_state.is_paused and not game_state.is_gameover and event.key == pygame.K_UP:
        game_state.piece.turn_once()
    # 迅速移动到底部
    elif not game_state.is_paused and not game_state.is_gameover and (event.key == pygame.K_SPACE or event.key == pygame.K_d):
        game_state.piece.goto_bottom()
        game_state.judge()

if __name__ == '__main__':
    main()
