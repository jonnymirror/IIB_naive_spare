#include <iostream>
#include <vector>
#include <intrin.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>  

using namespace std;

//定数開始
vector<vector<long long int>> G;//入力されるグラフ
long long int n;//頂点数
long long int m;//枝数
long long int k;//パラメータ(最終的に感染する頂点の数の最大値)
long long int l;//パラメータ(免疫を持たせる頂点の数の最大値)
vector<long long int> T;//関数
//定数終了
//最終的に感染する頂点を求める関数
long long int who_is_influenced(long long int bit) {
	long long int influenced = 0;//感染している頂点をbit1で表す
	for (long long int u = 0; u < n; u++) {
		if (!(bit & (static_cast<long long>(1) << u)) && T[u] == 0)influenced |= (static_cast<long long>(1) << u);
	}
	long long int before = -1;
	while (influenced != before) {
		before = influenced;
		for (long long int u = 0; u < n; u++) {
			if (bit & (static_cast<long long>(1) << u))continue;
			long long int count = 0;
			for (long long unsigned i = 0; i < G[u].size(); i++) {
				if (influenced & (static_cast<long long>(1) << G[u][i]))count++;
			}
			if (count >= T[u])influenced |= (static_cast<long long>(1) << u);
		}
	}
	return influenced;
}
//メイン関数

int main() {
	//入力開始
	ifstream ifs1("Zachary karate club.txt");

	if (!ifs1) {
		std::cout << "Error!";
		return 1;
	}

	string s;
	long long int count = 0;
	long long int x = 0;
	long long int y = 0;

	while (getline(ifs1, s, ' ')) {     // スペース（' '）で区切って，格納
		if (count == 0) {//頂点数
			n = stoll(s);
			G.resize(n);//グラフの大きさ確保
			count++;
		}
		else if (count == 1) {//枝数
			m = stoll(s);
			count++;
		}
		else if (count == 2) {//パラメータk
			k = stoll(s);
			count++;
		}
		else if (count == 3) {//パラメータl
			l = stoll(s);
			count++;
		}
		else if (count > 3 && count < 4 + 2 * m && count % 2 == 0) {//グラフの枝の端点
			x = stoll(s);
			x--;
			count++;
		}
		else if (count > 3 && count < 4 + 2 * m && count % 2 == 1) {//グラフの枝のもう一つの端点
			y = stoll(s);
			y--;
			count++;
			G[x].push_back(y);
			G[y].push_back(x);
		}
	}

	ifs1.close();

	ifstream ifs2("Zachary karate club threshold.txt");

	if (!ifs2) {
		std::cout << "Error!";
		return 1;
	}

	T.resize(n);
	count = 0;

	while (getline(ifs2, s, ' ')) {//頂点の閾値
		x = stoll(s);
		T[count] = x;
		count++;
	}

	ifs2.close();
	//入力終了

	/*
	cout << "頂点数:" << n << endl;
	cout << "枝数:" << m << endl;
	cout << "k:" << k << endl;
	cout << "l:" << l << endl;
	long long int edge_number = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < G[i].size(); j++) {
			cout << "枝" << edge_number + 1 << "本目:" << i << " " << G[i][j] << endl;
			edge_number++;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << "i: " << i << endl;
		cout << T[i] << endl;
	}

	cout << endl;
	*/
	clock_t start = clock();    //時間測定開始

	long long int checker;//bit確認用.

	//bit全探索開始
	//1が立っている頂点は免疫がついているとする
	for (long long int bit = 0; bit < (static_cast<long long>(1) << n); bit++) {
		//cout <<"bit:" << bit << endl;
		checker = bit;
		long long int influenced;
		clock_t now = clock();
		if ((double)(now - start) / CLOCKS_PER_SEC >= 3600) {
			cout << (double)(now - start) / CLOCKS_PER_SEC << "sec.\n";
			cout << "Timeout!" << endl;
			return 0;
		}
		if (__popcnt64(bit) > l)continue;//免疫がついている頂点の数がl以上の場合,スキップする.
		influenced = who_is_influenced(bit);
		if (__popcnt64(influenced) <= k) {
			cout << "influenced:" << influenced << endl;
			cout << "YES" << endl;
			clock_t Yesend = clock();     // 時間測定終了
			cout << "duration = " << (double)(Yesend - start) / CLOCKS_PER_SEC << "sec.\n";
			return 0;
		}
	}
	cout << "checker:" << checker << endl;
	cout << "No" << endl;

	clock_t Noend = clock();     // 時間測定終了
	cout << "duration = " << (double)(Noend - start) / CLOCKS_PER_SEC << "sec.\n";

	return 0;
}