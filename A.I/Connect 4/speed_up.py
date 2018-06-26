red_list_values = {}
black_list_values = {}
list_size = 0

# Dictionary to allow saving values to avoid processing a line twice
def get_list_value(k, color):
    global red_list_values
    global black_list_values

    if color == 1:
        list_key = tuple(k)
        if list_key in red_list_values:
            # print("Found the row in the dictionary")
            return red_list_values[list_key]
        else:
            return None
    elif color == 0:
        list_key = tuple(k)
        if list_key in black_list_values:
            # print("Found the row in the dictionary")
            return black_list_values[list_key]
        else:
            return None


# Save a list to the dictionary
def save_list_value(line, value, color):
    global red_list_values
    global black_list_values
    global list_size

    k = tuple(line)
    if color == 1:
        red_list_values[k] = value
        list_size += 1
    elif color == 0:
        black_list_values[k] = value
        list_size += 1


# Get the number of values saved in list_values
def get_list_values_size():
    global list_size
    return list_size
