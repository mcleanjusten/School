# Get the size of the board and return as a list with position 0 as X and position 1 as Y
def get_board_size():
    return_vals = [None]*2
    return_vals[0] = int(input('Input the X size of the board: '))
    return_vals[1] = int(input('Input the Y size of the board: '))
    return return_vals


# Get the number of pieces needed in a row to win the game
def get_connect_length():
    return int(input('Input the R length to win: '))


# Find out if the specified player is a human or A.I.
def get_player(player_num):
    player = int(input('Is player ' + str(player_num) + ' Human or A.I.? ( 1 for Human, 0 for A.I.) '))
    return player


# Find out if the specified player is going to be red or black
def get_color(player_num):
    color = int(input('Is player ' + str(player_num) + ' red or black ? ( 1 for red, 0 for black) '))
    return color


# Get the time_limit for the A.I. to search for an answer
def get_time_limit():
    return int(input('What should the time limit be in seconds?'))


# Get the max depth the A.I. is allowed to search to get an answer
def get_search_depth():
    return int(input('How deep should the A.I. search?'))


# Initialize the connect 4 board by using a list of columns
def initialize_board(width, height):
    print('Width = '+str(width))
    print('Height = '+str(height))
    cols = [None] * height                            # Initialize a column with the specified height
    print('Col = ' + str(cols))
    list_of_cols = []
    for x in range(0, width):
        list_of_cols.append(cols[:])

    print('List of cols = ' + str(list_of_cols))
    return list_of_cols
