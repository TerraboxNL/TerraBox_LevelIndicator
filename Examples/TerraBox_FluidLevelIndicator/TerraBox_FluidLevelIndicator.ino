#include <TerraBox_Widgets.h>        // For Levels
#include <TaskScheduler.h>           // TaskScheduler
#include <FluidTankLevelGUI.h>

#define USE_TASK_MONITOR            0
#define USE_SENSOR_A02_AUTO         1    // If disables, then the sensor simulation will run

#if USE_SENSOR_A02_AUTO

//
//  Create the A02 AUTO distance sensor
//
#include <A02_UART_Auto.h>           // A02_UART_Auto sensor
A02_UART_Auto theSensorAuto("LevelSensor", 1000);

#else
//
//  Simulated DistanceSensor
//
#include <SimulatedDistanceSensor.h>
SimulatedDistanceSensor theSimulatedSensor("SimulatedSensor", 1000, SIMU_TYPE_RANDOM, 0, 300);

#endif

//
//  The primary object containing the actual 
//
FluidTankLevelGUI theFluidGUI(
  "FluidMonitor",   // Name of the fluidmonitor task 
  1000,             // Runs every 1000 milliseconds
  "Water",          // The fluid of which you monitor its level

#if USE_SENSOR_A02_AUTO
&theSensorAuto      // Use the A02 Automatic distance sensor

#else
&theSimulatedSensor // Use a software simulated sensor

#endif

);  // Terminating the FluidTakLevelMonitor declaration

//
//  Create a task monitor
//
#if USE_TASK_MONITOR
#include <TaskMonitor.h>             // When using the TaskMonitor
TaskMonitor theTaskMonitor(10000);   // The task monitor runs every 10-thouseand milliseconds
#endif


void setup() {
  //
  //  Initialize Serial for diagnistics messages
  //
  Serial.begin(115200); 
  while(!Serial);

  //
  //  Initialize TFT screen
  //
  Serial.println();
  Serial.println("Configuring TFT screen");
  Screen.beginFull();
 
  //
  //  Since cycle times for both tasks are equal (5000 ms)
  //  Invoke run() for the sensor last, makes it the first task to execute
  //  After which the monitor will run...
  //  Processing the sensor return the field data i.e. a distance in mm.
  //  Which is requested from the sensor by the levelMonitor and after
  //  Field to GUI data conversion passed on to to GUI level indicator.
  //
#if USE_TASK_MONITOR
  Serial.println("Configuring Task Monitor");
  scheduler.run(&theTaskMonitor);     // Monitors the tasks runs last
#endif

  Serial.println("Configuring Fluid monitor");
  scheduler.run(&theFluidGUI);    // Fluid monitor GUI run() third in the TaskList 

#if USE_SENSOR_A02_AUTO

  Serial.println("Configuring A02 Auto sensor");
  scheduler.run(&theSensorAuto);      // Sensor run() second in the TaskList

#else

  Serial.println("Configuring Simulation sensor");
  scheduler.run(&theSimulatedSensor); // Sensor run() second in the TaskList

#endif

  Serial.println("Configuring Touching device");
  scheduler.run(&Touch);              // Touch handler, which handles TFT touches runs first

  Serial.println("Configuration ready");
  Serial.println("Start fluid monitoring...");
}

bool started = false;

void loop() {

  if (!started) {
    Serial.println("Fluid monitoring started");
    started = true;
  }

  scheduler.schedule();  // Schedule each task at the specified interval times

}

//================================================
//==    X K C  Y 2 3 A  V Sensor
//================================================
//
//  Pins to which the XKC_Y23A_V Sensors are connected
//  Maximally 4 sensors LOW
//
#define XKC_Y23A_V_1   1
#define XKC_Y23A_V_2   2
#define XKC_Y23A_V_3   3
#define XKC_Y23A_V_4   4

int XYC_Y23A_V_Pins [] = {
  XKC_Y23A_V_1,   // LOWLOW
  XKC_Y23A_V_2,   // LOW
  XKC_Y23A_V_3,   // HIGH
  XKC_Y23A_V_4    // HIGHHIGH
};

uint16_t XKC_Y23A_V_NrSensors  = 0;
uint16_t XKC_Y23A_V_Configured = 0;
/*
 *  Configurate the XYC_Y23A_V sensors.
 */
void XKC_Y23A_V_Config() {
  // TODO Code the dialog to specify the number of sensors
  XKC_Y23A_V_NrSensors = 4; // For now.
  XKC_Y23A_V_Configured = 1;
}

/*
 *  Initialize the XYZ-Y32-V sensors
 */
void XKZ_Y23_V_Init() {

}

/*---------------------------------------------------
 *    The highest XKC_Y23A_V sensor being HIGH is considered
 *    to indicate the current fluid level and its value is returned.
 *    Being one of LEVEL_LOWLOW, LEVEL_LOW, LEVEL_HIGH or LEVEL_HIGHHIGH.
 *---------------------------------------------------*/
 /*
uint16_t XKC_Y23A_V_Sensor() {
  uint16_t level = theLevels.min;

  switch (XKC_Y23A_V_NrSensors) {
    //
    //  Illegal state wil always return LEVEL_MIN, i.e. empty
    //
    case 0: {
      break;
    }

    //
    //  Supports only the LOWLOW level
    //
    case 1: {
      if (digitalRead(XYC_Y23A_V_Pins[0]) == HIGH)
        level = theLevels.lowlow;

      break;
    }

    //
    //  Supports the LOWLOW and HIGHHIGH levels
    //
    case 2: {
      if (digitalRead(XYC_Y23A_V_Pins[0]) == HIGH)
        level = theLevels.lowlow;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[1]) == HIGH)
        level = theLevels.highhigh;

      break;
    }

    //
    //  Supports the LOWLOW, LOW and HIGH levels
    case 3: {
      if (digitalRead(XYC_Y23A_V_Pins[0]) == HIGH)
        level = theLevels.lowlow;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[1]) == HIGH)
        level = theLevels.low;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[2]) == HIGH)
        level = theLevels.highhigh;
      
      break;
    }

    //
    //  Supports the LOWLOW, LOW, HIGH and HIGHHIGH levels
    //
    default: {
      if (digitalRead(XYC_Y23A_V_Pins[0]) == HIGH)
        level = theLevels.lowlow;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[1]) == HIGH)
        level = theLevels.low;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[2]) == HIGH)
        level = theLevels.high;
      else
        break;

      if (digitalRead(XYC_Y23A_V_Pins[3]) == HIGH)
        level = theLevels.highhigh;
    }

  }

  return level; 
}
*/

