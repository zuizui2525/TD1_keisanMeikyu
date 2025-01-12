#include "structure.h"

int stage0(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,2,2,2,2,2,2,2,2},//2
	{2,2,2,2,2,2,2,2,2},//3
	{2,2,2,2,2,2,2,2,2},//4
	{2,2,2,2,2,2,2,2,2},//5
	{2,2,2,2,2,2,2,2,2},//6
	{2,2,2,2,2,2,2,2,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage1(int y ,int x){
	int stage1[9][9] = {
	{2,2,1,1,1,1,2,2,2},//1
	{2,2,1,0,0,1,2,2,2},//2
	{2,2,1,0,0,1,2,2,2},//3
	{2,2,1,0,0,1,2,2,2},//4
	{2,2,1,0,0,1,2,2,2},//5
	{2,2,1,0,0,1,2,2,2},//6
	{2,2,1,0,0,1,2,2,2},//7
	{2,2,1,0,0,1,2,2,2},//8
	{2,2,1,1,1,1,2,2,2}//9
	};
	return stage1[y][x];
}

int stage2(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,2,2,2,2,2,2,2,2},//2
	{1,1,1,1,1,1,1,1,2},//3
	{1,0,0,1,0,0,0,1,2},//4
	{1,0,0,0,0,0,0,1,2},//5
	{1,0,0,0,0,0,0,1,2},//6
	{1,1,1,1,1,1,1,1,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage3(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,1,1,1,1,1,2,2,2},//2
	{2,1,0,0,0,1,1,2,2},//3
	{2,1,0,0,0,0,1,2,2},//4
	{2,1,0,1,0,0,1,2,2},//5
	{2,1,0,0,0,0,1,2,2},//6
	{2,1,1,1,1,1,1,2,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage4(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,1,1,1,1,1,2,2,2},//2
	{2,1,0,0,0,1,2,2,2},//3
	{2,1,0,0,0,1,1,2,2},//4
	{2,1,0,0,0,0,1,2,2},//5
	{2,1,1,0,0,0,1,2,2},//6
	{2,2,1,1,1,1,1,2,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage5(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,1,1,1,1,1,1,2,2},//2
	{2,1,0,0,1,0,1,2,2},//3
	{2,1,0,0,0,0,1,2,2},//4
	{2,1,0,1,0,0,1,2,2},//5
	{2,1,0,0,0,1,1,2,2},//6
	{2,1,1,1,1,1,2,2,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage6(int y, int x) {
	int stage1[9][9] = {
	{2,2,1,1,1,1,1,2,2},//1
	{2,2,1,0,0,0,1,2,2},//2
	{2,2,1,0,0,0,1,2,2},//3
	{2,2,1,0,0,0,1,2,2},//4
	{2,2,1,1,0,1,1,2,2},//5
	{2,2,1,0,0,0,1,2,2},//6
	{2,2,1,0,0,0,1,2,2},//7
	{2,2,1,0,0,0,1,2,2},//8
	{2,2,1,1,1,1,1,2,2}//9
	};
	return stage1[y][x];
}

int stage7(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,2,1,1,1,1,1,2,2},//2
	{2,1,1,0,0,0,1,2,2},//3
	{2,1,0,0,1,0,1,1,2},//4
	{2,1,0,0,0,0,0,1,2},//5
	{2,1,0,0,0,0,0,1,2},//6
	{2,1,1,1,1,1,1,1,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage8(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,2,2,2,2,2,2,2,2},//2
	{2,1,1,1,1,1,1,1,2},//3
	{1,1,0,0,0,0,0,1,2},//4
	{1,0,0,0,0,0,0,1,2},//5
	{1,0,0,0,1,1,1,1,2},//6
	{1,1,1,1,1,2,2,2,2},//7
	{2,2,2,2,2,2,2,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage9(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{1,1,1,1,1,1,1,2,2},//2
	{1,0,0,1,0,0,1,2,2},//3
	{1,0,0,0,0,0,1,1,2},//4
	{1,0,0,0,0,0,0,1,2},//5
	{1,0,0,0,1,0,0,1,2},//6
	{1,1,1,1,1,0,0,1,2},//7
	{2,2,2,2,1,1,1,1,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

int stage10(int y, int x) {
	int stage1[9][9] = {
	{2,2,2,2,2,2,2,2,2},//1
	{2,2,2,1,1,1,1,2,2},//2
	{2,1,1,1,0,0,1,2,2},//3
	{2,1,0,0,0,0,1,2,2},//4
	{2,1,0,1,0,0,1,2,2},//5
	{2,1,0,0,0,0,1,2,2},//6
	{2,1,1,1,0,0,1,2,2},//7
	{2,2,2,1,1,1,1,2,2},//8
	{2,2,2,2,2,2,2,2,2}//9
	};
	return stage1[y][x];
}

