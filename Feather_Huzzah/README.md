# Examples for Feather Huzzah

These examples are made to work for the Feather Huzzah board which is sold by Adafruit.

This board is a wifi enabled board based on a ESP8266, it features a built-in port to charge and use batteries (3.7V lithium) and it runs at 3.3V.

Some links from the Adafruit website :

- [Overview](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview)
- [Setup with arduino ide](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)
- [Pinout](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts)

Three examples are available :

- [Receive data via http](/receive_text_vae_lagging_encoder_poetry) : which receives text data from the VAE laggin encoder poetry model and turns it into morse code through a blinking led.
- [Send data via http basic](/send_text_attnGan) : which uses a potentiometer to navigate through the lines of a poetry and send those lines to the attnGan model for it to generate an image.
- [Send data via http to vector](/send_vector_BigGan) : which will help you navigate through BigGan's latent space using a potentiometer.

These examples use the the built-in wifi library and make use of the [arduinoJson library v6](https://arduinojson.org/) available via the library manager in the arduino ide.


