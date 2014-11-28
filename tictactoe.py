#!/usr/bin/env python

# import copy
import numpy
import itertools

SIZE = 3

class Board(object):
    def __init__(self, board_arr):
        self.board_arr = board_arr

    def get_moves(self):
        moves = []
        # print(self.board_arr)
        for y in range(len(self.board_arr)):
            for x in range(len(self.board_arr[y])):
                if self.board_arr[y][x] == 0:
                    moves.append((x, y))
        return moves

    def won(self, letter):
        rows = [0] * SIZE
        cols = [0] * SIZE
        diags = [0] * 2
        for y, x in itertools.product(range(SIZE), range(SIZE)):
            # for y in range(len(self.board_arr)):
            # for x in range(len(self.board_arr[y])):
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
        trans = [" ", "X", "O"]
        for i in self.board_arr:
            if not first:
                print("-"*(SIZE*2))
            first = False

            arr = []
            for j in i:
                arr.append(trans[j])
            print("|".join(arr))


# @profile
def minimax(board, letter):
    moves = board.get_moves()
    # arr = copy.deepcopy(board.board_arr)
    # zeros = numpy.zeros
    # empty = numpy.empty
    # nsum = numpy.sum
    # arr = numpy.array(board.board_arr)
    arr = board.board_arr
    # scores = []
    scores = numpy.empty((len(moves),), dtype=numpy.int)
    index = 0

    for move in moves:
        # arr2 = arr.copy()
        arr2 = numpy.empty_like(arr)
        arr2[:] = arr
        arr2[move[1]][move[0]] = letter
        # print("Orig: %s" % board.board_arr)
        board2 = Board(arr2)

        if board2.won(letter):
            # scores.append(10)
            scores[index] = 10
        else:
            if letter == 1:
                letter2 = 2
            else:
                letter2 = 1

            # scores2 = numpy.array([])
            scores2 = numpy.zeros((len(moves),), dtype=numpy.int)
            index2 = 0
            for i in board2.get_moves():
                arr3 = arr2.copy()
                arr3[i[1]][i[0]] = letter2
                # print(arr3)
                board3 = Board(arr3)
                if board3.won(letter2):
                    # scores2.append(-10)
                    scores2[index2] = -10
                else:
                    # scores2.append(sum(minimax(board3, letter)))
                    scores2[index2] = sum(minimax(board3, letter))

                index2 += 1

            # scores.append(sum(scores2))
            # print(index)
            scores[index] = sum(scores2)
        index += 1

    # print(index)
    return scores


def player_turn(board):
    scores = minimax(board, 1)
    print(scores)
    # max_score = max(scores)
    # max_ind = scores.index(max_score)
    max_ind = scores.argmax()

    moves = board.get_moves()
    print(moves, max_ind)
    move = moves[max_ind]

    board.board_arr[move[1]][move[0]] = 1

    return board


def user_turn(board):
    accept = False

    while not accept:
        x_coord = int(input("Enter your desired x-coord: "))
        y_coord = int(input("Enter your desired y-coord: "))

        if(x_coord >= 1 and x_coord <= SIZE and y_coord >= 1
           and y_coord <= SIZE and board.board_arr[y_coord-1][x_coord-1] == 0):
            accept = True

    board.board_arr[y_coord-1][x_coord-1] = 2

    return board


def main():
    # 1 is the computer
    # 2 is the player

    arr = numpy.array([[0 for col in range(SIZE)] for row in range(SIZE)])
    # arr[1][1] = 2
    print(arr)

    board = Board(arr)

    while(not board.won(1) and not board.won(2)
          and any(0 in i for i in board.board_arr)):
        board = player_turn(board)
        board.prettyprint()

        if(board.won(1) or board.won(2)
           or not any(0 in i for i in board.board_arr)):
            break

        board = user_turn(board)

    if board.won(1):
        print("Ooh, you lost! That blows!")
    elif board.won(2):
        print("Hey, you won! Awesome!")
    else:
        print("It was a tie? I have... strongly mixed feelings.")

main()
