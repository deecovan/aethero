#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
## This example demonstrates a basic single-layer
## perceptron capable of learning linearly separable patterns like an AND gate.
## Version v3 with Used pattern "X1 AND X2 OR X3".
## It initializes weights randomly, trains the perceptron using a simple
## learning algorithm, and tests it with a set of inputs.
*/

/*
## Define a simple perceptron structure.
## It has three inputs (x1, x2, x3), one bias, weights for each input,
## a learning rate, and a threshold for activation.
*/
typedef struct
{
    /*
    ## For THREE inputs (x1, x2, x3) and one bias
    ## The perceptron has three weights, one bias, a learning rate, and a threshold
    */
    double weights[3];
    double bias;
    double learning_rate;
    double threshold;
} Perceptron;

/*
## Initialize the perceptron with random weights and given parameters.
## The weights are initialized randomly, and the learning rate and threshold are set.
## The random seed is set using the current time to ensure different results on each run.
## The weights are initialized to random values between 0 and 1, and the bias is
*/
void init_perceptron(Perceptron *p, double lr, double th)
{
    srand(time(NULL));                                 /* Seed for random numbers */
    p->weights[0] = (double)rand() / RAND_MAX;         /* Random weight for x1 */
    p->weights[1] = (double)rand() / RAND_MAX;         /* AND Random weight for x2 */
    p->weights[2] = (double)(rand() * 2.0) / RAND_MAX; /* OR Random weight for x3 */
    p->bias = (double)rand() / RAND_MAX;               /* Random bias */
    p->learning_rate = lr;
    p->threshold = th;
}

/*
## Predict the output for given inputs.
## The perceptron computes the weighted sum of inputs plus the bias,
## and applies a step activation function based on the threshold.
*/
int predict(Perceptron *p, double x1, double x2, double x3)
{
    double sum = (x1 * p->weights[0]) + (x2 * p->weights[1]) + (x3 * p->weights[2]) + p->bias;
    return (sum >= p->threshold) ? 1 : 0; /* Step activation function */
}

/*
## Train the perceptron.
## The training process involves adjusting the weights and bias based on the error
## between the predicted and desired outputs.
*/
void train(Perceptron *p, double inputs[][3], int outputs[], int num_samples, int epochs)
{
    int i, epoch;
    for (epoch = 0; epoch < epochs; epoch++)
    {
        int total_error = 0;
        for (i = 0; i < num_samples; i++)
        {
            double x1 = inputs[i][0];
            double x2 = inputs[i][1];
            double x3 = inputs[i][2];
            int desired_output = outputs[i];

            int predicted_output = predict(p, x1, x2, x3);
            int error = desired_output - predicted_output;

            /*
            ## Update weights and bias.
            ## The weights are adjusted based on the error and the learning rate.
            ## The bias is also adjusted similarly.
            */
            p->weights[0] += p->learning_rate * error * x1;
            p->weights[1] += p->learning_rate * error * x2;
            p->weights[2] += p->learning_rate * error * x3;
            p->bias += p->learning_rate * error;

            total_error += abs(error);
        }
        printf("Epoch %d, Total Error: %d\n", epoch + 1, total_error);
        if (total_error == 0)
        {
            printf("Training converged!\n");
            break;
        }
    }
}

int main()
{
    Perceptron my_perceptron;
    /*
    ## Learning rate 0.1, Threshold 0.5.
    ## Initialize the perceptron with a learning rate and threshold.
    ## The learning rate controls how much the weights are adjusted during training,
    */
    init_perceptron(&my_perceptron, 0.1, 0.5);

    /*
    ## Example data for an AND gate.
    ## The inputs are combinations of three binary inputs (x1, x2, x3),
    ## and the outputs are the expected results for the AND operation.
    */
    double inputs[][3] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 0}, {0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    /*
    ## Expected outputs for AND gate.
    ## The outputs are binary values representing the result of the AND operation
    ## for the corresponding inputs.
    */
    int outputs[] = {0, 0, 0, 1, 1, 1, 1, 1};
    int num_samples = 8;
    int epochs = 1000;

    printf("\nInitial Weights: w1=%.2f, w2=%.2f, w3=%.2f, bias=%.2f\n",
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.weights[2], my_perceptron.bias);

    train(&my_perceptron, inputs, outputs, num_samples, epochs);

    printf("\nFinal Weights: w1=%.2f, w2=%.2f, w3=%.2f, bias=%.2f\n",
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.weights[2], my_perceptron.bias);

    /*
    ## Test the trained perceptron.
    ## The perceptron is tested with various combinations of inputs to verify its
    ## ability to predict the AND operation correctly.
    */
    printf("Testing Perceptron (AND Gate):\n");
    printf("0 AND 0 OR 0 = %d\n", predict(&my_perceptron, 0, 0, 0));
    printf("0 AND 1 OR 0 = %d\n", predict(&my_perceptron, 0, 1, 0));
    printf("1 AND 0 OR 0 = %d\n", predict(&my_perceptron, 1, 0, 0));
    printf("1 AND 1 OR 0 = %d\n", predict(&my_perceptron, 1, 1, 0));
    printf("0 AND 0 OR 1 = %d\n", predict(&my_perceptron, 0, 0, 1));
    printf("0 AND 1 OR 1 = %d\n", predict(&my_perceptron, 0, 1, 1));
    printf("1 AND 0 OR 1 = %d\n", predict(&my_perceptron, 1, 0, 1));
    printf("1 AND 1 OR 1 = %d\n", predict(&my_perceptron, 1, 1, 1));

    return 0;
}
