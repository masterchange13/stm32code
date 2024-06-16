#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HW504.h"
#include "Key.h"
#include "Game.h"

uint8_t SW, KeyNum;
uint16_t X, Y;

struct Human
{
	uint8_t Life;
	uint8_t Mode;
	uint32_t Num, j;
	uint8_t x, y;
	uint8_t CD, o, action, point, CD1;
	
}Human1;

struct enemy
{
	uint8_t Life;
	uint8_t Mode;
	uint8_t Num, j;
	uint8_t x, y, CD;
}enemy1, enemy2;

int main()
{
	OLED_Init();
	Game_Init();
	OLED_Clearx();		
	Show_Life();
	OLED_ShowNum(1, 1, Human1.point, 3);
	while (1)
	{
		OLED_ShowNum(1, 1, Human1.point, 3);
		Game_Run();
		
		
		if (Human1.CD == 0 && Human1.x == enemy1.x && Human1.y == enemy1.y && enemy1.Life > 0)
		{
			Human1.Life --;
			Human1.o = 0;
			Human1.CD = 1;
			OLED_Clearx();			
			Show_Life();
		}
		else if (Human1.CD == 0 && Human1.x == enemy2.x && Human1.y == enemy2.y && enemy2.Life > 0)
		{
			Human1.Life --;
			Human1.o = 0;
			Human1.CD = 1;
			OLED_Clearx();		
			Show_Life();
		}
		
		if (Human1.Life <= 0 && (enemy1.Life > 0 || enemy2.Life > 0))
		{
			break;
		}

	}
	OLED_Clearx();		
	OLED_Clear();	
	OLED_ShowNum(3, 7, Human1.point, 3);	
	OLED_ShowString(2, 4, "Game Over!");	
}
