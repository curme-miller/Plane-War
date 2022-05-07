#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <graphics.h> //ͼ�ο�
#include <conio.h>
#include <easyx.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
#define Width 600
#define Height 750
#define BULLET_NUM 15 //����ӵ�����
#define ENEMY_NUM 10  //�о�����
struct Image
{
	IMAGE bk;
	IMAGE player1;
	IMAGE player2;
	IMAGE bullet1;
	IMAGE bullet2;
	IMAGE enemy;
	IMAGE startmenu;
	IMAGE start1;
	IMAGE start2;
	IMAGE explain;
	IMAGE expla;
	IMAGE end;
} image; //����ͼƬ��
enum Type
{
	SMALL,
};
struct plane
{
	float x;
	float y;
	bool flag; //���
	int score;
	int type;
	int hp;										//Ѫ��
} player, bullet[BULLET_NUM], enemy[ENEMY_NUM]; //�ɻ��ģ�X,Y��������Ƿ���Ľṹ��
DWORD t1, t2, t3, t4;
void Enemyhp(int i) //���ɵл���Ѫ��hp�Ĵ�С�Ǽ����ӵ�����������ʧ
{
	if (rand() % 10 == 0)
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
	}
	else
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
	}
}
int judgeBTNumber(ExMessage msg)
{
	if (msg.x > 150 && msg.x < 520 && msg.y > 100 && msg.y < 280)
		return 1;
	else if (msg.x > 150 && msg.x < 520 && msg.y > 500 && msg.y < 680)
		return 2;
	else if (msg.x > 150 && msg.x < 520 && msg.y > 300 && msg.y < 480)
		return 4;
	return 0;
}

void GameInit()
{
	srand(GetTickCount());
	t1 = t2 = t3 = t4 = GetTickCount(); //��ȡ��������ֹ����
	loadimage(&image.bk, _T("../images/bg.png"));
	loadimage(&image.player1, _T("../images/31.png"), 100, 100);
	loadimage(&image.player2, _T("../images/32.png"), 100, 100);
	loadimage(&image.bullet1, _T("../images/11.png"), 20, 10);
	loadimage(&image.bullet2, _T("../images/12.png"), 20, 10);
	loadimage(&image.enemy, _T("../images/2.png"), 50, 50);
	loadimage(&image.startmenu, _T("../images/5start.png"));
	loadimage(&image.start1, _T("../images/6s1.png"));
	loadimage(&image.start2, _T("../images/6s2.png"));
	loadimage(&image.end, _T("../images/7s.png"));
	loadimage(&image.expla, _T("../images/9.png"));
	loadimage(&image.explain, _T("../images/8s.png"));
	//��Ŀ/����/���ֽ�/Unicode->���ַ�(�������Ļ�)�����ĸ�����ͼƬ�ĵ�ַ�����Ի�

	//��ʼ���������
	player.x = Width / 2;
	player.y = Height / 2 + 300;
	player.flag = true;
	player.hp = 99;
	player.score = 0;
	//��ʼ���ӵ�����
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].flag = false;
	}
	//��ʼ���л�
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].flag = false;
		Enemyhp(i);
	}
}
void Gamedraw()
{
	putimage(0, 0, &image.bk);							  //���Ʊ���ͼƬ
	putimage(player.x, player.y, &image.player2, SRCAND); //���Ʒɻ�ͼƬ
	putimage(player.x, player.y, &image.player1, SRCPAINT);
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
		{
			putimage(bullet[i].x, bullet[i].y, &image.bullet2, SRCAND);
			putimage(bullet[i].x, bullet[i].y, &image.bullet1, SRCPAINT);
		}
	} //�����ӵ�
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag)
		{
			putimage(enemy[i].x, enemy[i].y, &image.enemy);
		}
	}
}
void CreateBullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == false)
		{
			bullet[i].flag = true;
			bullet[i].x = player.x + 40;
			bullet[i].y = player.y;
			break;
		}
	}
}
void BulletMove(int speed)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
		{
			bullet[i].y -= speed;
			if (bullet[i].y <= 0)
				bullet[i].flag = false;
		}
	}
} //�ӵ��ƶ�
void CreateEnemy()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag == 0)
		{
			enemy[i].flag = true;
			enemy[i].x = rand() % (Width - 100);
			enemy[i].y = 0;
			Enemyhp(i);
			break;
		}
	}
} //����л�
void EnemyMove(float speed)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag)
		{
			enemy[i].y += speed;
			if (enemy[i].y >= Height)
				enemy[i].flag = false;
		}
	}
}
void GameControl(float speed)
{
	//ǰ�ĸ�if�ֱ�Ϊǰ������
	if (GetAsyncKeyState(VK_UP) && player.y >= 0)
		player.y -= speed;
	if (GetAsyncKeyState(VK_DOWN) && player.y + 100 <= Height)
		player.y += speed;
	if (GetAsyncKeyState(VK_LEFT) && player.x + 50 >= 0)
		player.x -= speed;
	if (GetAsyncKeyState(VK_RIGHT) && player.x + 50 <= Width)
		player.x += speed;

	//�����ӵ�
	if (GetAsyncKeyState(VK_SPACE) && (t2 - t1 > 200))
	{
		CreateBullet();
		t1 = t2;
	}
	t2 = GetTickCount();
	if (t4 - t3 > rand() % 1000 + 1500)
	{
		CreateEnemy();
		t3 = t4;
	}
	t4 = GetTickCount();
	EnemyMove(0.3); //�޸�������Կ��ƿ�������ٶ�
	BulletMove(1);
}
void PlayEnemy(int &flag) //�ж��ӵ��Ƿ���ел�
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].x > player.x - 80 && enemy[i].x < player.x + 100 && enemy[i].y > player.y - 50 && enemy[i].y < player.y)
		{
			// player.x = -1;
			// player.y = -1;
			flag = 3;
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				enemy[i].x = 0;
				enemy[i].y = 0;
				Enemyhp(i);
			}
			break; //����ɻ�����ص�0��0��
		}
		if (!enemy[i].flag)
			continue;
		for (int k = 0; k < BULLET_NUM; k++)
		{
			if (!bullet[k].flag)
				continue;
			if (bullet[k].x > enemy[i].x && bullet[k].x < enemy[i].x + 50 && bullet[k].y > enemy[i].y && bullet[k].y < enemy[i].y + 50)
			{
				bullet[k].flag = false;
				enemy[i].hp--;
				player.score++;
			}
		}
		if (enemy[i].hp <= 0)
		{
			enemy[i].flag = false;
		}
	}
}

void startmenu(int &flag)
{
	putimage(0, 0, &image.startmenu); //���Ʊ���ͼƬ
	putimage(150, 100, &image.start2, SRCAND);
	putimage(150, 100, &image.start1, SRCPAINT);
	putimage(150, 300, &image.explain);
	putimage(150, 500, &image.end);
	ExMessage m;
	m = getmessage(EM_MOUSE | EM_KEY);
	int number;
	FlushBatchDraw();
	number = judgeBTNumber(m);
	if (number == 1 && m.message == WM_LBUTTONDOWN)
		flag = 1;
	else if (number == 2 && m.message == WM_LBUTTONDOWN)
		flag = 2;
	else if (number == 4 && m.message == WM_LBUTTONDOWN)
		flag = 4;
}

void explain(int &flag, int &end)
{
	putimage(0, 0, &image.expla);
	FlushBatchDraw();
	Sleep(3000);
	flag = 0;
	end = 1;
}
void endGame(int &flag, int &end)
{
	end = 1;
	putimage(0, 0, &image.startmenu);
	putimage(150, 100, &image.start2, SRCAND);
	putimage(150, 100, &image.start1, SRCPAINT);
	putimage(150, 300, &image.explain);
	putimage(150, 500, &image.end);
	ExMessage m;
	m = getmessage(EM_MOUSE | EM_KEY);
	int number = judgeBTNumber(m);
	if (number == 1 && m.message == WM_LBUTTONDOWN)
		flag = 1;
	else if (number == 2 && m.message == WM_LBUTTONDOWN)
		flag = 2;
	else
		flag = 0;
}
int main()
{
	int flag = 0;
	int end = 1;
	bool isPlay = true;
	mciSendString(TEXT("open ../musics/timi.mp3 alias timi"), NULL, 0, NULL);
	mciSendString(TEXT("play timi"), NULL, 0, NULL);
	Sleep(1.00 * 1000);
	mciSendString(TEXT("close timi"), NULL, 0, NULL);
	initgraph(Width, Height);
	BeginBatchDraw();
	while (1)
	{
		if (end)
		{
			GameInit();
			end = 0;
			isPlay = true;
		}
		if (flag == 0)
			startmenu(flag);
		if (flag == 1)
		{
			if (isPlay)
			{
				mciSendString(TEXT("open ../musics/Star_Sky.mp3 alias bkSong"), NULL, 0, NULL);
				mciSendString(TEXT("play bkSong repeat"), NULL, 0, NULL);
				isPlay = false;
			}
			Gamedraw();
			FlushBatchDraw();
			GameControl(1); //�����޸ķɻ������ȣ������ܵĿ���
			PlayEnemy(flag);
			putimage(0, 0, &image.end);
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				flag = 1;
		}
		else if (flag == 2)
		{
			EndBatchDraw();
			break;
		}
		else if (flag == 3)
		{
			endGame(flag, end);
			FlushBatchDraw();
			mciSendString(TEXT("close bkSong"), NULL, 0, NULL);
		}
		else if (flag == 4)
		{
			explain(flag, end);
		}
	}
	return 0;
}
