#include <16f887.h>
#fuses hs
#use delay(clock=20m)
#define ser pin_d0
#define sck pin_d1
#define rck pin_d2
#define x1_d2 0x11
#define v1_d2 0x14
#define d1_x2 0x0a
#define d1_v2 0x22
#define tg_do 29
#define tg_xanh 26
#define tg_vang 2

void xuat_1byte(unsigned int8 bytexuat)
{
   unsigned int8 i;

   #bit bser = bytexuat.7

   for(i=0;i<8;i++)
   {
      output_bit(ser,bser);
      output_low(sck); output_high(sck);
      bytexuat=bytexuat<<1;
   }
}

void xuat_4led_7doan(unsigned int8 led4, led3, led2, led1)
{
   xuat_1byte(led4);
   xuat_1byte(led3);
   xuat_1byte(led2);
   xuat_1byte(led1);
   output_low(rck); output_high(rck);
}

unsigned int8 dem1, dem2;
unsigned int8 ma7doan[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void main ()
{
   set_tris_d (0x00) ;
   set_tris_c (0x00) ;

   laplai:
   output_c (x1_d2) ;
   dem1 = tg_xanh;
   dem2 = tg_do;

   do
   {
      xuat_4led_7doan (ma7doan[dem1 / 10], ma7doan[dem1 % 10], ma7doan[dem2 / 10], ma7doan[dem2 % 10]);
      delay_ms (1000) ;
      dem1--;
      dem2--;
   }

   while (dem1 != 255);
   output_c (v1_d2) ;
   dem1 = tg_vang;

   do
   {
      xuat_4led_7doan (ma7doan[dem1 / 10], ma7doan[dem1 % 10], ma7doan[dem2 / 10], ma7doan[dem2 % 10]);
      delay_ms (1000) ;
      dem1--;
      dem2--;
   }

   while (dem1 != 255);
   output_c (d1_x2) ;
   dem1 = tg_do;
   dem2 = tg_xanh;

   do
   {
      xuat_4led_7doan (ma7doan[dem1 / 10], ma7doan[dem1 % 10], ma7doan[dem2 / 10], ma7doan[dem2 % 10]);
      delay_ms (1000) ;
      dem1--;
      dem2--;
   }

   while (dem2 != 255);
   output_c (d1_v2) ;
   dem1 = tg_do;
   dem2 = tg_vang;

   do
   {
      xuat_4led_7doan (ma7doan[dem1 / 10], ma7doan[dem1 % 10], ma7doan[dem2 / 10], ma7doan[dem2 % 10]);
      delay_ms (1000) ;
      dem1--;
      dem2--;
   }

   while (dem2 != 255);
   goto laplai;
}

