#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cmath"
#include<iostream>
#include<algorithm>
using namespace cv;
using namespace std;
Mat img(300, 300, CV_8UC3, Scalar(60,60,60));
Mat endImg(300, 300, CV_8UC3, Scalar(60,60,60));
Mat space ;
int Map[3][3]={0};
int mode = 0;
int player=1;
int first=1;
int stop=0;
int preventIrp=0;

void createOX(int x,int y,int player);

int winner(int Map[3][3]);

bool checkFull(int Map[3][3]);

int minimax(int M[3][3],int player);

int show(int M[3][3],int x,int y);


void AI(int Map[3][3],int &a,int &b);

void selectOXImg();

void On_mouse(int event, int x, int y, int flags, void*);

void startImg();



int main(){


    line(img, Point(100,0), Point(100,300), Scalar(255,0,0), 3);
    line(img, Point(200,0), Point(200,300), Scalar(255,0,0), 3);
    line(img, Point(0,100), Point(300,100), Scalar(255,0,0), 3);
    line(img, Point(0,200), Point(300,200), Scalar(255,0,0), 3);
    img.copyTo(space);
    startImg();



    setMouseCallback("OX game", On_mouse, 0);



     waitKey(0);
     return 0;
}







void startImg(){

    rectangle(img, Point(0,0), Point(149,300), Scalar(0,0,255), -1);
    rectangle(img, Point(151,0), Point(300,300), Scalar(0,255,255), -1);
    putText(img, std::string("Player"), Point(15,150), 4, 1.1, Scalar(60,60,60),1.5);
    putText(img, std::string("AI"), Point(200,150), 4, 1.1, Scalar(60,60,60),1.5);
    imshow("OX game", img);
}


void On_mouse(int event, int x, int y, int flags, void*){

//*******************************************************************************************************
    if (event == EVENT_LBUTTONDOWN &&mode ==1){

	    show(Map,x,y);

	    imshow("OX game", img);
	    if(winner(Map)){
            mode = 3;
            waitKey(300);

            if(winner(Map)==1)
                putText(endImg, std::string("O Win"), Point(40,150), 4, 2, Scalar(200,0,200),2);
            else
                putText(endImg, std::string("X Win"), Point(40,150), 4, 2, Scalar(200,0,200),2);

            imshow("OX game", endImg);


	    }else if(checkFull(Map)){
            mode = 3;
            waitKey(300);
            putText(endImg, std::string("Tie"), Point(90,150), 4, 2, Scalar(200,0,200),2);
            imshow("OX game", endImg);

	    }

	}
//*******************************************************************************************************
	if(event == EVENT_LBUTTONDOWN &&mode ==2&&first==1&&preventIrp==0){


            if(show(Map,x,y)){
                preventIrp=1;
                imshow("OX game", img);
                waitKey(300);
                int a,b;


                AI(Map,a,b);
                show(Map,a,b);
                imshow("OX game", img);
                preventIrp=0;

            }


            if(winner(Map)){
                mode = 3;
                waitKey(300);
                if(winner(Map)==1)
                    putText(endImg, std::string("You Win"), Point(40,150), 4, 1.5, Scalar(200,0,200),2);
                else
                    putText(endImg, std::string("AI Win"), Point(40,150), 4, 2, Scalar(200,0,200),2);

                imshow("OX game", endImg);


            }else if(checkFull(Map)){
                mode = 3;
                waitKey(300);
                putText(endImg, std::string("Tie"), Point(90,150), 4, 2, Scalar(200,0,200),2);
                imshow("OX game", endImg);

            }
	}

//*******************************************************************************************************
	if (first==0&&mode ==2){
        int a,b;
        if(stop==0){
            stop=1;
            waitKey(300);

            AI(Map,a,b);
            preventIrp=1;
            show(Map,a,b);
            imshow("OX game", img);

        }

        if(event == EVENT_LBUTTONDOWN&&preventIrp==1){
            preventIrp=0;
            if(show(Map,x,y)){
                imshow("OX game", img);
                stop=0;

            }
        }
        if(winner(Map)){
            mode = 3;
            waitKey(300);




            if(winner(Map)==0)
                putText(endImg, std::string("You Win"), Point(20,150), 4, 1.5, Scalar(200,0,200),2);
            else
                putText(endImg, std::string("AI Win"), Point(40,150), 4, 2, Scalar(200,0,200),2);

            imshow("OX game", endImg);


        }else if(checkFull(Map)){
            mode = 3;
            waitKey(300);

            putText(endImg, std::string("Tie"), Point(90,150), 4, 2, Scalar(200,0,200),2);
            imshow("OX game", endImg);

        }


    }

//*******************************************************************************************************



	if (event == EVENT_LBUTTONDOWN && x<150 &&mode ==10){
        first=1;
	    mode = 2;
	    space.copyTo(img);
	    imshow("OX game", img);

	}else if(event == EVENT_LBUTTONDOWN && x>150 &&mode ==10){
	    first=0;
        mode = 2;
	    space.copyTo(img);
	    imshow("OX game", img);

	}
    if (event == EVENT_LBUTTONDOWN && x<150 &&mode ==0){
	    mode = 1;
	    space.copyTo(img);
	    imshow("OX game", img);

	}else if(event == EVENT_LBUTTONDOWN && x>150 &&mode ==0){
        mode = 10;
	    space.copyTo(img);
        selectOXImg();
	    imshow("OX game", img);

	}






}


void selectOXImg(){

    rectangle(img, Point(0,0), Point(150,300), Scalar(0,0,255), -1);
    rectangle(img, Point(150,0), Point(300,300), Scalar(0,255,255), -1);
    putText(img, std::string("O"), Point(40,170), 3, 3, Scalar(40,40,40),2);
    putText(img, std::string("X"), Point(190,170), 3, 3, Scalar(40,40,40),2);
    imshow("OX game", img);
}

void AI(int Map[3][3],int &a,int &b){


    if(checkFull(Map))return;
    if(winner(Map))return;
    int M[3][3];


    if(player==1){
        int Max=-2;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(Map[i][j]==0){
                    Map[i][j]=1;
                    int m=minimax(Map,-player);
                    if(m>Max){
                        a=i;
                        b=j;
                        Max =m;


                    }


                    Map[i][j]=0;

               }
            }
        }

    }else if(player == -1){

        int Min=2;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(Map[i][j]==0){
                    Map[i][j]=-1;
                    int m=minimax(Map,-player);
                    if(m<Min){
                        a=i;
                        b=j;
                        Min =m;


                    }


                    Map[i][j]=0;

               }
            }
        }


    }

    if(a==0&&b==0){a=50;b=50;}
    if(a==0&&b==1){a=150;b=50;}
    if(a==0&&b==2){a=250;b=50;}
    if(a==1&&b==0){a=50;b=150;}
    if(a==1&&b==1){a=150;b=150;}
    if(a==1&&b==2){a=250;b=150;}
    if(a==2&&b==0){a=50;b=250;}
    if(a==2&&b==1){a=150;b=250;}
    if(a==2&&b==2){a=250;b=250;}









}


void createOX(int x,int y,int player){
    if(player==1){
            circle(img, Point(x,y), 40, Scalar(0,255,255), 3);

    }
    if(player==-1){
        line(img, Point(x,y), Point(x+30,y+30), Scalar(255,0,255), 3);
        line(img, Point(x-30,y-30), Point(x,y), Scalar(255,0,255), 3);
        line(img, Point(x-30,y+30), Point(x,y), Scalar(255,0,255), 3);
        line(img, Point(x+30,y-30), Point(x,y), Scalar(255,0,255), 3);


    }

}

int winner(int Map[3][3]){
    for(int i=0;i<3;i++) if(Map[i][0]!=0&&Map[i][0]==Map[i][1]&&Map[i][1]==Map[i][2]) return Map[i][0];//列勝利判斷
    for(int i=0;i<3;i++) if(Map[0][i]!=0&&Map[0][i]==Map[1][i]&&Map[1][i]==Map[2][i]) return Map[0][i];//行勝利判斷
    if(Map[0][0]!=0&&Map[0][0]==Map[1][1]&&Map[1][1]==Map[2][2]) return Map[0][0];//左上右下斜勝利判斷
    if(Map[0][2]!=0&&Map[0][2]==Map[1][1]&&Map[1][1]==Map[2][0]) return Map[0][2];//右上左下斜勝利判斷
    return 0;//如果沒有勝利出現
}

bool checkFull(int Map[3][3]){
    int flag =0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(Map[i][j]==0){
                flag=1;
                break;
            }
        }
    }
    if(flag==1)return false;
    else  return true;
}

int minimax(int M[3][3],int player){


    if(winner(M)==1)return 1;
    else if(winner(M)==-1) return -1;
    if(checkFull(M))return 0;
    int MinMax =0;
    if(player == 1){
         MinMax=-2;
        for(int i=0;i<3;i++){

            for(int j=0;j<3;j++){

                if(M[i][j]==0){


                    M[i][j]=1;
                    MinMax = max(MinMax,minimax(M,-player));

                    M[i][j]=0;

                }


            }
        }

    }else if(player == -1){

        MinMax=2;
        for(int i=0;i<3;i++){

            for(int j=0;j<3;j++){

                if(M[i][j]==0){

                    M[i][j]=-1;
                    MinMax = min(MinMax,minimax(M,-player));
                    M[i][j]=0;




                }



            }
        }

    }

    return MinMax;





}



int show(int M[3][3],int x,int y){

     line(img, Point(100,0), Point(100,300), Scalar(255,0,0), 3);
     line(img, Point(200,0), Point(200,300), Scalar(255,0,0), 3);
     line(img, Point(0,100), Point(300,100), Scalar(255,0,0), 3);
     line(img, Point(0,200), Point(300,200), Scalar(255,0,0), 3);

     if(x<100&&y<100){
            x=50; y=50;
            if(M[0][0]!=0)return 0;
            M[0][0]=player;
     }else if(x>100&&x<200&&y<100){
            x=150;y=50;
            if(M[0][1]!=0)return 0;
            M[0][1]=player;
     }else if(x>200&&y<100){
            x = 250; y=50;
            if(M[0][2]!=0)return 0;
            M[0][2]=player;
     }else if(x<100&&y>100&&y<200){
            x = 50; y=150;
            if(M[1][0]!=0)return 0;
            M[1][0]=player;
     }else if(x>100&&x<200&&y>100&&y<200){
            x=150;y=150;
            if(M[1][1]!=0)return 0;
            M[1][1]=player;
     }else if(x>200&&y>100&&y<200){
         x = 250; y=150;
         if(M[1][2]!=0)return 0;
         M[1][2]=player;
     }else if(x<100&&y>200){
         x = 50; y=250;
         if(M[2][0]!=0)return 0;
         M[2][0]=player;
     }else if(x>100&&x<200&&y>200){
         x=150;y=250;
         if(M[2][1]!=0)return 0;
         M[2][1]=player;
     }else if(x>200&&y>200){
         x = 250; y=250;
         if(M[2][2]!=0)return 0;
         M[2][2]=player;
     }else{
        return 0;
     }




    createOX(x,y,player);
    player = -player;
    return 1;




}
