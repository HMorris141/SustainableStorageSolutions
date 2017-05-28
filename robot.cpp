#include "mbed.h"

//Motors
DigitalOut in1(D5), in2(D2), in3(D3), in4(D4);
//pin defintions for directions

PwmOut ENA(D9), ENB(D10);  //pwm definitions

//Ultrasonic sensor definitions
PwmOut usTrig(PC_8);
DigitalIn usEcho(D14);
Timer t;

//Line sensors
/*DigitalIn line0(D6), line1(D7), line2(D8);
DigitalOut p1(D1), p2(D11), p3(D12);*/

class Motor //motor class
{
public:
    Motor(): pulse1(20), pulse2(20) {}; //supposed to be initialiser list

    //PWM control
    void pulse(void);
    void change_period1(int cyc1);
    void change_period2(int cyc2);

    //Motor directions
    void forward(void);
    void back(void);
    void right(void);
    void left(void);
    void slow(void);

private:
    int pulse1, pulse2;
};

int main()
{
    /*p1 = 1; //line sensor initialisation
    p2 = 1;
    p3 = 1;
    int detect0, detect1, detect2;*/

    //PWM
    usTrig.period_us(99990);    //changed this so it operates at 10 cycles/sec
    usTrig.pulsewidth_us(10);
    //usTrig.write(0.5f);
    float cm, dist;

    //char response[1];
    Motor spin;
    spin.pulse();

    printf("Hello world 1!\n");

    while(1) {
        //PWM checking
        while (! usEcho.read()); //wait for us_echo to go high
        t.start();
        while (usEcho.read()); //wait for echo to go low
        dist = t.read_us();
        t.stop();
        cm = (dist*5)/300;
        printf("%.2f cm\n", cm);
        t.reset();


        //setting up reading for line following
        /*detect0 = line0.read();
        detect1 = line1.read();
        detect2 = line2.read();

        //line following
        if (detect0 && !detect1 && detect2) {
            spin.forward();
        }
        if (detect0 && detect1 && !detect2){
            spin.right();
        }
        if (!detect0 && detect1 && detect2) {
            spin.left();
        }
        if (detect0 && detect1 && detect2) {
            spin.slow();
        }
        else {
            spin.slow();
        }*/

        //motor response
        /*scanf("%s", response);  //gets a user response for direction;
        printf("%s\n", response);

        if(strcmp(response, "f") == 0) {
            spin.forward();
        } else if (strcmp(response,"b") == 0) {
            spin.back();
        } else if (strcmp(response,"r") == 0) {
            spin.right();
        } else if (strcmp(response,"l") == 0) {
            spin.left();
        } else if(strcmp(response,"+") == 0) {
            spin.change_period1(50);
            spin.change_period2(50);
        } else if (strcmp(response, "s") == 0) {
            spin.slow();
        } else {
            continue;
        }*/

        spin.forward();
        if (cm <= 5.0) {
            spin.back();
            wait(0.1);
            spin.right();
            wait(0.1);
        }
    }
}

void Motor :: forward(void)
{
    in1 = 1;    //motor1 CW
    in2 = 0;
    in3 = 0;    //motor2 CCW
    in4 = 1;
}

void Motor :: back(void)
{
    in1 = 0;    //motor1 CCW
    in2 = 1;
    in3 = 1;    //motor2 CW
    in4 = 0;
}

void Motor :: right(void)
{
    in1 = 0;    //motor1 CCW
    in2 = 1;
    in3 = 0;    //motor2 CCW
    in4 = 1;
}

void Motor :: left(void)
{
    in1 = 1;    //motor1 CW
    in2 = 0;
    in3 = 1;    //motor2 CW
    in4 = 0;
}

void Motor :: slow(void)
{
    in1 = 0;
    in2 = 0;
    in3 = 0;
    in4 = 0;
}

void Motor :: pulse(void)
{
    ENA.pulsewidth_ms(pulse1);
    ENA.write(0.5f);
    ENB.pulsewidth_ms(pulse2);
    ENB.write(0.5f);
}

void Motor :: change_period1(int cyc1)
{
    if (pulse1 <= 10) {
        printf("Duty cycle too short\n");
    } else {
        pulse1 += cyc1;
    }
}

void Motor :: change_period2(int cyc2)
{
    if (pulse2 <= 10) {
        printf("Duty cycle too short\n");
    } else {
        pulse2 += cyc2;
    }
}