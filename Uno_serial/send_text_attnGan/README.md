# Send data to AttnGAN from Arduino Uno

You will be able to find the p5js client code here : https://editor.p5js.org/b2renger/sketches/HSu5bjj3P

The goal will be to use a potentiometer to navigate through the lines of a poetry and generate an image for each line using the AttnGAN model.

## List of parts necessary

- a arduino uno
- a breadboard
- a 10kohms potentiometer


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



## Code break down

### Getting data from the potentiometer and map it

### Formatting data as a JSON string

The code uses the amazing [arduinoJson](https://arduinojson.org/) library. Which has a great documentation and a lot of examples.

```c
#include <ArduinoJson.h>
```
### Using the serial connection to send data to P5JS

#### Setting up p5.serialcontrol app

#### Using p5.serialport lib in the p5js editor










