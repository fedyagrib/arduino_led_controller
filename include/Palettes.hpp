#include <FastLED.h>

DEFINE_GRADIENT_PALETTE( bhw3_62_gp ) {
    0, 255,255, 45,
   43, 208, 93,  1,
  137, 224,  1,242,
  181, 159,  1, 29,
  255,  63,  4, 68};

DEFINE_GRADIENT_PALETTE( bhw3_61_gp ) {
    0,  14,  1, 27,
   48,  17,  1, 88,
  104,   1, 88,156,
  160,   1, 54, 42,
  219,   9,235, 52,
  255, 139,235,233};

DEFINE_GRADIENT_PALETTE( gr63_hult_gp ) {
    0, 168,254,184,
   63, 170,205,206,
  126,  86,255,159,
  189, 198,243,203,
  255, 167, 34,211,};

CRGBPalette16 SetupTotallyRandomPalette(){
  CRGBPalette16 result;
    for( int i = 0; i < 16; i++) {
      result[i] = CHSV( random8(), 255, random8());
    }
  return result;
}



