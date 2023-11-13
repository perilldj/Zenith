from build import Zenith
import os
from mnist import MNIST
import sys
import time
import numpy as np

import matplotlib.pyplot as plt

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

    for i in (x_train) :
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

    #network.Flatten()
    #network.MaxPooling()
    #network.MaxPooling()
    network.Dense(64, Zenith.EActivation.ReLU)
    network.Dense(10, Zenith.EActivation.Softmax)

    network.Cost = Zenith.ECost.CrossEntropy
    network.Initializer = Zenith.EInitialization.Kaiming
    network.Distribution = Zenith.EDistribution.Normal

    network.DoLearningRateDecay = True
    network.DecayRate = 0.15
    network.LearningRate = 0.05
    network.Epochs = 5
    network.BatchSize = 25

    network.Compile()
    network.Train()

    # Create a figure and subplots
    fig, axs = plt.subplots(2, 2, figsize=(10, 8))

    epochs = np.arange(0, len(network.TrainingCost))

    # Plot the data on separate subplots
    axs[0, 0].plot(epochs, network.TrainingCost, label='Training Cost')
    axs[0, 0].set_title('Training Cost')
    axs[0, 0].set_xlabel('Epochs')
    axs[0, 1].plot(epochs, network.TrainingAccuracy, label='Training Accuracy', c="orange")
    axs[0, 1].set_title('Training Accuracy')
    axs[0, 1].set_xlabel('Epochs')
    axs[0, 1].set_ylim(0, 1.0)
    axs[1, 0].plot(epochs, network.TestingCost, label='Testing Cost')
    axs[1, 0].set_title('Testing Cost')
    axs[1, 0].set_xlabel('Epochs')
    axs[1, 1].plot(epochs, network.TestingAccuracy, label='Testing Accuracy', c="orange")
    axs[1, 1].set_title('Testing Accuracy')
    axs[1, 1].set_xlabel('Epochs')
    axs[1, 1].set_ylim(0, 1.0)

    # Add legends to each subplot
    # Set x-axis ticks to display integers only
    for ax in axs.flat:
        ax.set_xticks(epochs)
        ax.set_xticklabels([str(int(e)) for e in epochs])

    # Adjust layout and show the plot
    plt.tight_layout()
    plt.show()

def unpickle(file):
    import pickle
    with open(file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    return dict

if __name__ == '__main__' :
    main()