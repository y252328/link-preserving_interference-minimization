// LinkPreservingInterferenceMinimization.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <memory>

#include "Mesh.h"
#include "Station.h"

using namespace std;

int main()
{
	auto mesh = Mesh(6);
	for( int i = 0 ; i < 5 ; ++ i )
		mesh.add_station(make_shared<Station>(3, 6, 10));

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
	auto y = mesh.stations[2]->best_response();
	y = mesh.stations[2]->best_response();

    std::cout << "Hello World!\n"; 
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
