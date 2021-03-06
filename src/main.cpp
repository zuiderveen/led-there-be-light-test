#include "FastLED.h"

#define NUM_LEDS 156
CRGB leds[NUM_LEDS];
#define PIN 8

void RGBLoop();

void FadeInOut(byte red, byte green, byte blue);

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

void RunningLights(byte red, byte green, byte blue, int WaveDelay);

void colorWipe(byte red, byte green, byte blue, int SpeedDelay);

void rainbowCycle(int SpeedDelay);

void theaterChase(byte red, byte green, byte blue, int SpeedDelay);

void theaterChaseRainbow(int SpeedDelay);

void Fire(int Cooling, int Sparking, int SpeedDelay);

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous);

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay,
                int SpeedDelay);

void setup() {
    FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    pinMode(2, INPUT_PULLUP);  // internal pull-up resistor
}

void loop() {
    // RGBLoop - no parameters
    RGBLoop();

    // FadeInOut - Color (red, green. blue)
    FadeInOut(0xff, 0x00, 0x00); // red
    FadeInOut(0xff, 0xff, 0xff); // white
    FadeInOut(0x00, 0x00, 0xff); // blue

    // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
    Strobe(0xff, 0xff, 0xff, 10, 50, 1000);

    // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
    CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);

    // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
    NewKITT(0xff, 0x00, 0x00, 8, 10, 50);

    // Running Lights - Color (red, green, blue), wave dealy
    RunningLights(0xff, 0x00, 0x00, 50);  // red
    RunningLights(0xff, 0xff, 0xff, 50);  // white
    RunningLights(0x00, 0x00, 0xff, 50);  // blue

    // colorWipe - Color (red, green, blue), speed delay
    colorWipe(0x00, 0xff, 0x00, 50);
    colorWipe(0x00, 0x00, 0x00, 50);

    // rainbowCycle - speed delay
    rainbowCycle(20);

    // theatherChase - Color (red, green, blue), speed delay
    theaterChase(0, 0, 0xff, 50);

    // theaterChaseRainbow - Speed delay
    theaterChaseRainbow(50);

    // Fire - Cooling rate, Sparking rate, speed delay
    Fire(55, 120, 15);

    // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
    // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
    // CAUTION: If set to continuous then this effect will never stop!!!

    // mimic BouncingBalls
    byte onecolor[1][3] = {{0xff, 0x00, 0x00}};
    BouncingColoredBalls(1, onecolor, false);

    // multiple colored balls
    byte colors[3][3] = {{0xff, 0x00, 0x00},
                         {0xff, 0xff, 0xff},
                         {0x00, 0x00, 0xff}};
    BouncingColoredBalls(3, colors, false);

    // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
    meteorRain(0xff, 0xff, 0xff, 10, 64, true, 30);
}

// ***************************************
// ** FastLed/NeoPixel Common Functions **
// ***************************************

// Apply LED color changes
void showStrip() {
    FastLED.show();
}

// Set a LED color (not yet visible)
void setPixel(int Pixel, byte red, byte green, byte blue) {
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}

// Set all LEDs to a given color and apply it (visible)
void setAll(byte red, byte green, byte blue) {
    for (int i = 0; i < NUM_LEDS; i++) {
        setPixel(i, red, green, blue);
    }
    showStrip();
}

// ** LEDEffect Functions **
void RGBLoop() {
    for (int j = 0; j < 3; j++) {
        // Fade IN
        for (int k = 0; k < 256; k++) {
            switch (j) {
                case 0:
                    setAll(k, 0, 0);
                    break;
                case 1:
                    setAll(0, k, 0);
                    break;
                case 2:
                    setAll(0, 0, k);
                    break;
            }
            showStrip();
            delay(3);
        }
        // Fade OUT
        for (int k = 255; k >= 0; k--) {
            switch (j) {
                case 0:
                    setAll(k, 0, 0);
                    break;
                case 1:
                    setAll(0, k, 0);
                    break;
                case 2:
                    setAll(0, 0, k);
                    break;
            }
            showStrip();
            delay(3);
        }
    }
}

void FadeInOut(byte red, byte green, byte blue) {
    float r, g, b;

    for (int k = 0; k < 256; k = k + 1) {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
    }

    for (int k = 255; k >= 0; k = k - 2) {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
    }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
    for (int j = 0; j < StrobeCount; j++) {
        setAll(red, green, blue);
        showStrip();
        delay(FlashDelay);
        setAll(0, 0, 0);
        showStrip();
        delay(FlashDelay);
    }

    delay(EndPause);
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {

    for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);

    for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);
}

// used by NewKITT
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
    for (int i = ((NUM_LEDS - EyeSize) / 2); i >= 0; i--) {
        setAll(0, 0, 0);

        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

        setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(NUM_LEDS - i - j, red, green, blue);
        }
        setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

        showStrip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

// used by NewKITT
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
    for (int i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
        setAll(0, 0, 0);

        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

        setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(NUM_LEDS - i - j, red, green, blue);
        }
        setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

        showStrip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

// used by NewKITT
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
    for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

// used by NewKITT
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
    for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}


void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}


void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
    int Position = 0;

    for (int i = 0; i < NUM_LEDS * 2; i++) {
        Position++; // = 0; //Position + Rate;
        for (int i = 0; i < NUM_LEDS; i++) {
            // sine wave, 3 offset waves make a rainbow!
            //float level = sin(i+Position) * 127 + 128;
            //setPixel(i,level,0,0);
            //float level = sin(i+Position) * 127 + 128;
            setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
                     ((sin(i + Position) * 127 + 128) / 255) * green,
                     ((sin(i + Position) * 127 + 128) / 255) * blue);
        }

        showStrip();
        delay(WaveDelay);
    }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        setPixel(i, red, green, blue);
        showStrip();
        delay(SpeedDelay);
    }
}

// used by rainbowCycle and theaterChaseRainbow
byte *Wheel(byte WheelPos) {
    static byte c[3];

    if (WheelPos < 85) {
        c[0] = WheelPos * 3;
        c[1] = 255 - WheelPos * 3;
        c[2] = 0;
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        c[0] = 255 - WheelPos * 3;
        c[1] = 0;
        c[2] = WheelPos * 3;
    } else {
        WheelPos -= 170;
        c[0] = 0;
        c[1] = WheelPos * 3;
        c[2] = 255 - WheelPos * 3;
    }
    return c;
}


void rainbowCycle(int SpeedDelay) {
    byte *c;
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        for (i = 0; i < NUM_LEDS; i++) {
            c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
            setPixel(i, *c, *(c + 1), *(c + 2));
        }
        showStrip();
        delay(SpeedDelay);
    }
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
    for (int j = 0; j < 10; j++) {  //do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, red, green, blue);    //turn every third pixel on
            }
            showStrip();

            delay(SpeedDelay);

            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, 0, 0, 0);        //turn every third pixel off
            }
        }
    }
}

void theaterChaseRainbow(int SpeedDelay) {
    byte *c;

    for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                c = Wheel((i + j) % 255);
                setPixel(i + q, *c, *(c + 1), *(c + 2));    //turn every third pixel on
            }
            showStrip();

            delay(SpeedDelay);

            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, 0, 0, 0);        //turn every third pixel off
            }
        }
    }
}

void setPixelHeatColor(int Pixel, byte temperature) {
    // Scale 'heat' down from 0-255 to 0-191
    byte t192 = round((temperature / 255.0) * 191);

    // calculate ramp up from
    byte heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2; // scale up to 0..252

    // figure out which third of the spectrum we're in:
    if (t192 > 0x80) {                     // hottest
        setPixel(Pixel, 255, 255, heatramp);
    } else if (t192 > 0x40) {             // middle
        setPixel(Pixel, 255, heatramp, 0);
    } else {                               // coolest
        setPixel(Pixel, heatramp, 0, 0);
    }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
    static byte heat[NUM_LEDS];
    int cooldown;

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++) {
        cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

        if (cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i] - cooldown;
        }
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = NUM_LEDS - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if (random(255) < Sparking) {
        int y = random(7);
        heat[y] = heat[y] + random(160, 255);
        //heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for (int j = 0; j < NUM_LEDS; j++) {
        setPixelHeatColor(j, heat[j]);
    }

    showStrip();
    delay(SpeedDelay);
}


void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
    float Gravity = -9.81;
    int StartHeight = 1;

    float Height[BallCount];
    float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
    float ImpactVelocity[BallCount];
    float TimeSinceLastBounce[BallCount];
    int Position[BallCount];
    long ClockTimeSinceLastBounce[BallCount];
    float Dampening[BallCount];
    boolean ballBouncing[BallCount];
    boolean ballsStillBouncing = true;

    for (int i = 0; i < BallCount; i++) {
        ClockTimeSinceLastBounce[i] = millis();
        Height[i] = StartHeight;
        Position[i] = 0;
        ImpactVelocity[i] = ImpactVelocityStart;
        TimeSinceLastBounce[i] = 0;
        Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        ballBouncing[i] = true;
    }

    while (ballsStillBouncing) {
        for (int i = 0; i < BallCount; i++) {
            TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
            Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) +
                        ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

            if (Height[i] < 0) {
                Height[i] = 0;
                ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
                ClockTimeSinceLastBounce[i] = millis();

                if (ImpactVelocity[i] < 0.01) {
                    if (continuous) {
                        ImpactVelocity[i] = ImpactVelocityStart;
                    } else {
                        ballBouncing[i] = false;
                    }
                }
            }
            Position[i] = round(Height[i] * (NUM_LEDS - 1) / StartHeight);
        }

        ballsStillBouncing = false; // assume no balls bouncing
        for (int i = 0; i < BallCount; i++) {
            setPixel(Position[i], colors[i][0], colors[i][1], colors[i][2]);
            if (ballBouncing[i]) {
                ballsStillBouncing = true;
            }
        }

        showStrip();
        setAll(0, 0, 0);
    }
}

// used by meteorrain
void fadeToBlack(int ledNo, byte fadeValue) {
    leds[ledNo].fadeToBlackBy(fadeValue);
}


void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay,
                int SpeedDelay) {
    setAll(0, 0, 0);

    for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {


        // fade brightness all LEDs one step
        for (int j = 0; j < NUM_LEDS; j++) {
            if ((!meteorRandomDecay) || (random(10) > 5)) {
                fadeToBlack(j, meteorTrailDecay);
            }
        }

        // draw meteor
        for (int j = 0; j < meteorSize; j++) {
            if ((i - j < NUM_LEDS) && (i - j >= 0)) {
                setPixel(i - j, red, green, blue);
            }
        }

        showStrip();
        delay(SpeedDelay);
    }
}

