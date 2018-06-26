# Justen McLean
# Artificial Intelligence
# Project 4
import random
import math
import copy

num_input_nodes = 64
num_hidden_nodes = 16
num_output_nodes = 10

weight_set = {}     # Set of initialized weights to keep weights unique

# Solutions
target_nodes = [0] * num_output_nodes

# Testing
testing = False

# Input layer
input_nodes = [0] * num_input_nodes
input_weights = []          # weights of input layer edges
new_input_weights = []

# hidden layer nodes
hl_nodes = [0] * num_hidden_nodes
# hl_nodes[1] = 1             # set the bias node value
hl_weights = []             # weights from middle layer edges
new_hl_weights = []

# output layer
output_nodes = [0] * num_output_nodes
error_rate = []
total_error = 0

# back propagation
learning_rate = .5  # .5  # 4
err_total = 0
err_output = [0]

# bias nodes
input_bias_value = 1
input_bias_weights = [0] * num_hidden_nodes
hl_bias_value = 1
hl_bias_weights = [0] * num_output_nodes

rnd = random
seed = 1

# Creates a unique initial edge weight
def create_weight():
    global rnd
    global seed
    rnd.seed(seed)
    weight = rnd.uniform(.1, .7)
    seed += 1
    while weight in weight_set:
        rnd.seed(seed)
        weight = rnd.uniform(.1, .7)
        seed += 1
        print("Weight already existed trying again")

    return weight


# Creates a list of initial weights
def set_layer_weights(cur_layer_size, next_layer_size):
    layer_weights = [0] * cur_layer_size                          # list of all node_weights
    node_weights = [0] * next_layer_size  # list of all weights from a node

    # For each node in a layer make a list of weights to the next layer
    for i in range(0, cur_layer_size):

        # Set a weight for each edge coming from this node
        for j in range(0, next_layer_size):
            weight = create_weight()
            node_weights[j] = weight

        layer_weights[i] = node_weights[:]                          # copy the node weights to layer weights

    return layer_weights


# Creates a list of initial bias weights
def set_bias_weights(num_bias_weights):
    global input_bias_weights
    global hl_bias_weights

    bias_weights = [0] * num_bias_weights

    # Set the bias weights for input_bias_weights
    for i in range(0, num_bias_weights):
        weight = create_weight()
        bias_weights[i] = weight

    return bias_weights


# Set the input node values
def set_input(input_values):
    global input_nodes
    # print("set_input input_value: " + str(input_values))
    create_targets(input_values[-1])       # store the training solution
    # print("Target nodes:" + str(target_nodes))
    input_nodes = copy.deepcopy(input_values)
    input_nodes.pop()  # remove the solution from the input data
    # print("input_nodes size: " + str(len(input_nodes)))
    return


# Creates a set of values that are the targets for each output node
def create_targets(answer):
    global target_nodes
    for x in range(0, len(target_nodes)):
        if x == answer:
            target_nodes[x] = 0.99  # assign the solution value to correct node, leaving all others as 0
        else:
            target_nodes[x] = 0.01       # reset all target nodes to 0

    return


# Sums previous node * edge value to next nodes value
# input_nodes, input_weights, hl_nodes
def sum_nodes(cur_nodes, cur_weights, next_nodes):

    # Loop through all nodes in the cur_nodes
    for i in range(0, len(cur_nodes)):

        # Loop through all weight for the cur_node
        for j in range(0, len(cur_weights[i])):
            cur_val = cur_nodes[i] * cur_weights[i][j]      # Get the value of a node * its edge weight
            next_nodes[j] += cur_val                        # Add the value to the node at the other end of the edge

    return next_nodes


# sums the bias nodes
def sum_bias_nodes(bias_value, cur_weights, next_nodes):
    # Loop through all weight for the cur_node
    # print("size of cur_weights: " + str(cur_weights))
    for j in range(0, len(cur_weights)):
        cur_val = bias_value * cur_weights[j]  # Get the value of a node * its edge weight
        # print("cur_value: " + str(cur_val))
        # print("bias_value: " + str(bias_value))
        # print("cur_weights[" + str(j) + "]: " + str(cur_weights[j]))
        next_nodes[j] += cur_val  # Add the value to the node at the other end of the edge

    return next_nodes


# apply the sigmoid function to all nodes in a layer
def apply_sigmoid(cur_nodes):
    for x in range(0, len(cur_nodes)):
        cur_nodes[x] = sigmoid_function(cur_nodes[x])
    return


# applies a sigmund function to the given value
def sigmoid_function(value):
    return 1 / (1 + math.exp(-value))


# forward propagate the neural net
def forward_prop():
    global input_nodes
    global input_weights
    global input_bias_value
    global input_bias_weights
    global hl_nodes
    global hl_weights
    global hl_bias_value
    global hl_bias_weights
    global output_nodes

    # Get the sums for all hidden layer nodes
    hl_nodes = sum_nodes(input_nodes, input_weights, hl_nodes)
    # print("summed hl_nodes pre bias: " + str(hl_nodes))
    hl_nodes = sum_bias_nodes(input_bias_value, input_bias_weights, hl_nodes)
    # print("summed hl_nodes after bias: " + str(hl_nodes))
    # print("hl_nodes: " + str(hl_nodes))
    apply_sigmoid(hl_nodes)
    # print("hl_nodes after sigmoid: " + str(hl_nodes))

    # Get the sums for all output layer nodes
    output_nodes = sum_nodes(hl_nodes, hl_weights, output_nodes)
    output_nodes = sum_bias_nodes(hl_bias_value, hl_bias_weights, output_nodes)
    apply_sigmoid(output_nodes)
    get_total_error()

    return


# gets the probability of each column
def get_solution_prob():
    global output_nodes
    category_prob = []

    for x in range(len(output_nodes)):
        category_prob.append(output_nodes[x] * float(100))

    return category_prob


# gets which category had the highest percentage
def get_answer_category():
    global output_nodes
    max_val = 0
    position = -1

    # get the category with the highest percentage
    for x in range(0, len(output_nodes)):
        if output_nodes[x] > max_val:
            position = x
            max_val = output_nodes[x]

    return position


def get_total_error():
    global output_nodes
    global target_nodes
    global error_rate
    global total_error

    total_error = 0
    error_rate = [0] * len(output_nodes)
    for i in range(len(output_nodes)):
        error_rate[i] = .5 * ((target_nodes[i] - output_nodes[i]) * (target_nodes[i] - output_nodes[i]))
        total_error += error_rate[i]

    # print("Total error = " + str(total_error))


# back propagation for weights between the hidden layer and output
def back_prop_hl():
    global hl_nodes
    global hl_weights
    global new_hl_weights
    global output_nodes
    global target_nodes
    global learning_rate

    # temporary store new weights in a new list to avoid effecting next layers back propagation
    new_hl_weights = copy.deepcopy(hl_weights)
    weight_delta_output_dict = {}
    # Loop through all hidden layer nodes
    for i in range(0, len(hl_weights)):

        # Loop through all weights from that node
        for j in range(0, len(hl_weights[i])):

            if j in weight_delta_output_dict:
                # decrease processing time by avoiding repeated math
                weight_delta = weight_delta_output_dict[j]
            else:
                weight_delta = -(target_nodes[j] - output_nodes[j])
                # print("d ETotal / d Out" + str(j) + ": " + str(weight_delta))
                weight_delta = weight_delta * output_nodes[j] * (1 - output_nodes[j])
                # print("d Out" + str(j) + " / d Net" + str(j) + ": " + str(weight_delta))
                weight_delta_output_dict[j] = weight_delta
            weight_delta = weight_delta * hl_nodes[i]
            new_hl_weights[i][j] = hl_weights[i][j] - (learning_rate * weight_delta)
            # print()

    return


# back propagation for weights between the hidden layer bias and output
def back_prop_hl_bias():
    global hl_bias_value
    global hl_bias_weights
    global output_nodes
    global target_nodes
    global learning_rate
    weight_delta_output_dict = {}
    # Loop through all hidden layer bias nodes
    for i in range(0, len(hl_bias_weights)):
        # weight_delta = -(target_nodes[i] - output_nodes[i]) * output_nodes[i] * (1 - output_nodes[i]) * hl_bias_value
        if i in weight_delta_output_dict:
            # decrease processing time by avoiding repeated math
            weight_delta = weight_delta_output_dict[i]
        else:
            weight_delta = -(target_nodes[i] - output_nodes[i]) * output_nodes[i] * (1 - output_nodes[i])
            weight_delta_output_dict[i] = weight_delta
        hl_bias_weights[i] -= (learning_rate * weight_delta)

    return


# back propagation for weights between the input and hidden layer
def back_prop_input():
    global hl_nodes
    global hl_weights
    global output_nodes
    global target_nodes
    global learning_rate
    global input_nodes
    global input_weights
    global new_input_weights

    new_input_weights = copy.deepcopy(input_weights)
    # print("Running back_prop_input")
    # print(str(len(input_nodes)))
    # decrease processing time by avoiding repeated math
    output_delta_dict = {}
    # Loop through all the input nodes
    for i in range(0, len(input_nodes)):
        # print("i = " + str(i))
        # Loop through all the input weights
        for j in range(0, len(input_weights[i])):             # Pick a weight to update
            all_output_delta = 0

            # Loop through all the output nodes, ( Sum (DEtotal/Dout0) * (Dout0/dnet0) * (Dnet0/Douth1))
            for k in range(0, len(output_nodes)):
                if k in output_delta_dict:
                    # if False:
                    output_delta = output_delta_dict[k]
                else:
                    output_delta = -(target_nodes[k] - output_nodes[k])
                    # print("d Eo" + str(k) +" / d out" + str(k) + ": " + str(output_delta))
                    output_delta = output_delta * output_nodes[k] * (1 - output_nodes[k])
                    # print("d Out" + str(k) + " / d Net" + str(k) + ": " + str(output_delta))
                    output_delta_dict[k] = output_delta
                    # print("d Eo" + str(k) +" / d Out" + str(k) + " + " + "d Out" + str(k) + " / d Net" + str(k) + ": " + str(output_delta))
                output_delta = output_delta * hl_weights[j][k]
                # print("d Eo" + str(k) + " / d Out" + str(j) + ": " + str(output_delta))
                # print("output_delta: " + str(output_delta))
                all_output_delta += output_delta
                # print("d Etotal" + " / d Out" + str(j) + "+= " + str(output_delta))
            # print("All output_delta: " + str(all_output_delta))
            # Assign the new weight value to the input weight at ij
            # print("")
            # print("d Etotal" + " / d Out" + str(j) + "+= " + str(all_output_delta))
            # print("d Out h" + str(j) + " / d Net h" + str(j) + " = " + str(hl_nodes[j] * (1 - hl_nodes[j])))
            # print("d net h" + str(j) + " / d w" + str(j) + " = " + str(input_nodes[i]))
            new_val = all_output_delta * hl_nodes[j] * (1 - hl_nodes[j]) * input_nodes[i]
            new_val = (learning_rate * new_val)
            # print("input nodes: " + str(input_nodes))
            # print("hl nodes: " + str(hl_nodes))
            # print("hl nodes[j]: " + str(hl_nodes[j]) + " input_nodes[i]: " + str(input_nodes[i]))
            # print("new delta weight: " + str(new_val))
            new_input_weights[i][j] = input_weights[i][j] - new_val


# back propagation for weights between the input and hidden layer
def back_prop_input_bias():
    global hl_nodes
    global hl_weights
    global output_nodes
    global target_nodes
    global learning_rate
    global input_bias_value
    global input_bias_weights
    output_delta_dict = {}
    # Loop through all the input bias weights
    for j in range(0, len(input_bias_weights)):
        all_output_delta = 0

        # Loop through all the output nodes
        for k in range(0, len(output_nodes)):
            # output_delta = -(target_nodes[k] - output_nodes[k]) * output_nodes[k] * (1 - output_nodes[k])
            if k in output_delta_dict:
                output_delta = output_delta_dict[k]
            else:
                output_delta = -(target_nodes[k] - output_nodes[k]) * output_nodes[k] * (1 - output_nodes[k])
                output_delta_dict[k] = output_delta
            output_delta = output_delta * hl_weights[j][k]
            # print("output_delta: " + str(output_delta))
            all_output_delta += output_delta
            # print("All output_delta: " + str(all_output_delta))

        # Assign the new weight value to the input weight at ij
        new_val = all_output_delta * hl_nodes[j] * (1 - hl_nodes[j]) * input_bias_value
        # print("new bias weight: " + str(new_val))
        input_bias_weights[j] -= new_val

    return


# performs back propagation
def back_prop():
    global hl_weights
    global new_hl_weights
    global hl_bias_weights
    global input_weights
    global input_bias_weights
    back_prop_hl()
    back_prop_hl_bias()
    back_prop_input()
    back_prop_input_bias()

    # Print the old weights
    # print("New weights from hidden layer to output layer")
    # print(new_hl_weights)
    # print("")
    # print("New weights from input layer to hidden layer ")
    # print(input_weights)

    # print("Old Input weights: " + str(input_weights))
    # print("New Input weights: " + str(new_input_weights))

    # print("hl_bias_weights: " + str(hl_bias_weights))
    # print("input_bias_weights: " + str(input_bias_weights))

    # Save the new hidden layer weights
    hl_weights = new_hl_weights
    input_weights = new_input_weights

    return

