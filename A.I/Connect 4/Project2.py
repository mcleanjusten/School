# Justen McLean
# Artificial Intelligence
# Project 2
# Project2.py
import threading
import time
import game_setup       # User prompts for game setup
import minimax          # Minimax algorithm
import alpha_beta       # Minimax with alpha_beta pruning
import speed_up         # Dictionary for saving row values
import testing          # Test alpha_beta utility functionality

# Global Variables
board_size = [100, 100]     # The size of the board N X M
r_val = 4               # How many pieces need to be connected to win a game
player_1 = 0            # Player 1 A.I. or Human ( 1 for human, 0 for A.I.)
player_1_color = 1      # Red or Black ( 1 for red, 0 for black)
player_2 = 0            # Player 2 A.I. or Human ( 1 for human, 0 for A.I.)
player_2_color = None   # Red or Black ( 1 for red, 0 for black)
time_limit = 10         # How long can the A.I. search for a solution ( -1 for infinite )
search_depth = 2        # How deep can the A.I. search for a solution ( -1 for infinite )
game_over = False       # Is the game over?
current_board = None    # The current board represented as an array
current_turn = 1        # Always start with red going first
ai_done = False         # Is the A.I. done making its move ?
ai_status = False       # Should an ai_thread be running? (0 for stopped, 1 for running)
red_char = 'X'          # The character to use for the red piece
black_char = 'O'        # The character to use for the black piece
empty_char = '.'        # the character to use for an empty space
turn_num = 1


# Setup the game
def setup_game():
    global board_size
    global r_val
    global player_1
    global player_1_color
    global player_2
    global player_2_color
    global time_limit
    global search_depth
    global current_board

    board_size = game_setup.get_board_size()
    r_val = game_setup.get_connect_length()
    player_1 = game_setup.get_player(1)
    player_1_color = game_setup.get_color(1)
    player_2 = game_setup.get_player(2)

    # Set player 2's color
    if player_1_color == 0:
        player_2_color = 1
    else:
        player_2_color = 0

    # Ask for a time limit and search depth if one player or more players is A.I.
    if player_1 == 0 or player_2 == 0:
        # x = 1 + 1
        time_limit = game_setup.get_time_limit()
        search_depth = game_setup.get_search_depth()

    current_board = game_setup.initialize_board(board_size[0], board_size[1])

    # Set the connect value in alpha_beta
    alpha_beta.sem.acquire()
    alpha_beta.connect = r_val
    alpha_beta.sem.release()


# Display the board
def print_board():
    global empty_char
    global red_char
    global black_char

    print("Lines in dictionary = " + str(speed_up.get_list_values_size()))
    print("Current Board: ")
    # print the board values
    for x in range(board_size[1]-1, -1, -1):
        for y in range(0, board_size[0]):
            if current_board[y][x] is None:
                print(empty_char, end=' ')
            else:
                print(current_board[y][x], end=' ')
        print('')
    # print numbers for each row
    for x in range(1, board_size[0]+1):
        print(str(x), end=' ')
    print('')
    print('')
    print('')


# Start a players turn
def turn(player_num):
    global time_limit
    global ai_done
    global ai_status
    global current_board
    global player_1_color
    global player_2_color
    global player_1
    global player_2
    global turn_num

    # Print who's turn it is
    print("Turn Number: " + str(turn_num))

    # check if it's player 1's turn or player 2's turn
    if player_num == 1:
        if player_1 == 0:           # Check if the player is an A.I. agent

            # Reset the alpha_beta variables so the AI can run
            alpha_beta.sem.acquire()
            alpha_beta.time_up = False
            alpha_beta.done = False
            alpha_beta.best_move_state = None
            alpha_beta.ai_color = player_1_color
            alpha_beta.sem.release()

            # Start a new thread and run the A.I. for this player
            ai_thread = threading.Thread(target=get_ai_move, args=(player_1_color, ))
            ai_thread.start()
            ai_done = False

            # Start a new timer for the A.I.
            start_time = time.time()
            stop_time = start_time + time_limit

            # Loop to check if the ai is out of time or done making it's move
            while stop_time >= time.time() and not ai_done:
                time.sleep(1)                               # Stop while loop from delaying thread semaphore acquires
                if alpha_beta.sem.acquire(blocking=False):
                    ai_done = alpha_beta.done
                    alpha_beta.sem.release()

            # Get the stop time, print how long the turn took
            done_time = time.time()
            print("Time taken = " + str(abs(done_time - start_time)))

            # If the ai is out of time set the time_up flag to true
            if stop_time < done_time:
                print("AI out of time")

                alpha_beta.sem.acquire()
                alpha_beta.time_up = True
                current_board = alpha_beta.best_move_state
                alpha_beta.sem.release()

            else:
                print("AI done")
                alpha_beta.sem.acquire()
                current_board = alpha_beta.best_move_state
                alpha_beta.sem.release()

        # Player is a human
        else:
            col_to_add_piece = get_human_move()
            add_piece_to_board(col_to_add_piece, player_1_color)

        # Check for a winner
        check_winner(1, player_1_color)

    # Player 2's turn
    else:
        if player_2 == 0:           # Check if the player is an A.I. agent

            # Reset the alpha_beta variables so the AI can run
            alpha_beta.sem.acquire()
            alpha_beta.time_up = False
            alpha_beta.done = False
            alpha_beta.best_move_state = None
            alpha_beta.ai_color = player_2_color
            alpha_beta.sem.release()

            # Start a new thread and run the A.I. for this player
            ai_status = True
            ai_thread = threading.Thread(target=get_ai_move, args=(player_2_color, ))
            ai_thread.start()
            ai_done = False

            # Start a new timer for the A.I.
            start_time = time.time()
            stop_time = start_time + time_limit

            # Loop to check if the ai is out of time or done making it's move
            while stop_time >= time.time() and not ai_done:
                time.sleep(1)                                # Stop while loop from delaying thread semaphore acquires
                if alpha_beta.sem.acquire(blocking=False):
                    ai_done = alpha_beta.done
                    alpha_beta.sem.release()

            # Get the stop time, print how long the turn took
            done_time = time.time()
            print("Time taken = " + str(abs(done_time - start_time)))

            # If the ai is out of time set the time_up flag to true
            if stop_time < done_time:
                print("AI out of time")

                alpha_beta.sem.acquire()
                alpha_beta.time_up = True
                current_board = alpha_beta.best_move_state
                alpha_beta.sem.release()

            else:
                print("AI done")
                alpha_beta.sem.acquire()
                current_board = alpha_beta.best_move_state
                alpha_beta.sem.release()

        # Player is a human
        else:
            col_to_add_piece = get_human_move()
            add_piece_to_board(col_to_add_piece, player_2_color)

        # Check for a winner
        check_winner(2, player_2_color)


# Get's human's move and add it to the board
def get_human_move():
    global board_size
    row_to_add = int(input('Where would you like to place your piece? ( 1 - ' + str(board_size[0]) + ')')) - 1
    return row_to_add


# Get's the A.I.'s move and add's it to the board
def get_ai_move(color):
    global search_depth
    global board_size
    global r_val
    global current_board

    # Run either the minimax or alpha_beta algorithm
    # minimax.minimax_decision(current_board, search_depth, board_size[0], board_size[1], color, r_val)
    alpha_beta.alpha_beta_search(current_board, search_depth, board_size[0], board_size[1], color, r_val)
    return 0


# Add a selection to the board
def add_piece_to_board(col_num, color):
    x = 0
    while current_board[col_num][x] is not None:
        x += 1
    if color == 1:
        current_board[col_num][x] = red_char
    else:
        current_board[col_num][x] = black_char


# Checks the board for a winner
def check_winner(player_num, color):
    global game_over
    global current_board

    print("Is game_over : " + str(game_over))

    if game_over or current_board is None:
        return
    # check if the ai one
    alpha_beta.ai_color = color

    # Use the eval_state function to see if a board is equal to the max possible value
    alpha_beta.sem.acquire()
    board_value = alpha_beta.eval_state(current_board)
    alpha_beta.sem.release()

    print("Board State: " + str(board_value))
    if board_value >= alpha_beta.max_val:
        if player_num == 1:
            game_over = True
            print_board()
            print("Player 1 wins!")
        else:
            game_over = True
            print_board()
            print("Player 2 wins!")

    print("")


# Sets the turn to the next player
def set_next_turn():
    global current_turn
    global game_over
    global turn_num
    if game_over:
        return
    turn_num += 1

    if current_turn == 1:
        # print("Player 1's Turn")
        current_turn = 0
    else:
        # print("Player 2's Turn")
        current_turn = 1


# Set the game_over value to true
def set_game_over():
    global game_over
    game_over = True


def main():
    global board_size
    global current_board
    global game_over

    # testing.test_row_eval()           # Test the eval_list function

    setup_game()                        # Set up the game value

    # Main game looop
    while not game_over:
        print_board()  # Print the current Board
        turn(current_turn)              # Get the current players move
        set_next_turn()                 # Set the next turn

if __name__ == "__main__":
    main()