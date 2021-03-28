#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

DigitalIn bt_up(D12);      // D12
DigitalIn bt_down(D11);    // D11
DigitalIn bt_sl(D10);      // D10
//InterruptIn button(USER_BUTTON); 
//DigitalOut led_up(LED1);
DigitalOut led_down(LED2);
DigitalOut led_sl(LED3);
AnalogOut  aout(D7);
AnalogOut  Aout(D13);
AnalogIn ain(A0);
Timer t;
int freq = 0;
int sample = 500;
float ADCdata[500];
// generate wave
Thread thread;
//Thread Wave_Sampling;

uLCD_4DGL uLCD(D1, D0, D2);

void wave()
{   
    float i;
    while (1){
        if (freq == 1) {        // 200Hz
            for (i = 0.0f; i < 1; i+=0.0145635f) {
                aout = i;
            }
            for (i = 1.0f; i > 0.0f; i -= 0.001626f) {
                aout = i;
            }
        } else if(freq == 2) {  // 1 Hz
            for (i = 0.0f; i < 1; i+=0.000109f) {
                aout = i;
            }
            for (i = 1.0f; i > 0.0f; i -= 0.000012f) {
                aout = i;
                // ThisThread::sleep_for(1ms);
            }
        } else {    // >> 10*200Hz
            for (i = 0.0f; i < 1; i+=0.27f) {
                aout = i;
            }
            for (i = 1.0f; i > 0.0f; i -= 0.03f) {
                aout = i;
            }
        }
    }
}

void wave_sampling() {
    int i = 0;
    //t.start();
    for (i = 0; i < sample; i++){
        Aout = ain;
        ADCdata[i] = ain;
        ThisThread::sleep_for(1000ms/sample); // sampling rate = 500/s 實際55/s
    }
    //t.stop();
    //auto ms = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();
    for (i = 0; i < sample; i++) {
        printf("%f\r\n", ADCdata[i]);
    }
    //printf ("Timer time: %llu ms\n", ms);
}


int main()
{
    int pre_freq = 0;
    // bool sl = 0;

    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    bt_up.mode(PullDown);
    bt_down.mode(PullDown);
    bt_sl.mode(PullDown);
    // LED initialization
    //led_up = 0;
    led_down = 0;
    led_sl = 0;
    // uLCD initialization
    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.textbackground_color(WHITE);
    uLCD.color(BLUE);
    uLCD.printf("\n108061113\n"); 
    uLCD.text_width(2); //3X size text
    uLCD.text_height(2);
    uLCD.color(GREEN);
    uLCD.locate(1,2);
    uLCD.printf("freq_1");
    uLCD.locate(1,4);
    uLCD.printf("freq_2");
    thread.start(wave);
    //Wave_Sampling.start(wave_sampling);
    //button.rise(&wave_sampling);

    while (1) {
        //led_up = bt_up; // toggle led based on value of button
        led_down = bt_down; // toggle led based on value of button
        led_sl = bt_sl; // toggle led based on value of button
        // printf("led_up = %d, led_down = %d, led_sl = %d\n", bt_up.read(), bt_down.read(), bt_sl.read());
        if (freq == 1) {
            // show freq_1 on uLCD
            uLCD.locate(1,2);
            uLCD.printf("freq_1");
            uLCD.locate(1,4);
            uLCD.printf("      ");

            if (pre_freq == 0) {
                wave_sampling();
                pre_freq = 1;
            }
            if (bt_down.read() == 1) {
                pre_freq = 2;
            } else if (bt_sl.read()) {
                freq = pre_freq;
                pre_freq = 0;
            }
        } else if (freq == 2) {
            // show freq_2 on uLCD
            uLCD.locate(1,2);
            uLCD.printf("      ");
            uLCD.locate(1,4);
            uLCD.printf("freq_2");

            if (pre_freq == 0) {
                wave_sampling();
                pre_freq = 2;
            }
            if (bt_up.read()) {
                pre_freq = 1;
            } else if (bt_sl.read()) {
                freq = pre_freq;
                //wave_sampling();
                pre_freq = 0;
            }
        } else if (freq == 0) {
            // show freq_1 and freq_2 on uLCD
            uLCD.locate(1,2);
            uLCD.printf("freq_1");
            uLCD.locate(1,4);
            uLCD.printf("freq_2");

            // no wave
            // thread.join();

            if (bt_up.read() == 1) {
                pre_freq = 1;
            } else if (bt_down.read() == 1) {
                pre_freq = 2;
            } else if (bt_sl.read() == 1) {
                freq = pre_freq;
                //wave_sampling();
                pre_freq = 0;
            }
        }

        // ThisThread::sleep_for(100ms);
    }
}