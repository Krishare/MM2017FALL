#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

const int freq = 400;
const int Fs = 8000; //sampler rate
const int sec = 1;
const int channel = 1;
const int bit = 16;
const int amp = 32767; //16 bit: 32767~-32768
const int buff = sec*Fs*channel;

int main(int argc, char** argv)
{
    ofstream out;
    out.open("sintest.wav", ios::binary);

    int siz[buff];
    memset(siz, 0 , buff*2); //set memory space for siz

    for (int i = 0; i < buff; i++)
    {
        siz[i] = sin((2 * 3.14)* freq * i / Fs )*amp; // formula in pdf
        //cout<<"1";
    }

    out.write((const char*)&siz[0], buff*2);

    out.close();
    return 0;
}
