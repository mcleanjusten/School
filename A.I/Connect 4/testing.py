import alpha_beta
import Project2


def test_row_eval_manual():
    length = int(input('What size row to test?'))
    color = int(input('What color to test?'))
    connect = int(input('What is the connect value?'))

    row = []
    for i in range(0, length):
        space_val = input('input a value ( R for red, B for black, . for empty')
        if space_val == '.':
            row.append(None)
        elif space_val == 'R':
            row.append('R')
        else:
            row.append('B')

    alpha_beta.connect = connect

    print(str(row))
    print('Row value is ' + str(alpha_beta.eval_list(row, color)))


def test_row_eval():

    Project2.set_game_over()                          # Stop the main loop from running in main()
    color = 1
    connect = 4

    # Set a row to evaluate
    # row = ['X', None, 'X', None, 'O', None, None]
    # row = ['O', 'O', 'X', 'X', None, None]
    # row = ['O', 'O', 'X', 'X', 'X', 'X', 'X']
    # row = ['X', 'O', 'X', 'X', 'O', 'X']
    # row = [None, None, None, 'X', None, None, None]
    row = ['X', 'O', 'O', 'O', 'O', None, None]
    # row = ['O', None, None, 'O', 'O', 'O']
    # row = [None, None, None, None, None, None, 'X']

    alpha_beta.connect = connect                      # Set the connect value in alpha_beta

    print(str(row))
    print('Row value is ' + str(alpha_beta.print_eval_list(row, color)))
