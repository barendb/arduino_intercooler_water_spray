const float INPUT_VOLTAGE		= 3.3;
const int INPUT_TEMP 			= 0;
const int OUTPUT_OVERTHRESHOLD 	= 9;
const int OUTPUT_SPRAY			= 10;
const float TEMP_THRESHOLD 		= 50.00;	// 50 degrees
const int SPRAY_PULSE_DURATION	= 2*1000;	// 4 seconds
const int SLEEP_BETWEEN_SPRAY	= 10*1000;	// 15 seconds;
const int SLEEP					= 1*1000;	// 1 second

const int ON 					= 255;
const int OFF 					= 0;

void setup()
{
	Serial.begin(9600);

  	analogReference(EXTERNAL);
  	pinMode(OUTPUT_OVERTHRESHOLD, OUTPUT);
  	pinMode(OUTPUT_SPRAY, OUTPUT);
}
 
void loop()
{
	float temp = getCurrentTemp();

	// if less do nothing
	if (temp < TEMP_THRESHOLD)
	{
		setOverThresholdOff();
		delay(SLEEP);
		return;
	}

	setOverThresholdOn();
	spray();
}

float getCurrentTemp() {
	int reading = analogRead(INPUT_TEMP);
	float voltage = reading * INPUT_VOLTAGE;
 	voltage /= 1024.0; 
 	float temperatureC = voltage * 100;

 	Serial.print("CurrentTemp: ");
 	Serial.print(voltage); 
 	Serial.print(" volts, Temp: ");
 	Serial.print(temperatureC);
 	Serial.println(" degrees C");

 	return temperatureC;
}

void spray() {
	Serial.println("Begin spray");
	analogWrite(OUTPUT_SPRAY, ON);
	delay(SPRAY_PULSE_DURATION);
	analogWrite(OUTPUT_SPRAY, OFF);

	delay(SLEEP_BETWEEN_SPRAY);
	Serial.println("End spray");
}

void setOverThresholdOn() {
	Serial.println("Over threshold ON");
	analogWrite(OUTPUT_OVERTHRESHOLD, ON);
}

void setOverThresholdOff() {
	Serial.println("Over threshold OFF");
	analogWrite(OUTPUT_OVERTHRESHOLD, OFF);
}