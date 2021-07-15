# Gameduino
Code for the Gameduino Project
Code vom Arduino: 

## Einleitung
Der Gameduino™ ist die perfekte Mischung aus einem Gameboy und einem Arduino, der TFT Touchbildschirm ermöglicht zusammen mit dem 360° Joystick und den 2 ergonomisch platzierten Knöpfen ein intensives Spielerlebnis. Spiele wie PacMan, Tetris können neu erlebt werden.

## Technische Herausforderungen
- Die SPI-Übertragungsrate des Arduinos ist mit 8MHz zu langsam für einen Bildschirm, deshalb mussten wir 2 Mikrokontroller benutzen, einen ESP-8266 und einen Arduino Uno. 
- Die Stromstärke einer handelsüblichen 5V Batterie ist zu niedrig für unsere beiden Mikrokontroller, deshalb sind wir auf eine externe Stromversorgung umgestiegen.

## Ausblick
Man kann weitere Spiele entwickeln und die WiFi Funktionalität des ESP-8266 noch stärker ausnutzen. Außerdem besteht die Möglichkeit weitere Geräte an den Gameduino™ über seine I²C-Schnittstelle anzuschließen.
