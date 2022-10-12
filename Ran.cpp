#include <winbgim.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#define maxh 500
#define maxc 1000
using namespace std;
class Point{
	public:
	int x, y;
};
int xTA = 30, yTA = 115;int diem[100], n = 1;
Point* khoitao(){	
	Point* ran = new Point[3];
	ran[0].x = 20; ran[0].y = 5;
	ran[1].x = 10; ran[1].y = 5;
	ran[2].x = 0; ran[2].y = 5;
	return ran;
}
void ve(const Point* ran, int& doDai){
	//setcolor(15);
	//circle(c, d, 5);
	cleardevice();	
	//setcolor(9);	
	for(int i = 0; i < doDai; i++){
		circle(ran[i].x, ran[i].y, 5);		
		setfillstyle(1, 14);
		floodfill(ran[i].x, ran[i].y, 1);
		//cout << c << endl;
	}
	int c = 4;
	setfillstyle(1, c);
	setcolor(c);	
	circle(xTA, yTA, 5);
	floodfill(xTA, yTA, c);
	setcolor(1);
	char s[100];
	for(int i = 0; i < n; i++){
		s[i] = diem[n-1-i]+48;
	}
	settextstyle(8, 0, 3);
	outtextxy(290, 460, "Nhan enter de ket thuc, phim mui ten de di chuyen!");
	outtextxy(650, 430, "Tong diem:");
	outtextxy(800, 430, s);
}
void chuyen(Point* ran, int& doDai){
	//c = ran[doDai - 1].x;
	//d = ran[doDai - 1].y;
	for(int i = doDai - 1; i > 0; i--){
		ran[i].x = ran[i-1].x;
		ran[i].y = ran[i-1].y;
	}
}
bool check(const Point* ran, int& doDai){
	for(int i = 1; i < doDai; i++)
		if(ran[0].x==ran[i].x && ran[0].y==ran[i].y)return 1;
	return 0;
}
void doi(Point* ran, int& doDai){
	if(ran[0].y>=maxh){
		chuyen(ran, doDai);
		ran[0].y = 0;
	}
	if(ran[0].y<0){
		chuyen(ran, doDai);
		ran[0].y = maxh;
	}
	if(ran[0].x>=maxc){
		chuyen(ran, doDai);
		ran[0].x = 0;
	}
	if(ran[0].x<0){
		chuyen(ran, doDai);
		ran[0].x = maxc;
	}
}
bool ranan(const Point*ran, int& doDai){
	if((ran[0].x-xTA)*(ran[0].x-xTA) + (ran[0].y-yTA)*(ran[0].y-yTA) <= 64)return 1;
	return 0;
}
void tang(Point* ran, int& doDai){
	Point* ran1 = new Point[doDai];
	for(int i = 0; i < doDai; i++) ran1[i] = ran[i];	
	delete ran; ran = new Point[doDai + 1];
	for(int i = 0; i < doDai; i++) ran[i] = ran1[i];
	delete ran1;
	if(ran[doDai-1].x!=ran[doDai-2].x)ran[doDai].x=ran[doDai-1].x-ran[doDai-2].x;
	if(ran[doDai-1].y!=ran[doDai-2].y)ran[doDai].y=ran[doDai-1].y-ran[doDai-2].y;
	doDai++;
}
bool checkTA(int a, int b, const Point* ran, int& doDai){
	if(a>=maxc-5||a<5||b>=maxh-5||b<5||((a-800)*(a-800)+(b-400)*(b-400)<=100)||a%10!=0||b%5!=0)return 1;
	for(int i = 0; i < doDai; i++){
		if((ran[i].x-a)*(ran[i].x-a)+(ran[i].y-b)*(ran[i].y-b)<100)return 1;
	}
	return 0;
}
int main(){
	bool kt = 1;int doDai = 0, a, b, tt = 1;char k;
	initwindow(maxc, maxh);
	setbkcolor(15); setcolor(1);
	cleardevice();	
	Point* ran = khoitao();doDai = 3;
	do{
		if(!kbhit()){			
			doi(ran, doDai);			
			ve(ran, doDai);		
			//cout << ran[0].x << ", " << ran[0].y << endl;
			//cout << xTA << ", " << yTA << endl;			
			if(ranan(ran, doDai)){
				do{
					xTA	= rand();
					yTA	= rand();
				}while(checkTA(xTA, yTA, ran, doDai));
				tang(ran, doDai);int nho, i = 1;
				diem[0]+=8;if(diem[0]>9){nho = (diem[0])/10; diem[0]=(diem[0])%10;}else nho = 0;
				while(nho!=0){
					diem[i]+=nho; if(diem[i]>9){nho = (diem[i])/10; diem[i]=(diem[i])%10;}else nho = 0;i++;
				}if(i>n)n = i;
			}
			a = ran[0].x-ran[1].x;							
			b = ran[0].y-ran[1].y;					
			chuyen(ran, doDai);
			if(a>10||a==-10) ran[0].x -= 10; 
			if(a<-10||a==10) ran[0].x += 10; 
			if(b>10||b==-10) ran[0].y -= 10;
			if(b<-10||b==10) ran[0].y += 10; 
			if(check(ran, doDai)){kt = 0; tt = 2; break;}									
		}
		if(kbhit()){
			k = getch();
			//if(k == 224){
				//k = getch();
				switch(k){
					case 72:{
						if(ran[0].x!=ran[1].x){
							chuyen(ran, doDai);						
							ran[0].y-=10;
						}	
						break;
					}
					case 80:{
						if(ran[0].x!=ran[1].x){
							chuyen(ran, doDai);
							ran[0].y+=10;
						}
						break;
					}
					case 75:{
						if(ran[0].y!=ran[1].y){
							chuyen(ran, doDai);
							ran[0].x-=10;
						}
						break;
					}
					case 77:{
						if(ran[0].y!=ran[1].y){
							chuyen(ran, doDai);
							ran[0].x+=10;						
						}
						break;
					}
					case 13:{
						tt = 1;
						kt = 0;
						break;
					}
				}
			//}
			if(check(ran, doDai)){kt = 0; tt = 2; break;} 
		}
		Sleep(100);		
	}while(kt);
	if(tt == 1) cout << "Ket thuc chuong trinh!";
	else cout << "Ran chet!";
	cout << "\nTong diem:  ";
	for(int i = n-1; i >= 0; i--) cout << diem[i]; 
	if(ran!=NULL)delete ran;
	return 0;
}
