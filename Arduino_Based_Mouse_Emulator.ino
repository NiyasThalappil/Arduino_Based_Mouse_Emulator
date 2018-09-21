/*
 * Arduino Based Mouse Emulator
 *
 * 
 * by Niyas Thalappil
 * 
 * www.youtube.com/c/NiyasThalappil
 * NiyazThalappil@gmail.com
 *
 */
#include <Mouse.h>

int horzPin = A1;                                                                                
int vertPin = A0;                                                                                 
int selPin = 9;                                                                                   
int vertZero, horzZero;                                                                         
int vertValue, horzValue;                                                                        
const int sensitivity = 200;                                                                     
int mouseClickFlag = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(horzPin, INPUT);                                                                      
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT);                                                                         
  digitalWrite(selPin, HIGH);                                                                     
  delay(1000);                                                                                   
  vertZero = analogRead(vertPin);                                                                
  horzZero = analogRead(horzPin);                                                                

}

void loop()
{
  vertValue = analogRead(vertPin) - vertZero;                                                     // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;                                                     // read horizontal offset

/*
  Serial.print("x ");
  Serial.println(horzValue);
  Serial.print("y ");
  Serial.println(vertValue);
 */
 

                                                                                                  // Mouse.move(xpos,ypos,wheel)
                                                                                                  // Mouse.move is always relative to the last position of the mouse cursor

  if (vertValue != 0)
    Mouse.move(0, vertValue/sensitivity, 0);                                                      // move mouse on y axis
  if (horzValue != 0)
    Mouse.move((horzValue/sensitivity)*-1, 0, 0);                                                 // move mouse on x axis

    
  if ((digitalRead(selPin) == 0) && (!mouseClickFlag))                                            // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);                                                                      // click the left button down
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag))                                               // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);                                                                    // release the left button
  }
}

