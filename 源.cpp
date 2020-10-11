#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<iomanip>
#include<algorithm>

using namespace std;

char warriorname[6][10] = { "","dragon","ninja","iceman","lion","wolf" },headname[2][10] = { "red","blue" };
int a[] = { 0,3,4,5,2,1,0 }, b[] = { 0,4,1,2,3,5,0 }, li[10] = { 0 }, at[10] = { 0 },
ti = 0, ts = 0, k = 0, woc = 0, m = 0, n = 0, t = 0, r = 0;
bool win = false;

class weapon {
public:
	int kind = 0;
	int atk = 0;
	int ci = 0;
	weapon(int x, int y) :kind(x) {
		switch (x) {
		case 0:
			atk = at[y] * 2 / 10;
			ci = 10000000;
			break;
		case 1:
			atk = 10000;
			ci = 1;
			break;
		case 2:
			atk = r;
			ci = 3;
			break;
		}
	}
};

class warrior {
public:
	weapon* w[3];
	int kind = 0;
	int num = 0;
	int life = 0;
	int atk = 0;
	int loyalty = 1;
	double morale = 1;
	warrior(){
		for (int i = 0;i < 3;i++)
			w[i] = NULL;
	}
};

class dragon :public warrior {
public:
	dragon(int y, int x) : warrior()
	{
		morale = double(y) / double(li[1]);
		num = x;
		w[num % 3] = new weapon(num % 3, 1);
		if (num % 3 == 0 && w[num % 3]->atk == 0) {
			delete w[0];
			w[0] = NULL;
		}
		kind = 1;
		life = li[1];
		atk = at[1];
		printf("%03d:00 %s dragon %d born\n", ti, headname[c], num);
		printf("Its morale is %.2lf\n", morale);
	}
};

class ninja :public warrior {
public:
	ninja(int x) : warrior(){
		num = x;
		w[num % 3] = new weapon(num % 3, 2);
		if (num % 3 == 0 && w[num % 3]->atk == 0) {
			delete w[0];
			w[0] = NULL;
		}
		w[(num + 1) % 3] = new weapon((num + 1) % 3, 2);
		if ((num + 1) % 3 == 0 && w[(num + 1) % 3]->atk == 0) {
			delete w[0];
			w[0] = NULL;
		}
		kind = 2;
		life = li[2];
		atk = at[2];
		printf("%03d:00 %s ninja %d born\n", ti, headname[c], num);
	}
};

class iceman :public warrior {
public:
	iceman(int x) : warrior() {
		num = x;
		w[num % 3] = new weapon(num % 3, 3);
		if (num % 3 == 0 && w[num % 3]->atk == 0) {
			delete w[0];
			w[0] = NULL;
		}
		kind = 3;
		life = li[3];
		atk = at[3];
		printf("%03d:00 %s iceman %d born\n", ti, headname[c], num);
	}
};

class lion :public warrior {
public:
	lion(int y, int x) : warrior() {
		num = x;
		kind = 4;
		loyalty = y;
		life = li[4];
		atk = at[4];
		printf("%03d:00 %s lion %d born\n", ti, headname[c], num);
		printf("Its loyalty is %d\n", loyalty);
	}
};


class wolf :public warrior {
public:
	wolf(int x) : warrior() {
		num = x;
		kind = 5;
		life = li[5];
		atk = at[5];
		printf("%03d:00 %s wolf %d born\n", ti, headname[c], num);
	}
};

class head {
public:
	int count[10] = { 0 };
	int elements = 0;
	int preelements = 0;
	int kind = 0;;
	int i = 1, j = 1;
	warrior *w = NULL, *wo1 = NULL, *wo2 = NULL;
	head(int x, int y) :kind(x), elements(y) {}
	void build() {
		if (kind == 1) {
			if (elements >= li[a[i]]) {
				elements -= li[a[i]];
				switch (i) {
				case 1:w = new iceman(j); break;
				case 2:w = new lion(elements, j); break;
				case 3:w = new wolf(j); break;
				case 4:w = new ninja(j); break;
				case 5:w = new dragon(elements, j); break;
				};
				i++;j++;
				if (i > 5)
					i = 1;
			}
		}
		else {
			if (elements >= li[b[i]]) {
				elements -= li[b[i]];
				switch (i) {
				case 1:w = new lion(elements, j); break;
				case 2:w = new dragon(elements, j); break;
				case 3:w = new ninja(j); break;
				case 4:w = new iceman(j); break;
				case 5:w = new wolf(j); break;
				};
				i++;j++;
				if (i > 5)
					i = 1;
			}
		}
	}
};

class city {
public:
	warrior *redone = NULL, *blueone = NULL, *newred = NULL, *newblue = NULL;
	int flag = 0;
	int elements = 0;
	int redwin = 0;
	int bluewin = 0;
	bool redkill = false;
	bool bluekill = false;
};

head *red = NULL, *blue = NULL;
city *cit = NULL;

void run() {
	if (red->w != NULL && red->w->loyalty <= 0) {
		printf("%03d:05 red lion %d ran away\n", ti, red->w->num);
		delete red->w;
		red->w = NULL;
	}
	for (int i = 1;i <= n;i++) {
		if (cit[i].redone != NULL && cit[i].redone->loyalty <= 0) {
			printf("%03d:05 red lion %d ran away\n", ti, cit[i].redone->num);
			delete cit[i].redone;
			cit[i].redone = NULL;
		}
		if (cit[i].blueone != NULL && cit[i].blueone->loyalty <= 0) {
			printf("%03d:05 blue lion %d ran away\n", ti, cit[i].blueone->num);
			delete cit[i].blueone;
			cit[i].blueone = NULL;
		}
	}
	if (blue->w != NULL && blue->w->loyalty <= 0) {
		printf("%03d:05 blue lion %d ran away\n", ti, blue->w->num);
		delete blue->w;
		blue->w = NULL;
	}
	return;
}

void march() {
	if (cit[1].blueone != NULL) {
		if (red->wo1 == NULL) {
			red->wo1 = cit[1].blueone;
			cit[1].blueone = NULL;
			if (red->wo1->kind == 3 && (n + 1) % 2 == 0) {
				red->wo1->life -= 9;
				if (red->wo1->life <= 0)
					red->wo1->life = 1;
				red->wo1->atk += 20;
			}
			printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
				ti, warriorname[red->wo1->kind], red->wo1->num, red->wo1->life, red->wo1->atk);
		}
		else {
			red->wo2 = cit[1].blueone;
			cit[1].blueone = NULL;
			if (red->wo2->kind == 3 && (n + 1) % 2 == 0) {
				red->wo2->life -= 9;
				if (red->wo2->life <= 0)
					red->wo2->life = 1;
				red->wo2->atk += 20;
			}
			printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
				ti, warriorname[red->wo2->kind], red->wo2->num, red->wo2->life, red->wo2->atk);
			printf("%03d:10 red headquarter was taken\n", ti);
			win = true;
		}
	}
	for (int i = 1;i <= n;i++) {
		if (i == 1) {
			if (red->w != NULL) {
				cit[1].newred = red->w;
				red->w = NULL;
				printf("%03d:10 red %s %d marched to city 1 with %d elements and force %d\n",
					ti, warriorname[cit[1].newred->kind], cit[1].newred->num, cit[1].newred->life, cit[1].newred->atk);
			}
			if (n >= 2) {
				if (cit[2].blueone != NULL) {
					cit[1].newblue = cit[2].blueone;
					cit[2].blueone = NULL;
					if (cit[1].newblue->kind == 3 && n % 2 == 0)
					{
						cit[1].newblue->life -= 9;
						if (cit[1].newblue->life <= 0)
							cit[1].newblue->life = 1;
						cit[1].newblue->atk += 20;
					}
					printf("%03d:10 blue %s %d marched to city 1 with %d elements and force %d\n",
						ti, warriorname[cit[1].newblue->kind], cit[1].newblue->num, cit[1].newblue->life, cit[1].newblue->atk);
				}
			}
			else {
				if (blue->w != NULL) {
					cit[1].newblue = blue->w;
					blue->w = NULL;
					printf("%03d:10 blue %s %d marched to city 1 with %d elements and force %d\n",
						ti, warriorname[cit[1].newblue->kind], cit[1].newblue->num, cit[1].newblue->life, cit[1].newblue->atk);
				}
			}
			continue;
		}
		if (i == n) {
			if (cit[n - 1].redone != NULL) {
				cit[n].newred = cit[n - 1].redone;
				cit[n - 1].redone = NULL;
				if (cit[n].newred->kind == 3 && n % 2 == 0) {
					cit[n].newred->life -= 9;
					if (cit[n].newred->life <= 0)
						cit[n].newred->life = 1;
					cit[n].newred->atk += 20;
				}
				printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
					ti, warriorname[cit[n].newred->kind], cit[n].newred->num, n, cit[n].newred->life, cit[n].newred->atk);
			}
			if (blue->w != NULL) {
				cit[n].newblue = blue->w;
				blue->w = NULL;
				printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
					ti, warriorname[cit[n].newblue->kind], cit[n].newblue->num, n, cit[n].newblue->life, cit[n].newblue->atk);
			}
			continue;
		}
		if (cit[i - 1].redone != NULL) {
			cit[i].newred = cit[i - 1].redone;
			cit[i - 1].redone = NULL;
			if (cit[i].newred->kind == 3 && i % 2 == 0)
			{
				cit[i].newred->life -= 9;
				if (cit[i].newred->life <= 0)
					cit[i].newred->life = 1;
				cit[i].newred->atk += 20;
			}
			printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
				ti, warriorname[cit[i].newred->kind], cit[i].newred->num, i, cit[i].newred->life, cit[i].newred->atk);
		}
		if (cit[i + 1].blueone != NULL) {
			cit[i].newblue = cit[i + 1].blueone;
			cit[i + 1].blueone = NULL;
			if (cit[i].newblue->kind == 3 && (n + 1 - i) % 2 == 0)
			{
				cit[i].newblue->life -= 9;
				if (cit[i].newblue->life <= 0)
					cit[i].newblue->life = 1;
				cit[i].newblue->atk += 20;
			}
			printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
				ti, warriorname[cit[i].newblue->kind], cit[i].newblue->num, i, cit[i].newblue->life, cit[i].newblue->atk);
		}
	}
	if (cit[n].redone != NULL) {
		if (blue->wo1 == NULL) {
			blue->wo1 = cit[n].redone;
			cit[n].redone = NULL;
			if (blue->wo1->kind == 3 && (n + 1) % 2 == 0) {
				blue->wo1->life -= 9;
				if (blue->wo1->life <= 0)
					blue->wo1->life = 1;
				blue->wo1->atk += 20;
			}
			printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
				ti, warriorname[blue->wo1->kind], blue->wo1->num, blue->wo1->life, blue->wo1->atk);
		}
		else {
			blue->wo2 = cit[n].redone;
			cit[n].redone = NULL;
			if (blue->wo2->kind == 3 && (n + 1) % 2 == 0) {
				blue->wo2->life -= 9;
				if (blue->wo2->life <= 0)
					blue->wo2->life = 1;
				blue->wo2->atk += 20;
			}
			printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
				ti, warriorname[blue->wo2->kind], blue->wo2->num, blue->wo2->life, blue->wo2->atk);
			printf("%03d:10 blue headquarter was taken\n", ti);
			win = true;
		}
	}
	for (int i = 1;i <= n;i++) {
		cit[i].redone = cit[i].newred;
		cit[i].newred = NULL;
		cit[i].blueone = cit[i].newblue;
		cit[i].newblue = NULL;
	}
	return;
}

void produce() {
	for (int i = 1;i <= n;i++)
		cit[i].elements += 10;
	return;
}

void take() {
	for (int i = 1;i <= n;i++) {
		if (cit[i].redone != NULL && cit[i].blueone == NULL) {
			red->elements += cit[i].elements;
			printf("%03d:30 red %s %d earned %d elements for his headquarter\n", ti,
				warriorname[cit[i].redone->kind], cit[i].redone->num, cit[i].elements);
			cit[i].elements = 0;
		}
		if (cit[i].redone == NULL && cit[i].blueone != NULL) {
			blue->elements += cit[i].elements;
			printf("%03d:30 blue %s %d earned %d elements for his headquarter\n", ti,
				warriorname[cit[i].blueone->kind], cit[i].blueone->num, cit[i].elements);
			cit[i].elements = 0;
		}
	}
	return;
}

void shoot() {
	if (red->w != NULL && cit[1].blueone != NULL) {
		if (red->w->w[2] != NULL) {
			cit[1].blueone->life -= r;
			red->w->w[2]->ci--;
			if (cit[1].blueone->life > 0)
				printf("%03d:35 red %s %d shot\n", ti, warriorname[red->w->kind], red->w->num);
			else
				printf("%03d:35 red %s %d shot and killed blue %s %d\n", ti, warriorname[red->w->kind],
					red->w->num, warriorname[cit[1].blueone->kind], cit[1].blueone->num);
		}
	}
	for (int i = 1;i <= n;i++) {
		if (i == 1) {
			if (n > 1 && cit[1].redone != NULL && cit[2].blueone != NULL) {
				if (cit[1].redone->w[2] != NULL) {
					cit[2].blueone->life -= r;
					cit[1].redone->w[2]->ci--;
					if (cit[2].blueone->life > 0)
						printf("%03d:35 red %s %d shot\n", ti, warriorname[cit[1].redone->kind], cit[1].redone->num);
					else
						printf("%03d:35 red %s %d shot and killed blue %s %d\n", ti, warriorname[cit[1].redone->kind],
							cit[1].redone->num, warriorname[cit[2].blueone->kind], cit[2].blueone->num);
				}
			}
			continue;
		}
		if (i == n) {
			if (cit[n].blueone != NULL && cit[n - 1].redone != NULL) {
				if (cit[n].blueone->w[2] != NULL) {
					cit[n - 1].redone->life -= r;
					cit[n].blueone->w[2]->ci--;
					if (cit[n - 1].redone->life > 0)
						printf("%03d:35 blue %s %d shot\n", ti, warriorname[cit[n].blueone->kind], cit[n].blueone->num);
					else
						printf("%03d:35 blue %s %d shot and killed red %s %d\n", ti, warriorname[cit[n].blueone->kind],
							cit[n].blueone->num, warriorname[cit[n - 1].redone->kind], cit[n - 1].redone->num);
				}
			}
			continue;
		}
		if (cit[i].redone != NULL && cit[i + 1].blueone != NULL) {
			if (cit[i].redone->w[2] != NULL) {
				cit[i + 1].blueone->life -= r;
				cit[i].redone->w[2]->ci--;
				if (cit[i].redone->w[2]->ci == 0) {
					delete cit[i].redone->w[2];
					cit[i].redone->w[2] = NULL;
				}
				if (cit[i + 1].blueone->life > 0)
					printf("%03d:35 red %s %d shot\n", ti, warriorname[cit[i].redone->kind], cit[i].redone->num);
				else
					printf("%03d:35 red %s %d shot and killed blue %s %d\n", ti, warriorname[cit[i].redone->kind],
						cit[i].redone->num, warriorname[cit[i + 1].blueone->kind], cit[i + 1].blueone->num);
			}
		}
		if (cit[i].blueone != NULL && cit[i - 1].redone != NULL) {
			if (cit[i].blueone->w[2] != NULL) {
				cit[i - 1].redone->life -= r;
				cit[i].blueone->w[2]->ci--;
				if (cit[i].blueone->w[2]->ci == 0) {
					delete cit[i].blueone->w[2];
					cit[i].blueone->w[2] = NULL;
				}
				if (cit[i - 1].redone->life > 0)
					printf("%03d:35 blue %s %d shot\n", ti, warriorname[cit[i].blueone->kind], cit[i].blueone->num);
				else
					printf("%03d:35 blue %s %d shot and killed red %s %d\n", ti, warriorname[cit[i].blueone->kind],
						cit[i].blueone->num, warriorname[cit[i - 1].redone->kind], cit[i - 1].redone->num);
			}
		}
	}
	if (blue->w != NULL && cit[n].redone != NULL) {
		if (blue->w->w[2] != NULL) {
			cit[n].redone->life -= r;
			blue->w->w[2]->ci--;
			if (cit[n].redone->life > 0)
				printf("%03d:35 blue %s %d shot\n", ti, warriorname[blue->w->kind], blue->w->num);
			else
				printf("%03d:35 blue %s %d shot and killed red %s %d\n", ti, warriorname[blue->w->kind],
					blue->w->num, warriorname[cit[n].redone->kind], cit[n].redone->num);
		}
	}
	return;
}

void suicide() {
	for (int i = 1;i <= n;i++) {
		if (cit[i].redone == NULL || cit[i].blueone == NULL)
			continue;
		if (cit[i].redone->life <= 0 || cit[i].blueone->life <= 0)
			continue;
		bool reddie = false, bluedie = false;
		if (cit[i].flag == 1 || (cit[i].flag == 0 && i % 2 == 1)) {
			int bluelife = cit[i].blueone->life - cit[i].redone->atk;
			if (cit[i].redone->w[0] != NULL)
				bluelife -= cit[i].redone->w[0]->atk;
			if (bluelife <= 0)
				bluedie = true;
			if (bluedie == false && cit[i].blueone->kind != 2) {
				int redlife = cit[i].redone->life - cit[i].blueone->atk / 2;
				if (cit[i].blueone->w[0] != NULL)
					redlife -= cit[i].blueone->w[0]->atk;
				if (redlife <= 0)
					reddie = true;
			}
		}
		else {
			int redlife = cit[i].redone->life - cit[i].blueone->atk;
			if (cit[i].blueone->w[0] != NULL)
				redlife -= cit[i].blueone->w[0]->atk;
			if (redlife <= 0)
				reddie = true;
			if (reddie == false && cit[i].redone->kind != 2) {
				int bluelife = cit[i].blueone->life - cit[i].redone->atk / 2;
				if (cit[i].redone->w[0] != NULL)
					bluelife -= cit[i].redone->w[0]->atk;
				if (bluelife <= 0)
					bluedie = true;
			}
		}
		if (reddie&&cit[i].redone->w[1] != NULL) {
			printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n", ti, warriorname[cit[i].redone->kind],
				cit[i].redone->num, warriorname[cit[i].blueone->kind], cit[i].blueone->num);
			delete cit[i].redone;
			cit[i].redone = NULL;
			delete cit[i].blueone;
			cit[i].blueone = NULL;
		}
		if (bluedie&&cit[i].blueone->w[1] != NULL) {
			printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n", ti, warriorname[cit[i].blueone->kind],
				cit[i].blueone->num, warriorname[cit[i].redone->kind], cit[i].redone->num);
			delete cit[i].blueone;
			cit[i].blueone = NULL;
			delete cit[i].redone;
			cit[i].redone = NULL;
		}
	}
	return;
}

void fight() {
	red->preelements = red->elements;
	blue->preelements = blue->elements;
	for (int i = 1;i <= n;i++) {
		cit[i].redkill = cit[i].bluekill = false;
		if (cit[i].redone != NULL && cit[i].blueone == NULL) {
			if (cit[i].redone->life <= 0) {
				delete cit[i].redone;
				cit[i].redone = NULL;
			}
		}
		if (cit[i].blueone != NULL && cit[i].redone == NULL) {
			if (cit[i].blueone->life <= 0) {
				delete cit[i].blueone;
				cit[i].blueone = NULL;
			}
		}
		if (cit[i].redone == NULL || cit[i].blueone == NULL)
			continue;
		if (cit[i].redone->life <= 0 && cit[i].blueone->life <= 0) {
			delete cit[i].redone;
			cit[i].redone = NULL;
			delete cit[i].blueone;
			cit[i].blueone = NULL;
			continue;
		}
		int redlife = cit[i].redone->life, bluelife = cit[i].blueone->life;
		if (cit[i].flag == 1 || (cit[i].flag == 0 && i % 2 == 1)) {
			if (cit[i].redone->life <= 0)
				cit[i].bluekill = true;
			else {
				if (cit[i].blueone->life <= 0)
					cit[i].redkill = true;
				else {
					cit[i].blueone->life -= cit[i].redone->atk;
					if (cit[i].redone->w[0] != NULL) {
						cit[i].blueone->life -= cit[i].redone->w[0]->atk;
						cit[i].redone->w[0]->atk = cit[i].redone->w[0]->atk * 8 / 10;
						if (cit[i].redone->w[0]->atk == 0) {
							delete cit[i].redone->w[0];
							cit[i].redone->w[0] = NULL;
						}
					}
					printf("%03d:40 red %s %d attacked blue %s %d in city %d with %d elements and force %d\n", ti,
						warriorname[cit[i].redone->kind], cit[i].redone->num, warriorname[cit[i].blueone->kind],
						cit[i].blueone->num, i, cit[i].redone->life, cit[i].redone->atk);
					if (cit[i].blueone->life <= 0) {
						cit[i].redkill = true;
						printf("%03d:40 blue %s %d was killed in city %d\n", ti, warriorname[cit[i].blueone->kind],
							cit[i].blueone->num, i);
					}
					else {
						if (cit[i].blueone->kind != 2) {
							cit[i].redone->life -= cit[i].blueone->atk / 2;
							if (cit[i].blueone->w[0] != NULL) {
								cit[i].redone->life -= cit[i].blueone->w[0]->atk;
								cit[i].blueone->w[0]->atk = cit[i].blueone->w[0]->atk * 8 / 10;
								if (cit[i].blueone->w[0]->atk == 0) {
									delete cit[i].blueone->w[0];
									cit[i].blueone->w[0] = NULL;
								}
							}
							printf("%03d:40 blue %s %d fought back against red %s %d in city %d\n", ti,
								warriorname[cit[i].blueone->kind], cit[i].blueone->num, warriorname[cit[i].redone->kind],
								cit[i].redone->num, i);
							if (cit[i].redone->life <= 0) {
								cit[i].bluekill = true;
								printf("%03d:40 red %s %d was killed in city %d\n", ti, warriorname[cit[i].redone->kind],
									cit[i].redone->num, i);
							}
						}
					}
				}
			}
			if (cit[i].redkill) {
				if (cit[i].redone->kind == 1) {
					cit[i].redone->morale += 0.2;
					if (cit[i].redone->morale > 0.8)
						printf("%03d:40 red dragon %d yelled in city %d\n", ti, cit[i].redone->num, i);
				}
				if (cit[i].blueone->kind == 4 && bluelife > 0)
					cit[i].redone->life += bluelife;
				if (cit[i].redone->kind == 5) {
					for (int j = 0;j < 3;j++) {
						if (cit[i].redone->w[j] == NULL && cit[i].blueone->w[j] != NULL) {
							cit[i].redone->w[j] = cit[i].blueone->w[j];
							cit[i].blueone->w[j] = NULL;
						}
					}
				}
				red->elements += cit[i].elements;
				printf("%03d:40 red %s %d earned %d elements for his headquarter\n", ti,
					warriorname[cit[i].redone->kind], cit[i].redone->num, cit[i].elements);
				cit[i].elements = 0;
				cit[i].redwin++;
				cit[i].bluewin = 0;
				if (cit[i].redwin == 2 && cit[i].flag != 1) {
					cit[i].flag = 1;
					printf("%03d:40 red flag raised in city %d\n", ti, i);
				}
				delete cit[i].blueone;
				cit[i].blueone = NULL;
			}
			else {
				if (cit[i].redone->kind == 1)
					cit[i].redone->morale -= 0.2;
				if (cit[i].bluekill) {
					if (cit[i].redone->kind == 4 && redlife > 0)
						cit[i].blueone->life += redlife;
					if (cit[i].blueone->kind == 5) {
						for (int j = 0;j < 3;j++) {
							if (cit[i].blueone->w[j] == NULL && cit[i].redone->w[j] != NULL) {
								cit[i].blueone->w[j] = cit[i].redone->w[j];
								cit[i].redone->w[j] = NULL;
							}
						}
					}
					blue->elements += cit[i].elements;
					printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", ti,
						warriorname[cit[i].blueone->kind], cit[i].blueone->num, cit[i].elements);
					cit[i].elements = 0;
					cit[i].redwin = 0;
					cit[i].bluewin++;
					if (cit[i].bluewin == 2 && cit[i].flag != 2) {
						cit[i].flag = 2;
						printf("%03d:40 blue flag raised in city %d\n", ti, i);
					}
					delete cit[i].redone;
					cit[i].redone = NULL;
				}
				else {
					if (cit[i].redone->kind == 4)
						cit[i].redone->loyalty -= k;
					if (cit[i].blueone->kind == 4)
						cit[i].blueone->loyalty -= k;
					cit[i].redwin = 0;
					cit[i].bluewin = 0;
					if (cit[i].redone->kind == 1) {
						if (cit[i].redone->morale > 0.8)
							printf("%03d:40 red dragon %d yelled in city %d\n", ti, cit[i].redone->num, i);
					}
				}
			}
		}
		else {
			if (cit[i].blueone->life <= 0)
				cit[i].redkill = true;
			else {
				if (cit[i].redone->life <= 0)
					cit[i].bluekill = true;
				else {
					cit[i].redone->life -= cit[i].blueone->atk;
					if (cit[i].blueone->w[0] != NULL) {
						cit[i].redone->life -= cit[i].blueone->w[0]->atk;
						cit[i].blueone->w[0]->atk = cit[i].blueone->w[0]->atk * 8 / 10;
						if (cit[i].blueone->w[0]->atk == 0) {
							delete cit[i].blueone->w[0];
							cit[i].blueone->w[0] = NULL;
						}
					}
					printf("%03d:40 blue %s %d attacked red %s %d in city %d with %d elements and force %d\n", ti,
						warriorname[cit[i].blueone->kind], cit[i].blueone->num, warriorname[cit[i].redone->kind],
						cit[i].redone->num, i, cit[i].blueone->life, cit[i].blueone->atk);
					if (cit[i].redone->life <= 0) {
						cit[i].bluekill = true;
						printf("%03d:40 red %s %d was killed in city %d\n", ti, warriorname[cit[i].redone->kind],
							cit[i].redone->num, i);
					}
					else {
						if (cit[i].redone->kind != 2) {
							cit[i].blueone->life -= cit[i].redone->atk / 2;
							if (cit[i].redone->w[0] != NULL) {
								cit[i].blueone->life -= cit[i].redone->w[0]->atk;
								cit[i].redone->w[0]->atk = cit[i].redone->w[0]->atk * 8 / 10;
								if (cit[i].redone->w[0]->atk == 0) {
									delete cit[i].redone->w[0];
									cit[i].redone->w[0] = NULL;
								}
							}
							printf("%03d:40 red %s %d fought back against blue %s %d in city %d\n", ti,
								warriorname[cit[i].redone->kind], cit[i].redone->num, warriorname[cit[i].blueone->kind],
								cit[i].blueone->num, i);
							if (cit[i].blueone->life <= 0) {
								cit[i].redkill = true;
								printf("%03d:40 blue %s %d was killed in city %d\n", ti, warriorname[cit[i].blueone->kind],
									cit[i].blueone->num, i);
							}
						}
					}
				}
			}
			if (cit[i].bluekill) {
				if (cit[i].blueone->kind == 1) {
					cit[i].blueone->morale += 0.2;
					if (cit[i].blueone->morale > 0.8)
						printf("%03d:40 blue dragon %d yelled in city %d\n", ti, cit[i].blueone->num, i);
				}
				if (cit[i].redone->kind == 4 && redlife > 0)
					cit[i].blueone->life += redlife;
				if (cit[i].blueone->kind == 5) {
					for (int j = 0;j < 3;j++) {
						if (cit[i].blueone->w[j] == NULL && cit[i].redone->w[j] != NULL) {
							cit[i].blueone->w[j] = cit[i].redone->w[j];
							cit[i].redone->w[j] = NULL;
						}
					}
				}
				blue->elements += cit[i].elements;
				printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", ti,
					warriorname[cit[i].blueone->kind], cit[i].blueone->num, cit[i].elements);
				cit[i].elements = 0;
				cit[i].bluewin++;
				cit[i].redwin = 0;
				if (cit[i].bluewin == 2 && cit[i].flag != 2) {
					cit[i].flag = 2;
					printf("%03d:40 blue flag raised in city %d\n", ti, i);
				}
				delete cit[i].redone;
				cit[i].redone = NULL;
			}
			else {
				if (cit[i].blueone->kind == 1)
					cit[i].blueone->morale -= 0.2;
				if (cit[i].redkill) {
					if (cit[i].blueone->kind == 4 && bluelife > 0)
						cit[i].redone->life += bluelife;
					if (cit[i].redone->kind == 5) {
						for (int j = 0;j < 3;j++) {
							if (cit[i].redone->w[j] == NULL && cit[i].blueone->w[j] != NULL) {
								cit[i].redone->w[j] = cit[i].blueone->w[j];
								cit[i].blueone->w[j] = NULL;
							}
						}
					}
					red->elements += cit[i].elements;
					printf("%03d:40 red %s %d earned %d elements for his headquarter\n", ti,
						warriorname[cit[i].redone->kind], cit[i].redone->num, cit[i].elements);
					cit[i].elements = 0;
					cit[i].bluewin = 0;
					cit[i].redwin++;
					if (cit[i].redwin == 2 && cit[i].flag != 1) {
						cit[i].flag = 1;
						printf("%03d:40 red flag raised in city %d\n", ti, i);
					}
					delete cit[i].blueone;
					cit[i].blueone = NULL;
				}
				else {
					if (cit[i].redone->kind == 4)
						cit[i].redone->loyalty -= k;
					if (cit[i].blueone->kind == 4)
						cit[i].blueone->loyalty -= k;
					cit[i].redwin = 0;
					cit[i].bluewin = 0;
					if (cit[i].blueone->kind == 1) {
						if (cit[i].blueone->morale > 0.8)
							printf("%03d:40 blue dragon %d yelled in city %d\n", ti, cit[i].blueone->num, i);
					}
				}
			}
		}
	}
	for (int i = n;i >= 1;i--) {
		if (red->preelements < 8)
			break;
		if (cit[i].redkill) {
			red->preelements -= 8;
			red->elements -= 8;
			cit[i].redone->life += 8;
		}
	}
	for (int i = 1;i <= n;i++) {
		if (blue->preelements < 8)
			break;
		if (cit[i].bluekill) {
			blue->preelements -= 8;
			blue->elements -= 8;
			cit[i].blueone->life += 8;
		}
	}
	return;
}

void report1() {
	printf("%03d:50 %d elements in red headquarter\n", ti, red->elements);
	printf("%03d:50 %d elements in blue headquarter\n", ti, blue->elements);
	return;
}

void report2() {
	for (int i = 1;i <= n;i++) {
		if (cit[i].redone != NULL) {
			printf("%03d:55 red %s %d has ", ti, warriorname[cit[i].redone->kind], cit[i].redone->num);
			bool comma = false;
			if (cit[i].redone->w[2] != NULL) {
				printf("arrow(%d)", cit[i].redone->w[2]->ci);
				comma = true;
			}
			if (cit[i].redone->w[1] != NULL) {
				if (comma)
					printf(",");
				printf("bomb");
				comma = true;
			}
			if (cit[i].redone->w[0] != NULL) {
				if (comma)
					printf(",");
				printf("sword(%d)", cit[i].redone->w[0]->atk);
				comma = true;
			}
			if (!comma)
				printf("no weapon");
			printf("\n");
		}
	}
	if (blue->wo1 != NULL) {
		printf("%03d:55 red %s %d has ", ti, warriorname[blue->wo1->kind], blue->wo1->num);
		bool comma = false;
		if (blue->wo1->w[2] != NULL) {
			printf("arrow(%d)", blue->wo1->w[2]->ci);
			comma = true;
		}
		if (blue->wo1->w[1] != NULL) {
			if (comma)
				printf(",");
			printf("bomb");
			comma = true;
		}
		if (blue->wo1->w[0] != NULL) {
			if (comma)
				printf(",");
			printf("sword(%d)", blue->wo1->w[0]->atk);
			comma = true;
		}
		if (!comma)
			printf("no weapon");
		printf("\n");
	}
	if (red->wo1 != NULL) {
		printf("%03d:55 blue %s %d has ", ti, warriorname[red->wo1->kind], red->wo1->num);
		bool comma = false;
		if (red->wo1->w[2] != NULL) {
			printf("arrow(%d)", red->wo1->w[2]->ci);
			comma = true;
		}
		if (red->wo1->w[1] != NULL) {
			if (comma)
				printf(",");
			printf("bomb");
			comma = true;
		}
		if (red->wo1->w[0] != NULL) {
			if (comma)
				printf(",");
			printf("sword(%d)", red->wo1->w[0]->atk);
			comma = true;
		}
		if (!comma)
			printf("no weapon");
		printf("\n");
	}
	for (int i = 1;i <= n;i++) {
		if (cit[i].blueone != NULL) {
			printf("%03d:55 blue %s %d has ", ti, warriorname[cit[i].blueone->kind], cit[i].blueone->num);
			bool comma = false;
			if (cit[i].blueone->w[2] != NULL) {
				printf("arrow(%d)", cit[i].blueone->w[2]->ci);
				comma = true;
			}
			if (cit[i].blueone->w[1] != NULL) {
				if (comma)
					printf(",");
				printf("bomb");
				comma = true;
			}
			if (cit[i].blueone->w[0] != NULL) {
				if (comma)
					printf(",");
				printf("sword(%d)", cit[i].blueone->w[0]->atk);
				comma = true;
			}
			if (!comma)
				printf("no weapon");
			printf("\n");
		}
	}
	return;
}

int main() {
	cin >> woc;
	for (int i = 1; i <= woc; i++) {
		cin >> m >> n >> r >> k >> t;
		for (int j = 1; j <= 5; j++)cin >> li[j];
		for (int j = 1; j <= 5; j++)cin >> at[j];
		cout << "Case " << i << ":" << endl;
		if (red != NULL)delete red;
		if (blue != NULL)delete blue;
		if (cit != NULL)delete[]cit;
		red = new head(1, m);
		blue = new head(2, m);
		cit = new city[n + 1];
		ti = 0, ts = 0;
		win = false;
		while (1) {
			red->build();
			blue->build();
			ts += 5;
			if (ts > t)
				break;
			run();
			ts += 5;
			if (ts > t)
				break;
			march();
			if (win)
				break;
			ts += 10;
			if (ts > t)
				break;
			produce();
			ts += 10;
			if (ts > t)
				break;
			take();
			ts += 5;
			if (ts > t)
				break;
			shoot();
			ts += 3;
			if (ts > t)
				break;
			suicide();
			ts += 2;
			if (ts > t)
				break;
			fight();
			ts += 10;
			if (ts > t)
				break;
			report1();
			ts += 5;
			if (ts > t)
				break;
			report2();
			ts += 5;
			if (ts > t)
				break;
			ti++;
		}
	}
	return 0;
}