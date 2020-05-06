#!/usr/bin/env python
# coding: utf-8

class GameConfig(object):
    SCREEN_WIDTH = 1200
    SCREEN_HEIGHT = 900
    CELL_WIDTH = 40
    CELL_HEIGHT = 40
    COLUMN_NUM = 10
    LINE_NUM = 20
    GAME_AREA_WIDTH = CELL_WIDTH * COLUMN_NUM
    GAME_AREA_HEIGHT = CELL_WIDTH * LINE_NUM
    GAME_AREA_LEFT = (SCREEN_WIDTH - GAME_AREA_WIDTH) // 2
    GAME_AREA_TOP = SCREEN_HEIGHT - GAME_AREA_HEIGHT - 50
    NEXT_PIECE_WIDTH = CELL_WIDTH * 4
    NEXT_PIECE_HEIGHT = CELL_HEIGHT * 4
    NEXT_PIECE_LEFT = GAME_AREA_WIDTH + GAME_AREA_LEFT + (SCREEN_WIDTH - GAME_AREA_WIDTH - GAME_AREA_LEFT) // 2
    NEXT_PIECE_TOP = GAME_AREA_TOP
    EDGE_WIDTH = 5  # 游戏区域外框线宽度
    EDGE_HEIGHT = 5
    MARGIN_WIDTH = 40  # 游戏区域外框线与文字之间的间距
    MARGIN_HEIGHT = 40
    SCORE_LEFT = NEXT_PIECE_LEFT
    SCORE_TOP = NEXT_PIECE_TOP + NEXT_PIECE_HEIGHT + EDGE_HEIGHT + MARGIN_HEIGHT
    SCORE_SIZE = 28

    EDGE_COLOR = (100, 100, 100)
    CELL_COLOR = (100, 100, 100)
    BG_COLOR = (230, 230, 230)
    TEXT_COLOR = (0, 0, 0)
    SCORE_COLOR = (0, 0, 0)
    GAMEOVER_COLOR = (255, 0, 0)
    TITLE_COLOR = (0, 0, 255)

    SHAPES = 'SZIOJLT'
    S_SHAPE_TEMPLATE = [['.OO.',
                         'OO..',
                         '....'],
                        ['.O..',
                         '.OO.',
                         '..O.']]

    Z_SHAPE_TEMPLATE = [['OO..',
                         '.OO.',
                         '....'],
                        ['..O.',
                         '.OO.',
                         '.O..']]

    I_SHAPE_TEMPLATE = [['OOOO',
                         '....',
                         '....',
                         '....'],
                        ['.O..',
                         '.O..',
                         '.O..',
                         '.O..']
                        ]

    O_SHAPE_TEMPLATE = [['OO',
                         'OO']]

    J_SHAPE_TEMPLATE = [['..O.',
                         '..O.',
                         '.OO.'],
                        ['O...',
                         'OOO.',
                         '....'],
                        ['.OO.',
                         '.O..',
                         '.O..'],
                        ['OOO.',
                         '..O.',
                         '....']
                        ]

    L_SHAPE_TEMPLATE = [['.O..',
                         '.O..',
                         '.OO.'],

                        ['....',
                         'OOO.',
                         'O...'],

                        ['.OO.',
                         '..O.',
                         '..O.'],

                        ['..O.',
                         'OOO.',
                         '....'],
                        ]

    T_SHAPE_TEMPLATE = [
        ['OOO.',
         '.O..',
         '....'],

        ['..O.',
         '.OO.',
         '..O.'],

        ['.O..',
         'OOO.',
         '....'],

        ['.O..',
         '.OO.',
         '.O..'],
    ]

    PIECES = {'S': S_SHAPE_TEMPLATE,
              'Z': Z_SHAPE_TEMPLATE,
              'J': J_SHAPE_TEMPLATE,
              'L': L_SHAPE_TEMPLATE,
              'I': I_SHAPE_TEMPLATE,
              'O': O_SHAPE_TEMPLATE,
              'T': T_SHAPE_TEMPLATE}

    PIECE_COLORS = {
        'S': (0, 255, 128),
        'Z': (255, 128, 255),
        'J': (128, 0, 255),
        'L': (0, 0, 255),
        'I': (255, 255, 0),
        'O': (255, 0, 0),
        'T': (255, 128, 0)
    }

    BLANK_LABEL = '-'  # 20*10游戏区域中，单元格表示为'-'，意味着为空。
    TIMER_INTERVAL = 1000  # 最开始方块每个1000ms下降1行。
    SCORE_PER_LINE = 10 # 每消除一行方块得到的分数
