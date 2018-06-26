# Justen McLean
# Artificial Intelligence
# Project 3
# 2017
import tkinter as tk
import random
import sarsa
import time


class GridWorld(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        # Frames

        header_frame = tk.Frame(self)
        header_frame.pack(side="top", fill="x")
        button_frame = tk.Frame(header_frame)
        button_frame.pack(side="left", anchor="nw")
        text_frame = tk.Frame(header_frame)
        text_frame.pack(side="right", anchor="ne")
        entry_frame = tk.Frame(header_frame)
        entry_frame.pack(side="right", anchor="nw")
        button_frame_sub1 = tk.Frame(button_frame)
        button_frame_sub1.pack(side="top", anchor="nw", padx=10)
        button_frame_sub2 = tk.Frame(button_frame)
        button_frame_sub2.pack(side="top", anchor="nw", padx=10)
        entry_frame_sub1 = tk.Frame(entry_frame)
        entry_frame_sub1.pack(side="top", anchor="nw", fill="x", padx=10)
        entry_frame_sub2 = tk.Frame(entry_frame)
        entry_frame_sub2.pack(side="top", anchor="nw", fill="x", padx=10)
        entry_frame_sub3 = tk.Frame(entry_frame)
        entry_frame_sub3.pack(side="top", anchor="nw", fill="x", padx=10)
        text_frame_sub1 = tk.Frame(text_frame)
        text_frame_sub1.pack(side="left", anchor="nw", fill="x", padx=10)
        text_frame_sub2 = tk.Frame(text_frame)
        text_frame_sub2.pack(side="left", anchor="nw", fill="x", padx=10)
        text_frame_sub3 = tk.Frame(text_frame)
        text_frame_sub3.pack(side="left", anchor="nw", fill="x", padx=10)

        # Buttons
        self.obstacle_button = tk.Button(button_frame_sub1, text="Create Obstacles", width="15", command=(
            lambda: self.create_obstacles(self.obstacles_str_var.get())))
        self.obstacle_button.pack(side="left", anchor="n", fill="x", padx=0, pady=0)
        self.train_button = tk.Button(button_frame_sub1, text="Train", width="15", command=(lambda: self.train(
            self.training_str_var.get())))
        self.train_button.pack(side="left", anchor="n", fill="x", padx=10, pady=0)
        self.test_button = tk.Button(button_frame_sub1, text="Test", width="15", command=(lambda: self.multi_test(
            self.testing_str_var.get())))
        self.test_button.pack(side="left", anchor="n", fill="x", padx=0, pady=0)
        self.increase_test_button = tk.Button(button_frame_sub2, text="Increase Test Speed", width="15", command=(
            lambda: self.increase_speed()))
        self.increase_test_button.pack(side="left", anchor="nw", pady=5)
        self.decrease_test_button = tk.Button(button_frame_sub2, text="Decrease Test Speed", width="15", command=(
            lambda: self.decrease_speed()))
        self.decrease_test_button.pack(side="left", anchor="nw", padx=10, pady=5)

        # Summary
        # Summary Label
        self.summary_str_var = tk.StringVar()
        self.summary_str_var.set("Summary ")
        self.summary_text = tk.Label(text_frame_sub1,
                                     textvariable=self.summary_str_var, font="TKDefaultFont 9 underline")
        self.summary_text.pack(side="top", anchor="nw")

        # Episode text
        self.episode_str_var = tk.StringVar()
        self.episode_str_var.set("Episode: ")
        self.episode_text = tk.Label(text_frame_sub1, textvariable=self.episode_str_var)
        self.episode_text.pack(side="top", anchor="nw")

        # Step text
        self.step_str_var = tk.StringVar()
        self.step_str_var.set("Step: ")
        self.step_text = tk.Label(text_frame_sub1, textvariable=self.step_str_var)
        self.step_text.pack(side="top", anchor="nw")

        # Steps per episode label
        self.label_step_str_var = tk.StringVar()
        self.label_step_str_var.set("Steps per episode")
        self.label_step_text = tk.Label(text_frame_sub2,
                                        textvariable=self.label_step_str_var, font="TKDefaultFont 9 underline")
        self.label_step_text.pack(side="top", anchor="nw")

        # Total Average step text
        self.avg_step_str_var = tk.StringVar()
        self.avg_step_str_var.set("Total Average: ")
        self.avg_step_text = tk.Label(text_frame_sub2, textvariable=self.avg_step_str_var)
        self.avg_step_text.pack(side="top", anchor="nw")

        # Testing Average step text
        self.test_avg_step_str_var = tk.StringVar()
        self.test_avg_step_str_var.set("Testing Average: ")
        self.test_avg_step_text = tk.Label(text_frame_sub2, textvariable=self.test_avg_step_str_var)
        self.test_avg_step_text.pack(side="top", anchor="nw")
        
        # others per episode label
        self.label_other_str_var = tk.StringVar()
        self.label_other_str_var.set("Other")
        self.label_other_text = tk.Label(text_frame_sub3,
                                         textvariable=self.label_other_str_var, font="TKDefaultFont 9 underline")
        self.label_other_text.pack(side="top", anchor="nw")

        # Epsilon text
        self.epsilon_str_var = tk.StringVar()
        self.epsilon_str_var.set("Epsilon: ")
        self.epsilon_text = tk.Label(text_frame_sub3, textvariable=self.epsilon_str_var)
        self.epsilon_text.pack(side="top", anchor="nw")

        # Speed text
        self.speed_str_var = tk.StringVar()
        self.speed_str_var.set("Test Delay: 0.3 ")
        self.speed_text = tk.Label(text_frame_sub3, textvariable=self.speed_str_var)
        self.speed_text.pack(side="top", anchor="nw")

        # Config Input
        
        # training Label
        self.training_label_str_var = tk.StringVar()
        self.training_label_str_var.set("Times to train: ")
        self.training_label_text = tk.Label(entry_frame_sub1, textvariable=self.training_label_str_var)
        self.training_label_text.pack(side="left", anchor="nw")

        # Training input
        self.training_str_var = tk.StringVar()
        self.training_str_var.set("1000")
        self.training_entry = tk.Entry(entry_frame_sub1, textvariable=self.training_str_var, width="8")
        self.training_entry.pack(side="right", anchor="ne")
        
        # testing Label
        self.testing_label_str_var = tk.StringVar()
        self.testing_label_str_var.set("Times to test: ")
        self.testing_label_text = tk.Label(entry_frame_sub2, textvariable=self.testing_label_str_var)
        self.testing_label_text.pack(side="left", anchor="nw")

        # testing input
        self.testing_str_var = tk.StringVar()
        self.testing_str_var.set("1")
        self.testing_entry = tk.Entry(entry_frame_sub2, textvariable=self.testing_str_var, width="8")
        self.testing_entry.pack(side="right", anchor="ne")
        
        # obstacles Label
        self.obstacles_label_str_var = tk.StringVar()
        self.obstacles_label_str_var.set("Obstacles to make: ")
        self.obstacles_label_text = tk.Label(entry_frame_sub3, textvariable=self.obstacles_label_str_var)
        self.obstacles_label_text.pack(side="left", anchor="nw")

        # obstacles input
        self.obstacles_str_var = tk.StringVar()
        self.obstacles_str_var.set("20")
        self.obstacles_entry = tk.Entry(entry_frame_sub3, textvariable=self.obstacles_str_var, width="8")
        self.obstacles_entry.pack(side="right", anchor="ne")

        # Canvas
        self.canvas = tk.Canvas(self, width=1000, height=1000, borderwidth=0, highlightthickness=0)
        self.canvas.pack(side="top", anchor="s", fill="both", expand="true")

        # Agent
        self.agent = sarsa.Player()
        self.player_row = -10
        self.player_col = -10
        self.player_start_col = 0
        self.player_start_row = 0

        # Obstacles
        self.obstacles = []

        # Grid
        self.rows = 20
        self.columns = 20
        self.cell_width = 50
        self.cell_height = 50

        # Reward
        self.goal_row = 10
        self.goal_col = 10
        self.agent.set_reward_tile(self.goal_col, self.goal_row)

        # Canvas objects
        self.rect = {}              # The rectangles that form the grid
        self.obstacle = {}          # The rectangles that are obstacles
        self.player = 0             # The oval that is the player
        self.goal = 0               # The rectangle that is the goal state

        # The directional arrows
        self.up_char = u'\u2b06'
        self.down_char = u'\u2b07'
        self.left_char = u'\u2b05'
        self.right_char = u'\u27a1'
        self.arrows = []
        self.arrow_direction_dict = {}
        self.draw_count = 0
        self.arrow_color = "#000000"
        self.small_font_size = 11
        self.max_font_size = 38
        self.font_multiplier = 40

        # Random
        self.rand = random
        self.rand.seed(2)

        # UI Config
        self.stop = False
        self.delay = 0.3

        # Testing data
        self.test_episodes = 0
        self.test_steps = 0

        # Create the rectanges that make up the grid
        for column in range(self.columns):
            arrow_row = []
            for row in range(self.rows):
                x = column * self.cell_width + (self.cell_width / 2)
                y = row * self.cell_height + (self.cell_height / 2)
                x1 = column * self.cell_width
                y1 = row * self.cell_height
                x2 = x1 + self.cell_width
                y2 = y1 + self.cell_height
                self.rect[row, column] = self.canvas.create_rectangle(x1, y1, x2, y2, fill="white", tags="rect")
                cur_val = self.canvas.create_text(x, y, text="", tags="arrow", font=('Arial', self.small_font_size))
                arrow_row.append(cur_val)
            self.arrows.append(arrow_row)

        # Set player position
        x1 = self.player_col * self.cell_width
        x2 = x1 + self.cell_width
        y1 = self.player_row * self.cell_height
        y2 = y1 + self.cell_height
        self.player = self.canvas.create_oval(x1 + 2, y1 + 2, x2 - 2, y2 - 2, fill="blue", tags="player")

        # Set the goal position
        x1 = self.goal_col * self.cell_width
        x2 = x1 + self.cell_width
        y1 = self.goal_row * self.cell_height
        y2 = y1 + self.cell_height
        self.goal = self.canvas.create_rectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2, fill="green", tags="goal")

        self.redraw(1000)

    def redraw(self, delay):
        self.draw_arrows()
        self.episode_str_var.set("Episode: " + str(self.agent.episodes))
        if self.agent.total_steps > 0 and self.agent.episodes > 0:
            self.avg_step_str_var.set(
                "Total Average: " + str(round((self.agent.total_steps / self.agent.episodes), 2)))
        self.epsilon_str_var.set("Epsilon: " + str(round(self.agent.epsilon, 4)))
        self.step_str_var.set("Step: " + str(self.agent.steps))
        self.canvas.tag_raise("visited")
        self.canvas.tag_raise("arrow")
        self.canvas.tag_raise("obstacle")
        self.canvas.tag_raise("goal")
        self.canvas.tag_raise("player")
        self.after(delay, lambda: self.redraw(delay))

    def set_player_pos(self, col, row):
        x1 = col * self.cell_width
        y1 = row * self.cell_height
        x2 = x1 + self.cell_width
        y2 = y1 + self.cell_height

        # self.canvas.move("player", move_x, move_y)
        self.canvas.coords("player", x1, y1, x2, y2)

        self.player_row = row
        self.player_col = col
        # self.canvas.create_rectangle(x1 + 12, y1 + 12, x2 - 12, y2 - 12, fill="orange", tags="visited")
        if row >= 0 and col >= 0:
            self.canvas.itemconfig(self.arrows[col][row], fill="red")

    def draw_arrows(self):
        self.draw_count += 1
        for i in range(0, self.columns, 1):
            for j in range(0, self.rows, 1):
                direction = self.agent.get_tile_direction(i, j)

                if direction[0] == 0:
                    arrow_value = self.up_char
                elif direction[0] == 1:
                    arrow_value = self.right_char
                elif direction[0] == 2:
                    arrow_value = self.down_char
                elif direction[0] == 3:
                    arrow_value = self.left_char
                else:
                    arrow_value = ""

                font_size = min(int(self.small_font_size + (self.font_multiplier * direction[1])), self.max_font_size)
                self.arrow_direction_dict[(int(i), int(j))] = direction
                self.canvas.itemconfig(self.arrows[i][j], text=arrow_value, font=('Arial', font_size))

    def draw_color(self):
        if 1 < self.draw_count <= 255:  # Red
            self.arrow_color = "#" + self.get_hex_color(self.draw_count) + "0000"
        elif 255 < self.draw_count <= 510:  # Blue
            self.arrow_color = "#00" + self.get_hex_color(self.draw_count) + "00"
        elif 510 < self.draw_count <= 765:  # Green
            self.arrow_color = "#0000" + self.get_hex_color(self.draw_count)
        elif 765 < self.draw_count <= 1275:  # Purple
            self.arrow_color = "#" + self.get_hex_color(self.draw_count) + "FF00"
        elif 1275 < self.draw_count <= 1530:  # Cyan
            self.arrow_color = "#00" + self.get_hex_color(self.draw_count) + "FF"
        elif self.draw_count > 1530:          # Reset to red
            self.draw_count = 2
            self.arrow_color = "#" + self.get_hex_color(self.draw_count) + "0000"
        # print("draw_color: " + str(self.arrow_color))

    def get_hex_color(self, color):
        if color < 125:
            return str(hex(125))[2:4]
        else:
            return str(hex(color))[2:4]

    # Allow the user to decrease the test speed
    def decrease_speed(self):
        self.delay += 0.2
        self.speed_str_var.set("Test Delay: " + str(round(self.delay, 2)))

    # Allow the user to increase the test speed
    def increase_speed(self):
        self.delay -= 0.2
        if self.delay < 0:
            self.delay = 0
        self.speed_str_var.set("Test Delay: " + str(round(self.delay, 2)))

    def create_obstacles(self, num_to_make):
        # Set the obstacles
        for i in range(int(num_to_make)):
            row = self.rand.randint(0, 19)
            col = self.rand.randint(0, 19)

            # make sure an obstacle is not placed on top of the goal state
            while row == self.goal_row and col == self.goal_col:
                row = self.rand.randint(0, 19)
                col = self.rand.randint(0, 19)

            item_id = self.rect[row, col]
            self.canvas.itemconfig(item_id, fill="grey", tags="obstacle")
            self.obstacles.append([col, row])
        self.agent.set_obstacle_boundaries(self.obstacles)       # update the player with the obstacle bounds

    def train(self, iterations):
        self.train_button.config(state="disabled")
        self.test_button.config(state="disabled")

        # Change arrows back to black
        self.arrow_color = "#000000"
        self.arrow_direction_dict.clear()
        self.draw_count = 1
        self.canvas.itemconfig("arrow", fill=self.arrow_color)

        self.set_player_pos(-10, -10)     # hide the player

        for i in range(int(iterations)):
            if i == 0:
                self.agent.episode(self.player_start_col, self.player_start_row)        # send start pos coordinates
            else:
                self.agent.episode(-1, -1)              # get random start pos
            self.update()

        self.train_button.config(state="normal")
        self.test_button.config(state="normal")

    def multi_test(self, iterations):
        self.train_button.config(state="disabled")
        self.test_button.config(state="disabled")
        for i in range(int(iterations)):
            if i == 0:
                self.test(self.player_start_col, self.player_start_row)
            else:
                self.test(-1, -1)

        self.train_button.config(state="normal")
        self.test_button.config(state="normal")

    def test(self, start_col, start_row):
        # Reset the arrow colors for this iteration
        self.arrow_color = "#000000"
        self.arrow_direction_dict.clear()
        self.draw_count = 1
        self.canvas.itemconfig("arrow", fill=self.arrow_color)

        # Start an episode
        self.test_episodes += 1
        self.agent.episodes += 1

        if start_col == -1 or start_row == -1:
            self.agent.get_random_start()
        else:
            self.agent.state = [start_row, start_col]

        self.set_player_pos(self.agent.state[0], self.agent.state[1])
        time.sleep(self.delay)

        self.agent.action = self.agent.get_action(self.agent.state[0], self.agent.state[1])  # get an action
        self.agent.set_etable()
        self.agent.steps = 0

        # Update gui objects with current episode info
        # self.episode_str_var.set(" Episode: " + str(self.agent.episodes))
        self.player_row = self.agent.state[1]
        self.player_col = self.agent.state[0]

        # Perform episode steps
        while self.agent.r_tile != self.agent.state and not self.stop:

            self.test_steps += 1
            self.agent.step()
            col = self.agent.state_p[0]
            row = self.agent.state_p[1]
            self.set_player_pos(col, row)
            self.update()
            time.sleep(self.delay)

        if not self.stop:
            if self.agent.epsilon_decreasing and self.agent.epsilon >= 0.1:
                self.agent.epsilon -= self.agent.epsilon_decrease

            self.test_avg_step_str_var.set("Testing Average: " + str(
                self.test_steps / self.test_episodes))
        else:
            self.after(0, lambda: self.redraw(self.delay))

if __name__ == "__main__":
    app = GridWorld()
    app.mainloop()
