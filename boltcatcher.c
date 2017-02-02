/* Motors need to be configured here in the control panel
 * Please configure the following:
 * 		1. motorFL for front-left wheel
 *		2. motorBL for back-left wheel
 *		3. motorFR for front-right wheel
 *		4. motorBR for back-right wheel
 *		5. motorCatch for the bolt-catching mechanism
 * You may have to reverse some of these motors
 * All motor's are case-sensitive. E.g., motorfl and motorFL are NOT 
 the same motor.
 */

/* 
Copyright 2017 Herman Dhami.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* BOLT CATCHER PROGRAM
 * Program 
 * Inputs: User joystick commands, left-analog sticks's y-axis 
 * controlling the left-hand side of the robot, right-analog stick's y-
 * axis controlling the right-hand side of the robot. Top-right bumper 
 * engages the bolt collector.
 */

task main() {
	// Declares variables that read user inputs and control motor outputs
	int joy_l; // for left wheels
	int joy_r; // for right wheels
	int threshold = 10; // threshold value, so user input must a minimum
						// value for the robot to actually move.
	int modifier = 2; // set the joystick to move the robot at half speed
					  // 3 -> one-third speed, 4 -> one-quarter speed, ...
	int catch_modifier = 2; // sets the catching mechanism to half speed;
	while (1 == 1) {
		// sets the variables declared above to left and right analog stick
		joy_l = vexRT[ch3];
		joy_r = vexRT[ch2];
		
		// if neither analog stick exceeds the threshold, do not move.
		if (abs(joy_l) < threshold && abs(joy_r) < threshold) {
			motor[motorBL] = motor[motorFL] = motor[motorBR] 
			    = motor[motorFR] = 0;
		}
		// if only the right-analog stick exceeds the threshold, move the 
		// right side only
		else if (abs(joy_l) < threshold) {
			motor[motorBL] = motor[motorFL] = 0;
			motor[motorBR] = motor[motorFR] = joy_r / modifier;
		}
		// if only the left-analog stick exceeds the threshold, move the 
		// left side only
		else if (abs(joy_l) < threshold) {
			motor[motorBL] = motor[motorFL] = joy_l / modifier;
			motor[motorBR] = motor[motorFR] = 0;
		}
		// if both analog stick's exceed the threshold, move both;
		else {
			motor[motorBL] = motor[motorFL] = joy_l / modifier;
			motor[motorBR] = motor[motorFR] = joy_r / modifier;
		}
		
		// Engages the motor-catching mechanism
		// Top-right bumper causes catcher to PULL in material completely.
		if (vexRT[Btn6U] == 1) {
			motor[motorCatch] = 127 / catch_modifier;
		}
		// Bottom-right bumper causes catcher to PUSH out material
		// completely.
		else if (vexRT[Btn6D] == 1) {
			motor[motorCatch] = -128 / catch_modifier;
		}
		// No bumper activated causes catcher to disengage completely.
		else {
			motor[motorCatch] = 0;
		}
	}
}