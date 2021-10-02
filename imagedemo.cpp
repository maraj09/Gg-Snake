#include "iGraphics.h"

int ground_width = 800, ground_height = 600, ground_width_start = 240, ground_height_start = 60, ground_width_end = ground_width + ground_width_start, ground_height_end = ground_height + ground_height_start;
int ground_img, side_logo, sound_on, sound_off, toogle_music = 1, reset_img, toogle_pause = 0, pause_btn, play_btn, back_btn, exit_btn;
int snake_head_bottom, snake_head_top, snake_head_left, snake_head_right, snake_body_x, snake_body_y, snake_tail, fruit;
int snake_width = 20, snake_height = 20;
int x[2000], y[2000], d = 1, length = 50, dir = 1, p_d = 0;
int snake = 12, game_over = 0;
int rx = 320, ry = 320;
char t_score[50], score[5], highScore[5];

int obs_1_x[100], obs_1_y[100], obs_rendered = 0;

int playbutton_hover, learnbutton_hover, scorebutton_hover, creditbutton_hover, exitbutton_hover;
int playbutton, learnbutton, scorebutton, creditbutton, exitbutton;
char homemenu[25] = "images\\gg poster.bmp";
char Exit[30] = "images\\exit screen01.bmp";
int gState = -1, gLevel = 3;
int music_fix[] = {0, 0, 0, 0, 0};
int button_hover[] = {0, 0, 0, 0, 0};

int check_hit_times = (gLevel > 2) ? 40 : 36;

char name[100] = "Rashid\n";
int score_number = 0;
int file_output_length = 1;
char players_name[20];
int *score_point;
int high_score;
// int score_point[9999];
FILE *fW;
FILE *fR;
FILE *fN;

void iDraw()
{
	iClear();

	if (gState == -1)
	{
		iShowBMP(0, 0, homemenu);
		if (button_hover[0] == 0)
			iShowImage(50, 400, 300, 300, playbutton);
		else
		{
			iShowImage(50, 400, 300, 300, playbutton_hover);
		}
		if (button_hover[1] == 0)
			iShowImage(50, 300, 300, 300, learnbutton);
		else
		{
			iShowImage(50, 300, 300, 300, learnbutton_hover);
		}
		if (button_hover[2] == 0)
			iShowImage(50, 200, 300, 300, scorebutton);
		else
		{
			iShowImage(50, 200, 300, 300, scorebutton_hover);
		}
		if (button_hover[3] == 0)
			iShowImage(25, 100, 150, 100, creditbutton);
		else
		{
			iShowImage(25, 100, 150, 100, creditbutton_hover);
		}
		if (button_hover[4] == 0)
			iShowImage(250, 100, 150, 100, exitbutton);
		else
		{
			iShowImage(250, 100, 150, 100, exitbutton_hover);
		}
	}
	else if (gState == 0)
	{

		if (toogle_music == 1 && toogle_pause == 0)
		{

			mciSendString(TEXT("resume  mp3"), NULL, 0, NULL);
		}
		else
		{
			mciSendString(TEXT("pause  mp3"), NULL, 0, NULL);
		}
		if (game_over == 1)
		{
			mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
		}
		
		iSetColor(30, 30, 30);
		iFilledRectangle(0, 0, 1280, 720);
		if (gLevel == 1)
		{
			iShowImage(ground_width_start, ground_height_start, ground_width, ground_height, ground_img);
		}
		else if (gLevel > 1)
		{
			iSetColor(255, 0, 0);
			iShowImage(ground_width_start, ground_height_start, ground_width, ground_height, ground_img);

			for (int i = 1; i <= check_hit_times; i++)
			{
				if (i <= 5)
				{
					obs_1_x[i] = obs_1_x[i - 1] + 30;
					obs_1_y[i] = obs_1_y[0];
				}
				else if (i >= 6 && i <= 9)
				{
					obs_1_x[i] = obs_1_x[0] + 30;
					obs_1_y[i] = obs_1_y[i - 1] - 30;
				}
				else if (i >= 10 && i <= 14)
				{
					if (i == 10)
					{
						obs_1_x[i] = 700 + 30;
					}
					else
					{
						obs_1_x[i] = obs_1_x[i - 1] + 30;
					}
					obs_1_y[i] = obs_1_y[0];
				}
				else if (i >= 15 && i <= 18)
				{
					obs_1_x[i] = obs_1_x[i - 1];
					obs_1_y[i] = obs_1_y[i - 1] - 30;
				}
				else if (i >= 19 && i <= 23)
				{

					if (i == 19)
					{
						obs_1_x[i] = 370 + 30;
					}
					else
					{
						obs_1_x[i] = obs_1_x[i - 1] + 30;
					}
					obs_1_y[i] = 130;
				}
				else if (i >= 24 && i <= 27)
				{
					obs_1_x[i] = 400;
					obs_1_y[i] = obs_1_y[i - 1] + 30;
				}
				else if (i >= 28 && i <= 32)
				{
					if (i == 28)
					{
						obs_1_x[i] = 700 + 30;
					}
					else
					{
						obs_1_x[i] = obs_1_x[i - 1] + 30;
					}

					obs_1_y[i] = 130;
				}
				else if (i >= 33 && i <= 36)
				{
					obs_1_x[i] = obs_1_x[i - 1];
					obs_1_y[i] = obs_1_y[i - 1] + 30;
				}
				else if (i >= 37 && i <= 40)
				{
					if (i <= 38)
					{
						if (i == 37)
						{
							obs_1_x[i] = 610;
						}
						else
						{
							obs_1_x[i] = obs_1_x[i - 1] + 30;
						}
						obs_1_y[i] = 350;
					}
					else
					{
						if (i == 39)
						{
							obs_1_x[i] = 610;
						}
						else
						{
							obs_1_x[i] = obs_1_x[i - 1] + 30;
						}
						obs_1_y[i] = 320;
					}
				}

				iFilledRectangle(obs_1_x[i], obs_1_y[i], 28, 28);
			}

			// iFilledRectangle(500, 500, 30, 30);
		}

		iSetColor(255, 255, 255);
		iRectangle(ground_width_start, ground_height_start, ground_width, ground_height);
		iSetColor(255, 255, 255);
		iText(10, 10, "Press p for pause, r for resume, END for exit.");
		iSetColor(255, 0, 0);
		// Game UI
		iShowImage(10, 450, 200, 200, side_logo);
		iSetColor(255, 255, 255);
		iText(75, 420, "Music", GLUT_BITMAP_9_BY_15);
		if (toogle_music == 1)
		{
			iShowImage(75, 350, 50, 50, sound_on);
		}
		else
		{
			iShowImage(75, 350, 50, 50, sound_off);
		}
		iText(75, 300, "Pause/Play", GLUT_BITMAP_9_BY_15);
		if (toogle_pause == 0)
		{
			iShowImage(75, 230, 50, 50, pause_btn);
		}
		else
		{
			iShowImage(75, 230, 50, 50, play_btn);
		}
		iText(25, 175, "Return To Menu or End", GLUT_BITMAP_9_BY_15);
		iShowImage(35, 100, 40, 40, back_btn);
		iShowImage(125, 100, 50, 50, exit_btn);
		//	Score Board
		iSetColor(102, 0, 255);
		iText(1100, 550, "ScoreBoard", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 102, 0);
		iText(1125, 510, "LEVEL 1", GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 255, 0);
		iText(1075, 450, "Your Current Score", GLUT_BITMAP_9_BY_15);
		sprintf(score, "%d", score_number);
		iText(1150, 425, score, GLUT_BITMAP_9_BY_15);
		iSetColor(0, 255, 0);
		iText(1100, 350, "Highest Score", GLUT_BITMAP_9_BY_15);
		if (score_number > high_score)
		{
			sprintf(highScore, "%d", score_number);
		}
		else
		{
			sprintf(highScore, "%d", high_score);
		}

		iText(1150, 325, highScore, GLUT_BITMAP_9_BY_15);

		//////////////////////////////////////////////////////////////
		// FOR SNAKE MOVEMENT-Start
		//////////////////////////////////////////////////////////////
		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
		{
			d = 1;
		}
		else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
		{
			d = 2;
		}
		else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
		{
			d = 3;
		}
		else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
		{
			d = 4;
		}
		else
		{
			d = 0;
		}
		for (int i = 0; i < length; i++)
		{
			if (i > 0)
			{

				if (y[i - 1] != y[i])
				{
					if (y[i - 1] > y[i])
					{
						iShowImage(x[i], y[i] - 5, snake_height, snake_width + 5, snake_body_y);
					}
					else
					{
						iShowImage(x[i], y[i], snake_height, snake_width + 5, snake_body_y);
					}
				}
				else if (x[i - 1] != x[i])
				{
					if (x[i - 1] > x[i])
					{
						iShowImage(x[i] - 5, y[i], snake_width + 5, snake_height, snake_body_x);
					}
					else
					{
						iShowImage(x[i], y[i], snake_width + 5, snake_height, snake_body_x);
					}
				}
			}
			else if (i == 0)
			{
				if (dir == 1)
				{
					iShowImage(x[i], y[i] - 5, snake_width, snake_height + 10, snake_head_right);
				}
				else if (dir == 2)
				{
					iShowImage(x[i], y[i] - 5, snake_width, snake_height + 10, snake_head_left);
				}
				else if (dir == 3)
				{
					iShowImage(x[i] - 5, y[i], snake_width + 10, snake_height, snake_head_bottom);
				}
				else if (dir == 4)
				{
					iShowImage(x[i] - 5, y[i], snake_width + 10, snake_height, snake_head_top);
				}
			}
		}

		if (game_over == 0 && toogle_pause == 0)
		{

			for (int i = 999; i > 0; i--)
			{
				x[i] = x[i - 1];
				y[i] = y[i - 1];
			}
		}

		//////////////////////////////////////////////////////////////
		// FOR SNAKE MOVEMENT-End
		/////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		// FOR Fruit-Start
		//////////////////////////////////////////////////////////////
		if (x[0] > rx - 20 && x[0] < rx + 20 && y[0] > ry - 20 && y[0] < ry + 20)
		{

			length += 5;
			score_number = score_number + 2;
			PlaySound(TEXT("music//food.wav"), NULL, SND_ASYNC);
			rx = (rand() % ((ground_width_end - 30) - ground_width_start)) + ground_width_start;
			ry = (rand() % ((ground_height_end - 30) - ground_height_start)) + ground_height_start;
			for (int i = 1; i <= check_hit_times; i++)
			{
				while (rx >= obs_1_x[i] - 30 && rx <= obs_1_x[i] + 50 && ry >= obs_1_y[i] - 30 && ry <= obs_1_y[i] + 50)
				{
					rx = (rand() % (ground_width_end - ground_width_start)) + ground_width_start;
					ry = (rand() % (ground_height_end - ground_height_start)) + ground_height_start;
				}
			}
		}
		iShowImage(rx, ry, 30, 30, fruit);
		//////////////////////////////////////////////////////////////
		// FOR Fruit-End
		//////////////////////////////////////////////////////////////
		sprintf(t_score, "Your Score is: %d", score_number);
		//////////////////////////////////////////////////////////////
		// Game Over-Start
		//////////////////////////////////////////////////////////////
		if (game_over == 1)
		{
			iSetColor(255, 0, 0);
			iFilledRectangle(385, 300, 500, 300);
			iSetColor(255, 255, 255);
			iText(575, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(560, 470, "OPPS! You Eat YourSelf.", GLUT_BITMAP_9_BY_15);
			iText(575, 425, t_score, GLUT_BITMAP_HELVETICA_18);
			iShowImage(615, 325, 60, 60, reset_img);
		}
		if (toogle_pause == 1)
		{
			iSetColor(255, 255, 255);
			iText(575, 500, "GAME PAUSED!", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}else if (gState == 1)
	{
		iShowBMP(0, 0, Exit);
	}
	
	// File Handeling
	// if (game_over == 1)
	// {
	// 	fputs(name, fW);
	// 	fprintf(fW, "%d\n", score_number);
	// 	fclose(fW);
	// }
}

void game_over_func()
{
	game_over = 1;
	iPauseTimer(0);
	PlaySound(TEXT("music//gameover.wav"), NULL, SND_SYNC);
	fputs(name, fW);
	fprintf(fW, "%d\n", score_number);
	fclose(fW);
}
void get_high_score()
{
	char chk_file_line;
	for (chk_file_line = getc(fN); chk_file_line != EOF; chk_file_line = getc(fN))
		if (chk_file_line == '\n')
			file_output_length = file_output_length + 1;

	score_point = (int *)malloc(file_output_length * sizeof(int));

	for (int i = 0; i < file_output_length; i++)
	{
		fscanf(fR, "%s%d", &players_name, &score_point[i]);
	}
	high_score = score_point[0];
	for (int i = 1; i < file_output_length / 2; i++)
	{
		if (high_score < score_point[i])
		{
			high_score = score_point[i];
		}
	}
}
void snake_movement()
{
	if (game_over == 0 && gState == 0)
	{

		switch (d)
		{
		case 0:
			if (dir == 1)
			{
				if (x[0] + snake_width >= ground_width_end && gLevel < 3)
				{
					x[0] = ground_width_start;
				}
				else if (x[0] + snake_width >= ground_width_end && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					x[0] = x[0] + snake;
					p_d = 1;
				}
			}
			else if (dir == 2)
			{
				if (x[0] <= ground_width_start && gLevel < 3)
				{
					x[0] = ground_width_end - snake_width;
				}
				else if (x[0] <= ground_width_start && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					x[0] = x[0] - snake;
					p_d = 2;
				}
			}
			else if (dir == 3)
			{
				if (y[0] <= ground_height_start + 10 && gLevel < 3)
				{
					y[0] = ground_height_end - snake_height;
				}
				else if (y[0] <= ground_height_start + 10 && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					y[0] = y[0] - snake;
					p_d = 3;
				}
			}
			else if (dir == 4)
			{
				if (y[0] + snake_height + 10 >= ground_height_end && gLevel < 3)
				{
					y[0] = ground_height_start;
				}
				else if (y[0] + snake_height + 10 >= ground_height_end && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					y[0] = y[0] + snake;
					p_d = 4;
				}
			}
			else
			{
				d = 0;
			}
			break;
		case 1:
			if (p_d != 2)
			{
				if (x[0] + snake_width + 10 >= ground_width_end && gLevel < 3)
				{
					x[0] = ground_width_start;
				}
				else if (x[0] + snake_width >= ground_width_end && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					dir = 1;
					x[0] = x[0] + snake;
				}
			}
			else
			{

				dir = 2;
				x[0] = x[0] - snake;
			}
			break;
		case 2:
			if (p_d != 1)
			{
				if (x[0] <= ground_width_start && gLevel < 3)
				{
					x[0] = ground_width_end - snake_width;
				}
				else if (x[0] <= ground_width_start && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					x[0] = x[0] - snake;
					dir = 2;
				}
			}
			else
			{
				dir = 1;
				x[0] = x[0] + snake;
			}
			break;
		case 3:
			if (p_d != 4)
			{
				if (y[0] <= ground_height_start + 10 && gLevel < 3)
				{
					y[0] = ground_height_end - snake_height;
				}
				else if (y[0] <= ground_height_start + 10 && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					dir = 3;
					y[0] = y[0] - snake;
				}
			}
			else
			{
				dir = 4;
				y[0] = y[0] + snake;
			}

			break;
		case 4:
			if (p_d != 3)
			{
				if (y[0] + snake_height + 10 >= ground_height_end && gLevel < 3)
				{
					y[0] = ground_height_start;
				}
				else if (y[0] + snake_height + 10 >= ground_height_end && gLevel == 3)
				{
					game_over_func();
				}
				else
				{
					dir = 4;
					y[0] = y[0] + snake;
				}
			}
			else
			{
				dir = 3;
				y[0] = y[0] - snake;
			}

			break;
		}
	}
	if (game_over == 0)
	{
		for (int i = 2; i < length; i++)
		{
			if (x[0] == x[i] && y[0] == y[i])
			{
				game_over_func();
				break;
			}
		}
		if (gLevel > 1)
		{
			for (int i = 1; i <= check_hit_times; i++)
			{
				if (x[0] + snake_width >= obs_1_x[i] && x[0] <= obs_1_x[i] + 30 && y[0] + snake_width >= obs_1_y[i] && y[0] <= obs_1_y[i] + 30)
				{
					game_over_func();
					break;
				}
			}
		}
	}
}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iPassiveMouse() is called when the user moves the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iPassiveMouse(int mx, int my)
{
	if (gState == -1)
	{
		// printf("%d%d\n", mx, my);

		if (mx >= 125 && mx <= 300 && my >= 525 && my <= 575)
		{
			if (music_fix[0] == 0)
			{
				PlaySound(TEXT("music\\sd.wav"), NULL, SND_ASYNC);
				music_fix[0] = 1;
				button_hover[0] = 1;
			}
		}
		else
		{
			music_fix[0] = 0;
			button_hover[0] = 0;
		}
		if (mx >= 125 && mx <= 300 && my >= 425 && my <= 475)
		{

			if (music_fix[1] == 0)
			{
				PlaySound(TEXT("music\\sd.wav"), NULL, SND_ASYNC);
				music_fix[1] = 1;
				button_hover[1] = 1;
			}
		}
		else
		{
			music_fix[1] = 0;
			button_hover[1] = 0;
		}
		if (mx >= 125 && mx <= 300 && my >= 325 && my <= 375)
		{
			//printf("%d%d\n",mx,my);
			if (music_fix[2] == 0)
			{
				PlaySound(TEXT("music\\sd.wav"), NULL, SND_ASYNC);
				music_fix[2] = 1;
				button_hover[2] = 1;
			}
		}
		else
		{
			music_fix[2] = 0;
			button_hover[2] = 0;
		}
		if (mx >= 40 && mx <= 160 && my >= 130 && my <= 175)
		{
			//printf("%d%d\n",mx,my);
			if (music_fix[3] == 0)
			{
				PlaySound(TEXT("music\\sd.wav"), NULL, SND_ASYNC);
				music_fix[3] = 1;
				button_hover[3] = 1;
			}
		}
		else
		{
			music_fix[3] = 0;
			button_hover[3] = 0;
		}
		if (mx >= 250 && mx <= 385 && my >= 130 && my <= 175)
		{
			//printf("%d%d\n",mx,my);
			if (music_fix[4] == 0)
			{
				PlaySound(TEXT("music\\sd.wav"), NULL, SND_ASYNC);
				music_fix[4] = 1;
				button_hover[4] = 1;
			}
		}
		else
		{
			music_fix[4] = 0;
			button_hover[4] = 0;
		}
	}
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// printf("%d%d%d\n", mx, my, toogle_music);
		if (gState == 0)
		{
			/* code */

			if (mx >= 75 && mx <= 125 && my >= 350 && my <= 400)
			{
				if (toogle_music == 0)
				{
					toogle_music = 1;
				}
				else
				{
					toogle_music = 0;
				}
			}
			if (mx >= 75 && mx <= 125 && my >= 230 && my <= 280)
			{
				if (toogle_pause == 0)
				{
					PlaySound(TEXT("music//gameover.wav"), NULL, SND_ASYNC);
					toogle_pause = 1;
					iPauseTimer(0);
				}
				else
				{
					toogle_pause = 0;
					iResumeTimer(0);
				}
			}
			if (mx >= 125 && mx <= 175 && my >= 100 && my <= 150)
			{
				exit(0);
			}
			if (mx >= 35 && mx <= 75 && my >= 100 && my <= 140)
			{
				gState = -1;
				toogle_pause = 1;
				iPauseTimer(0);
			}
			if (mx >= 615 && mx <= 675 && my >= 325 && my <= 385)
			{
				if (game_over == 1)
				{
					game_over = 0;
					toogle_pause = 0;
					iResumeTimer(0);
					length = 10;
					x[0] = 300;
					y[0] = 300;
					score_number = 0;
					d = 1;
					dir = 1;
					p_d = 1;
					fW = fopen("GGSNAKE_SCORES.txt", "a");
					get_high_score();
				}
			}
		}
		else if (gState == -1)
		{
			if (mx >= 125 && mx <= 300 && my >= 525 && my <= 575)
			{
				gState++;
			}
			if (mx >= 250 && mx <= 385 && my >= 130 && my <= 175)
			{
				gState = 1;
				
			}
			if(mx >= 40 && mx <= 160 && my >= 130 && my <= 175)
			{
				gState =2;
			}
		}
		else if (gState == 1)
		{
			if (mx >= 708 && mx <= 830 && my >= 250 && my <= 290)
			{
				exit(0);
			}
			else if (mx >= 470 && mx <= 590 && my >= 250 && my <= 290)
			{
				gState = -1;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

	if (key == 'p')
	{
		//do something with 'q'
		PlaySound(TEXT("music//gameover.wav"), NULL, SND_ASYNC);
		iPauseTimer(0);
		toogle_pause = 1;
	}
	if (key == 'r')
	{
		if (game_over != 1)
		{
			iResumeTimer(0);
		}
		toogle_pause = 0;
	}
	if (key == 'w' || key == 's' || key == 'a' || key == 'd' && game_over == 0)
	{
		PlaySound(TEXT("music//move.wav"), NULL, SND_ASYNC);
	}

	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_UP || key == GLUT_KEY_RIGHT || key == GLUT_KEY_DOWN && game_over == 0)
	{
		PlaySound(TEXT("music//move.wav"), NULL, SND_ASYNC);
	}

	//place your codes for other keys here
}

// void playSound(){
// 	PlaySound(TEXT("music//music.wav"), NULL, SND_ASYNC|SND_NOSTOP);
// }
int main()
{

	//place your own initialization codes here.
	iSetTimer(50, snake_movement);

	iSetColor(255, 255, 255);
	iInitialize(1280, 720, "Gg Snake");
	mciSendString(TEXT("open \"music//music_2.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	if (gState == 0)
	{
		mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
	}
	else
	{
		mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
	}

	// loading images.
	/* iLoadImage() will return an interger type id
	   for each image you load.
	*/
	// IN GAME
	snake_head_bottom = iLoadImage("images\\head_bot.png");
	snake_head_top = iLoadImage("images\\head_top.png");
	snake_head_left = iLoadImage("images\\head_left.png");
	snake_head_right = iLoadImage("images\\head_right.png");
	snake_body_x = iLoadImage("images\\body_x.png");
	snake_body_y = iLoadImage("images\\body_y.png");
	snake_tail = iLoadImage("images\\tail.png");
	fruit = iLoadImage("images\\apple1.png");
	ground_img = iLoadImage("images\\board.png");
	side_logo = iLoadImage("images\\logo.png");
	sound_on = iLoadImage("images\\volume.png");
	sound_off = iLoadImage("images\\no-sound.png");
	reset_img = iLoadImage("images\\reset.png");
	pause_btn = iLoadImage("images\\pause.png");
	play_btn = iLoadImage("images\\play.png");
	back_btn = iLoadImage("images\\previous.png");
	exit_btn = iLoadImage("images\\exit.png");
	// In Menu
	playbutton_hover = iLoadImage("images\\Goldenplay.png");
	scorebutton_hover = iLoadImage("images\\scores_g.png");
	learnbutton_hover = iLoadImage("images\\learn_g.png");
	creditbutton_hover = iLoadImage("images\\CREDIT_W.png");
	exitbutton_hover = iLoadImage("images\\EXIT_W.png");
	playbutton = iLoadImage("images\\play2.png");
	scorebutton = iLoadImage("images\\score2.png");
	learnbutton = iLoadImage("images\\learn2.png");
	creditbutton = iLoadImage("images\\CREDIT_G.png");
	exitbutton = iLoadImage("images\\EXIT_R.png");

	for (int i = 0; i < 2000; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}

	for (int i = 0; i < 100; i++)
	{
		obs_1_x[i] = 0;
		obs_1_y[i] = 0;
	}

	x[0] = 300;
	y[0] = 300;

	obs_1_x[0] = 370;
	obs_1_y[0] = 550;

	fW = fopen("GGSNAKE_SCORES.txt", "a");
	fR = fopen("GGSNAKE_SCORES.txt", "r");
	fN = fopen("GGSNAKE_SCORES.txt", "r");
	if (fW == NULL || fR == NULL)
	{
		fW = fopen("GGSNAKE_SCORES.txt", "w");
	}
	
	get_high_score();
	iStart(); // it will start drawing

	return 0;
}

