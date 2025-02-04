/*
 * neural_network.h
 *
 */

#ifndef NEURAL_NETWORK_H_
#define NEURAL_NETWORK_H_

#ifdef __cplusplus
extern "C" {
#endif

double dot(double v[], double u[], int n);
double sigmoid(double x);
double nn_predict(double * input, double * weights, int n);

#ifdef __cplusplus
}
#endif

#endif /* NEURAL_NETWORK_H_ */
