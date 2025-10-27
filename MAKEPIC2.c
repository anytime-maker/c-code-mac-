#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdarg.h>


#ifdef TEST_ENV
int getch(void) {
    return getchar();
}
#endif

void clrscr(void) {


void clrscr(void) {
    printf("\033[2J\033[1;1H");
    fflush(stdout);
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void textcolor(int color) {
    if(color<=7){
        switch(color){
            case 0: color = 0; break; // Black
            case 1: color = 4; break; // Blue
            case 2: color = 2; break; // Green
            case 3: color = 6; break; // Cyan
            case 4: color = 1; break; // Red
            case 5: color = 5; break; // Magenta
            case 6: color = 3; break; // Yellow (Brown tone)
            case 7: color = 7; break; // White (Gray)
        }
        printf("\033[3%dm", color);
    }

    else if(color>=8){
        switch(color){
            case 8: color = 0; break; // Bright Black (Gray)
            case 9: color = 4; break; // Bright Blue
            case 10: color = 2; break; // Bright Green
            case 11: color = 6; break; // Bright Cyan
            case 12: color = 1; break; // Bright Red
            case 13: color = 5; break; // Bright Magenta
            case 14: color = 3; break; // Bright Yellow
            case 15: color = 7; break; // Bright White
        }
        printf("\033[9%dm", color);
    }

}

int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void putch(char c) {
    putchar(c);
    fflush(stdout);
}

void cprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}

// 화살표 키 대신 일반 키로 변경
#define whereX 3
#define whereY 3
#define LEFT 'a'    // 왼쪽 화살표 대신 'a' 사용
#define RIGHT 'd'   // 오른쪽 화살표 대신 'd' 사용
#define UP 'w'      // 위쪽 화살표 대신 'w' 사용
#define DOWN 'z'    // 아래쪽 화살표 대신 'z' 사용


void mon(void);
void make(void);
void filesave(int nowx,int nowy);
void filewrite1(void);
void filewrite2(void);
void prxy(int x,int y,char *msg);
void cls(void);
void linefill(int nowx,int nowy);

char picture[25][25]=
   {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

int longx=10,longy=10;
int main()
{
    FILE *fp;
    int allxy[101],lastxy;
    char readline,ch,filename,sel;
    cls();
	textcolor(10);
	prxy(10,7,"You can make pictures with \"*,0,o\"");
	textcolor(9);
	prxy(25,3," P I C T U R E   M A K E E R ");
	textcolor(11);
	prxy(45,10,"How many count for x(1~20):");
	scanf("%d",&longx);
    prxy(45,11,"How many count for y(1~20):");
	scanf("%d",&longy);
    /*lastxy=longx*longy;*/
    textcolor(15);
    cls();
    mon();
    gotoxy(whereX-1,whereY);
    make();
    return 0;
}
void make() 
{
    int nowx=whereX-1,nowy=whereY,picx=0,picy=0,x,y;
    char go,yn;
    while(1/*(go=getch())!='!'*/){
    go=getch();
    switch(go){
        case LEFT  : if(nowx==whereX-1){prxy(47,20,"You can't go there(LEFT)        ");gotoxy(nowx,nowy);} // a키
                     else{
                        nowx=nowx-2;
                        gotoxy(nowx,nowy);
                        picx--;
                        }
                     break;
        case RIGHT : if(nowx==(whereX-3+(longx*2))){prxy(47,20,"You can't go there(RIGHT)       ");gotoxy(nowx,nowy);} // d키
                     else{
                        nowx=nowx+2;
                        gotoxy(nowx,nowy);
                        picx++;
                        }
                     break;
        case UP    : if(nowy<=whereY) {prxy(47,20, "You can't go there(UP)       ");gotoxy(nowx, nowy);} // w키
                     else {
                        nowy=nowy-1; 
                        gotoxy(nowx,nowy);
                        picy--;
                     }
                     break;

        case DOWN  : if(nowy>=whereY + longy -1) {prxy(47,20, "You can't go there(DOWN)       ");gotoxy(nowx, nowy);} // z키
                     else {
                        nowy=nowy+1;
                        gotoxy(nowx,nowy);
                        picy++;
                     }
                     break;

        case '1'   : picture [picy][picx] = '*';
                     gotoxy(nowx, nowy);
                     putch('*');
                     gotoxy(nowx,nowy);
                     break;

        case '2'   : picture [picy][picx] = '0';
                     gotoxy(nowx, nowy);
                     putch('0');
                     gotoxy(nowx,nowy);
                     break;

        case '3'   : picture [picy][picx] = 'o';
                     gotoxy(nowx, nowy);
                     putch('o');
                     gotoxy(nowx,nowy);
                     break;

        case '4'   : picture [picy][picx] = ' ';
                     gotoxy(nowx, nowy);
                     putch(' ');
                     gotoxy(nowx,nowy);
                     break;

        case 'q'   : filesave(nowx,nowy);
                     exit(0);
                     break;

        case 'x'   : exit(0);

		case 's'   : filesave(nowx,nowy);
                     gotoxy(nowx,nowy);
                     break;

        case 'r'   : for(y=0; y<longy; y++) {
                        for(x=0; x<longx; x++) {
                            picture [y][x] = ' '; //picture 배열을 공백으로 초기화
                        }
                    }
                     clrscr();
                     mon();
                     nowx = whereX - 1; //화면 x좌표 초기화
                     nowy = whereY; //화면 y좌표 초기화
                     picx = 0; //배열 x 초기화
                     picy = 0; //배열 y 초기화
                     prxy(47,20, "reset       ");
                     gotoxy(nowx,nowy);
                     break;
	
	    case 'f'   : linefill(nowx,nowy);
		             break;
        default    : gotoxy(nowx,nowy);
                     /*putch(go);*/
                     break;
            }
        }

}


//새로 추가한 기능 한 줄 모양 넣기
void linefill(int nowx, int nowy){
	int x_src, x_dest, y_src, y_dest, i, j;
    int line_n=0;
	char fill;
	
    // 채우기 시작 줄
	prxy(47,20, " start Y index to fill: ");
	scanf("%d",&y_src);
    // 채우기 마지막 줄
    prxy(47,21, " final Y index to fill: ");
    scanf("%d", &y_dest);
    // 채우기 시작 칸
    prxy(47,22, " start X index to fill: ");
	scanf("%d",&x_src);
    // 채우기 마지막 칸
    prxy(47,23, " final X index to fill: ");
    scanf("%d", &x_dest);
    prxy(47, 20,"                           ");
    prxy(47, 21,"                           ");
    prxy(47, 22,"                           ");
    prxy(47, 23,"                           ");
	while (getchar() != '\n');	//숫자 입력 후 엔터 남아서 필요
	prxy(47,20, "what do you want to fill?"); //넣을 문자 선택
    prxy(47, 21, "1: '*', 2: '0', 3: 'o': ");
    scanf("%c", &fill);
	
	switch(fill){	
	case '1' : fill = '*';
	break;
	case '2' : fill = '0';
	break;
	case '3' : fill = 'o';
	break;
	default:
        while (getchar() != '\n');  //숫자 입력 후 엔터 남아서 필요
        prxy(47,23, "Not allowed");
        getch();
        prxy(47, 21,"                                                     ");
        prxy(47, 22,"                                                     ");
        prxy(47, 23,"                                                     ");
        gotoxy(nowx, nowy);
        return;
	}

    for(i=y_src-1; i<y_dest; i++){
        for(j=x_src-1; j<x_dest; j++){
            picture[i][j] = fill;
            char temp[2] = { fill, '\0'};
            prxy(j*2+2, i+whereY, temp);
        }
    }


    prxy(47, 20,"                             ");
    prxy(47, 21,"                             ");

    gotoxy (nowx,nowy);

}


void filesave(int nowx,int nowy)
{
    int yn;
	prxy(47,22,"Save with \" \' \" or now (y/n/q): ");
	yn=getch();
	prxy(47,22,"                                        ");
	if(yn=='y'){
	filewrite1();gotoxy(nowx,nowy);}
    else if(yn=='n'){
	filewrite2();gotoxy(nowx,nowy);}
	else {gotoxy(nowx,nowy);}
}

void filewrite1()
{
     FILE *fp;
     char filename[10],buff[20],buff2[100];
     int tempx,tempy;
     prxy(47,22,"File Name:");
     scanf("%s",filename);
     sprintf(buff,"%s",filename);
     if((fp=fopen(buff,"w+t"))==NULL){prxy(47,20,"File open error");exit(0);}
     putc('{',fp);
     putc('\n', fp);
     for(tempy=0;tempy<longy;tempy++)
     {
        putc(' ', fp);
        for(tempx=0;tempx<longx;tempx++)
        {
            if(tempx < longx) // 옆에 또 다른 배열이 있다면 , 출력
            {
                putc(',', fp);
            }

            putc('\'', fp);
            putc(picture[tempy][tempx], fp); // ''포함해서 출력 ('*','*','*',)
            putc('\'', fp);
        }
        if(tempy < longy) // 행 마지막에 , 출력 (행 구분)
        {
            putc(',', fp);
	        fprintf(fp, "\n"); // 마지막 행이 아니라면 줄 바꿈 -> 변경 후
        }
     }
     putc('\n', fp);
     putc('}',fp);putc(';',fp);
     fclose(fp);
	 prxy(47,22,"                         ");
}

void filewrite2()
{
     FILE *fp;
     char filename[10],buff[20],buff2[100];
     int tempx,tempy;
     prxy(47,22,"File Name:");
     scanf("%s",filename);
     sprintf(buff,"%s",filename);
     if((fp=fopen(buff,"w+t"))==NULL){prxy(45,20,"File open error");exit(0);}
     putc('{',fp);
     putc('\n', fp);
     for(tempy=0;tempy<longy;tempy++)
     {
        putc(' ', fp);
        for(tempx=0;tempx<longx;tempx++)
        { 
            if(tempx < longx) // x기준 옆에 또 다른 배열이 있다면 , 출력
            {
                putc(',', fp);
            }

            putc(picture[tempy][tempx], fp); // ' ' 제거한 문자 출력 (*,*,*,*)
        }
        if(tempy < longy) // 행 마지막에 , 출력 (행 구분)
        {
            putc(',', fp);
            fprintf(fp, "\n"); // 마지막 행이 아니라면 줄 바꿈 -> 변경 후
        }
     }
    //  putc('\n', fp);
     putc('}',fp);putc(';',fp);
	 fclose(fp);
	 prxy(47,22,"                         ");
}

void mon() /* 메뉴 화면 출력 */
{
    int x,y,tempy,myx,myy,i;
    char buff[12];
    i=0;
    myx=(2*longx)+whereX; // myx에 x축 길이 * 2 + 3
    myy=longy+whereX; // myy에 y축 길이 + 3
    tempy=myy;


    for(y=0; y<longy; y++){
        for(x=1; x<myx; x++){ // 1 3 5 7 9...
            if(x%2==1){
                prxy(x, y + whereY, ",");
            }
            else{
                if(picture[y][i]==' ')
                    prxy(x, y + whereY, " ");
                else
                {
                    // NULL문자 포함된 문자열로 보내지 않으면 prxy 함수 조건에 맞지않음
                    // 고로, 문자열로 변환하는 과정
                    char temp[2] = { picture[y][i], '\0'};
                    prxy(x, y + whereY, temp);
                }
                // x축 index를 출력하여 채우기함수를 원활히 활용할 수 있도록 함
                // 첫번째 줄에서만 실행되도록함
                if(y==0){
                    // 마지막 index는 출력되지 않아야함
                    // x 길이가 20인 경우 21이 출력되는 현상 방지
                    if(i!=longx*2+1){
                        // 10 이상으로 넘어갈시 x축 간격이 좁아 10을 뺀 숫자로 출력
                        if(i>=19){
                            snprintf(buff, sizeof(buff), "%d", (i+1)/2-10);
                        }
                        else{
                            snprintf(buff, sizeof(buff), "%d", (i+1)/2);
                        }
                        prxy(x, 2, buff);
                    }
                }
            }
            
            i++;
            
        }
        snprintf(buff, sizeof(buff), "%d", y+1);
        prxy(x, y + whereY, buff);
        i=0;
    }


    textcolor(11);
 	prxy(48,5,"--- M E N U ---");
    textcolor(10);
 	prxy(48,6," 1 . put \"*\"");
 	prxy(48,7," 2 . put \"0\"");
 	prxy(48,8," 3 . put \"o\"");
 	prxy(48,9," 4 . put \" \"");
 	prxy(48,10," w . move up");
 	prxy(48,11," z . move down");
 	prxy(48,12," a . move left");
 	prxy(48,13," d . move right");
 	prxy(48,14," s . save");
 	prxy(48,15," q . save & exit");
 	prxy(48,16," x . exit");
	prxy(48,17," f . linefill ");
	prxy(48,18," r . reset");
	
    textcolor(15);
}
void cls(void)
{
    clrscr();
}
void prxy(int x,int y,char *msg)
{
    gotoxy(x,y);
	cprintf("%s",msg);
}

