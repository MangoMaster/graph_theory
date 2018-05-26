#include <cstdlib>
#include<iostream>
#include <iomanip>
#include<cstring>
#include<queue>
#define INTM 2147483647
using namespace std;

class sets{
	int n;
	int num[300][300];
	int matches[300];
	int price[300];
	int edge[302][302];
public:
	sets();
	~sets(){}
	void MATCH();
	bool match(int index, int *y);
	void convert();
	int ff();
	int search(int *path);
	void print();
};

sets::sets(){
	cin >> n;
	memset(num, 0, sizeof(num));
	for(int i = 0; i < n; i++){
		int pot;
		cin >> pot;
		for(int j = 0; j < pot; j++){
			int tmp;
			cin >> tmp;
			tmp--;
			num[i][tmp] = 1; 
		} 
	}
	for(int i = 0; i < n; i++){
		cin >> price[i];
		price[i] = -price[i];
	}
	memset(matches, -1, sizeof(matches));
	memset(edge, 0, sizeof(edge));
}

void sets::MATCH(){
	int y[300];
	for(int i = 0; i < n; i++){
		memset(y, 0, sizeof(y));
		match(i, y);
	}
}

bool sets::match(int index, int *y){
	if(index == -1) return true;
	for(int i = 0; i < n; i++)
		if(num[index][i] && !y[i]){
			y[i] = 1;
			if(matches[i] == -1 || match(matches[i], y)){
				matches[i] = index;
				return true;
			}
		}
	return false;
}

void sets::convert(){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(num[i][j]){
				if(price[i] < 0) edge[i + 1][n + 1] = -price[i];
				else if(price[i] > 0) edge[0][i + 1] = price[i];
				if(matches[j] != i) edge[i + 1][matches[j] + 1] = INTM;
			}
}

int sets::ff(){
	int path[302];
	memset(path, -1, sizeof(path));
	int sum = 0, sum2 = 0;
	for(int i = 0; i < n; i++)
		if(price[i] > 0) sum += price[i];
	for (int i = 0; i < n; ++i)
		if (price[i] < 0) sum2 -= price[i];
	int flow, maxflow = 0;
	while((flow = search(path)) != -1){
		maxflow += flow;
		int now = n + 1, pre = path[now];
		while(now){
			edge[pre][now] -= flow;
			edge[now][pre] += flow;
			now = pre, pre = path[now];
		}
		memset(path, -1, sizeof(path));
	}
	cout << maxflow << endl;
	cout << sum << endl;
	cout << sum2 << endl;
	cout << maxflow - sum;
}

int sets::search(int *path){
	int flow[302] = {INTM};
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int index = q.front();
		q.pop();
		if(index == n + 1) break;
		for(int i = 1; i <= n + 1; i++){
			if(!edge[index][i] || path[i] != -1) continue;
			flow[i] = flow[index] < edge[index][i] ? flow[index] : edge[index][i];
			path[i] = index;
			q.push(i);
		}
	}
	if(path[n + 1] == -1) return -1;
	return flow[n + 1];
}

void sets::print()
{
	for (int i = 0; i < 300; ++i)
		cout << i << "  " << matches[i] << endl;
	cout << endl;
	/*for (int i = 0; i < 302; ++i)
	{
		for (int j = 0; j < 302; ++j)
			cout << setw(10) << edge[i][j] << "  ";
		cout << endl;
	}*/	
}

int main(){
	freopen("input4.txt", "r", stdin);
	freopen("outputcjw.txt", "w", stdout);
	sets s;
	s.MATCH();
	s.convert();
	s.print();
	s.ff();
	return 0;
}
