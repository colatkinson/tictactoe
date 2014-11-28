#!/usr/bin/env python

import copy
import numpy

SIZE = 4

class Board(object):
    def __init__(self, board_arr):
        self.board_arr = board_arr[:]

    def get_moves(self):
        moves = []
        # print(self.board_arr)
        for y in range(len(self.board_arr)):
            for x in range(len(self.board_arr[y])):
                if self.board_arr[y][x] == " ":
                    moves.append((x, y))
        return moves

    def won(self, letter):
        # rows = [0, 0, 0]
        rows = [0] * SIZE
        # cols = [0, 0, 0]
        cols = [0] * SIZE
        # diags = [0, 0]
        diags = [0] * 2
        for y in range(len(self.board_arr)):
            for x in range(len(self.board_arr[y])):
                if self.board_arr[y][x] == letter:
                    rows[y] += 1
                    cols[x] += 1

                    if x == y:
                        diags[0] += 1

                    if x+y == 2:
                        diags[1] += 1

        return (SIZE in rows or SIZE in cols or SIZE in diags)

    def prettyprint(self):
        first = True
        for i in self.board_arr:
            if not first:
                print("-"*(SIZE*2))
            first = False
            print("|".join(i))


def minimax(board, letter):
    moves = board.get_moves()
    arr = copy.deepcopy(board.board_arr)
    scores = []

    for move in moves:
        arr2 = copy.deepcopy(arr)
        arr2[move[1]][move[0]] = letter
        # print("Orig: %s" % board.board_arr)
        board2 = Board(arr2)

        if board2.won(letter):
            scores.append(10)
        else:
            if letter == "X":
                letter2 = "O"
            else:
                letter2 = "X"

            scores2 = []
            for i in board2.get_moves():
                arr3 = copy.deepcopy(arr2)
                arr3[i[1]][i[0]] = letter2
                # print(arr3)
                board3 = Board(arr3)
                if board3.won(letter2):
                    scores2.append(-10)
                else:
                    scores2.append(sum(minimax(board3, letter)))

            scores.append(sum(scores2))

    return scores

def main():
    # arr = [[" ", " ", " ", " "],
    #       [" ", " ", " ", " "],
    #       [" ", " ", " ", " "],
    #       [" ", " ", " ", " "]]
    # arr = [[" "]*SIZE]*SIZE
    arr = [[" " for col in range(SIZE)] for row in range(SIZE)]
    print(arr)

    board = Board(arr)

    while not board.won("X") and not board.won("O"):
        scores = minimax(board, "X")
        print(scores)
        max_score = max(scores)
        max_ind = scores.index(max_score)

        moves = board.get_moves()
        print(moves, max_ind)
        move = moves[max_ind]

        board.board_arr[move[1]][move[0]] = "X"
        board.prettyprint()

        if(board.won("X")):
            break

        x_coord = int(input("Enter your desired x-coord: "))
        y_coord = int(input("Enter your desired y-coord: "))

        board.board_arr[y_coord-1][x_coord-1] = "O"

main()
