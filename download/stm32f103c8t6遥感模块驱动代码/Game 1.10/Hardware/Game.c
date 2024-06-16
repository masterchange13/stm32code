#include "stm32f10x.h"                  // Device header
#include "AD.h"
#include "OLED.h"
#include "Delay.h"
#include "Key.h"
#include "HW504.h"
#include "Timer.h"


extern uint8_t SW;
extern uint16_t X, Y;
extern uint8_t o;


extern struct Human
{
	uint8_t Life;
	uint8_t Mode;
	uint32_t Num, j;
	uint8_t x, y;
	uint8_t CD, o, action, point, CD1;
	
}Human1;

extern struct enemy
{
	uint8_t Life;
	uint8_t Mode;
	uint8_t Num, j;
	uint8_t x, y, CD;
}enemy1, enemy2;



void Game_enemy_Init()
{

	enemy1.x = 120;
	enemy1.y = 2;
	enemy1.Mode = 0;
	enemy1.Num = 0;
	enemy1.Life = 1;
	enemy1.CD = 1;
	
	enemy2.x = 10;
	enemy2.y = 2;
	enemy2.Mode = 0;
	enemy2.Num = 0;
	enemy2.Life = 1;
	enemy2.CD = 1;
	
}

void Show_Life()
{
	switch(Human1.Life)
	{
		case 1:
			OLED_Setpos(110, 0);
			OLED_ShowHuman(3);
			break;
		case 2:
			OLED_Setpos(110, 0);
			OLED_ShowHuman(3);
		
			OLED_Setpos(110 - 8, 0);
			OLED_ShowHuman(3);
			break;
		case 3:
			OLED_Setpos(110, 0);
			OLED_ShowHuman(3);
		
			OLED_Setpos(110 + 8, 0);
			OLED_ShowHuman(3);
		
			OLED_Setpos(110 - 8, 0);
			OLED_ShowHuman(3);
			break;
		
		default:
			break;

	}	
}


void Game_Init()
{
	Human1.x = 60;
	Human1.y = 4;
	Human1.point = 0;
	Human1.CD = 0;
	Human1.CD1 = 0;
	Key_Init();
	HW504_Init();
	Timer_Init();
	Game_enemy_Init();
	OLED_Setpos(Human1.x, Human1.y);
	OLED_ShowHuman(0);
	OLED_Setpos(Human1.x, Human1.y - 1);
	Human1.Num = 0;
	Human1.Mode = 1;
	Human1.Life = 3;
	Show_Life();	
	OLED_Showenemy(0);
	OLED_Showenemy(1);
	

}


void Game_GetMode()
{
	if (Human1.Mode == 4)
	{
		OLED_Setpos(Human1.x, Human1.y - 1);
		OLED_Setpos(Human1.x, Human1.y);		
		OLED_ShowHuman(2);
		OLED_Setpos(Human1.x + 8, Human1.y);
		OLED_ShowKill(4);
		Delay_ms(50);
		
		OLED_Clear();
		OLED_Setpos(Human1.x, Human1.y - 1);
		Show_Life();	
		OLED_Setpos(Human1.x, Human1.y);
		OLED_ShowHuman(2);
		OLED_Setpos(Human1.x, Human1.y);			
		OLED_Setpos(Human1.x + 8, Human1.y);
		if (enemy1.x - Human1.x <= 8 && enemy1.y == Human1.y && enemy1.x - Human1.x >= 0 && enemy1.Life != 0)
		{
			enemy1.Life = 0;
			Human1.point ++;
			
		}
		if (enemy2.x - Human1.x <= 8 && enemy2.y == Human1.y && enemy2.x - Human1.x >= 0 && enemy2.Life != 0)
		{
			enemy2.Life = 0;
			Human1.point ++;
			
		}
		
		
		OLED_ShowKill(5);
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		
		Delay_ms(50);
		
		OLED_Clear();
		
		OLED_Setpos(Human1.x, Human1.y - 1);
		Show_Life();	
		OLED_Setpos(Human1.x, Human1.y);
		OLED_ShowHuman(2);
		OLED_Setpos(Human1.x, Human1.y);	
		OLED_Setpos(Human1.x + 8, Human1.y);
		if (enemy1.x - Human1.x <= 8 && enemy1.y == Human1.y && enemy1.x - Human1.x >= 0 && enemy1.Life != 0)
		{
			enemy1.Life = 0;
			Human1.point ++;
			
		}
		if (enemy2.x - Human1.x <= 8 && enemy2.y == Human1.y && enemy2.x - Human1.x >= 0 && enemy2.Life != 0)
		{
			enemy2.Life = 0;
			Human1.point ++;
			
		}
		
		OLED_ShowKill(6);
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		
		Delay_ms(50);
		
		OLED_Clear();
		
		OLED_Setpos(Human1.x, Human1.y - 1);
		Show_Life();	
		OLED_Setpos(Human1.x, Human1.y);
		OLED_ShowHuman(2);
		OLED_Setpos(Human1.x, Human1.y);	
		OLED_Setpos(Human1.x + 8, Human1.y);
		if (enemy1.x - Human1.x <= 8 && enemy1.y == Human1.y && enemy1.x - Human1.x >= 0 && enemy1.Life != 0)
		{
			enemy1.Life = 0;
			Human1.point ++;
			
		}
		if (enemy2.x - Human1.x <= 8 && enemy2.y == Human1.y && enemy2.x - Human1.x >= 0 && enemy2.Life != 0)
		{
			enemy2.Life = 0;
			Human1.point ++;
			
		}
	
		OLED_ShowKill(3);
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		
		Delay_ms(50);
		
		OLED_Clear();
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		
		OLED_Setpos(Human1.x, Human1.y);
		

		Human1.Mode = 0;
		
	
	}
	
	
	else if (Human1.Mode == 3)
	{
		if (Human1.CD == 0)
		{
			uint8_t x = Human1.Life;
			if(Human1.x + 8 <= 120){Human1.x += 8;}
			OLED_Setpos(Human1.x, Human1.y);
			OLED_ShowKill(7);
			if (enemy1.Life > 0)
			{
				OLED_Showenemy(0);
			}
			if (enemy2.Life > 0)
			{
				OLED_Showenemy(1);
			}	
			if (Human1.x - enemy1.x <= 8 && enemy1.y == Human1.y && Human1.x - enemy1.x >= 0 && enemy1.Life != 0)
			{
				enemy1.Life = 0;
				Human1.point ++;
				
			}
			if (Human1.x - enemy2.x <= 8 && enemy2.y == Human1.y && Human1.x - enemy2.x >= 0 && enemy2.Life != 0)
			{
				enemy2.Life = 0;
				Human1.point ++;
				
			}
			
			Delay_ms(40);
			OLED_Clear();
			if (enemy1.Life > 0)
			{
				OLED_Showenemy(0);
			}
			if (enemy2.Life > 0)
			{
				OLED_Showenemy(1);
			}
			
			if(Human1.x + 8 <= 120){Human1.x += 8;}		
			OLED_Setpos(Human1.x - 8, Human1.y);
			OLED_ShowKill(9);
			OLED_Setpos(Human1.x, Human1.y);
			OLED_ShowKill(7);			
			if (Human1.x - enemy1.x <= 16 && enemy1.y == Human1.y && Human1.x - enemy1.x >= 0 && enemy1.Life != 0)
			{
				enemy1.Life = 0;
				Human1.point ++;
				
			}
			if (Human1.x - enemy2.x <= 16 && enemy2.y == Human1.y && Human1.x - enemy2.x >= 0 && enemy2.Life != 0)
			{
				enemy2.Life = 0;
				Human1.point ++;
				
			}
			
			
			Delay_ms(40);
			OLED_Clear();
			if(Human1.x + 8 <= 120){Human1.x += 8;}		
			if (enemy1.Life > 0)
			{
				OLED_Showenemy(0);
			}
			if (enemy2.Life > 0)
			{
				OLED_Showenemy(1);
			}
			OLED_Setpos(Human1.x - 16, Human1.y);
			OLED_ShowKill(9);		
			OLED_Setpos(Human1.x - 8, Human1.y);
			OLED_ShowKill(8);
			OLED_Setpos(Human1.x, Human1.y);
			OLED_ShowKill(7);			
			if (Human1.x - enemy1.x <= 24 && enemy1.y == Human1.y && Human1.x - enemy1.x >= 0 && enemy1.Life != 0)
			{
				enemy1.Life = 0;
				Human1.point ++;
				
			}
			if (Human1.x - enemy2.x <= 24 && enemy2.y == Human1.y && Human1.x - enemy2.x >= 0 && enemy2.Life != 0)
			{
				enemy2.Life = 0;
				Human1.point ++;
				
			}
			
			Delay_ms(40);
			OLED_Clear();
			if (enemy1.Life > 0)
			{
				OLED_Showenemy(0);
			}
			if (enemy2.Life > 0)
			{
				OLED_Showenemy(1);
			}
			
			if(Human1.x + 8 <= 120){Human1.x += 8;}
			OLED_Setpos(Human1.x - 8, Human1.y);
			OLED_ShowKill(9);		
			OLED_Setpos(Human1.x, Human1.y);
			OLED_ShowKill(7);			
			if (Human1.x - enemy1.x <= 24 && enemy1.y == Human1.y && Human1.x - enemy1.x >= 0 && enemy1.Life != 0)
			{
				enemy1.Life = 0;
				Human1.point ++;
				
			}
			if (Human1.x - enemy2.x <= 24 && enemy2.y == Human1.y && Human1.x - enemy2.x >= 0 && enemy2.Life != 0)
			{
				enemy2.Life = 0;
				Human1.point ++;
				
			}
			
			Human1.Life = x;
			Human1.Mode = 0;
		}	
	}
	
	
	
	else if (Human1.Mode == 0)
	{
		OLED_ShowHuman(0);
		OLED_Setpos(Human1.x, Human1.y - 1);
		Show_Life();
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		

	}
	else if (Human1.Mode == 1)
	{
		OLED_ShowHuman(1);
		OLED_Setpos(Human1.x, Human1.y - 1);
		Show_Life();
		if (enemy1.Life > 0)
		{
			OLED_Showenemy(0);
		}
		if (enemy2.Life > 0)
		{
			OLED_Showenemy(1);
		}
		
	}

	
}

void Game_Run()
{
	unsigned char KeyNum;
	KeyNum = Key_GetNum();
	X = HW504_R_X();
	Y = HW504_R_Y();
	SW = HW504_R_SW();
	if(X <= 10)
	{	
		Human1.Num ++;
		if (Human1.Num >= 7)
		{
			Human1.Num = 0;
			Human1.Mode ++;
			if (Human1.Mode == 0){Human1.Mode = 1;}
			else {Human1.Mode = 0;}
		}
		Human1.x += 7;
		if(Human1.x > 120)
		{
			Human1.x = 120;
		}
		
	}
	
	if(X >= 4000)
	{
		Human1.Num ++;
		if (Human1.Num >= 7)
		{
			Human1.Num = 0;
			if (Human1.Mode == 0){Human1.Mode = 1;}
			else {Human1.Mode = 0;}

		}
		Human1.x -= 7;
		if(Human1.x < 10)
		{
			Human1.x = 10;
		}		
	}
	
	if(Y >= 4000)
	{
		Human1.Num ++;
		if (Human1.Num >= 7)
		{
			Human1.Num = 0;
			if (Human1.Mode == 0){Human1.Mode = 1;}
			else {Human1.Mode = 0;}
		}

		Human1.y++;
		if(Human1.y >= 7)
		{
			Human1.y = 7;
		}
		
	}
	
	if(Y <= 10)
	{	
		Human1.Num ++;
		if (Human1.Num >= 7)
		{
			Human1.Num = 0;
			if (Human1.Mode == 0){Human1.Mode = 1;}
			else {Human1.Mode = 0;}
		}
		
		Human1.y--;
		if(Human1.y <= 2)
		{
			Human1.y = 2;
		}
		
	}
	
	if (SW == 0)
	{
		if(Human1.j % 12 == 0)
		{
			Human1.Mode = 3;
			OLED_Clearx();
			OLED_ShowNum(1, 1, Human1.point, 3);
			Show_Life();
		}
	}
	if (KeyNum == 1)
	{
		if (Human1.j % 5 == 0)
		{
			Human1.Mode = 4;
		}
	}
	
	Human1.j ++;
	OLED_Clear();
	OLED_Setpos(Human1.x, Human1.y);
	Game_GetMode();
	if (enemy1.Life > 0)
	{
		OLED_Showenemy(0);
	}
	if (enemy2.Life > 0)
	{
		OLED_Showenemy(1);
	}

	Delay_ms(1);
}

