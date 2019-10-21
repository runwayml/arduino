
let serial; // instance of a serial connection
let img; // hold the image generated by runway and received with http
let txt; // hold the text received from arduino

function setup() {
  createCanvas(400, 400);

  imageMode(CENTER);
  textAlign(CENTER, BOTTOM);
  
  serial = new p5.SerialPort();
  // Assuming our Arduino is connected, let's open the connection to it
  // Change this to the name of your arduino's serial port
  serial.open("/dev/tty.usbmodem145101");
  // When we connect to the underlying server
  serial.on('connected', serverConnected);
  // When we some data from the serial port : callback the 'gotData' function
  serial.on('data', gotData);
  
  textSize(20);
  fill(255);
  stroke(0);

}

function draw() {
  background(220);
  if (img != null) image(img, width*0.5, height*0.5, width,height);
  if (txt != null) text(txt.caption,width*0.5, height - 20);
}

// There is data available to work with from the serial port
function gotData() {
  let currentString = serial.readLine(); // read the incoming string
  trim(currentString); // remove any trailing whitespace
  if (!currentString) return; // if the string is empty, do no more
  
  txt = JSON.parse(currentString); // parse the json file read from arduino
  console.log(txt);
  
  // post the json file to runway and handle the response as an anonnymous function
  httpPost("http://localhost:8000/query", txt, function(response) {
    //console.log("got response");
    let data = JSON.parse(response);
    img = loadImage(data.result);

  })
}

// We are connected and ready to go
function serverConnected() {
  print("Connected to Server");
}