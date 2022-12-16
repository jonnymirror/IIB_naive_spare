#include <iostream>
#include <vector>
#include <intrin.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>  

using namespace std;

//�萔�J�n
vector<vector<long long int>> G;//���͂����O���t
long long int n;//���_��
long long int m;//�}��
long long int k;//�p�����[�^(�ŏI�I�Ɋ������钸�_�̐��̍ő�l)
long long int l;//�p�����[�^(�Ɖu���������钸�_�̐��̍ő�l)
vector<long long int> T;//�֐�
//�萔�I��
//�ŏI�I�Ɋ������钸�_�����߂�֐�
long long int who_is_influenced(long long int bit) {
	long long int influenced = 0;//�������Ă��钸�_��bit1�ŕ\��
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
//���C���֐�

int main() {
	//���͊J�n
	ifstream ifs1("Zachary karate club.txt");

	if (!ifs1) {
		std::cout << "Error!";
		return 1;
	}

	string s;
	long long int count = 0;
	long long int x = 0;
	long long int y = 0;

	while (getline(ifs1, s, ' ')) {     // �X�y�[�X�i' '�j�ŋ�؂��āC�i�[
		if (count == 0) {//���_��
			n = stoll(s);
			G.resize(n);//�O���t�̑傫���m��
			count++;
		}
		else if (count == 1) {//�}��
			m = stoll(s);
			count++;
		}
		else if (count == 2) {//�p�����[�^k
			k = stoll(s);
			count++;
		}
		else if (count == 3) {//�p�����[�^l
			l = stoll(s);
			count++;
		}
		else if (count > 3 && count < 4 + 2 * m && count % 2 == 0) {//�O���t�̎}�̒[�_
			x = stoll(s);
			x--;
			count++;
		}
		else if (count > 3 && count < 4 + 2 * m && count % 2 == 1) {//�O���t�̎}�̂�����̒[�_
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

	while (getline(ifs2, s, ' ')) {//���_��臒l
		x = stoll(s);
		T[count] = x;
		count++;
	}

	ifs2.close();
	//���͏I��

	/*
	cout << "���_��:" << n << endl;
	cout << "�}��:" << m << endl;
	cout << "k:" << k << endl;
	cout << "l:" << l << endl;
	long long int edge_number = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < G[i].size(); j++) {
			cout << "�}" << edge_number + 1 << "�{��:" << i << " " << G[i][j] << endl;
			edge_number++;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << "i: " << i << endl;
		cout << T[i] << endl;
	}

	cout << endl;
	*/
	clock_t start = clock();    //���ԑ���J�n

	long long int checker;//bit�m�F�p.

	//bit�S�T���J�n
	//1�������Ă��钸�_�͖Ɖu�����Ă���Ƃ���
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
		if (__popcnt64(bit) > l)continue;//�Ɖu�����Ă��钸�_�̐���l�ȏ�̏ꍇ,�X�L�b�v����.
		influenced = who_is_influenced(bit);
		if (__popcnt64(influenced) <= k) {
			cout << "influenced:" << influenced << endl;
			cout << "YES" << endl;
			clock_t Yesend = clock();     // ���ԑ���I��
			cout << "duration = " << (double)(Yesend - start) / CLOCKS_PER_SEC << "sec.\n";
			return 0;
		}
	}
	cout << "checker:" << checker << endl;
	cout << "No" << endl;

	clock_t Noend = clock();     // ���ԑ���I��
	cout << "duration = " << (double)(Noend - start) / CLOCKS_PER_SEC << "sec.\n";

	return 0;
}