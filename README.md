# Valor Animatronic


## Animation instructions
Each step in the timeline is sequential, so if there is a 1000-second delay, the second animation component will only start after the first finishes.

The animation system comprises of a TimeLineValue array which holds all the values on the timeline. The Timeline consists of an array of values and its length. The Animation contains the AnimationComponents (must be in the same order as it is in the TimeLine) and the TimeLine.
For an example of creating a timeline go to "Timelines.h" and "main.cpp". 

After the final step of the animation, the robot goes to the default position. Wings down and head forward.

### Animation values
Variable  | Meaning | Supported values |
----|----| ---- |
 instruction  | Instruction to the animatable component. For motors it is the angle where the motor goes and for the speaker, it refers to the song. |  Up to 16 characters string. 
 delay | Delay in milliseconds. Essentially how long does it wait to start playing this part. | All long values| 
 maxDuration | Maximum duration in milliseconds. How does it stay on this step or when it is finished.  For a servo, there is no finish so it stays for that duration in the animation state. | All long values| 

### Head servo
Position  | Angle |
----|----|
 Left   | 180  |
 Middle | 90 |
 Right | 0 |


### Wing servo
Position  | Angle |
----|----|
 Up  | 110 |
 Down| 180 |

Wings take about 2000 milliseconds to go up.


## Assembly  
### Wiring Diagram
![Wiring Diagram](docs/diagrams/WireDiagram.drawio.png "Wiring Diagram")

### Pin usage
Pin  | Type  | Purpose   |
----|----|---|
 0  | Serial | MP3 module  TX |
 1  | Serial | MP3 module  RX |
 3  | INPUT  | Button         |
 10 | PWM | Wing Servo        |
 11 | PWM | Head Servo        |

### STL Files


### Assembly instructions