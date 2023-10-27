from build import Zenith
import os
from mnist import MNIST
import sys
import time
import numpy as np

def main() :
 
    print('Loading Dataset...')

    # Get the current directory
    current_dir = os.path.dirname(os.path.abspath(__file__))

    # Specify the path to the MNIST dataset directory
    mnist_data_dir = os.path.join(current_dir, 'Digits-MNIST')

    mnist = MNIST(mnist_data_dir)

    # Load the MNIST dataset
    x_train, y_train = mnist.load_training()
    x_test, y_test = mnist.load_testing()

    # Display the shape of the loaded data
    print("Training data shape:", len(x_train))     # Number of training samples
    print("Training labels shape:", len(y_train))   # Number of training labels
    print("Test data shape:", len(x_test))          # Number of test samples
    print("Test labels shape:", len(y_test))        # Number of test labels

    print('Loading Complete! Unpacking to network...')

    network = Zenith.Network()

    for i, j in enumerate(x_train) :
        network.AddDatapoint(x_train[i], y_train[i])
    for i, j in enumerate(x_test) :
        network.AddDatapoint(x_test[i], y_test[i])

    network.SetInputShape(1, 784, 1)

    network.Dense(250, Zenith.EActivation.Sigmoid)
    network.Dense(75, Zenith.EActivation.Softmax)

    network.Cost = Zenith.ECost.CrossEntropy

    network.Compile()

def unpickle(file):
    import pickle
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

if __name__ == '__main__' :
    main()