# Justen McLean
# Artificial Intelligence
# Project 3
# 2017

import random
import copy
import sys


class Player:

    def __init__(self):
        self.seed = 2               # The seed value for random
        self.q_table = []
        self.e_table = []
        self.state = [0, 0]         # s = [col, row]
        self.action = 0             # value between 0-3
        self.r_tile = [10, 10]      # position of the reward tile = [col, row]
        self.reward = []
        self.action_p = 0           # between 0-3, 0 = up, 1 = right, 2 = down, 3 = left
        self.state_p = [0, 0]       # s' = [col, row]
        self.alpha = 0.4
        self.delta = 0
        self.gamma = 0.8
        self.lambda_ = 0.9
        self.epsilon = 0.9
        self.epsilon_decrease = 0.001
        self.epsilon_decreasing = True
        self.total_steps = 0
        self.episodes = 0
        self.steps = 0
        self.random = random
        self.set_qtable()
        self.set_etable()
        self.obstacles = set()
        self.set_grid_boundaries()

    # Set the values for the q_table
    def set_qtable(self):
        for i in range(20):
            row = []
            for j in range(20):
                directions = []
                for k in range(4):
                    self.random.seed(self.seed)
                    direction = self.random.uniform(0, 0.1)
                    directions.append(direction)
                    self.seed += 1
                row.append(directions)
            self.q_table.append(row)

        # print("q_table length: " + str(len(self.q_table)))
        # print(self.q_table)

    # Set the values for the e_table
    def set_etable(self):
        _cols = []
        for i in range(20):
            row = []
            for j in range(20):
                vals = [0, 0, 0, 0]
                row.append(vals)
            _cols.append(row)
        self.e_table = copy.deepcopy(_cols)
        # print("e_table length: " + str(len(self.e_table)))
        # print("e_table[0] length: " + str(len(self.e_table[0])))

    # Set Q values outside of the grid to -1
    def set_grid_boundaries(self):

        # Set Q value for moving outside the grid rows to -1
        for i in range(len(self.q_table[0])):
            self.q_table[i][0][0] = copy.copy(-1.0)
            self.q_table[i][19][2] = copy.copy(-1.0)

        # print(self.q_table)
        # Set Q for moving outside the grid cols to -1
        for i in range(len(self.q_table)):
            self.q_table[0][i][3] = copy.copy(-1.0)
            self.q_table[19][i][1] = copy.copy(-1.0)

        # print(self.q_table)

    # Set Q values for obstacles to -1, obstacles = list of [col, row] of obstacles
    def set_obstacle_boundaries(self, obstacles):

        # Change all actions leading to the obstacle to 0
        for i in range(len(obstacles)):
            col = int(obstacles[i][0])
            row = int(obstacles[i][1])
            if not (col, row) in obstacles:
                self.obstacles.add((col, row))

            if col >= 1:
                self.q_table[col - 1][row][1] = -1
            if col <= (len(self.q_table) - 2):
                self.q_table[col + 1][row][3] = -1
            if row >= 1:
                self.q_table[col][row - 1][2] = -1
            if row <= (len(self.q_table[0]) - 2):
                self.q_table[col][row + 1][0] = -1

        # print("q_table after adding obstacles: " + str(self.q_table))

    # Set the reward tile position
    def set_reward_tile(self, col, row):
        self.r_tile = [col, row]

    # perform an episode
    def episode(self, start_col, start_row):

        self.episodes += 1
        if start_col == -1 or start_row == -1:
            self.get_random_start()
        else:
            self.state = [start_row, start_col]
        self.action = self.get_action(self.state[0], self.state[1])  # get an action
        self.set_etable()
        self.steps = 0

        while self.r_tile != self.state:
            self.step()

        if self.epsilon_decreasing and self.epsilon >= 0.1:
            self.epsilon -= self.epsilon_decrease

    # perform a step of an episode
    def step(self):
        self.steps += 1                                             # increment the step count
        self.total_steps += 1
        self.state_p = copy.deepcopy(self.get_state(self.state, self.action))      # perform the action
        # print("state_p: " + str(self.state_p))
        if self.r_tile == self.state_p:
            reward = 1
        else:
            reward = 0
        self.action_p = self.get_action(self.state_p[0], self.state_p[1])               # get a'
        # print("action_p: " + str(self.action_p))

        self.get_delta(reward)
        self.e_table[self.state[0]][self.state[1]][self.action] += 1

        # Modify all q_tables and e_tables
        for i in range(20):
            for j in range(20):
                for k in range(4):
                    # Do not modify the out of bound q_values
                    if self.q_table[i][j][k] == -1:
                        continue
                    else:
                        self.q_table[i][j][k] += (self.alpha * self.delta * self.e_table[i][j][k])
                        self.e_table[i][j][k] *= self.gamma * self.lambda_

        self.state = copy.deepcopy(self.state_p)
        self.action = copy.deepcopy(self.action_p)

    # get an action for the current state
    def get_action(self, col, row):
        # Use epsilon greedy
        _action = 0
        try:
            if self.random.random() < self.epsilon:

                _action = self.random.randint(0, 3)
                # Don't allow the player to move into a restricted area
                # print("col: " + str(col) + " row: " + str(row) + " action: " + str(_action))
                while self.q_table[int(col)][int(row)][int(_action)] == -1:

                    _action = self.random.randint(0, 3)
                    # print("action = -1, retrying. col: " + str(col) + " row: " + str(row) + " action: " + str(action))
            else:
                # Otherwise get the max q value for the state
                _action = 0
                _action_val = 0
                # compare the q_table values for the current pos
                for i in range(4):

                    # Don't allow the player to move into a restricted area
                    if self.q_table[int(col)][int(row)][i] == -1:
                        continue

                    elif _action_val < self.q_table[int(col)][int(row)][i]:
                        _action_val = self.q_table[int(col)][int(row)][i]
                        _action = i
        except IndexError:
            print("Get_action exception: ", sys.exc_info()[0])
            print("q_table: " + str(self.q_table[19][10]))
        return _action

    # get a the new state given a state and an action
    def get_state(self, state, action):
        new_state = copy.deepcopy(state)

        if action == 0:
            new_state[1] -= 1
        elif action == 1:
            new_state[0] += 1
        elif action == 2:
            new_state[1] += 1
        elif action == 3:
            new_state[0] -= 1
        else:
            print("Player.get_state: action outside of allowed range")
        return new_state

    def get_delta(self, reward):
        self.delta = 0
        self.delta += reward
        q_val = ((self.gamma * self.q_table[self.state_p[0]][self.state_p[1]][self.action_p])
                 - self.q_table[self.state[0]][self.state[1]][self.action])
        self.delta += q_val

    # Put the player in a random start position
    def get_random_start(self):
        self.state = [random.randint(0, 19), random.randint(0, 19)]  # pick initial position
        # Don't let the player generate in the same position as the reward tile
        while self.r_tile == self.state or (self.state[0], self.state[1]) in self.obstacles:
            self.state = [random.randint(0, 19), random.randint(0, 19)]

    # Get the direction to point the tiles arrow
    def get_tile_direction(self, col, row):
        _max = 0
        max_value = 0
        if col >= 20 or row >= 20:
            print("get_tile_direction: request indices too high")
            return -1, 0

        for i in range(4):
            if self.q_table[col][row][i] > max_value:
                _max = i
                max_value = self.q_table[col][row][i]

        return _max, max_value

