#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

const int size_x = 5;
const int size_y = 5;
const int mini_size = 5;

void find(int posx, int posy, int sx, int ex, int sy, int ey, vector<string> &board)
{
	int minx;
	int miny;
	int mindis = 1e6;;
	for(int i=sx; i<ex; i++)
		for(int j=sy; j<ey; j++)
		{
			if( board[i][j] != 'd' )
				continue;
			if( abs(posx - i) + abs(posy - j) < mindis )
			{
				mindis = abs(posx - i) + abs(posy - j);
				minx = i;
				miny = j;
			}
		}
	
	if( miny > posy )
	{
		cout << "RIGHT" << endl;
	}
	else if( miny < posy )
	{
		cout << "LEFT" << endl;
	}
	else if( minx > posx )
	{
		cout << "DOWN" << endl;
	}
	else
	{
		cout << "UP" << endl;
	}
	
}

void next_mini(int &mini_x, int &mini_y)
{
	if( mini_x % 2 == 0 )
	{
		if( mini_y != (size_y-1) / mini_size )
			mini_y ++;
		else
			mini_x ++;
	}
	else
	{
		if( mini_y != 0 )
			mini_y --;
		else
			mini_x ++;
	}
	if( mini_x > (size_x-1) / mini_size )
	{
		mini_x = 0;
		mini_y = 0;
	}
}

/* Head ends here */
void next_move(int posx, int posy, vector <string> &board) {
    //add logic here
	if( board[posx][posy] == 'd')
	{
		cout << "CLEAN" << endl;
		return;
	}
	int mini_x = posx / mini_size;
	int mini_y = posy / mini_size;
	int sx;
	int sy;
	int ex;
	int ey;
	
	bool flag = false;
	while( flag == false)
	{
		sx = mini_x * mini_size;
		sy = mini_y * mini_size;
		ex = (mini_x+1) * mini_size < size_x-1 ? (mini_x+1) * mini_size : size_x;
		ey = (mini_y+1) * mini_size < size_y-1 ? (mini_y+1) * mini_size : size_y;
		for(int i=sx; i<ex; i++)
			for(int j=sy; j<ey; j++)
			{
				if( board[i][j] == 'd')
					flag = true;
			}
		if( flag == true )
		{
			break;
		}
		next_mini(mini_x, mini_y);
	}
	
	find(posx, posy, sx, ex, sy, ey, board);
}

/* Tail starts here */
int main() {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
    return 0;
}