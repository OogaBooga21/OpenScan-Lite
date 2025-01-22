
const int table_dirPin = 2;
const int table_stepPin = 3; // this is for the big "table", that controls the tilt

const int stand_dirPin = 9;
const int stand_stepPin = 10; // this is for the small "stand", which cotnrolls rotation

const int steps_per_revolution = 200 * 16; // using 1/16 microstepping
const float ratio = 5.33333; // gear ratio between the stepper spock and the big arm spock

int table_angles_per_fram_angle = 60; // number of pictures taken during a full revolution
int table_tilt_number = 3; // how many times is the whole table gona tilt ? 
int table_tilt_angle = 30; // by how much is the table gonna tilt ?
int new_pose_delay = 3100; //3.1 seconds if you camera focuses faster, lower this for better speeds

const bool started = false;
int pictures_taken = 0;

void setup()
{
	pinMode(table_stepPin, OUTPUT);
	pinMode(table_dirPin, OUTPUT);
  pinMode(stand_stepPin, OUTPUT);
	pinMode(stand_dirPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Press 1 to start");
}

char processSerialdata()
{
  if(Serial.available()!=0)
  {
   return Serial.read(); 
  }
  else
  {
    return '0';
  }
}

char scan_object()
{
Serial.println("Press 2 to stop scanner");
// Set motor direction clockwise
	digitalWrite(table_dirPin, HIGH); // clockwise
  digitalWrite(stand_dirPin, LOW); // counter-clockwise this works for me, might need to be changed depending on how you mount your steppers + camera

  for(int stand_pos = 0;stand_pos<table_tilt_number;stand_pos++)
  {
    for(int table_angles=0;table_angles<table_angles_per_fram_angle;table_angles++)
    {
      pictures_taken += 1;
      Serial.print("Pic:");
      Serial.print(pictures_taken);
      Serial.println("");
      delay(new_pose_delay); // delay between table rotations

        char a = processSerialdata();
        if( a == '2')
        {
        return "S";
        }


      for(int table_angle_step=0;table_angle_step<steps_per_revolution/table_angles_per_fram_angle;table_angle_step++)
      {
        digitalWrite(table_stepPin, HIGH);
		    delayMicroseconds(100);
		    digitalWrite(table_stepPin, LOW);
		    delayMicroseconds(100);
      }
    }

    if(stand_pos != table_tilt_number){
      for(int stand_angle=0;stand_angle<table_tilt_angle*(steps_per_revolution/360)*ratio;stand_angle++)
      {
        digitalWrite(stand_stepPin, HIGH);
		    delayMicroseconds(100);
		    digitalWrite(stand_stepPin, LOW);
		    delayMicroseconds(100);
      }
    }

  }
  return "C";
}

void loop()
{
  char a = processSerialdata();
  char flag = "?";
  if( a == '1')
  {
    flag = scan_object();
    Serial.print("Scan ");
    Serial.print(flag);
  }
	
}