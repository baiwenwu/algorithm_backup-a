#include"baseLib.h"
#include<time.h>
#include <bitset>
typedef unsigned int u32;
typedef unsigned char uchar;
typedef unsigned short u16;
/*
* run the programm for BitMap used 13 ms,but the BitMap can accelerate the decompression.
*/
static u32 BitMap[65535] = { 0 };
static void CreateBitMap()
{
	u16 R1 = 0,//大头的数字
		R2 = 0,//可解码个数
		R3 = 0,//偏移量
		R4 = 0;//有效解码位数,暂且不用
	u16 mask = -1;
	u32 tmp = -1;
	//cout << bitset<32>(tmp) << endl;
	for (u32 i = (1ULL << 8); i<65536; i++)
	{
		R1 = R2 =0;
		int j = 15;
		int num0 = 0;
		while (j >= 0)
		{
			if (i&(1 << j))
			{
				j -= num0;
				if ( j>= 0)
				{
					
					//if (j+num0+num0==15)
					if (!R2)
						R1 = (i >> j)&((1 << num0+1) - 1);
					R2++;
					R3 = 16-j;
					num0 = 0;
				}
				else
					break;
				
			}
			else
			{
				num0++;
			}
			j--;
		}
		cout << i;
		cout<< "\t" << bitset<16>(i);
		cout << "   R4:" << R4;
		cout << "   R3:" << R3;
		cout << "   R2:" << R2;
		cout<< "   R1:" << R1;
		BitMap[i] += (R1 & 0xff);
		BitMap[i] = (BitMap[i] << 8) + (R2 & 0xff);
		BitMap[i] = (BitMap[i] << 8) + (R3 & 0xff);
		cout <<"  "<< BitMap[i] << endl;
	}
}
#if 1
int main()
{
	clock_t start = clock();
	CreateBitMap();
	clock_t end = clock();
	cout << end - start << endl;
	return 0;
}
#endif