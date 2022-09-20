#include "Arduino.h"
#include <TimerOne.h>
#include "neural_network.h"
#include "core_pins.h"

#define DEBUG_PIN 9

/* Those weights were calculated by training the model */
double weights[] = {
  9.67299303,
  -0.2078435,
  -4.62963669};
/* Those are the weights for the NN with the hidden layer */
double weights_1[32][3] = {
    { 1.5519611 ,  0.65860842, -0.85158313},
    { 1.06265208,  0.31949065, -0.13750623},
    {-2.30455417,  0.30591339,  0.7240955 },
    { 0.30877321,  0.13609545,  0.06030529},
    {-1.17039621,  0.37650795,  0.68144084},
    {-0.69348733,  0.60220631,  0.28797794},
    { 0.40589165, -0.18831817,  0.35705378},
    {-0.05932593,  0.59004868, -0.1701374 },
    { 1.392689  ,  0.70259631, -0.74218012},
    { 0.48329391,  0.60207043,  0.38431145},
    {-0.95295493,  0.07404055,  0.3302735 },
    { 2.10166106,  0.39611358, -1.00823685},
    {-0.08448525, -0.10317019,  0.53841852},
    { 2.540211  ,  0.05323626, -1.06332893},
    {-1.84539917,  0.48765352,  0.5685712 },
    {-0.01802026,  0.18219485,  0.62404852},
    { 0.92427558,  0.04736742,  0.12561239},
    { 1.08965851, -0.0801783 , -0.08860555},
    {-1.82176436, -0.20573879,  0.780304  },
    { 0.45220284,  0.4997675 , -0.18653686},
    { 2.14035487, -0.03879152, -0.80268326},
    { 1.82177898, -0.11746983, -0.36502932},
    { 0.62309348,  0.30696019, -0.13735078},
    {-0.05199235, -0.05282913,  0.91758557},
    { 0.29694869,  0.54693956,  0.69834386},
    { 0.39180283,  0.07674308,  0.54732749},
    {-1.72233784,  0.36036508,  0.28150989},
    {-1.70252288,  0.30217376,  0.69514718},
    { 0.78278019, -0.07366525, -0.16997775},
    { 1.28860736,  0.17580282, -0.17742198},
    {-0.47323461,  0.48374213,  0.08422625},
    { 1.49427898,  0.191315  , -0.6043115 }
};

double weights_2[] = {
      1.45800076,
      0.70967606,
     -2.68516009,
      0.02268129,
     -1.49619033,
     -0.91787325,
      0.09344477,
     -0.29547836,
      1.28547469,
      0.04046954,
     -1.29961045,
      2.02908422,
     -0.42753493,
      2.49285692,
     -2.11993655,
     -0.59068471,
      0.62114759,
      0.76446439,
     -2.22804807,
      0.25244996,
      1.9591224 ,
      1.53351039,
      0.37624935,
     -0.74102723,
     -0.48484892,
     -0.2683768 ,
     -2.020174  ,
     -1.99787033,
      0.54688533,
      0.90035289,
     -0.67413096,
      1.31408841,
};

/* Those are the inputs to test and benchmark */
double inputs[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1},
};


String cmd = "";


static inline void debug_pin_toggle()
{
  // First toggle
  digitalWrite(DEBUG_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DEBUG_PIN, LOW);    // turn the LED off by making the voltage LOW

  // Second toggle
  digitalWrite(DEBUG_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DEBUG_PIN, LOW);    // turn the LED off by making the voltage LOW
}

void test_neural_network(void)
{
  for (int i=0; i<8; i++) {
    double result = sigmoid(dot(inputs[i], weights, 3));
    Serial.print("result: ");
    Serial.println(result);
  }
  Serial.println();
}

void benchmark_neural_network(void)
{
  // Before run the NN prediction function, we're toggling
  // the pin twice, then by using the oscilloscope we measure
  // the time and then substract the T/2 from the time that
  // the prediction actually spend
  debug_pin_toggle();

  // Benchmark the predict function
  digitalWrite(DEBUG_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  double result = sigmoid(dot(inputs[0], weights, 3));
  digitalWrite(DEBUG_PIN, LOW);    // turn the LED off by making the voltage LOW

  Serial.print("DONE: ");
  Serial.println(result);
}

/*** Neural network with 1 hidden layer and 32 neurons ***/

void test_neural_network2(void)
{
  double layer[32];

  for (int k=0; k<8; k++) {
    for (int i=0; i<32; i++) {
      layer[i] = sigmoid(dot(inputs[k], weights_1[i], 3));
    }
    double output = sigmoid(dot(layer, weights_2, 32));
    Serial.print("result: ");
    Serial.println(output);
  }
}

void benchmark_neural_network2(void)
{
  double layer[32];

  digitalWrite(DEBUG_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  for (int i=0; i<32; i++) {
    layer[i] = sigmoid(dot(inputs[0], weights_1[i], 3));
  }
  double output = sigmoid(dot(layer, weights_2, 32));
  digitalWrite(DEBUG_PIN, LOW);    // turn the LED off by making the voltage LOW

  Serial.print("DONE: ");
  Serial.println(output);
}

void benchmark_neural_network2_serial(void)
{
  double layer[32];
  double output = 0.0;
  double exectime = 0.0;
#ifdef TEENSY
  uint32_t myTime = ARM_DWT_CYCCNT; 
#else
  unsigned long startMicros = micros();
#endif

  for (int i=0; i<1000; i++) 
  {
  for (int i=0; i<32; i++) {
    layer[i] = sigmoid(dot(inputs[0], weights_1[i], 3));
  }
    output = sigmoid(dot(layer, weights_2, 32));
  }
#ifdef TEENSY
  myTime = ARM_DWT_CYCCNT - myTime -2; 

  exectime = double(myTime)/F_CPU_ACTUAL/1000.0;
  Serial.println("we\'re using teensy");
  Serial.print(F_CPU_ACTUAL);
  Serial.println();
#else
  unsigned long endMicros = micros();
  exectime = double(endMicros - startMicros)/1000.0;
#endif
  Serial.print("Average inference time: ");
  Serial.print(exectime);
  Serial.print("us / inference\r\n");
  Serial.print("Total for 1000 predictions:");
#ifdef TEENSY
  Serial.print(myTime); 
//  Serial.print(myTime/F_CPU_ACTUAL); 
#else
  Serial.print(endMicros - startMicros);
#endif
  Serial.print("us\r\n");

  Serial.print("DONE, value of last prediction: ");
  Serial.println(output);
}
void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Started");
  Serial.println("Enter 'test=<1 or 2>'");
  
  pinMode(DEBUG_PIN, OUTPUT);

  // Timer initialize
  Timer1.initialize(3000000);
  Timer1.stop();
}

void loop() {
  
  while(Serial.available()) {
    char tmp = Serial.read();
    // Tranform low case characters to upper case
    if (tmp>='a' && tmp<'z') tmp=tmp-32;
    Serial.print(tmp);
    cmd.concat(tmp);
//    if (tmp == '\n'){
      //to work with screen which by default outputs \r 
      //when pressing enter
    if (tmp == '\r'){
        Serial.println();
        cmd.concat('\n');
//      Serial.print("you pressed return");
//      for (int i=0;i<7;i++)
//        Serial.println(cmd[i]);
//      Serial.print("breaking from while");
      break;
    }
//    cmd.concat(tmp);
  }

  if (cmd != "") {
    if(cmd.indexOf('\n') >= 0) {
      if(cmd.indexOf("TEST=") >= 0) {
        // get mode
        char c_mode[2] = {0};
        c_mode[0] = cmd[5];
        int mode = atoi(c_mode);
        cmd = "";
        Serial.print("Running NN test mode ");Serial.println(mode);
        switch(mode) {
          case 1:
            test_neural_network();
            break;
          case 2:
            test_neural_network2();
            break;
          default:
            Serial.println("Available modes: 1-2");
        }
      }
      else if(cmd.indexOf("START=") >= 0) {
        // get mode
        char c_mode[2] = {0};
        c_mode[0] = cmd[6];
        int mode = atoi(c_mode);
        cmd = "";
        Serial.print("Starting benchmark mode ");Serial.println(mode);
        switch(mode) {
          case 1:
            Timer1.attachInterrupt(benchmark_neural_network);
            break;
          case 2:
            benchmark_neural_network2_serial();
            //Timer1.attachInterrupt(benchmark_neural_network2);
            break;
          default:
            Serial.println("Available modes: 1-2");
        }
        Timer1.start();
      }
      else if(cmd.indexOf("STOP") >= 0) {
        Serial.println("Stoping benchmark mode...");
        Timer1.stop();
        cmd = "";
      }
    }
  }
}
