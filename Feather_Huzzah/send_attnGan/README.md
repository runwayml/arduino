# Send data to AttnGAN from Feather Huzzah

In this example we will look into how to send data from the **feather huzzah** board to runway wirelessly via the **http** protocol.

The feather huzzah is board manufactured by Adafruit, it has a wifi (ESP8266) and a built-in battery port.

The goal will be to use a potentiometer to navigate through the lines of a poetry and generate an image for each line using the AttnGAN model.

## List of parts necessary

- a feather huzzah
- a breadboard
- a 10kohms potentiometer
- 10k resistance
- 47k or 22k resistance

## Setup the feather with arduino IDE
First you will want to setup your arduino IDE to work with this board following these instructions : https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide

## RunwayML setup
The runwayml is pretty straight forward :
- in the model directory look for the "AttnGAN" model which will take up some text to transform it to an image.
- run it 
- click on the network tab.
- make sure that in the input window http is selected.

The network tab will give usefull informations on how the input should be formatted eg **Input Specification**, the **server address** and **port** number, aswell as the usable **routes** to get/send data from/to the model.

In our case :

- we should send a **JSON** string with this kind of data :

    ```json
    {"caption":"the text I want to translate to image"}
    ```

- we want to send data to runwayml so we need to use the **POST** route from arduino to our computer running runway so our httpRoute will look something like:

    ```
    http://my-computer-ip:runway-port/query
    ```

So you should be sure to know the ip-adress of your computer, and take note of the port runway has allocated for our model to listen to.


## The circuit

Our circuit will be as follows :

![schematics](circuit.png)

Note that the feather only has only a 3.3V power pin, and we need to make a voltage divider with resistors to read the full range of our potentiometer.

You can find more information at this address : https://learn.adafruit.com/micropython-hardware-analog-i-o/analog-to-digital-converter


## Code break down





