# Justen Mclean
# Artificial Intelligence
# Project 4
# main.py

import neural_net
import time
import random

# Neural Net Configs
training_set_name = "optdigits_train.txt"
testing_set_name = "optdigits_test.txt"
weights_name = "neural_net_weights.txt"
training_set = []
testing_set = []


# get the testing data
def get_training_data():
    global training_set
    global training_set_name

    # open the testing file
    training_file = open(training_set_name, "r")

    # Add all lines into the testing_set
    for line in training_file:
        test = line.split(",")                 # split the line into values
        test = [int(x) for x in test]           # convert the strings to ints
        training_set.append(test)               # add the test to the training set

    training_file.close()                       # close the training file
    return


# get the testing data
def get_testing_data():
    global testing_set
    global testing_set_name

    # open the testing file
    testing_file = open(testing_set_name, "r")

    # Add all lines into the testing_set
    for line in testing_file:
        test = line.split(",")                 # split the line into values
        test = [int(x) for x in test]           # convert the strings to ints
        testing_set.append(test)                # add the test to the testing set

    testing_file.close()                        # close the testing file
    return


# saves the current weights to a text document
def save_weights():
    global weights_name

    # open the save file
    weights_file = open(weights_name, "a")

    # write the weights to the file
    weights_file.write("Start weights \n")
    # weights_file.write("Input weights: " + str(neural_net.input_weights) + "\n")
    weights_file.write("Input bias weights: " + str(neural_net.input_bias_weights) + "\n")
    # weights_file.write("Hidden Layer weights: " + str(neural_net.hl_weights) + "\n")
    weights_file.write("Hidden Layer bias weights: " + str(neural_net.hl_bias_weights) + "\n")
    weights_file.write("End weights \n")

    weights_file.close()
    return


# set up the weights for the neural net
def setup_neural_net():
    # Set the initial edge weights
    neural_net.input_weights = neural_net.set_layer_weights(neural_net.num_input_nodes, neural_net.num_hidden_nodes)
    neural_net.input_bias_weights = neural_net.set_bias_weights(neural_net.num_hidden_nodes)
    neural_net.hl_weights = neural_net.set_layer_weights(neural_net.num_hidden_nodes, neural_net.num_output_nodes)
    neural_net.hl_bias_weights = neural_net.set_bias_weights(neural_net.num_output_nodes)

    print("input bias weights: " + str(neural_net.input_bias_weights))
    print("hl bias weights: " + str(neural_net.hl_bias_weights))


# train the neural network
def train_neural_net(iterations):
    global training_set
    global testing_set
    get_training_data()             # load the training data
    get_testing_data()
    setup_neural_net()              # set the neural net weights

    print("Training set size is: " + str(len(training_set)))
    print("Training test size is: " + str(len(training_set[0])))
    print("Testing set size is: " + str(len(testing_set)))

    start_time = time.time()

    save_weights()
    # Loop for specified number of iterations to train
    for i in range(iterations+1):

        start_time = time.time()

        average_total_error = 0
        # Loop through all training data
        random.shuffle(training_set)
        for j in range(len(training_set)):
            # for j in range(1):
            neural_net.hl_nodes = [0] * len(neural_net.hl_nodes)
            neural_net.output_nodes = [0] * len(neural_net.output_nodes)
            # test neural net is properly working
            neural_net.set_input(training_set[j])               # set the neural net input data
            # print("Training set: " + str(training_set[j]))

            # Forward propagate
            neural_net.forward_prop()
            average_total_error += neural_net.total_error
            # if i % 10 == 0 and j % 1000 == 0:
                # print("  ")
                # print("i: " + str(i))
                # print(" output : " + str(neural_net.output_nodes) + " target : " + str(neural_net.target_nodes))
                # print("total error: " + str(neural_net.total_error))

            neural_net.back_prop()
            # if j % 500:
                # print("hl weights: " + str(neural_net.hl_weights))
                # print("input weights: " + str(neural_net.input_weights))

        average_total_error /= len(training_set)
        print("i: " + str(i) + " average_total_error for training data = " + str(average_total_error) + " time_taken = " + str(time.time() - start_time))
        if i % 10 == 0:
            # if False:
            num_correct = 0
            average_percentage = 0
            average_answer_category = 0
            # for k in range(len(training_set)):
            for k in range(len(testing_set)):
                neural_net.hl_nodes = [0] * len(neural_net.hl_nodes)
                neural_net.output_nodes = [0] * len(neural_net.output_nodes)
                # test neural net is properly working
                neural_net.set_input(testing_set[k])
                neural_net.forward_prop()
                # print("Test set answer is: " + str(testing_set[j][-1]))
                # print("Category probabilities are : " + str(neural_net.get_solution_prob()))
                answer_category = neural_net.get_answer_category()
                average_answer_category += answer_category
                solutions = neural_net.get_solution_prob()

                # if k % 500:
                    # print("hl weights: " + str(neural_net.hl_weights))
                    # print("input weights: " + str(neural_net.input_weights))
                # if k < 100:
                    # print(solutions)
                    # print(" given answer is : " + str(answer_category) + " the correct answer is : " + str(neural_net.target_nodes))

                # add the test stats to the current average
                if answer_category == training_set[k][-1]:
                    # print(solutions)
                    # print(answer_category)
                    num_correct += 1
                    average_percentage += solutions[answer_category]

                    # print("The output values are: " + str(neural_net.output_nodes))
            print("Got " + str(num_correct) + " correct out of " + str(len(testing_set)) + " = " + str((num_correct / len(training_set) * 100)))
            if num_correct > 0:
                print("Average correct category confidence: " + str(average_percentage / num_correct))
            else:
                print("None were correct")

    save_weights()

    num_correct = 0
    average_percentage = 0
    average_answer_category = 0
    for j in range(len(testing_set)):
        neural_net.hl_nodes = [0] * len(neural_net.hl_nodes)
        neural_net.output_nodes = [0] * len(neural_net.output_nodes)
        neural_net.set_input(testing_set[j])
        neural_net.forward_prop()
        # print("Test set answer is: " + str(testing_set[j][-1]))
        # print("Category probabilities are : " + str(neural_net.get_solution_prob()))
        answer_category = neural_net.get_answer_category()
        average_answer_category += answer_category
        solutions = neural_net.get_solution_prob()

        if j % 10 == 0:
            print(solutions)
            print(answer_category)

        # add the test stats to the current average
        if answer_category == testing_set[j][-1]:

            # print(solutions)
            # print(answer_category)
            num_correct += 1
            average_percentage += solutions[answer_category]

            # print("The output values are: " + str(neural_net.output_nodes))
    print("Got " + str(num_correct) + " correct out of " + str(len(testing_set)))
    print(" = " + str((num_correct / len(testing_set) * 100)))
    if num_correct > 0:
        print("Average correct category confidence: " + str(average_percentage / num_correct))
    else:
        print("None were correct")

    save_weights()

    return


# run the neural network
def run_neural_net():
    input = [0, 1, 6, 15, 12, 1, 0, 0, 0, 7, 16, 6, 6, 10, 0, 0, 0, 8, 16, 2, 0, 11, 2, 0, 0, 5, 16, 3, 0, 5, 7, 0, 0,
             7, 13, 3, 0, 8, 7, 0, 0, 4, 12, 0, 1, 13, 5, 0, 0, 0, 14, 9, 15, 9, 0, 0, 0, 0, 6, 14, 7, 1, 0, 0, 0
             ]
    # input = [1, 2, 3, 4, 5, 6, 7, 8]
    print("The list size is: " + str(len(input)))
    # input_weight = neural_net.set_layer_weights(64, 44)

    # print(input_weight)
    print()
    print()

    # Set the initial edge weights
    neural_net.input_weights = neural_net.set_layer_weights(neural_net.num_input_nodes, neural_net.num_hidden_nodes)
    neural_net.hl_weights = neural_net.set_layer_weights(neural_net.num_hidden_nodes, neural_net.num_output_nodes)
    print(len(neural_net.input_weights))

    # Set the input value
    neural_net.set_input(input)
    print("input_nodes: " + str(neural_net.input_nodes))
    print("input_weights[0]: " + str(neural_net.input_weights))

    # Run a summation from input to the hidden layer
    neural_net.sum_nodes(neural_net.input_nodes, neural_net.input_weights, neural_net.hl_nodes)
    neural_net.apply_sigmoid(neural_net.hl_nodes)
    print("hidden layer nodes: " + str(neural_net.hl_nodes))
    print("hidden layer weights: " + str(neural_net.hl_weights))
    print("output layer nodes: " + str(neural_net.output_nodes))

    # Run a summation from the hidden layer to the output layer
    neural_net.sum_nodes(neural_net.hl_nodes, neural_net.hl_weights, neural_net.output_nodes)
    neural_net.apply_sigmoid(neural_net.output_nodes)
    print("output layer nodes: " + str(neural_net.output_nodes))

    # perform back propagation on the network
    neural_net.back_prop()


# special test to see if neural network is working
def test_neural_net():

    # train with really easy data
    input_val = [[.05, .10]]
    target = [[.01, .99]]

    # neural_net.input_nodes = input_val
    neural_net.target_nodes = target
    neural_net.num_input_nodes = 2
    neural_net.num_output_nodes = 2
    neural_net.num_hidden_nodes = 2

    # setup_neural_net()
    neural_net.input_weights = [[.15, .25], [.2, .30]]
    neural_net.input_bias_weights = [.35, .35]
    neural_net.input_bias_value = 1
    neural_net.hl_weights = [[.40, .5], [.45, .55]]
    neural_net.hl_bias_weights = [.60, .60]
    neural_net.hl_bias_value = 1

    print(neural_net.input_weights)
    print(neural_net.input_bias_weights)
    print(neural_net.hl_weights)
    print(neural_net.hl_bias_weights)


    # for the number of times to train the network
    for i in range(0, 10000):
        average_total_error = 0
        for j in range(len(input_val)):
            neural_net.hl_nodes = [0] * neural_net.num_hidden_nodes
            neural_net.output_nodes = [0] * neural_net.num_output_nodes
            neural_net.input_nodes = input_val[j]
            neural_net.target_nodes = target[j]
            #  neural_net.input_bias_weights = [0] * neural_net.num_hidden_nodes
            # neural_net.hl_bias_weights = [0] * neural_net.num_output_nodes
            # print("Start values")
            # print("Input nodes: " + str(neural_net.input_nodes))
            # print("Input weights: " + str(neural_net.input_weights))
            # print("Input bias weights: " + str(neural_net.input_bias_weights))
            # print("Hl nodes: " + str(neural_net.hl_nodes))
            # print("Hl weights: " + str(neural_net.hl_weights))
            # print("Hl bias weights: " + str(neural_net.hl_bias_weights))
            # print("Output nodes: " + str(neural_net.output_nodes))
            # print("Target nodes: " + str(neural_net.target_nodes))
            #
            # print("")
            # print("Forward prop values")
            neural_net.forward_prop()
            # print("Input nodes: " + str(neural_net.input_nodes))
            # print("Input weights: " + str(neural_net.input_weights))
            # print("Input bias weights: " + str(neural_net.input_bias_weights))
            # print("Hl nodes: " + str(neural_net.hl_nodes))
            # print("Hl weights: " + str(neural_net.hl_weights))
            # print("Hl bias weights: " + str(neural_net.hl_bias_weights))
            # print("Output nodes: " + str(neural_net.output_nodes))
            # print("Target nodes: " + str(neural_net.target_nodes))

            # if i % 100 == 0:
                # print("  ")
                # print("i: " + str(i))
                # print(" output : " + str(neural_net.output_nodes) + " target : " + str(neural_net.target_nodes))
                # print("total error: " + str(neural_net.total_error))
                # print("input weights: " + str(neural_net.input_weights))
                # print("input bias weights: " + str(neural_net.input_bias_weights))
                # print("hidden weights: " + str(neural_net.hl_weights))
                # print("hiddle layer bias weigths: " + str(neural_net.hl_bias_weights))
                # print("  ")
            average_total_error += neural_net.total_error

            # print("")
            # print("Backward prop values")
            neural_net.back_prop()
            # print("Input nodes: " + str(neural_net.input_nodes))
            # print("Input weights: " + str(neural_net.input_weights))
            # print("Input bias weights: " + str(neural_net.input_bias_weights))
            # print("Hl nodes: " + str(neural_net.hl_nodes))
            # print("Hl weights: " + str(neural_net.hl_weights))
            # print("Hl bias weights: " + str(neural_net.hl_bias_weights))
            # print("Output nodes: " + str(neural_net.output_nodes))
            # print("Target nodes: " + str(neural_net.target_nodes))
            #
            # print("")
            # print("Forward prop values")
            # neural_net.forward_prop()
            # print("Output nodes: " + str(neural_net.output_nodes))

        average_total_error /= len(training_set)

        if i % 10000 == 0:
            print(" ")
            print(" ")


def main():
    global training_set
    print("num hidden nodes : " + str(neural_net.num_hidden_nodes))
    print("learning rate : " + str(neural_net.learning_rate))
    neural_net.random.seed(42)  # Insure consistency between different test runs
    train_neural_net(100)
    # run_neural_net()
    # test_neural_net()

if __name__ == "__main__":
    main()