#include<bits/stdc++.h>

#define DIM_Y 25
#define DIM_X 26

using namespace std;

typedef pair<int,int> pii;
typedef vector<pii> vpii;

char image[DIM_Y][DIM_X];
int visit_status[DIM_Y][DIM_X];
int dimension;

void dfs(pii & p)
{
	vpii adjs;
	visit_status[p.first][p.second] = 1;

	int y[] = {-1,-1,-1,0,1,1,1,0};
	int x[] = {-1,0,1,1,1,0,-1,-1};
	for (int i=0; i< 8; ++i)
	{
		int ny = p.first + y[i];
		int nx = p.second + x[i];  		
		if (ny>=0 && ny<dimension && nx >=0 && nx<dimension && image[ny][nx] == '1')
		{
			pii ad = make_pair(ny, nx);
			adjs.push_back(ad);
		}
	}

	while(!adjs.empty()) {
		pii current_v = adjs.back(); adjs.pop_back();
		
		int vx = current_v.first;
		int vy = current_v.second;
		
		
		if(!visit_status[vx][vy]) {
			dfs(current_v);
		}
	}
}

void printVisited() {
	for(int k=0;k<dimension;k++) {
		for(int l=0;l<dimension;l++) {
			cout << visit_status[k][l] << " ";
		}
		cout << endl;
	}
}

int main() {
	int cnt, k, l, tc=1;
	
	while ( cin >> dimension ) {
		cnt = 0;
		
		for(k=0;k<dimension;++k)
            for(l=0;l<dimension;++l)
				visit_status[k][l] = 0;
		
        for(k=0;k<dimension;++k)
           cin >> image[k];	
		
        for(k=0;k<dimension;k++)
            for(l=0;l<dimension;l++)
                if(image[k][l]=='1' && !visit_status[k][l])
                    {
                        ++cnt;
						pii current_v = make_pair(k, l);
                        dfs(current_v);
                    }
		//printVisited();

        cout<<"Image number "<<tc<<" contains "<<cnt<<" war eagles."<<endl;
		tc++;
	}
	return 0;
}
