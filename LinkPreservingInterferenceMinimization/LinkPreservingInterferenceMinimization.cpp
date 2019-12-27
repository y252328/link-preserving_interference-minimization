// LinkPreservingInterferenceMinimization.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <memory>
#include <random>
#include <chrono>

#include "Mesh.h"
#include "Station.h"

using namespace std;

void my() {
	auto mesh = Mesh();
	for (int i = 0; i < 5; ++i)
		mesh.create_station(3, 7, 5);

	mesh.add_neighbour(1, 2);
	mesh.add_neighbour(1, 3);
	mesh.add_neighbour(1, 2);
	mesh.add_neighbour(1, 4);

	mesh.add_neighbour(2, 1);
	mesh.add_neighbour(2, 3);
	mesh.add_neighbour(2, 5);

	mesh.add_neighbour(3, 1);
	mesh.add_neighbour(3, 4);
	mesh.add_neighbour(3, 2);
	mesh.add_neighbour(3, 5);

	mesh.add_neighbour(4, 1);
	mesh.add_neighbour(4, 3);
	mesh.add_neighbour(4, 5);

	mesh.add_neighbour(5, 2);
	mesh.add_neighbour(5, 3);
	mesh.add_neighbour(5, 4);

	mesh.init_channel();
	mesh.find_nash();
	mesh.print_status();
	std::cout << "phi: " << mesh.potential() << endl;

}

void paper() {
	auto mesh = Mesh();
	for (int i = 0; i < 5; ++i)
		mesh.create_station(3, 7, 5);

	mesh.add_neighbour(1, 2);
	mesh.add_neighbour(1, 3);
	mesh.add_neighbour(1, 2);
	mesh.add_neighbour(1, 4);

	mesh.add_neighbour(2, 1);
	mesh.add_neighbour(2, 3);
	mesh.add_neighbour(2, 5);

	mesh.add_neighbour(3, 1);
	mesh.add_neighbour(3, 4);
	mesh.add_neighbour(3, 2);
	mesh.add_neighbour(3, 5);

	mesh.add_neighbour(4, 1);
	mesh.add_neighbour(4, 3);
	mesh.add_neighbour(4, 5);

	mesh.add_neighbour(5, 2);
	mesh.add_neighbour(5, 3);
	mesh.add_neighbour(5, 4);

	mesh.stations[0]->assign_channel({ 2, 5, 7 });
	mesh.stations[1]->assign_channel({ 1, 2, 3 });
	mesh.stations[2]->assign_channel({ 1, 4, 5 });
	mesh.stations[3]->assign_channel({ 2, 4, 6 });
	mesh.stations[4]->assign_channel({ 3, 5, 6 });

	//mesh.find_nash();
	mesh.print_status();
	std::cout << "phi: " << mesh.potential() << endl;
	cout << "=== find nash ===" << endl;

	mesh.find_nash();
	mesh.print_status();
	std::cout << "phi: " << mesh.potential() << endl;
}

int main()
{
	constexpr int r_max = 3;
	constexpr int c_max = 9;
	constexpr int beta = 25;
	constexpr int node = 15;
	constexpr double range = 200;
	constexpr double x_rang = 1000;
	constexpr double y_rang = 1000;
	std::random_device rd;
	//std::default_random_engine generator(rd());
	std::default_random_engine generator(0);
	std::uniform_real_distribution<double> x_unif(0.0, x_rang);
	std::uniform_real_distribution<double> y_unif(0.0, y_rang);
	auto mesh = Mesh();
	for (int i = 0; i < node; ++i) {
		mesh.create_station(r_max, c_max, beta, x_unif(generator), y_unif(generator));
	}
	mesh.auto_connect(range);
	mesh.init_channel();
	auto t1 = std::chrono::steady_clock::now();
	mesh.find_nash();
	auto t2 = std::chrono::steady_clock::now();
	auto phi = mesh.potential();

	cout << phi << endl;
	cout << std::chrono::duration_cast<chrono::milliseconds>(t2-t1).count()/1000.0 << " s" << endl;
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
