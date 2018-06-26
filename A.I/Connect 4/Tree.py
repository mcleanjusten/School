# Justen McLean
# Artificial Intelligence
# Project 1
# Tree.py
import random


class Node:

    # initialize an instance of the node
    def __init__(self, value):
        self.value = value      # The node value
        self.children = {}      # Any children node in a dictionary
        self.parent = ''        # The parent of the node
        self.visited = False   # Has the node already been visited

    def __str__(self):
        return 'Value= ' + str(self.value) + ' Num children= ' + str(len(self.children))


class Tree:

    # Initialize an instance of the class
    def __init__(self, value):
        self.root = Node(value)
        self.search_stack = []      # The stack to use when searching with search_depth
        self.search_queue = []      # The queue to use when searching with search_breadth

    # Insert a child node
    def insert_child(self, parent_node, value):
        child_node = Node(value)
        parent_node.children[value] = child_node
        return child_node

    # Get the root node
    def get_root(self):
        return self.root

    # Searches the tree for an event and responds with a response
    def search(self, target_event):
        possible_responses = []
        self.search_stack = []
        self.search_queue = []
        # Get a subtree with all possible responses to the event
        event_node = Tree.search_breadth(self, self.root, target_event)
        # event_node = Tree.search_depth(self, self.root, target_event)

        # Check that the event was found
        if not isinstance(event_node, Node):
            print('The event was not found')
            return None

        # Get all leaf nodes from the tree and add them to possible_responses
        possible_responses += Tree.get_responses(self, event_node)
        rand_response = random.choice(possible_responses)
        Tree.reset_visited(self)
        #print(rand_response)
        return rand_response

    # Get all the leaf nodes from a tree
    def get_responses(self, root_node):
        responses = []

        # Check if the root_node is a leaf, if not recursively search all child nodes
        if len(root_node.children) > 0:
            child_keys = list(root_node.children)
            for key in child_keys:
                responses += Tree.get_responses(self, root_node.children[key])
        else:
            responses.append(root_node.value)           # The root_node is a leaf, add it's value to responses

        return responses

    # Perform a depth first search on the tree to find the target_value
    def search_depth(self, root_node, target_event):
        return_node = None
        root_node.visited = True                                            # Mark the current node as visited
        list_children = list(root_node.children)                            # Get list of child nodes
        # print(" Visiting " + root_node.value)  # Print the current root node

        # Check if the current node is the target_event
        if root_node.value == target_event:
            # print('Found the target_event')
            return root_node

        # Add all children nodes that have not previously been visited to the search_stack
        for child in list_children:                                         # Check all child nodes
            # print(child + ' visited = ' + str(root_node.children[child].visited))
            if not root_node.children[child].visited:                       # Check if the node was already visited
                # print(root_node.children[child].value + ' has not been visited')
                self.search_stack.append(root_node.children[child])         # Add the child node to the stack
                # print(self.search_stack)

        # If there are still nodes in the search_stack remove the last and visit it
        if len(self.search_stack) > 0:
            return_node = Tree.search_depth(self, self.search_stack.pop(), target_event)
            return return_node
        else:
            # print("Didn't find anything" + str(self.search_stack))
            return return_node

    # Performs a breadth first search on the tree to find the target_value
    def search_breadth(self, root_node, target_event):
        return_node = None
        root_node.visited = True
        list_children = list(root_node.children)
        # print(' Visiting ' + root_node.value)

        # Check if the current node is the target_event
        if root_node.value == target_event:
            return root_node

        # Add all children nodes that have not previously been visited to the search_queue
        for child in list_children:
            if not root_node.children[child].visited:                       # Check if the node was already visited
                self.search_queue.append(root_node.children[child])         # Add the child node to the queue

        # If there are still nodes in the queue visit them
        if len(self.search_queue) > 0:
            return_node = Tree.search_breadth(self, self.search_queue.pop(0), target_event)
            return return_node
        else:
            return return_node

    # Reset the visited flag on all Nodes in the tree
    def reset_visited(self):
        self.root.visited = False
        list_children = list(self.root.children)
        for child in list_children:
            Tree.reset_visited_subtree(self, self.root.children[child])

    # Reset the visited flag on all sub trees of parent
    def reset_visited_subtree(self, parent):
        parent.visited = False
        list_children = list(parent.children)
        for child in list_children:
            Tree.reset_visited_subtree(self, parent.children[child])

    # prints the node values for all sub trees starting at the parent node
    def print_child_tree(self, parent, tabs):
        # print(parent.value)
        t_tabs = int(tabs)
        spacing = ''

        # Create the white space before the current generation is printed
        while t_tabs > 0:
            spacing += '    '
            t_tabs -= 1

        children = list(parent.children)
        for child in children:

            if len(parent.children[child].children) != 0:
                print(spacing + 'behavior = '+parent.children[child].value)
                Tree.print_child_tree(self, parent.children[child], tabs+1)
            else:
                print(spacing + 'response = ' + parent.children[child].value)

    # prints the node values for the entire tree starting at the root node
    def print_tree(self):
        print('behavior = ' + self.root.value)
        list_children = list(self.root.children)
        for child in list_children:
            print('    ' + 'behavior = ' + self.root.children[child].value)
            Tree.print_child_tree(self, self.root.children[child], 2)


