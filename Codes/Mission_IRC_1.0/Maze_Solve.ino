int path_x[4][10], path_y[4][10];
int mark_vis[4][5][4];
int len[4]={0,0,0,0};
int new_x=0, new_y=0;
int end_pos=0,pr_end_pos=0;
int lenf[4];
int fpath[4][20];
int tg=0, tgm;

//1 +x
//2 +y
//-1 -x
//-2 -y

void initialize(){
  for(int aa=0;aa<4;aa++){
    for(int ab=0;ab<5;ab++){
      for(int ac=0;ac<4;ac++)
      mark_vis[aa][ab][ac]=0;
    }
    for(int ad=0;ad<10;ad++){
      path_x[aa][ad]=0;
      path_y[aa][ad]=0;
    }
    len[aa]=0;
  }
}
  
bool explore_grid(int x, int y, int dir, int opt){
  if(x<0||x>4||y<0||y>3) return false;
  //if(grid[i-1][x][y]>1) return false; wshop
  if(grid[i-1][x][y]==end_pos){
    new_x=x;
    new_y=y;
    Serial.print(new_x);
    Serial.println(new_y);
    mark_vis[opt][x][y]=1;
  path_x[opt][len[opt]]=x;
  path_y[opt][len[opt]]=y;
  len[opt]++;
    return true;
    }
  if(grid[i-1][x][y]>1&&grid[i-1][x][y]!=pr_end_pos) return false;
  /*{
    if(!(new_x==x &&new_y==y))
    return false;
    //else initialize();
  }*/

  mark_vis[opt][x][y]=1;
  path_x[opt][len[opt]]=x;
  path_y[opt][len[opt]]=y;
  len[opt]++;

  if(opt==1){
      if(x-1>=0){
        Serial.print("Entered 1.1 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=1)&&(mark_vis[opt][x-1][y]==0)){
            if(explore_grid(x-1,y,-1,opt)) return true;
            }
          }
      if(y-1>=0){
        Serial.print("Entered 1.2 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=2)&&(mark_vis[opt][x][y-1]==0)){
            if(explore_grid(x,y-1,-2,opt)) return true;
            }
          }
      if(x+1<=4){
        Serial.print("Entered 1.3 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-1)&&(mark_vis[opt][x+1][y]==0)){
            if(explore_grid(x+1,y,1,opt)) return true;
            }
          }
      if(y+1<=3){
        Serial.print("Entered 1.4 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-2)&&(mark_vis[opt][x][y+1]==0)){
            if(explore_grid(x,y+1,2,opt)) return true;
            }
          }
    }

  else if(opt==2){
      if(x+1<=4){
        Serial.print("Entered 2.3 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-1)&&(mark_vis[opt][x+1][y]==0)){
            if(explore_grid(x+1,y,1,opt)) return true;
            }
          }
      if(y-1>=0){
        Serial.print("Entered 2.2 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=2)&&(mark_vis[opt][x][y-1]==0)){
            if(explore_grid(x,y-1,-2,opt)) return true;
            }
          }
      if(x-1>=0){
        Serial.print("Entered 2.1 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=1)&&(mark_vis[opt][x-1][y]==0)){
            if(explore_grid(x-1,y,-1,opt)) return true;
            }
          }
      if(y+1<=3){
        Serial.print("Entered 2.4 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-2)&&(mark_vis[opt][x][y+1]==0)){
            if(explore_grid(x,y+1,2,opt)) return true;
            }
          }
    }

  else if(opt==3){
      if(y+1<=3){
        Serial.print("Entered 3.4 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-2)&&(mark_vis[opt][x][y+1]==0)){
            if(explore_grid(x,y+1,2,opt)) return true;
            }
          }
      if(x-1>=0){
        Serial.print("Entered 3.1 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=1)&&(mark_vis[opt][x-1][y]==0)){
            if(explore_grid(x-1,y,-1,opt)) return true;
            }
          }
      if(y-1>=0){
        Serial.print("Entered 3.2 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=2)&&(mark_vis[opt][x][y-1]==0)){
            if(explore_grid(x,y-1,-2,opt)) return true;
            }
          }
      if(x+1<=4){
        Serial.print("Entered 3.3 for grid[");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println("]");
          if((dir!=-1)&&(mark_vis[opt][x+1][y]==0)){
            if(explore_grid(x+1,y,1,opt)) return true;
            }
          }
    }
  len[opt]--;
  return false;
  }

void find_path(int xi, int yi, int nodef, int n){
  end_pos=nodef;
  Serial.println("fp");
  explore_grid(xi,yi,0,1);
  explore_grid(xi,yi,0,2);
  explore_grid(xi,yi,0,3);
  lenf[n]=len[1];
  if(len[1]==0) lenf[n]=len[2];
  else if(len[2]==0) lenf[n]=len[3];
  //len[1]=0;// wshop//ch
  int i=1;
  if(len[2]<lenf[n] && len[2]!=0) {lenf[n]=len[2];i=2;len[2]=0;}//wshop
  if(len[3]<lenf[n] && len[3]!=0) {lenf[n]=len[3];i=3;len[3]=0;}//wshop
  Serial.print("Shortest Length = ");
  Serial.println(lenf[n]);
  for(int j=0;j<lenf[n];j++){
    fpath[n][j]=path_x[i][j]*10+path_y[i][j];
    }
  }

int find_dir(int posi, int posf){
  if((posi-posf)==1) return -2; //2;wshop
  else if((posi-posf)==-1) return 2; //-2;wshop
  else if((posi-posf)==10) return -1; //1;wshop
  else if((posi-posf)==-10) return 1; //-1;wshop
  else return 0;
  }

void turn(int dir, int prv_dir){
  if(prv_dir+dir==0) turn_back();
  else{
    switch(dir)
    {
      case 1:
        if(prv_dir==2) turn_right();
        else if(prv_dir==-2) turn_left();
        else st();//wshop
        break;
      case 2:
        if(prv_dir==-1) turn_right();
        else if(prv_dir==1) turn_left();
        else st();//wshop
        break;
      case -1:
        if(prv_dir==-2) turn_right();
        else if(prv_dir==2) turn_left();
        else st();//wshop
        break;
      case -2:
        if(prv_dir==1) turn_right();
        else if(prv_dir==-1) turn_left();
        else st();//wshop
        break;
    }
    }
  }

void solve_grid(int z1){
  if(z1==0){
    find_path(4,0,4,0);
    initialize();//ch
    pr_end_pos=4;//ch
    find_path(new_x,new_y,7,1);
    initialize();//ch
    pr_end_pos=7;//ch
    find_path(new_x,new_y,3,2);
    initialize();//ch
    pr_end_pos=3;//ch
    find_path(new_x,new_y,6,3);
    //initialize();//ch
  }
  else find_path(new_x,new_y,9,4);
  }

void main_run(){
  initialize();
  /*grid[0][4][0]=1;
  grid[0][4][1]=1;
  grid[0][4][2]=1;
  grid[0][4][3]=2;
  grid[0][3][0]=2;
  grid[0][3][1]=1;
  grid[0][3][2]=1;
  grid[0][3][3]=4;
  grid[0][2][0]=1;
  grid[0][2][1]=1;
  grid[0][2][2]=2;
  grid[0][2][3]=1;
  grid[0][1][0]=7;
  grid[0][1][1]=1;
  grid[0][1][2]=1;
  grid[0][1][3]=1;
  grid[0][0][0]=1;
  grid[0][0][1]=3;
  grid[0][0][2]=1;
  grid[0][0][3]=6;*/
  i=1;
  int dir=0;
  int h;
  int prv_dir=2;// 1 wshop
  solve_grid(0);
  while(!check_node()) line_follow();
  
  for(h=0;h<lenf[0]-1;h++){
    dir=find_dir(fpath[0][h],fpath[0][h+1]);
    Serial.println(dir);//path1
    turn(dir,prv_dir);
    while(!check_node()) line_follow();
    prv_dir=dir;
  }
  
  //if(check_node()==4) pause();
  digitalWrite(ledb,LOW);
  delay(100);
  digitalWrite(ledb,HIGH);
    /*gr_open();
    tg=millis();
    while(millis()<tg+tgm) line_follow();   //blue block lego1
    gr_close();
    gr_up();*/ //wshop
    
  for(h=0;h<lenf[1]-1;h++){
    dir=find_dir(fpath[1][h],fpath[1][h+1]);  //path2
    Serial.println(dir);
    turn(dir,prv_dir);
    while(!check_node()) line_follow();
    prv_dir=dir;
    }
    digitalWrite(ledr,LOW);
    digitalWrite(ledg,LOW);
    digitalWrite(ledb,LOW);
    delay(100);
    digitalWrite(ledr,HIGH);
    digitalWrite(ledg,HIGH);
    digitalWrite(ledb,HIGH);
  /*if(prv_dir==2){
    turn_left();
    prv_dir=-1;
  }*/
  /*if(check_node()==7){
    while(sum!=7) line_follow();
    pause();
    }
    /*gr_down();
    gr_open();
    gr_up();*/ //wshop
    //turn_back();
    //prv_dir=-prv_dir;
    //while(sum!=7) line_follow();            //pit1
    
  for(h=0;h<lenf[2]-1;h++){
    dir=find_dir(fpath[2][h],fpath[2][h+1]);
    Serial.println(dir);
    turn(dir,prv_dir);
    while(!check_node()) line_follow();
    prv_dir=dir;
    }
  digitalWrite(ledr,LOW);
  delay(300);
  digitalWrite(ledr,HIGH);
  //if(check_node()==3) pause();
    /*gr_open();
    tg=millis();
    while(millis()<tg+tgm) line_follow();   //red block lego2
    gr_close();
    gr_up();*/ //wshop
    
  for(h=0;h<lenf[3]-1;h++){
    dir=find_dir(fpath[3][h],fpath[3][h+1]);
    Serial.println(dir);
    turn(dir,prv_dir);
    while(!check_node()) line_follow();
    prv_dir=dir;
    }
    
  //if(check_node()==6) {
    digitalWrite(ledr,LOW);
    digitalWrite(ledg,LOW);
    digitalWrite(ledb,LOW);
    delay(100);
    digitalWrite(ledr,HIGH);
    digitalWrite(ledg,HIGH);
    digitalWrite(ledb,HIGH);
  
  //end_ind++;
   /*gr_down();
    gr_open();
    tg=millis();
    while(millis()<tg+tgm) line_follow();   //pit2
    gr_close();
    gr_up();*/ //wshop
    
  /*i=2;
  initialize();
  solve_grid(1);
  for(h=0;h<lenf[4]-1;h++){
    dir=find_dir(fpath[4][h],fpath[4][h+1]);
    turn(dir,prv_dir);
    while(!check_node()) line_follow();
    prv_dir=dir;
    }

  gr_open();
  gr_down();
  if(check_node()==9) while(sum!=5) line_follow();            //lego4
  gr_close();
  turn_right();
  tg=millis();
  while(millis()<tg+tgm) line_follow();
  digitalWrite(led,HIGH);*/
  }
