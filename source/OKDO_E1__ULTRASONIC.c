#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

#include "lcd.h"
#include "back.h"

#define TRIGTIME 443
#define MAXDISTANCE 2000

#define DP_WIDTH 146
#define DP_HEIGHT 52

volatile uint16_t distance =0;
volatile bool ready=false;

char sbuff[30];
uint16_t distBuffer[DP_WIDTH]={0};
uint16_t wr=DP_WIDTH;

void Echo_callback(pint_pin_int_t pintr ,uint32_t pmatch_status)
{
	//distance [mm] = ( high level time [us] * 34 ) / 200
	float c = ((CTIMER_GetTimerCountValue(CTIMER0_PERIPHERAL)-TRIGTIME) * 34) / 200.0;

	distance = sqrt((c * c) + 182.25);

	if(distance > MAXDISTANCE){
		distance = MAXDISTANCE;
	}

	ready=true;
}

/*
 * @brief Application entry point.
 */

int main(void)
{
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	#endif

	LCD_Init(FLEXCOMM8_PERIPHERAL);

	while(1)
	{
		if(ready)
		{
			ready = false;

			LCD_Set_Bitmap((uint16_t*)back_160x128);

			LCD_7seg( 10, 9, distance, 5, 0x0FFF);
			LCD_Puts(138, 33, "mm", 0x0FFF);

			for(int i=0;i<distance*DP_WIDTH/MAXDISTANCE;i++){
				LCD_Draw_Line(7+i, 54, 7+i, 56, 0xFC00);
			}

			wr--;

			distBuffer[wr % DP_WIDTH] = distance*DP_HEIGHT/MAXDISTANCE;

			for(int i=0;i<DP_WIDTH;i++){
				LCD_Draw_Line(7+i, 120, 7+i, 120-distBuffer[(wr+i) % DP_WIDTH], 0x3F00);
			}

			if(wr==0){
				wr=DP_WIDTH;
			}

			LCD_GramRefresh();
		}
	}

	return 0 ;
}
