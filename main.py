from build import Zenith
import os
from mnist import MNIST
import sys
import time
import numpy as np

def main() :

     
    Zenith.RunTest()


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

    for index, i in enumerate(x_train) :
        for index, j in enumerate(i) :
            i[index] = i[index] / 255

    for i in (x_test) :
        for index, j in enumerate(i) :
            i[index] = i[index] / 255

    for i, j in enumerate(x_train) :
        network.AddDatapoint(x_train[i], y_train[i])
    for i, j in enumerate(x_test) :
        network.AddDatapoint(x_test[i], y_test[i])

    network.SetInputShape(1, 784, 1)

    network.Dense(10, Zenith.EActivation.Softmax)

    network.Cost = Zenith.ECost.CrossEntropy
    network.Initializer = Zenith.EInitialization.Kaiming
    network.Distribution = Zenith.EDistribution.Normal

    network.DoLearningRateDecay = True
    network.DecayRate = 0.1
    network.LearningRate = 0.01
    network.Epochs = 100
    network.BatchSize = 40

    network.Compile()
    network.Train()

def unpickle(file):
    import pickle
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

if __name__ == '__main__' :
    main()