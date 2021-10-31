#include<bits/stdc++.h>

using namespace std;

const int N = 100010;
int n, m, t_def, t_max, t_min;
string h;

struct IP{
	int state; // 0:未分配， 1: 待分配， 2: 占用，3: 过期
	int t;
	string owner;
} ip[N];

void update_ips_state(){
	for(int i = 1; i <= n; i++){
		ip[i].state = 0;
		ip[i].t = 0;
		ip[i].owner = "";
	}
}

int get_by_owner(string client){
	for(int i = 1; i <= n; i++){
		if(ip[i].owner == client)return i;
	}
	return 0;
}

int get_by_state(int st){
	for(int i = 1; i <= n; i++){
		if(ip[i].state == st)return i;
	}
	return 0;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> t_def >> t_max >> t_min >> h;
	cin >> m;
	while(m--){
		int tc;
		string client, server, type;
		int id, te;
		cin >> tc >> client >> server >> type >> id >> te;
		for(int i = 1; i <= n; i++){
			if(ip[i].state == 1 && ip[i].t <= tc){
				ip[i].state = 0;
				ip[i].owner = "";
				ip[i].t = 0;
			}
			if(ip[i].state == 2 && ip[i].t <= tc){
				ip[i].state = 3;
				ip[i].t = 0;
			}
		}
		if(server != h && server != "*"){
			if(type != "REQ")continue;
		}
		if(type != "DIS" && type != "REQ")continue;
		if(server == "*" && type != "DIS" || server == h && type == "DIS")continue;
		if(type == "DIS"){
			int k = get_by_owner(client);
			if(!k) k = get_by_state(0);
			if(!k) k = get_by_state(3);
			if(!k)continue;
			ip[k].state = 1; ip[k].owner = client;
			if(te == 0){
				ip[k].t = tc+t_def;
			}else{
				int t = te-tc;
				t = max(t, t_min), t = min(t, t_max);
				ip[k].t = tc+t;
			}
			cout << h << " " << client << " OFR " << k << " " << ip[k].t << endl;
 		}else{
			if(server != h){
				for(int i = 1; i <= n; i++){
					if(ip[i].owner == client){
						if(ip[i].state == 1){
							ip[i].state = 0;
							ip[i].owner = "";
							ip[i].t = 0;
						}
					}
				}
				continue;
			}
			if(!(id >= 1 && id <= n && ip[id].owner == client)){
				cout << h << " " << client << " NAK " << id << " " << 0 << endl;
				continue;
			}
			ip[id].state = 2;
			if(te == 0){
				ip[id].t = tc+t_def;
			}else{
				int t = te-tc;
				t = max(t, t_min), t = min(t, t_max);
				ip[id].t = tc+t;
			}
			cout << h << " " << client << " ACK " << id << " " << ip[id].t << endl;
 		}
	}
	return 0;
}
