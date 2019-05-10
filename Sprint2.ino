#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <EEPROM.h>
#define _NAMIKI_MOTOR   //for Namiki 22CL-103501PG80:1
#include <fuzzy_table.h>
#include <PID_Beta6.h>
#include <MotorWheel.h>
#include <Omni4WD.h>

#include <fuzzy_table.h>
#include <PID_Beta6.h>

/*

            \                    /
   wheel1   \                    /   wheel4
   Left     \                    /   Right


                              power switch

            /                    \
   wheel2   /                    \   wheel3
   Right    /                    \   Left

*/

/*
  irqISR(irq1,isr1);
  MotorWheel wheel1(5,4,12,13,&irq1);

  irqISR(irq2,isr2);
  MotorWheel wheel2(6,7,14,15,&irq2);

  irqISR(irq3,isr3);
  MotorWheel wheel3(9,8,16,17,&irq3);

  irqISR(irq4,isr4);
  MotorWheel wheel4(10,11,18,19,&irq4);
*/

irqISR(irq1, isr1);
MotorWheel wheel1(3, 2, 4, 5, &irq1);

irqISR(irq2, isr2);
MotorWheel wheel2(11, 12, 14, 15, &irq2);

irqISR(irq3, isr3);
MotorWheel wheel3(9, 8, 16, 17, &irq3);

irqISR(irq4, isr4);
MotorWheel wheel4(10, 7, 18, 19, &irq4);


Omni4WD Omni(&wheel1, &wheel2, &wheel3, &wheel4);

void setup() {
  //TCCR0B=TCCR0B&0xf8|0x01;    // warning!! it will change millis()
  TCCR1B = TCCR1B & 0xf8 | 0x01; // Pin9,Pin10 PWM 31250Hz
  TCCR2B = TCCR2B & 0xf8 | 0x01; // Pin3,Pin11 PWM 31250Hz

  Omni.PIDEnable(0.31, 0.01, 0, 10);
  
  losange(30, 1500, 400);
  delay(1000);
  losanger(30, 1500, 400);

  //delay(1000);
  //triangleR(15);


  //carre(30, 1500, 400);
  //delay(1000);
  //rectangle(30, 1500, 1000, 400);
  //delay(1000);
  //triangle(30, 1500, 400);
  //delay(1000);
  //rd(30, 1500, 400);
  //delay(1000);
  //rg(30, 1500, 400);
  //delay(1000);
}

void rd(int speedMMPS, int duration, int uptime) {
  Omni.setCarRotateRight(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void rg(int speedMMPS, int duration, int uptime) {
  Omni.setCarRotateLeft(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void av(int speedMMPS, int duration, int uptime) {
  Omni.setCarAdvance(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void ar(int speedMMPS, int duration, int uptime) {
  Omni.setCarBackoff(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void td(int speedMMPS, int duration, int uptime) {
  Omni.setCarRight(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void tg(int speedMMPS, int duration, int uptime) {
  Omni.setCarLeft(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void dag(int speedMMPS, int duration, int uptime) {
  Omni.setCarUpperLeft(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void dad(int speedMMPS, int duration, int uptime) {
  Omni.setCarUpperRight(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void darg(int speedMMPS, int duration, int uptime) {
  Omni.setCarLowerLeft(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

void dard(int speedMMPS, int duration, int uptime) {
  Omni.setCarLowerRight(speedMMPS);
  Omni.setCarSpeedMMPS(speedMMPS, uptime);
  delay(duration);
  Omni.setCarSlow2Stop(uptime);
}

//Partie Carré

void carre(int speedMMPS, int duration, int uptime) {
  av(speedMMPS, duration, uptime);
  td(speedMMPS, duration, uptime);
  ar(speedMMPS, duration, uptime);
  tg(speedMMPS, duration, uptime);
}

void carret(int taille) {
  int duree = (taille / 40) * 2;
  carre(40, duree * 1000, 0);
}

//rotation

void carrer(int speedMMPS, int duration, int uptime) {
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
}

void carreR(int taille) {
  int duree = (taille / 40) * 2;
  carrer(30, duree * 1000, 400);
}
// Partie Rectangle

void rectangle(int speedMMPS, int durationl, int durationL, int uptime) {
  av(speedMMPS, durationl, uptime);
  td(speedMMPS, durationL, uptime);
  ar(speedMMPS, durationl, uptime);
  tg(speedMMPS, durationL, uptime);
}

void rectanglet(int taillel, int tailleL) {
  int dureel = (taillel / 40) * 2000;
  int dureeL = (tailleL / 40) * 2000;
  rectangle(40, dureel, dureeL, 0);
}

//rotation

void rectangler(int speedMMPS, int duration, int uptime) {
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
  av(speedMMPS, duration, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 850, uptime);
}

void rectangleR(int taille) {
  int duree = (taille / 40) * 2;
  rectangler(30, duree * 1000, 400);
}

// Partie Triangle

void triangle(int speedMMPS, int duration, int uptime) {
  dag(speedMMPS, duration, uptime);
  darg(speedMMPS, duration, uptime);
  td(speedMMPS, duration, uptime);
}
void trianglet(int tailleT) {
  int dureeT = (tailleT / 40) * 2;
  triangle(40, dureeT * 1000, 0);
}

//rotation

void triangler(int speedMMPS, int duration, int uptime) {
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 1200, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 1200, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 1200, uptime);
}

void triangleR(int taille) {
  int duree = (taille / 40) * 2;
  triangler(30, duree * 1000, 400);
}

//Partie Losange

void losange(int speedMMPS, int duration, int uptime) {
  dad(speedMMPS, duration, uptime);
  dard(speedMMPS, duration, uptime);
  darg(speedMMPS, duration, uptime);
  dag(speedMMPS, duration, uptime);
}

void losanget(int tailleT) {
  int dureeT = (tailleT / 40) * 2;
  losange(40, dureeT * 1000, 0);
}

//rotation

void losanger(int speedMMPS, int duration, int uptime) {
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 1500, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 425, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 1500, uptime);
  av(speedMMPS, duration, uptime);
  rd(speedMMPS, 425, uptime);
}

void losangeR(int taille) {
  int duree = (taille / 40) * 2;
  losanger(30, duree * 1000, 400);
}

// Partie Cercle
void cercle() {
  wheel1.advancePWM(80);
  wheel2.advancePWM(80);
  wheel3.backoffPWM(3);
  wheel4.backoffPWM(3);
  Omni.setCarStop();
}


void loop() {
}
