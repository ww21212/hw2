# hw2
# hw2

(1) how to setup and run your program

Digital Input: D12, D11, D10 (used to read button)

Analog Input: A0 (source wave used to sample wave)

Analog Output: D13 (sampled wave), D7 (generated wave)

other pin: 5V, RX, TX, GND, RES (uLCD)

(2) what are the results

genrated wave
| 1Hz | 195Hz |
| -------- | -------- |
| ![](https://i.imgur.com/DoHsn27.png)|![](https://i.imgur.com/2akaMce.png)|

python plot
| 1Hz | 195Hz | 
| -------- | -------- | 
| ![](https://i.imgur.com/Pud30zS.png)| ![](https://i.imgur.com/9xHyMeZ.png)| 
Note:
    Because sleep_for funtion has some problem. My max sampling rate is 166.666667, which does not  achieve 195*2 = 390, so the sampled wave of 195 Hz wave is not complete.
    
show low pass filter function


| 3730Hz ||
| -------- | -------- |
|before filtered | after filtered|
| ![](https://i.imgur.com/c6W0DNl.png)| ![](https://i.imgur.com/zzW14RR.png)|
