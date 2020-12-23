#include <iostream> // Visual Studio & MacOS用


#include <Windows.h> // Visual Studio用
#include <GL\glew.h> // Visual Studio用
#include <GL\freeglut.h> // Visual Studio用

int WindowWidth = 1024;    //生成するウィンドウの幅
int WindowHeight = 1024;    //生成するウィンドウの高さ
int  k ,n ;  //kはアリティ nは次元
float moveX = 0, moveY = 0, moveZ = -10.0, xRotation = 0, yRotation = 0;
int Color = 0;
float dis = 0.6 ;//球体の距離
float   a = 3.0;//サイクル間の距離
     

//球体を作成する関数
void createSphere(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); //座標
    glutSolidSphere(0.05 /*半径*/, 20.0, 20.0);
    glPopMatrix();
}

//線を作成する関数
void createLine(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    glBegin(GL_LINES);
    glVertex3f(startX, startY, startZ); //スタート座標
    glVertex3f(endX, endY, endZ); //終了座標
    glEnd();
}

//軸を作成する関数
void createAxis() {
    glColor3f(1, 0, 0); //色を赤に変更
    //createLine(-1000.0, 0, 0, 1000.0, 0, 0); //x軸

    glColor3f(0, 0, 1); //色を青に変更
    //createLine(0, -1000.0, 0, 0, 1000.0, 0); //y軸

    glColor3f(1, 1, 1); //色を白に変更
}

//印刷//
void print(float x, float y, float z, char character) {
    glRasterPos3f(x, y, z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
}
//数字の印刷//
void printnumber(float x, float y, float z, int number) {
    char numbers[] = { '0','1','2','3','4','5','6','7','8','9' };
    glRasterPos3f(x, y, z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[number]);
}

//2次元のサイクルを作成する関数
void create2dCycle(float x, float y, float z) {
    if (Color % 5 == 0 || Color % 5 == 4) 
        glColor3f(1, 0, 0);
    createSphere(x, y, z);//左の球体
    glColor3f(1, 1, 1);
    if (Color % 5 == 1 || Color % 5 == 4)
        glColor3f(1, 0, 0);
    createSphere(x + dis, y + dis, z);//上の球体
    glColor3f(1, 1, 1);
    if (Color % 5 == 2 || Color % 5 == 4)
        glColor3f(1, 0, 0);
    createSphere(x + dis * 2, y, z);//右の球体
    glColor3f(1, 1, 1);
    if (Color % 5 == 3 || Color % 5 == 4)
        glColor3f(1, 0, 0);
    createSphere(x + dis, y - dis, z);//下の球体
    glColor3f(1, 1, 1);

    glColor3f(0, 1, 0);
    createLine(x, y, z, x + dis, y + dis, z);//右上の線
    createLine(x + dis, y + dis, z, x + dis * 2, y, z);
    createLine(x + dis * 2, y, z, x + dis, y - dis, z);
    createLine(x + dis, y - dis, z, x, y, z);
    glColor3f(1, 1, 1);
}


//2次元のサイクルとサイクルのつながりを作成する関数
void create2dConnection(float x, float y, float z) {
    glColor3f(1, 0, 1);
    createLine(x, y, z, x + a + dis, y - dis, z);
    createLine(x+dis*2, y, z, x + dis, y + a + dis, z);
    createLine(x - a, y , z, x + dis, y -dis, z);
    createLine(x+dis, y+dis, z, x + dis*2, y - a, z);
    glColor3f(1, 1, 1);
}

//2次元のTCCを作成する関数
void create2dTCC(float x, float y, float z) {
    int i, j,c;
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            create2dCycle(x + (j * a), y + (i * a), z);
            create2dConnection(x + (j * a), y + (i * a), z);
            for (c = 0; c < 4; c++) {
                if (c == 0 && Color % 5 == 0|| Color % 5 == 4) {
                    glColor3f(1.0, 1, 0);
                    print(x + (j * a) - 0.7, y + (i * a) + 0.1, z, '(');
                    printnumber(x + (j * a) - 0.6, y + (i * a) + 0.1, z, j);
                    print(x + (j * a) - 0.5, y + (i * a) + 0.1, z, ',');
                    printnumber(x + (j * a) - 0.4, y + (i * a) + 0.1, z, i);
                    print(x + (j * a) - 0.3, y + (i * a) + 0.1, z, ',');
                    printnumber(x + (j * a)-0.2, y + (i * a) + 0.1, z, 0);
                    print(x + (j * a) - 0.1, y + (i * a) + 0.1, z, ')');
                    glColor3f(1.0, 1.0, 1.0);
                }
                if (c == 1 && Color % 5 == 1 || Color % 5 == 4) {
                    glColor3f(1.0, 1, 0);
                    print(x + dis + (j * a) - 0.6, y + (i * a) + dis + 0.1, z, '(');
                    printnumber(x + dis + (j * a) - 0.5, y + (i * a) + dis + 0.1, z, j);
                    print(x + dis + (j * a) - 0.4, y + (i * a) + dis + 0.1, z, ',');
                    printnumber(x + dis + (j * a) - 0.3, y + (i * a) + dis + 0.1, z, i);
                    print(x + dis + (j * a) - 0.2, y + (i * a) + dis + 0.1, z, ',');
                    printnumber(x + dis + (j * a) - 0.1, y + (i * a) + dis + 0.1, z, 1);
                    print(x + dis + (j * a), y + (i * a) + dis + 0.1, z, ')');
                    glColor3f(1.0, 1.0, 1.0);
                }
                if (c == 2 && Color % 5 == 2 || Color % 5 == 4) {
                    glColor3f(1, 1, 0);
                    print(x + (j * a) + dis * 2+0.1 , y + (i * a) - 0.3, z, '(');
                    printnumber(x + (j * a) + dis * 2+0.2, y + (i * a) - 0.3, z, j);
                    print(x + (j * a) + dis * 2 + 0.3, y + (i * a) - 0.3, z, ',');
                    printnumber(x + (j * a) + dis * 2 + 0.4, y + (i * a) - 0.3, z, i);
                    print(x + (j * a) + dis * 2 + 0.5, y + (i * a) - 0.3, z, ',');
                    printnumber(x + (j * a) + dis * 2 + 0.6, y + (i * a) - 0.3, z, 2);
                    print(x + (j * a) + dis * 2 + 0.7
                        , y + (i * a) - 0.3, z, ')');
                    glColor3f(1.0, 1.0, 1.0);
                }
                if (c == 3 && Color % 5 == 3 || Color % 5 == 4) {
                    glColor3f(1.0, 1, 0);
                    print(x + (j * a) + dis + 0.1, y + (i * a) -dis- 0.2, z, '(');
                    printnumber(x + (j * a) + dis + 0.2, y + (i * a) -dis- 0.2, z, j);
                    print(x + (j * a) + dis + 0.3, y + (i * a) -dis- 0.2, z, ',');
                    printnumber(x + (j * a) + dis + 0.4, y + (i * a) -dis- 0.2, z, i);
                    print(x + (j * a) + dis + 0.5, y + (i * a) -dis- 0.2, z, ',');
                    printnumber(x + (j * a) + dis + 0.6, y + (i * a) -dis- 0.2, z, 3);
                    print(x + (j * a) + dis + 0.7, y + (i * a) -dis- 0.2, z, ')');
                    glColor3f(1.0, 1.0, 1.0);
                 }
            }
        }
    }
}


//3次元のサイクルを作成する関数
void create3dCycle(float x, float y, float z) {
    createSphere(x, y, z);//左の球体
    createSphere(x + dis, y + dis, z);//左上の球体
    createSphere(x + dis*2, y + dis, z);//右上の球体
    createSphere(x + dis*3, y , z);//右の球体
    createSphere(x + dis*2, y - dis, z);//右下の球体
    createSphere(x + dis, y - dis , z);//左下の球体
    

    glColor3f(1, 0, 0); //色を青に変更
    createLine(x, y, z, x + dis, y + dis, z);//左上の線
    createLine(x + dis, y + dis, z, x + dis * 2, y + dis, z);//上の線
    createLine(x + dis * 2, y + dis, z, x + dis*3, y , z);//右上の線
    createLine(x + dis*3, y , z, x + dis*2, y - dis, z);//右下の線
    createLine(x +dis*2, y -dis, z, x + dis, y - dis, z);//下の線
    createLine(x + dis, y - dis, z, x , y, z);//左下の線
    glColor3f(1, 1, 1); //色を白に変更

}

//3次元のサイクルとサイクルのつながりを作成する関数
void create3dConnection(float x, float y, float z) {
    glColor3f(0.4, 0.8, 0.4);
    createLine(x + dis*2, y-dis, z, x+a+dis , y-dis, z);
    createLine(x , y , z, x +dis, y+a+dis, z);
    createLine(x + dis * 2, y + dis, z,x+dis*3,y,z-a);
    createLine(x - a + dis * 2, y - dis, z, x + dis, y - dis, z);
    createLine(x, y - a , z, x + dis, y + dis, z);
    createLine(x+dis*2, y+dis, z+a, x +dis*3,y,z);
    glColor3f(1, 1, 1);
}
//3次元のTCCを作成する関数
void create3dTCC(float x, float y, float z) {
    int i, j,s,b;
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            for (s = 0; s < k; s++) {
                create3dCycle(x + (j * a), y + (i * a), z + (s * a));
                create3dConnection(x + (j * a), y + (i * a), z + (s * a));
                for (b = 0; b < 6; b++) {
                    
                    if (b == 0) {
                        glColor3f(1.0, 1.0, 0.5);
                        print(x +(j*a)- 0.7, y+(i*a)+0.1, z + (s * a), '(');
                        printnumber(x  + (j*a)-0.6, y + (i * a)+0.1, z + (s * a), j);
                        print(x + (j*a)-0.5, y + (i * a)+0.1, z + (s * a), ',');
                        printnumber(x + (j*a)-0.4, y + (i * a)+0.1, z + (s * a), i);
                        print(x  + (j*a)-0.3, y + (i * a)+0.1, z + (s * a), ',');
                        printnumber(x  + (j * a)-0.2, y + (i * a)+0.1, z + (s * a), s);
                        print(x + (j*a)-0.1, y + (i * a)+0.1, z + (s * a), ',');
                        printnumber(x + (j * a), y + (i * a)+0.1, z + (s * a), 0);
                        print(x + (j * a) + 0.1, y + (i * a)+0.1, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                    if (b == 1) {
                        glColor3f(1.0, 0.5, 0.5);
                        print(x + dis + (j * a) - 0.6, y + (i * a) + dis + 0.1, z + (s * a), '(');
                        printnumber(x + dis + (j * a) - 0.5, y + (i * a) + dis + 0.1, z + (s * a), j);
                        print(x + dis + (j * a) - 0.4, y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + dis + (j * a) - 0.3, y + (i * a) + dis + 0.1, z + (s * a), i);
                        print(x + dis + (j * a) - 0.2, y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + dis + (j * a) - 0.1, y + (i * a) + dis + 0.1, z + (s * a), s);
                        print(x + dis + (j * a), y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + dis + (j * a)+0.1, y + (i * a) + dis + 0.1, z + (s * a), 1);
                        print(x + dis + (j * a)+0.2, y + (i * a) + dis + 0.1, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                    if (b == 2) {
                        glColor3f(0, 0.5, 0.3);
                        print(x + (j * a) + dis * 2 - 0.1, y + (i * a) + dis + 0.1, z + (s * a), '(');
                        printnumber(x + (j * a) + dis * 2, y + (i * a) + dis + 0.1, z + (s * a), j);
                        print(x + (j * a) + dis * 2 + 0.1, y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.2, y + (i * a) + dis + 0.1, z + (s * a), i);
                        print(x + (j * a) + dis * 2 + 0.3, y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.4, y + (i * a) + dis + 0.1, z + (s * a), s);
                        print(x + (j * a) + dis * 2 + 0.5, y + (i * a) + dis + 0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.6, y + (i * a) + dis + 0.1, z + (s * a), 2);
                        print(x + (j * a) + dis * 2 + 0.7, y + (i * a) + dis + 0.1, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                    if (b == 3) {
                        glColor3f(1.0, 0.5, 0.3);
                        print(x + (j * a) + dis * 3 + 0.1, y + (i * a)-0.1, z + (s * a), '(');
                        printnumber(x + (j * a) + dis * 3 + 0.2, y + (i * a)-0.1, z + (s * a), j);
                        print(x + (j * a) + dis * 3 + 0.3, y + (i * a)-0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 3 + 0.4, y + (i * a)-0.1, z + (s * a), i);
                        print(x + (j * a) + dis * 3 + 0.5, y + (i * a)-0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 3 + 0.6, y + (i * a)-0.1, z + (s * a), s);
                        print(x + (j * a) + dis * 3 + 0.7, y + (i * a)-0.1, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 3 + 0.8, y + (i * a)-0.1, z + (s * a), 3);
                        print(x + (j * a) + dis * 3 + 0.9, y + (i * a)-0.1, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                    if (b == 4) {
                        glColor3f(0.5, 0, 0.7);
                        print(x + (j * a) + dis * 2 - 0.1, y + (i * a) - dis - 0.2, z + (s * a), '(');
                        printnumber(x + (j * a) + dis * 2, y + (i * a) - dis - 0.2, z + (s * a), j);
                        print(x + (j * a) + dis * 2 + 0.1, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.2, y + (i * a) - dis - 0.2, z + (s * a), i);
                        print(x + (j * a) + dis * 2 + 0.3, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.4, y + (i * a) - dis - 0.2, z + (s * a), s);
                        print(x + (j * a) + dis * 2 + 0.5, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis * 2 + 0.6, y + (i * a) - dis - 0.2, z + (s * a), 4);
                        print(x + (j * a) + dis * 2 + 0.7, y + (i * a) - dis - 0.2, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                    if (b == 5) {
                        glColor3f(1.0, 0.2, 0.5);
                        print(x + (j * a) + dis - 0.6, y + (i * a) - dis - 0.2, z + (s * a), '(');
                        printnumber(x + (j * a) + dis - 0.5, y + (i * a) - dis - 0.2, z + (s * a), j);
                        print(x + (j * a) + dis - 0.4, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis - 0.3, y + (i * a) - dis - 0.2, z + (s * a), i);
                        print(x + (j * a) + dis - 0.2, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis - 0.1, y + (i * a) - dis - 0.2, z + (s * a), s);
                        print(x + (j * a) + dis, y + (i * a) - dis - 0.2, z + (s * a), ',');
                        printnumber(x + (j * a) + dis+0.1, y + (i * a) - dis - 0.2, z + (s * a), 5);
                        print(x + (j * a) + dis+0.2, y + (i * a) - dis - 0.2, z + (s * a), ')');
                        glColor3f(1.0, 1.0, 1.0);
                    }
                   // glColor3f(1, 1, 1);
                }
           
            }
        }
    }
   

}
void colorchange(){
    
    if (Color % 4 == 0) {
        glColor3f(1, 1, 0);
    }

    if (Color % 4 == 1) {
        glColor3f(1, 0, 0);
    }
    if (Color % 4 == 2) {
        glColor3f(0, 0, 1);
    }
    if (Color % 4 == 3) {
        glColor3f(1, 0, 1);
    }
    print(-1.0, -0.5, 0, 't');
    print(-0.9, -0.5, 0, 'e');
    print(-0.8, -0.5, 0, 's');
    print(-0.7, -0.5, 0, 't');

    
    glColor3f(1, 1, 1);

    
}
 

   
//画面に映る関数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去x

    glPushMatrix();

    glTranslatef(moveX, moveY, moveZ);
    glRotatef(xRotation,0,1,0);
    glRotatef(yRotation,1,0,0);

    createAxis(); //軸を作成
    //colorchange();

  if(n==2)
    create2dTCC(-0.2, 0, 0);

   else if(n == 3) {
       create3dTCC(0, 0, 0);
   }

    glPopMatrix();

    glFlush();
}

//キーボードで操作する関数
void keyboardFunctions(unsigned char key, int a, int b) {
    if (key == 'x')
        moveZ = moveZ - 1.0;
    if (key == 'z')
        moveZ = moveZ + 1.0;
    if (key == 'a')
        moveX = moveX - 1.0;
    if (key == 's')
        moveX = moveX + 1.0;
    if (key == 'q')
        moveY = moveY - 1.0;
    if (key == 'w')
        moveY = moveY + 1.0;
    if (key == 'c')
        xRotation = xRotation + 1.0;
    if (key == 'v')
        xRotation = xRotation - 1.0;
    if (key == 'd')
        yRotation = yRotation + 1.0;
    if (key == 'f')
        yRotation = yRotation - 1.0;
    if (key == 'b')
        Color = Color + 1.0;

    glutPostRedisplay();
}


//初期設定の関数
void initialize(void) {
    glViewport(0, 0, WindowWidth, WindowHeight);
    glEnable(GL_DEPTH_TEST); //デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

    //透視投影法の視体積gluPerspactive
    gluPerspective(30.0,                                       //縦角度
        (double)WindowWidth / (double)WindowHeight, //横角度
        0.1,                                        //一番近いｚ軸
        1200);                                      //一番遠いｚ軸

    gluLookAt(0.0, 0.0, 10.0, //視点の位置
        0.0, 0.0, 0.0,  //視点の位置からの視点の中心
        0.0, 1.0, 0.0); //視点の上
}

//プログラムの開始位置
int main(int argc, char** argv) {
    printf(" k（アリティ）= ");
    scanf_s("%d",&k);
    printf(" n（次元）= ");
    scanf_s("%d", &n);
    glutInit(&argc, argv);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("We love TCC!");
    initialize(); //初期設定
    glutDisplayFunc(display); //画面に映る関数をここで呼び出す
    glutKeyboardFunc(keyboardFunctions);
    glutMainLoop();
    return 0;
}