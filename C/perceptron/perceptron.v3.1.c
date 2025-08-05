#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
## Version v3.1 with Used pattern "X1 AND X2 OR X3".
## Modified logic: old pattern was wrong.
## New predict pattern is: 
## ((X1 + X2 + bias) > threshold1) OR ((X3 + bias) > threshold2)
## where (X1 + X2 + bias) > threshold1) is ANDgate(X1, X2)
## Separate tresholds but one bias.
## This example selects random values, and this can be changed 
## so that not just a threshold is triggered, but a threshold 
## with a minimum bias. Also, X3 block can be expanded 
## to the expression NORgate(X3, X4)
*/

/*
## Define a simple perceptron structure.
*/
typedef struct
{
    /*
    ## For THREE inputs (x1, x2, x3) and one bias
    */
    double weights[3];
    double bias;
    double learning_rate;
    double threshold[2];
} Perceptron;

/*
## Initialize the perceptron with random weights and given parameters.
*/
void init_perceptron(Perceptron *p, double lr, double th[])
{
    srand(time(NULL));
    p->weights[0] = (double)rand() / RAND_MAX;
    p->weights[1] = (double)rand() / RAND_MAX;
    p->weights[2] = (double)rand() / RAND_MAX;
    p->bias = (double)rand() / RAND_MAX;
    p->learning_rate = lr;
    p->threshold[0] = th[0];
    p->threshold[1] = th[1];
}

/*
## Main logic function.
## Predict the output for given inputs.
## The perceptron computes the weighted sum of inputs plus the bias,
## and applies a step activation function based on the threshold.
*/
int predict(Perceptron *p, double x1, double x2, double x3)
{
    double ANDgate12 = (x1 * p->weights[0]) + (x2 * p->weights[1]) + p->bias;
    double ORvalue3 = (x3 * p->weights[2]) + p->bias;
    /* Step activation function */
    /* Changes in v3.1: threshold must be separate for each predict logical block */
    return ((ANDgate12 >= p->threshold[0]) || (ORvalue3 >= p->threshold[1])) ? 1 : 0;
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
            */
            p->weights[0] += p->learning_rate * error * x1;
            p->weights[1] += p->learning_rate * error * x2;
            p->weights[2] += p->learning_rate * error * x3;
            p->bias += p->learning_rate * error;

            total_error += abs(error);
        }
        printf("\nEpoch %d, Total Error: %d", epoch + 1, total_error);
        if (total_error == 0)
        {
            printf("\n\nTraining converged in epoch %d, iteration %d\n", epoch + 1, i);
            break;
        }
    }
}

int main()
{
    Perceptron my_perceptron;
    /*
    ## The learning rate controls how much the weights are adjusted during training
    */
    double thresholds[2] = {0.5, 0.75};
    double learning_rate = 0.05;
    init_perceptron(&my_perceptron, learning_rate, thresholds);

    /*
    ## Inputs and expected outputs for training and testing.
    */
    double inputs[][3] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 0}, {0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    int outputs[] = {0, 0, 0, 1, 1, 1, 1, 1};
    /*
    ## Training iterations variables.
    */
    int num_samples = sizeof(outputs) / sizeof(outputs[0]);
    int epochs = 100;

    printf("\nInitial Weights: X1 = %.2f, X2 = %.2f, X3 = %.2f, bias = %.2f\n",
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.weights[2], my_perceptron.bias);

    train(&my_perceptron, inputs, outputs, num_samples, epochs);
    
    /*
    ## Test the trained perceptron.
    */
    printf("\nTesting the trained perceptron using logic ANDgate(X1, X2) OR X3:");
    printf("\n((X1 + X2 + bias) > threshold1) OR ((X3 + bias) > threshold2)\n");
    printf("\nFinal Weights: X1 = %.2f, X2 = %.2f, X3 = %.2f, bias = %.2f\n",
           my_perceptron.weights[0], my_perceptron.weights[1], my_perceptron.weights[2], my_perceptron.bias);
    printf("threshold1 = %.2f, threshold2 = %.2f, learning rate = %.2f\n\n",
           thresholds[0], thresholds[1], learning_rate);
    printf("(0 AND 0) OR 0 = %d\n", predict(&my_perceptron, 0, 0, 0));
    printf("(0 AND 1) OR 0 = %d\n", predict(&my_perceptron, 0, 1, 0));
    printf("(1 AND 0) OR 0 = %d\n", predict(&my_perceptron, 1, 0, 0));
    printf("(1 AND 1) OR 0 = %d\n", predict(&my_perceptron, 1, 1, 0));
    printf("(0 AND 0) OR 1 = %d\n", predict(&my_perceptron, 0, 0, 1));
    printf("(0 AND 1) OR 1 = %d\n", predict(&my_perceptron, 0, 1, 1));
    printf("(1 AND 0) OR 1 = %d\n", predict(&my_perceptron, 1, 0, 1));
    printf("(1 AND 1) OR 1 = %d\n", predict(&my_perceptron, 1, 1, 1));

    return 0;
}
