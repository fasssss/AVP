#include<iostream>
#include<chrono>
#include "xmmintrin.h"

#define WIDS 4096                                 // was 64
#define HEIGHT 4096                               // was 64
using namespace std;
void manualOptim();
void withoutVec();
int main()
{
//#pragma clang loop vectorize(disable)
	chrono::high_resolution_clock clk1, clk2;
	chrono::duration<float> dur;
	chrono::high_resolution_clock::time_point start, end;
	float timeAccum = 0;
	float* matrix1 = new float[WIDS * HEIGHT];
	float* matrix2 = new float[WIDS * HEIGHT];
	float* matrixRes = new float[WIDS * HEIGHT];
	for (float i = 0; i < WIDS * HEIGHT; i++)
	{
		matrix1[(int)i] = i;
		matrix2[(int)i] = i;
	}

	int i = 0;
	int col = 0;
	int colStep = 0;
	float vector1[8], vector2[8];
	float particles[8];
	for (; i < WIDS * HEIGHT / 8; i++)
	{
		for (int k = i * 8; k < i * 8 + 8; k++)
		{
			float cell = 0;
			for (int j = col + colStep, l = i * 8, m = 0; j < WIDS * 8; j += WIDS, l++, m++)
			{
				vector1[m] = matrix1[l];
				vector2[m] = matrix2[j];
			}
//#pragma loop(no_vector)
			start = clk1.now();
			for (int j = 0; j < 8; j++)
			{
				particles[j] = vector1[j] * vector2[j];
			}

			for (int j = 0; j < 8; j++)
			{
				cell += particles[j];
			}

			end = clk2.now();
			dur = chrono::duration_cast<chrono::duration<float>>(end - start);
			timeAccum += dur.count();
			matrixRes[k] = cell;
			if ((i % (WIDS * 8) == 0) && i != 0)
			{
				col += (WIDS * 8);
			}

			colStep++;
			if (colStep >= WIDS)
			{
				colStep = 0;
			}
		}
	}

	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix1[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix2[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrixRes[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	std::cout << endl;
	std::cout << timeAccum << "sec";
	std::system("pause");
	manualOptim();
	withoutVec();
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrixRes;
	return 0;
}

void withoutVec()
{
	chrono::high_resolution_clock clk1, clk2;
	chrono::duration<float> dur;
	chrono::high_resolution_clock::time_point start, end;
	float timeAccum = 0;
	float* matrix1 = new float[WIDS * HEIGHT];
	float* matrix2 = new float[WIDS * HEIGHT];
	float* matrixRes = new float[WIDS * HEIGHT];
	for (float i = 0; i < WIDS * HEIGHT; i++)
	{
		matrix1[(int)i] = i;
		matrix2[(int)i] = i;
	}

	int i = 0;
	int col = 0;
	int colStep = 0;
	float vector1[8], vector2[8];
	for (; i < WIDS * HEIGHT / 8; i++)
	{
		for (int k = i * 8; k < i * 8 + 8; k++)
		{
			float cell = 0;
			for (int j = col + colStep, l = i * 8, m = 0; j < WIDS * 8; j += WIDS, l++, m++)
			{
				vector1[m] = matrix1[l];
				vector2[m] = matrix2[j];
			}
			//#pragma loop(no_vector)
			start = clk1.now();
			for (int j = 0; j < 8; j++)
			{
				cell += vector1[j] * vector2[j];
			}

			//for (int j = 0; j < 8; j++)
			//{
			//	cell += particles[j];
			//}

			end = clk2.now();
			dur = chrono::duration_cast<chrono::duration<float>>(end - start);
			timeAccum += dur.count();
			matrixRes[k] = cell;
			if ((i % (WIDS * 8) == 0) && i != 0)
			{
				col += (WIDS * 8);
			}

			colStep++;
			if (colStep >= WIDS)
			{
				colStep = 0;
			}
		}
	}

	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix1[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix2[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrixRes[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	std::cout << endl;
	std::cout << timeAccum << "sec withoutVec";
	std::system("pause");
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrixRes;
}

void manualOptim()
{
	chrono::high_resolution_clock clk1, clk2;
	chrono::duration<float> dur;
	chrono::high_resolution_clock::time_point start, end;
	float timeAccum = 0;
	float* matrix1 = new float[WIDS * HEIGHT];
	float* matrix2 = new float[WIDS * HEIGHT];
	float* matrixRes = new float[WIDS * HEIGHT];
	for (float i = 0; i < WIDS * HEIGHT; i++)
	{
		matrix1[(int)i] = i;
		matrix2[(int)i] = i;
	}

	int i = 0;
	int col = 0;
	int colStep = 0;
	float* vector1 = new float[8], *vector2 = new float[8];
	float* particles = new float[8];
	for (; i < WIDS * HEIGHT / 8; i++)
	{
		for (int k = i * 8; k < i * 8 + 8; k++)
		{
			float cell = 0;
			for (int j = col + colStep, l = i * 8, m = 0; j < WIDS * 8; j += WIDS, l++, m++)
			{
				vector1[m] = matrix1[l];
				vector2[m] = matrix2[j];
			}

			start = clk1.now();
			//for (int j = 0; j < 2; j++)
			//{
			//	_asm
			//	{
			//		pusha
			//		mov eax, dword ptr[vector1]
			//		movups xmm0, xmmword PTR[eax]
			//		mov eax, dword ptr[vector2]
			//		movups xmm1, xmmword ptr[eax]
			//		mulps xmm0, xmm1
			//		haddps xmm0, xmm0
			//		haddps xmm0, xmm0
			//		movd cell, xmm0
			//		popa
			//	}
			//	temp += cell;
			//}

			_asm
			{
				pusha
				mov eax, dword ptr[vector1]
				vmovups ymm0, ymmword ptr [eax]
				mov eax, dword ptr[vector2]
				vmovups ymm1, ymmword ptr[eax]
				vmulps  ymm3, ymm0, ymm1
				vhaddps ymm3, ymm3, ymm3
				vhaddps ymm3, ymm3, ymm3
				vextracti128 xmm1, ymm3, 1
				addps xmm3, xmm1
				movd cell, xmm3
				popa
			}

			//__m128 reg0;
			//__m128 reg1;
			//__m128 reg2;
			//float* resultRow = new float[8];
			//for (int j = 0; j < 8; j += 4)
			//{
			//	reg1 = _mm_load_ps(vector1 + j);
			//	reg2 = _mm_load_ps(vector2 + j);
			//	reg0 = _mm_mul_ps(reg1, reg2);
			//	_mm_store_ps(resultRow + j , reg0);
			//}

			end = clk2.now();
			dur = chrono::duration_cast<chrono::duration<float>>(end - start);
			timeAccum += dur.count();
			matrixRes[k] = cell;
			if ((i % (WIDS * 8) == 0) && i != 0)
			{
				col += (WIDS * 8);
			}

			colStep++;
			if (colStep >= WIDS)
			{
				colStep = 0;
			}
		}
	}

	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix1[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrix2[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	//std::cout << endl;
	//for (float j = 0; j < WIDS; j++)
	//{
	//	for (float i = 0; i < WIDS; i++)
	//	{
	//		std::cout << (int)matrixRes[((int)j * WIDS) + (int)i] << " ";
	//	}

	//	std::cout << endl;
	//}

	std::cout << endl;
	std::cout << timeAccum << "sec \"manual\"\n";
	std::system("pause");
	delete[] vector1;
	delete[] vector2;
	delete[] particles;
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrixRes;
}