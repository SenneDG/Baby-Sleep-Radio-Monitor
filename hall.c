/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 
	
#include "stm8s.h"

// local functions
void setupHall(void);

// variables
int statusH;

int read_hall(void)
{
	// setup GPIO pins
	setupHall();
	
	// Reading the Hall sensor
	// If changing magnetic field is detected, then external LED D3 is ON.
	if(GPIO_ReadInputPin(GPIOB, GPIO_PIN_1)){
		GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
		statusH = 1;
	}
	else{
		GPIO_WriteLow(GPIOA, GPIO_PIN_2);
		statusH = 0;
	}
}
	
	void setupHall(){
		
		// Hall Sensor
		GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
		GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
	}

