// Подключаем библиотеку FastLED.
#include "FastLED.h"

// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 30

// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 8

// Создаем переменную strip для управления нашей лентой.
CRGB strip[LED_COUNT];

void configLed()
{
  // Добавляем ленту.
  FastLED.addLeds<NEOPIXEL, LED_PIN>(strip, LED_COUNT);
}

void setled()
{
  // Включаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = CRGB::Red; // Красный цвет.
  }
  // Передаем цвета ленте.
  FastLED.show();
  // Ждем 500 мс.
  delay(500);
  // Выключаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = CRGB::Black; // Черный цвет, т.е. выключено.
  }
  // Передаем цвета ленте.
  FastLED.show();
  // Ждем 500 мс.
  delay(500);
}