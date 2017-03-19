#include <FreeRTOS_ARM.h>

#define GPIO_PIN 51

#define TIMER_PERIOD 1 //milliseconds
#define TIMER_PERIOD_IN_TICKS pdMS_TO_TICKS(TIMER_PERIOD)

int GPIO_STATE = 0;
void vClockCallback(TimerHandle_t pxTimer){
  GPIO_STATE = !GPIO_STATE;
  digitalWrite(GPIO_PIN, GPIO_STATE);
  }

void setup() {
  // initialize digital pin 51 as an output.
  pinMode(GPIO_PIN, OUTPUT);

  TimerHandle_t xClockTimer = xTimerCreate("Clock", TIMER_PERIOD_IN_TICKS, pdTRUE, 0, vClockCallback);
  xTimerStart(xClockTimer, portMAX_DELAY);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t clockTicks = 0;
  int32_t phaseOffset = 0;
  
  void vClockCallback(TimeHandle_t pxTimer) {
    uint32_t tick = ++clockTicks + phaseOffset;
    //clockTicks++;

    // every 10 ticks, toggle GPIO high
    if(tick % 10 == 0) {
      digitalWrite(GPIO_PIN, HIGH);
    }

    // every 11th ticks, toggle GPIO low
    if(tick % 10 == 1) {
      digitalWrite(GPIO_PIN, LOW);
    }
    
//    // every 10 ticks, toggle GPIO high
//    if(clockTicks % 10 == 0) {
//      digitalWrite(GPIO_PIN, HIGH);
//    }
//
//    // every 11th ticks, toggle GPIO low
//    if(clockTicks % 10 == 1) {
//      digitalWrite(GPIO_PIN, LOW);
//    }
 
  }

  void vSerialRead(void *arg) {
    while(1){
     if(SerialUSB.available()){
      switch(SerialUSB.read()){
        case 'a': //adjust phase offset +1
          phaseOffset++;
          break;
         case 'b' : //adjust phase offset -1
          phaseOffset--;
          break;
      }
     }
    }
   }
}
