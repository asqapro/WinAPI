#pragma config(Motor, port3, armMotor, tmotorNormal, openLoop)
task main(){
	while(true){
		motor[armMotor] = vexRT[Ch1];
	}
}
