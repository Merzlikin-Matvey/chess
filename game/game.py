from classes.board import Board
from classes.exception import *


board = Board()
print(board)
while board.game_is_going():
    try:
        board.move(*list(map(int, input().split())))
        print(board)
    except Exception as e:
        print(e)
print(board.how_is_winner())

