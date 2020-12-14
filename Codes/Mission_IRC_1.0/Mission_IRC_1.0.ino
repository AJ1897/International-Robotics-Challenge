//1 white node
//2 black node
//3 red block lego2
//4 blue block lego1
//5 photo point
//6 pit2
//7 pit1
//8 pit3
//9 lego 4
//10 sign board

#define mlf 23
#define mlb 22
#define mlp 11
#define mrf 26
#define mrb 27
#define mrp 10
#define ledr 2
#define ledg 4
#define ledb 5
#define ledc 3
//#define mlen 4
//#define mren 5


int mlpwm=0,mrpwm=0,mls=170,mrs=170;
int reading[7], dread[7];
int perr=0, derr=0, corr=0, err=0, kp=25, kd=15, sen_thr=500, sum=0, end_ind=0;
int grid[2][5][4];
int x=4, y=-1, i=1, a, b;
int pit1=0, pit2=0, ip_val=0, red=12, blue=23, arr_l=34, arr_r=45, lego4=56;
int t0=300, t1=0, t2=0,overshoot= 170;
long long int t3, t=0;

void print_grid(){
  Serial.println("Printing Maze");
  for(int r=4; r>=0; r--)
  {
    for(int c=0; c<4; c++)
    {
     Serial.print(grid[0][r][c]);
     Serial.print(" ,"); 
    }
   Serial.println(); 
  }
  }

void setup()
{
  Serial.begin(9600);
  Serial.println("Reset");
  pinMode(mlf, OUTPUT);
  pinMode(mlb, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrf, OUTPUT);
  pinMode(mrb, OUTPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledc, OUTPUT);
  digitalWrite(ledc,HIGH);
  digitalWrite(ledr,HIGH);
  digitalWrite(ledg,HIGH);
  digitalWrite(ledb,HIGH);
  //digitalWrite(mlen,HIGH);
  //digitalWrite(mren,HIGH);
}

  void sensor_read(){
    reading[0]=analogRead(A0);
    reading[1]=analogRead(A1);
    reading[2]=analogRead(A2);
    reading[3]=analogRead(A3);
    reading[4]=analogRead(A4);
    reading[5]=analogRead(A5);
    reading[6]=analogRead(A6);
    for(int l=0; l<7; l++)
    {
      if(reading[l]<sen_thr) dread[l]=0;
      else dread[l]=1;
      }
  }
  
      
  void calc_error(){
    sum=0;
    for(int l=0; l<7;l++)
      sum=sum+dread[l];
    int wsum=7*dread[0]+4*dread[1]+dread[2]-dread[4]-4*dread[5]-7*dread[6];
    err=wsum/sum;
  }
      
  void pause(){
    digitalWrite(mlb,LOW);
    digitalWrite(mrb,LOW);
    digitalWrite(mlf,LOW); 
    digitalWrite(mrf,LOW);
        
    analogWrite(mlp,0);
    analogWrite(mrp,0);
  }
        
  void move_(){
    digitalWrite(mlf,HIGH);
    digitalWrite(mrf,HIGH);
    digitalWrite(mlb,LOW);
    digitalWrite(mrb,LOW);
        
    analogWrite(mlp,mlpwm);
    analogWrite(mrp,mrpwm);
  }
  
  void motor(){ 
    derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    if(corr<0){
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
        }
      else {
         mrpwm=mrs+corr;
         mlpwm=mls-corr;
         }
       if(mlpwm>254) mlpwm=254;
      else if(mrpwm>254) mrpwm=254;
      else if(mlpwm<0) mlpwm=0;
      else if(mrpwm<0) mlpwm=0;
    move_();
  }

  void turn_left(){
    t=millis();
    while(millis()<t+t1) line_follow();
    while(!dread[0]){
      digitalWrite(mrf,HIGH);
      digitalWrite(mlf,LOW);
      digitalWrite(mrb,LOW);
      digitalWrite(mlb,HIGH);
        
      analogWrite(mlp,mls);
      analogWrite(mrp,mrs);
      sensor_read();
      }
  }

  void turn_right(){
    t=millis();
    while(millis()<t+t1) line_follow();
    while(!dread[6]){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,LOW);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,HIGH);
        
      analogWrite(mlp,mls);
      analogWrite(mrp,mrs);
      sensor_read();
      }
  }
  void st(){
    t=millis();
    while(millis()<t+350) line_follow();
    }

  void turn_back(){
    t=millis();
    while(!dread[6]||millis()<t+t1){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,LOW);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,HIGH);
        
      analogWrite(mlp,mls);
      analogWrite(mrp,mrs);
      sensor_read();
      }
  }

  void line_follow(){
    sensor_read();
    calc_error();
    motor();
  }

  void initialise(){
    for(int ii=0;ii<2;ii++){
      for(int ij=0;ij<5;ij++){
        for(int ik=0;ik<4;ik++){
          grid[ii][ij][ik]=0;
          }
        }
      }
    }

  int check_node(){
    sensor_read();
  /*Serial.print("(");
  Serial.print(x+a);
  Serial.print(",");
  Serial.print(y+b);
  Serial.print(") ");*/
  if(sum==7)
   {grid[i-1][x+a][y+b]=1;
   t=millis();
    while(millis()<t+overshoot)
    {
      line_follow();
    }
    }
    else if(dread[0]==1&&(dread[2]==0||dread[3]==0||dread[4]==0)&&dread[6]==1){
      //Serial.println("Kaala Kuan");
      grid[i-1][x+a][y+b]=2;
      t=millis();
      while(millis()<t+overshoot)
        line_follow();
      /*if(dread[0]==1&&dread[2]==0&&dread[4]==1){
        if(!pit2){
          grid[0][x+a][y+b]=6;
          pit2++;
        }
        }*/
       }
        else  grid[i-1][x+a][y+b]=0;
     /*if (us()){
      //check_color();
      if (ip_val==red) grid[0][x+a][y+b]=3;
      else if (ip_val==blue) grid[0][x+a][y+b]=4;
      }*/
    //Serial.println(grid[i-1][x+a][y+b]);
    return grid[i-1][x+a][y+b];
    }

  void follow(int a, int b){
    line_follow();
    if(check_node()){
      x+=a;
      y+=b;
  /*Serial.print("[");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print("] ");*/
      }
    /*if(grid[1][x][y]==5) check_box();
    if(ip_val==lego4) grid[1][x][y]=9;*/
    if((i==1&&x==2&&y==0)||(i==2&&(x==2||x==3||x==4)&&y==0)){
      if(i==2&&(x!=2||x!=4))
      turn_left();
      /*if(i==1) check_arrow();
      if(ip_val==arr_l) grid[0][3][0]=7;
      else if(ip_val==arr_r) grid[0][0][0]=7;
      if(i==2) check_box();
      if(ip_val==lego4) grid[1][x][0]=9;
      */
      if(i==2&&(x!=2||x!=4))
      turn_right();
      }
    }

  void traverse(int c, int d, int e){
    //if(i==1&&x==0&&y==1) return; wshop
    if(i==2&&x==1&&y==1) return;
    switch(d){
      case 0:
        while(x==c&&y<e) {
          a=0;
          b=1;
          follow(0,1);
          }
        if(x==0 && y==3) 
         break; //wshop
        turn_left();
        traverse(c,1,e);
        break;
      case 1:
        while(x>(c-1)&&y==e) {
          a=-1;
          b=0;
          follow(-1,0);}
        turn_left();
        traverse(c,2,e);
        break;
      case 2:
        while(x==(c-1)&&y>0) {
          a=0;
          b=-1;
          follow(0,-1);}
        turn_right();
        traverse(c,3,e);
        break;
      case 3:
        while(x>c-2&&y==0) {
          a=-1;
          b=0;
          follow(-1,0);
        }
        turn_right();
        traverse(c-2,0,e);
        break;
      }
      }
    
  void dry_run(){
    initialise();
//    grid[0][2][0]=10;
    grid[1][0][2]=8;
    for(int j=2;j<5;j++)
      grid[1][j][0]=5;
      
    /*if(x==4&&y==-1){
      a=0;
      b=1;
      }*/
    traverse(4,0,3);

    /*while(!(dread[0]==1&&dread[3]==0&&dread[6]==1)) line_follow();
    if(pit2>0&&dread[0]==1&&dread[3]==0&&dread[6]==1){
      i=2;
      x=0; y=-1;
      a=1; b=0;
      }*/
    /*while(sum) line_follow();*/
    
   /* y=2;
    while(x==0&&y<3) follow(0,1);
    turn_right();
    while(x<4&&y==3) follow(1,0);
    turn_right();
    traverse(5,2,2);*/

    //digitalWrite(buzzer,HIGH);
    grid[0][3][3]=4;
    grid[0][1][0]=7;
    grid[0][0][1]=3;
    grid[0][0][3]=6;
    print_grid();
    pause();
    delay(5000);
    end_ind++;
    }

void loop()
{
  if(!end_ind)
  dry_run();
  else
  
  main_run();
}
