import copy
import time
import Project2
import speed_up
from threading import *
red_char = 'X'
black_char = 'O'
empty_char = '.'
best_move_state = None
best_move = -2147483648
done = False
sem = Semaphore()
connect = 0
time_up = False
max_val = 2147483648
min_val = -2147483648
ai_color = ""


# The minimax algorithm  with alpha_beta pruning
def alpha_beta_search(state, depth, width, height, color, r):
    global best_move
    global best_move_state
    global done
    global connect
    global time_up
    global ai_color

    # print("Alpha_beta_search started")

    # for each legal move get the min-value()
    # a piece can be added to any slot that is not full
    v = [-2147483648, state]
    alpha = -2147483648
    beta = 2147483648
    rows_ful = 0
    for x in range(0, width):

        sem.acquire()
        out_of_time = time_up
        sem.release()
        if out_of_time:
            return

        y = col_pieces(state, x)                    # get the next open space in the slot
        if y < height:                             # make sure the slot is not full
            new_state = copy.deepcopy(state)
            new_state[x][y] = get_color_char(color)

            # Avoid the ai not being able to return any moves if it does not have long enough to compute
            sem.acquire()
            # print("Set initial best move state = " + str(best_move_state))
            if best_move_state is None:
                best_move_state = new_state
            sem.release()

            new_color = abs(color-1)
            max_v = max_value(new_state, depth, width, height, x, y, new_color, r, alpha, beta)

            sem.acquire()
            if int(v[0]) <= int(max_v[0]) and not time_up:
                v = max_v
                # print("Saving new best move")
                best_move = v[0]
                best_move_state = v[1]
            sem.release()
        else:
            rows_ful += 1
            if rows_ful == width - 1:
                Project2.set_game_over()
                print("Tie")
                return
    # print("State Utility = " + str(v[0]))
    # print_eval_state(v[1])
    sem.acquire()
    if not time_up:
        best_move = v[0]
        best_move_state = v[1]
        done = True
    sem.release()

    return


# The min-value function of the minimax algorithm
def min_value(state, depth, width, height, x, y, color, r, alpha, beta):
    global time_up
    # print("Calling min_val")
    v = [2147483648, state]
    # check if leaf node
    if depth == 0:  # check_terminal(state, x, y, r, width, height) or
        # return utility of the state
        eval_value = eval_state(state)
        # print("Eval state val = " + str(eval_value))
        return[eval_value, state]

    # Get all child nodes
    for x in range(0, width):

        sem.acquire()
        out_of_time = time_up
        sem.release()
        if out_of_time:
            return v

        y = col_pieces(state, x)                    # get the next open space in the slot
        if y < height:                             # make sure the slot is not full

            # Make a copy of the current board and add a piece to it
            new_state = copy.deepcopy(state)
            new_state[x][y] = get_color_char(color)
            new_color = abs(color-1)

            # Get the max value of the next board
            max_v = max_value(new_state, depth-1, width, height, x, y, new_color, r, alpha, beta)
            # print("max v = " + str(max_v))
            if int(max_v[0]) <= int(v[0]):
                # print("New max_v value = " + str(max_v[0]))
                v[0] = max_v[0]

            # Check if v is <= alpha
            if int(v[0]) <= alpha:
                return v

            if int(v[0]) > beta:
                beta = v[0]
            # v = max(v[0], max_v[0])

    # print("min_value returning " + str(v))
    return v


# The max-value function of the minimax algorithm
def max_value(state, depth, width, height, x, y, color, r, alpha, beta):
    global time_up
    # print("Calling max_val")
    v = [-2147483648, state]

    # check if leaf node
    if depth == 0:  # check_terminal(state, x, y, r, width, height) or
        # return utility of the state
        eval_value = eval_state(state)
        # print("Eval state val = " + str(eval_value))
        return [eval_value, state]

    # Get all child nodes
    for x in range(0, width):

        sem.acquire()
        out_of_time = time_up
        sem.release()
        if out_of_time:
            return v


        y = col_pieces(state, x)  # get the next open space in the slot
        if y < height:  # make sure the slot is not full

            # Make a copy of the current board and add a piece to it
            new_state = copy.deepcopy(state)
            new_state[x][y] = get_color_char(color)
            new_color = abs(color - 1)

            # Get the max value of the next board
            min_v = min_value(new_state, depth-1, width, height, x, y, new_color, r, alpha, beta )
            # print("min v = " + str(min_v))
            if int(min_v[0]) >= int(v[0]):
                # print("New min_v value = " + str(min_v[0]))
                v[0] = min_v[0]

            # Check if V is >= to beta
            if int(v[0]) >= beta:
                return v

            if int(v[0]) > alpha:
                alpha = v[0]

            # v = min(v[0], min_v[0])

    # print("max_value returning " + str(v))
    return v


# Number of pieces in a column
def col_pieces(state, x):
    for y in range(0, len(state[x])):
        if state[x][y] is None:
            return y

    return len(state[x])


# generate the utility value of a state
def eval_state(state):
    global ai_color
    # The state value is calculated as follows
    # Every single piece on the board in a direction is 1 point
    # Every chain on the board in a direction is 5 * (pieces in chain)^2 points

    col_total = 0
    row_total = 0
    up_diag_total = 0
    down_diag_total = 0
    color = ai_color
    # print_state(state, len(state), len(state[0]))

    # Get columns total
    for x in range(0, len(state)):
        # cur_row = state[x][:]

        # val = eval_list(cur_row, color)
        val = eval_list(state[x], color)
        # print("Col = " + str(cur_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        col_total += val

    # Get rows total
    for y in range(0, len(state[0])):
        row_list = []
        for x in range(0, len(state)):
            row_list.append(state[x][y])

        val = eval_list(row_list, color)
        # print(" Row = " + str(row_list) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        row_total += eval_list(row_list, color)

    # Get up diag total

    # The bottom left corner diagonal and below
    top = len(state[0])
    for x in range(0, top):
        up_diag_row = []
        for i in range(0, top+1):
            col = i + x
            row = i
            if col < len(state) and row < top:
                up_diag_row.append(state[col][row])
        val = eval_list(up_diag_row, color)
        # print("Up diag row = " + str(up_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        up_diag_total += val
    # print("second half of up diag")

    # The diag above the bottom left corner
    top = len(state[0])
    for x in range(0, top):
        up_diag_row = []
        for i in range(0, top + 1):
            col = i
            row = x + i + 1
            if col < len(state) and row < top:
                up_diag_row.append(state[col][row])
        val = eval_list(up_diag_row, color)
        # print("Up diag row above = " + str(up_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        up_diag_total += val

    # Get down diag total

    # The top left corner diagonal and below
    top = len(state[0]) - 1
    for x in range(top, -1, -1):
        down_diag_row = []
        for i in range(0, top+1):
            col = i
            row = x - i
            if col < len(state) and row >= 0:
                down_diag_row.append(state[col][row])
        val = eval_list(down_diag_row, color)
        # print("Down diag row = " + str(down_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        down_diag_total += val
    # print("second half of down diag")

    # Diagonals above the top left corner diagonal
    for x in range(top, -1, -1):
        down_diag_row = []
        for i in range(0, top + 1):
            col = 1 + i + top - x
            row = x - i
            if col < len(state) and row >= 0:
                down_diag_row.append(state[col][row])
        val = eval_list(down_diag_row, color)
        # print("Down diag row above= " + str(down_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        down_diag_total += val
    # print("Down diag total = " + str(down_diag_total))
    # print()
    # print('Total state utility = ' + str(col_total + row_total + up_diag_total + down_diag_total))
    # print()
    return col_total + row_total + up_diag_total + down_diag_total


# gets the number of points from a single row based on the formula in eval state
def eval_list(row, color):
    global red_char
    global black_char
    global connect
    global max_val
    global min_val

    # Check if the list has already been processed
    answer = speed_up.get_list_value(row, color)
    if answer is not None:
        return answer

    # New eval algorithm
    cur_color = None
    num_spaces = 0
    prev_spaces = 0
    chain_length = 0
    total = 0

    if len(row) < connect:
        return 0

    # print"Eval row = " + str(row))
    for x in range(0, len(row) + 1):

        if chain_length >= connect:
            if cur_color == black_char:
                if get_color_char(color) == black_char:
                    speed_up.save_list_value(row, max_val, color)
                    return max_val
                else:
                    speed_up.save_list_value(row, min_val, color)
                    return min_val
            elif cur_color == red_char:
                if get_color_char(color) == red_char:
                    speed_up.save_list_value(row, max_val, color)
                    return max_val
                else:
                    speed_up.save_list_value(row, min_val, color)
                    return min_val


        # print'Total = ' + str(total) + ' Cur_color = ' + str(cur_color) + " prev_spaces = " + str(prev_spaces) + " num_spaces = " + str(num_spaces) + " chain_length = " + str(chain_length))
        if x == len(row):
            # Evaluate the color
            # If changing colors
            if cur_color == black_char:

                if chain_length >= connect:
                    if get_color_char(color) == black_char:
                        speed_up.save_list_value(row, max_val, color)
                        return max_val
                    else:
                        speed_up.save_list_value(row, min_val, color)
                        return min_val
                        # print"Total = " + str(total), end=" ")
                # Eval the black pieces points
                elif (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    # print"Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == black_char:
                        total += points
                    else:
                        total -= points
                        # print"Total = " + str(total), end=" ")
            elif cur_color == red_char:

                if chain_length >= connect:
                    if get_color_char(color) == red_char:
                        speed_up.save_list_value(row, max_val, color)
                        return max_val
                    else:
                        speed_up.save_list_value(row, min_val, color)
                        return min_val
                        # print"Total = " + str(total), end=" ")
                # Eval the black pieces points
                elif (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    # print"Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == red_char:
                        total += points
                    else:
                        total -= points
                        # print"Total = " + str(total), end=" ")
            break

        if row[x] is None:
            num_spaces += 1
            if chain_length >= 1:
                chain_length -= .5

        # if the current piece is red
        elif row[x] == red_char:
            # print'row[x] == red_char')
            # If changing colors
            if cur_color == black_char:

                if chain_length >= connect:
                    if get_color_char(color) == black_char:
                        speed_up.save_list_value(row, max_val, color)
                        return max_val
                    else:
                        speed_up.save_list_value(row, min_val, color)
                        return min_val
                        # print"Total = " + str(total), end=" ")
                # Eval the black pieces points
                if (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    # print"Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == black_char:
                        total += points
                    else:
                        total -= points
                    # print"Total = " + str(total), end=" ")
                    chain_length = 1
                    prev_spaces = 0
                cur_color = red_char
                chain_length = 1
            elif cur_color == red_char:
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1
            else:
                cur_color = red_char
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1

        # If the current piece is black
        elif row[x] == black_char:
            # print"row[x] == black_char")
            # If changing colors
            if cur_color == red_char:

                if chain_length >= connect:
                    if get_color_char(color) == red_char:
                        speed_up.save_list_value(row, max_val, color)
                        return max_val
                    else:
                        speed_up.save_list_value(row, min_val, color)
                        return min_val
                        # print"Total = " + str(total), end=" ")
                # Eval the black pieces points
                if (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    # print"Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == red_char:
                        total += points
                    else:
                        total -= points
                    # print" Total = " + str(total), end=" ")
                    chain_length = 1
                    prev_spaces = 0
                cur_color = black_char
                chain_length = 1
            elif cur_color == black_char:
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1
            else:
                cur_color = black_char
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1

    # Save the answer to the dictionary
    speed_up.save_list_value(row, total, color)

    return total


# returns the proper character for a color
def get_color_char(color):
    if color == 0:
        # print("color = " + str(color) + " returning " + black_char)
        return black_char
    elif color == 1:
        # print("color = " + str(color) + " returning " + red_char)
        return red_char
    else:
        # print("color = " + str(color) + " returning " + '!')
        return '!'


# #############################################################################
#
#   Code Below this point was only used for testing purposes
#
# #############################################################################


# generate all possible states given an initial state, depth, width, and height
def generate_states(init_state, depth, width, height, color, r):
    global red_char
    global black_char
    new_states = []
    x_val = 0
    y_val = 0
    if depth < 0:
        return()

    # Generate a state for placing a piece in every slot
    for x in range(0, width):
        new_state = copy.deepcopy(init_state)                          # make a copy of the initial state
        x_val = x
        # get the next open position in the list for the x column
        for y in range(0, height + 1):

            if new_state[x][y] is None:
                if color == 1:
                    new_state[x][y] = red_char
                else:
                    new_state[x][y] = black_char
                y_val = y
                break
            if (height - 1) == y:
                # No empty spot was found, this slot is full
                break

        print_state(new_state, width, height)

        # Check if this is a terminal state
        if check_terminal(new_state, x_val, y_val, r, width, height):
            print("Terminal State found ")
            print('')
            print('')

        else:
            if color == 1:
                generate_states(new_state, depth - 1, width, height, 0, r)
            else:
                generate_states(new_state, depth - 1, width, height, 1, r)
        # new_states.append(new_state)                # add the new_state to the list of possible states


# check if a state is a terminal state, based on where a piece was placed
def check_terminal(state, x, y, r, width, height):
    global red_char
    global black_char
    print("Checking for terminal states  x = " + str(x) + " y = " + str(y))
    b_count = 0
    r_count = 0
    last_piece = 0

    # Four "lines" to check for r pieces in a row: vertical, horizontal, diagonal up, diagonal down

    # Check if vertical connections
    start = y - r
    stop = y + r

    if start < 0:           # Check to make sure the start position is not below the board
        start = 0
    if stop > height:     # check to make sure the stop position is not below the board
        stop = height

    print("Vertical start = " + str(start) + ", stop = " + str(stop))
    for y_val in range(start, stop):
        # Add any sequence of colors to the count seen so far

        if state[x][y_val] == red_char:
            if last_piece == black_char:
                b_count = 0
            r_count += 1
            last_piece = red_char
            print("Found red piece at state[" + str(x) + "][" + str(y_val) + "] r_count = " + str(r_count) + " b_count = " + str(b_count))
        elif state[x][y_val] == black_char:
            if last_piece == red_char:
                r_count = 0
            b_count += 1
            last_piece = black_char
            print("Found black piece at state[" + str(x) + "][" + str(y_val) + "] r_count = " + str(r_count) + " b_count = " + str(b_count))
        else:
            r_count = 0
            b_count = 0
            print("Found no piece at state[" + str(x) + "][" + str(y_val) + "] red_count = " + str(r_count) + " b_count = " + str(b_count))

        print("Vertical counts: red = " + str(r_count) + " black = " + str(b_count))
        # Check if any sequence meets the termination condition
        if b_count >= r or r_count >= r:
            return True

    # Check if horizontal connections
    b_count = 0
    r_count = 0
    start = x - r
    stop = x + r

    if start < 0:  # Check to make sure the start position is not below the board
        start = 0
    if stop > width:  # check to make sure the stop position is not below the board
        stop = width

    print("Horizontal start = " + str(start) + ", stop = " + str(stop))
    for x_val in range(start, stop, 1):
        # Add any sequence of colors to the count seen so far
        if state[x_val][y] == red_char:
            if last_piece == black_char:
                b_count = 0
            r_count += 1
            last_piece = red_char
            print("Found red piece at state[" + str(x_val) + "][" + str(y) + "] r_count = " + str(r_count) + " b_count = " + str(b_count))
        elif state[x_val][y] == black_char:
            if last_piece == red_char:
                r_count = 0
            b_count += 1
            last_piece = black_char
            print("Found black piece at state[" + str(x_val) + "][" + str(y) + "] r_count = " + str(r_count) + " b_count = " + str(b_count))
        else:
            last_piece = "0"
            r_count = 0
            b_count = 0
            print("Found no piece at state[" + str(x_val) + "][" + str(y) + "] red_count = " + str(r_count) + " b_count = " + str(b_count))

        # print("Horizontal counts: red = " + str(r_count) + " black = " + str(b_count))
        # Check if any sequence meets the termination condition
        if b_count >= r or r_count >= r:
            return True

    return False


# prints a state to the screen
def print_state(state, width, height):
    # print the board values
    print("A.I. State: ")
    for x in range(height - 1, -1, -1):
        for y in range(0, width):
            if state[y][x] is None:
                print('.', end=' ')
                # elif current_board[y][x] == 'R':
                # print('\033[0;31;40mR\033[0;37;40m', end=' ')
                # elif current_board[y][x] == 'B':
                # print('\033[0;30;40mB\033[0;37;40m', end=' ')
            else:
                print(state[y][x], end=' ')
        print('')
    # print numbers for each row
    for x in range(1, width + 1):
        print(str(x), end=' ')
    print('')
    print(' ')


# generate the utility value of a state
def print_eval_state(state):
    global ai_color
    # The state value is calculated as follows
    # Every single piece on the board in a direction is 1 point
    # Every chain on the board in a direction is 5 * (pieces in chain)^2 points

    total = 0
    col_total = 0
    row_total = 0
    up_diag_total = 0
    down_diag_total = 0
    color = ai_color
    # print_state(state, len(state), len(state[0]))

    # Get columns total
    for x in range(0, len(state)):
        cur_row = state[x][:]

        val = print_eval_list(cur_row, color)
        print("Col = " + str(cur_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        col_total += val

    # Get rows total
    for y in range(0, len(state[0])):
        row_list = []
        for x in range(0, len(state)):
            row_list.append(state[x][y])

        val = eval_list(row_list, color)
        print("Row = " + str(row_list) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        row_total += val

    # Get up diag total

    # The bottom left corner diagonal and below
    top = len(state[0])
    for x in range(0, top):
        up_diag_row = []
        for i in range(0, top+1):
            col = i + x
            row = i
            if col < len(state) and row < top:
                up_diag_row.append(state[col][row])
        val = eval_list(up_diag_row, color)
        print("Up diag row = " + str(up_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        up_diag_total += val
    print("second half of up diag")

    # The diag above the bottom left corner
    top = len(state[0])
    for x in range(0, top):
        up_diag_row = []
        for i in range(0, top + 1):
            col = i
            row = x + i + 1
            if col < len(state) and row < top:
                up_diag_row.append(state[col][row])
        val = eval_list(up_diag_row, color)
        print("Up diag row above = " + str(up_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        up_diag_total += val

    # Get down diag total

    # The top left corner diagonal and below
    top = len(state[0]) - 1
    for x in range(top, -1, -1):
        down_diag_row = []
        for i in range(0, top+1):
            col = i
            row = x - i
            if col < len(state) and row >= 0:
                down_diag_row.append(state[col][row])
        val = eval_list(down_diag_row, color)
        print("Down diag row = " + str(down_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        down_diag_total += val
    print("second half of down diag")

    # Diagonals above the top left corner diagonal
    for x in range(top, -1, -1):
        down_diag_row = []
        for i in range(0, top + 1):
            col = 1 + i + top - x
            row = x - i
            if col < len(state) and row >= 0:
                down_diag_row.append(state[col][row])
        val = eval_list(down_diag_row, color)
        print("Down diag row above= " + str(down_diag_row) + " val = " + str(val))
        if val >= max_val:
            return val
        elif val <= min_val:
            return val
        down_diag_total += val
    print("Down diag total = " + str(down_diag_total))
    print()
    print('Total state utility = ' + str(col_total + row_total + up_diag_total + down_diag_total))
    print()
    return col_total + row_total + up_diag_total + down_diag_total


# gets the number of points from a single row based on the formula in eval state
def print_eval_list(row, color):
    global red_char
    global black_char
    global connect
    global max_val
    global min_val

    # Check if the list has already been processed
    # answer = speed_up.get_list_value(row)
    # if answer is not None:
    #    return answer

    # New eval algorithm
    cur_color = None
    num_spaces = 0
    prev_spaces = 0
    chain_length = 0
    total = 0

    if len(row) < connect:
        return 0

    print("Eval row = " + str(row))
    for x in range(0, len(row) + 1):
        print('Total = ' + str(total) + ' Cur_color = ' + str(cur_color) + " prev_spaces = " + str(prev_spaces) + " num_spaces = " + str(num_spaces) + " chain_length = " + str(chain_length))

        if chain_length >= connect:
            if cur_color == black_char:
                if get_color_char(color) == black_char:
                    speed_up.save_list_value(row, max_val, color)
                    return max_val
                else:
                    speed_up.save_list_value(row, min_val, color)
                    return min_val
            elif cur_color == red_char:
                if get_color_char(color) == red_char:
                    speed_up.save_list_value(row, max_val, color)
                    return max_val
                else:
                    speed_up.save_list_value(row, min_val, color)
                    return min_val

        if x == len(row):
            # Evaluate the color
            # If changing colors
            if cur_color == black_char:

                if chain_length >= connect:
                    if get_color_char(color) == black_char:
                        return max_val
                    else:
                        return min_val
                        print("Total = " + str(total), end=" ")
                # Eval the black pieces points
                elif (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    print("Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == black_char:
                        total += points
                    else:
                        total -= points
                        print("Total = " + str(total), end=" ")
            elif cur_color == red_char:

                if chain_length >= connect:
                    if get_color_char(color) == red_char:
                        return max_val
                    else:
                        return min_val
                        print("Total = " + str(total), end=" ")
                # Eval the black pieces points
                elif (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    print("Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == red_char:
                        total += points
                    else:
                        total -= points
                        print("Total = " + str(total), end=" ")
            break

        if row[x] is None:
            num_spaces += 1
            if chain_length >= 1:
                chain_length -= .5

        # if the current piece is red
        elif row[x] == red_char:
            print('row[x] == red_char')
            # If changing colors
            if cur_color == black_char:

                if chain_length >= connect:
                    if get_color_char(color) == black_char:
                        return max_val
                    else:
                        return min_val
                        print("Total = " + str(total), end=" ")
                # Eval the black pieces points
                if (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    print("Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == black_char:
                        total += points
                    else:
                        total -= points
                    print("Total = " + str(total), end=" ")
                    chain_length = 1
                    prev_spaces = 0
                cur_color = red_char
                chain_length = 1
            elif cur_color == red_char:
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1
            else:
                cur_color = red_char
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1

        # If the current piece is black
        elif row[x] == black_char:
            print("row[x] == black_char")
            # If changing colors
            if cur_color == red_char:

                if chain_length >= connect:
                    if get_color_char(color) == red_char:
                        return max_val
                    else:
                        return min_val
                        print("Total = " + str(total), end=" ")
                # Eval the black pieces points
                if (prev_spaces + num_spaces) + chain_length < connect:
                    total += 0  # Give no points for chains that cannot be completed
                    print("Total = " + str(total), end=" ")
                else:
                    points = 5 * (chain_length ** 2) + min(num_spaces, connect) + min(prev_spaces, connect)
                    if get_color_char(color) == red_char:
                        total += points
                    else:
                        total -= points
                    print(" Total = " + str(total), end=" ")
                    chain_length = 1
                    prev_spaces = 0
                cur_color = black_char
                chain_length = 1
            elif cur_color == black_char:
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1
            else:
                cur_color = black_char
                prev_spaces += num_spaces
                num_spaces = 0
                chain_length += 1

    # Save the answer to the dictionary
    # speed_up.save_list_value(row, total)

    return total
