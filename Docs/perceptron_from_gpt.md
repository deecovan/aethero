# perceptron c example

A basic example of a perceptron implementation in C involves defining the perceptron's structure, its activation function, and the learning algorithm for training.

1. Perceptron Structure:
	A perceptron typically has:
	Weights: Numerical values associated with each input.
	Bias: A constant value added to the weighted sum of inputs.
	Activation Function: A function that determines the output based on the weighted sum.

2. Activation Function:
	A common choice for a simple perceptron is a step function (or sign function).

### C
```
int activation_function(double sum, double threshold) {
    if (sum >= threshold) {
        return 1; // "Fires" or activates
    } else {
        return 0; // Does not fire
    }
}
```

3. Training Algorithm (Perceptron Learning Rule):
	The perceptron learns by adjusting its weights and bias based on the error between its predicted output and the desired output.

### C
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a simple perceptron structure
typedef struct {
    double weights[2]; // For two inputs (x1, x2)
    double bias;
    double learning_rate;
    double threshold;
} Perceptron;

// Initialize the perceptron with random weights and given parameters
void init_perceptron(Perceptron *p, double lr, double th) {
    srand(time(NULL)); // Seed for random numbers
    p->weights[0] = (double)rand() / RAND_MAX; // Random weight for x1
    p->weights[1] = (double)rand() / RAND_MAX; // Random weight for x2
    p->bias = (double)rand() / RAND_MAX;       // Random bias
    p->learning_rate = lr;
    p->threshold = th;
}

// Predict the output for given inputs
int predict(Perceptron *p, double x1, double x2) {
    double sum = (x1 * p->weights[0]) + (x2 * p->weights[1]) + p->bias;
    return (sum >= p->threshold) ? 1 : 0; // Step activation function
}

// Train the perceptron
void train(Perceptron *p, double inputs[][2], int outputs[], int num_samples, int epochs) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        int total_error = 0;
        for (int i = 0; i < num_samples; i++) {
            double x1 = inputs[i][0];
            double x2 = inputs[i][1];
            int desired_output = outputs[i];

            int predicted_output = predict(p, x1, x2);
            int error = desired_output - predicted_output;

            // Update weights and bias
            p->weights[0] += p->learning_rate * error * x1;
            p->weights[1] += p->learning_rate * error * x2;
            p->bias += p->learning_rate * error;

            total_error += abs(error);
        }
        printf("Epoch %d, Total Error: %d\n", epoch + 1, total_error);
        if (total_error == 0) {
            printf("Training converged!\n");
            break;
        }
    }
}

int main() {
    Perceptron my_perceptron;
    init_perceptron(&my_perceptron, 0.1, 0.5); // Learning rate 0.1, threshold 0.5

    // Example data for an AND gate
    double inputs[][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    int outputs[] = {0, 0, 0, 1}; // Expected outputs for AND gate
    int num_samples = 4;
    int epochs = 100;

    printf("Initial Weights: w1=%.2f, w2=%.2f, bias=%.2f\n", 
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.bias);

    train(&my_perceptron, inputs, outputs, num_samples, epochs);

    printf("\nFinal Weights: w1=%.2f, w2=%.2f, bias=%.2f\n", 
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.bias);

    // Test the trained perceptron
    printf("\nTesting Perceptron (AND Gate):\n");
    printf("0 AND 0 = %d\n", predict(&my_perceptron, 0, 0));
    printf("0 AND 1 = %d\n", predict(&my_perceptron, 0, 1));
    printf("1 AND 0 = %d\n", predict(&my_perceptron, 1, 0));
    printf("1 AND 1 = %d\n", predict(&my_perceptron, 1, 1));

    return 0;
}
```

This example demonstrates a basic single-layer perceptron capable of learning linearly separable patterns like an AND gate. More complex problems require multi-layer perceptrons (neural networks) and different activation functions.