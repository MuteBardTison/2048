/*
 2048.cpp
 @author Zihan Qi
 @version 1.0 10/27/2017
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 2048;
int board [4][4]={0};
static int step;
static int score;

int random_index_generate(){
    int random_index = rand() % 4;
    return random_index;
}

int new_random_element(){
    int random_element = rand() % 10;
    random_element = (random_element==0) ? 4 : 2;
    return random_element;
}
//win or lose check
int is_win(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==MAX){
                return 1;
            }
        }
    }
    return 0;
}

int game_over(){
    int is_game_over = 1;
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]==0 || board[i][j+1]==0 || board[i][j] == board[i][j+1]){
                is_game_over = 0;
                break;
            }
        }
    }
    for(int j=0; j<4; j++){
        for(int i=0; i<3; i++){
            if(board[i][j]==0 || board[i+1][j]==0 || board[i][j] == board[i+1][j]){
                is_game_over = 0;
                break;
            }
        }
    }
    return is_game_over;
}
//show game board
void display(){
    int index_i1, index_j1, index_i2, index_j2;
    //test duplication
    while(1){
        index_i1 = random_index_generate();
        index_j1 = random_index_generate();
        index_i2 = random_index_generate();
        index_j2 = random_index_generate();
        if(index_i1==index_i2 && index_j1==index_j2){
            continue;
        }
        else
            break;
    }
    //initialize
    if(step == 0){
        cout<<"------2048------"<<endl;
        cout<<"@author Zihan Qi"<<endl;
        cout<<"Feedback: z.qi@jacobs-university.de"<<endl<<endl;
        cout<<"Rules:"<<endl;
        cout<<"Use w(up), s(down), a(left), d(right) keys to move the tiles in certain direction"<<endl;
        cout<<"Double up and merge titles with the same number touch"<<endl<<endl;
        for(int i=0; i<4; i++){
            cout<<"|-----------------------|"<<endl;
            for(int j=0; j<4; j++){
                cout<<"|";
                if(i==index_i1 && j==index_j1){
                    board[i][j]=2;
                    cout<<"  "<<2<<"  ";
                }
                else if(i==index_i2 && j==index_j2){
                    int temp = new_random_element();
                    board[i][j] = temp;
                    cout<<"  "<<temp<<"  ";
                }
                    else
                        cout<<"     ";
            }
            cout<<"|"<<endl;
        }
        cout<<"|-----------------------|"<<endl;
    }
    //redisplay
    else{
        for(int i=0; i<4; i++){
            cout<<"|-----------------------|"<<endl;
            for(int j=0; j<4; j++){
                cout<<"|";
                if(board[i][j]!=0){
                    if(board[i][j]==1024 || board[i][j]==2048)
                        cout<<" "<<board[i][j];
                    if(board[i][j]==128 || board[i][j]==256 || board[i][j]==512)
                        cout<<" "<<board[i][j]<<" ";
                    if(board[i][j]==16 || board[i][j]==32 || board[i][j]==64)
                        cout<<"  "<<board[i][j]<<" ";
                    if(board[i][j]==2 || board[i][j]==4 || board[i][j]==8)
                        cout<<"  "<<board[i][j]<<"  ";
                }
                else
                    cout<<"     ";
            }
            cout<<"|"<<endl;
        }
        cout<<"|-----------------------|"<<endl;
    }
    //cout<<"step "<<step<<endl;
}
//insert random element
void add_element(){
    int index_i3, index_j3;
    int flag=0;
    while(1){
        if(flag==1)break;
        index_i3 = random_index_generate();
        index_j3 = random_index_generate();
        if(board[index_i3][index_j3]==0){
            board[index_i3][index_j3] = new_random_element();
            flag=1;
        }
    }
}

//move functions
void move_left(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[i][k]==0 && board[i][k+1]!=0){
                    board[i][k]=board[i][k]^board[i][k+1];
                    board[i][k+1]=board[i][k]^board[i][k+1];
                    board[i][k]=board[i][k]^board[i][k+1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_right(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[i][k]==0 && board[i][k-1]!=0){
                    board[i][k]=board[i][k]^board[i][k-1];
                    board[i][k-1]=board[i][k]^board[i][k-1];
                    board[i][k]=board[i][k]^board[i][k-1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_up(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[k][i]==0 && board[k+1][i]!=0){
                    board[k][i]=board[k][i]^board[k+1][i];
                    board[k+1][i]=board[k][i]^board[k+1][i];
                    board[k][i]=board[k][i]^board[k+1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_down(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[k][i]==0 && board[k-1][i]!=0){
                    board[k][i]=board[k][i]^board[k-1][i];
                    board[k-1][i]=board[k][i]^board[k-1][i];
                    board[k][i]=board[k][i]^board[k-1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

int main(){
    srand((unsigned)time(NULL));
    char ch, c;
    int question = 0;
    //initialize board
    display();
    while(1){
        if(is_win() && !question){
            question = !question;
            cout<<step<<" steps"<<endl;
            cout<<"!!!YOU WIN!!!"<<endl;
            cout<<"Continue? (y/n)"<<endl;
            cin>>c;
            if(c=='n')
                exit(1);
        }
        if(game_over()){
            cout<<"~~~GAME OVER~~~"<<endl;
            exit(2);
        }
        cin>>ch;
        switch (ch) {
            case 'w':
                move_up();
                break;
            case 's':
                move_down();
                break;
            case 'a':
                move_left();
                break;
            case 'd':
                move_right();
                break;
            default:
                break;
        }
        //show current scores
        cout<<"score: "<<score<<endl;
    }
    return 0;
}

