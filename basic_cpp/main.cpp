#include "common.h"
#include "funcPart_00_09.h"
#include "funcPart_10_19.h"
#include "funcPart_20_29.h"
#include "funcPart_30_39.h"
#include "funcPart_40_49.h"
#include "funcPart_50_59.h"
#include "funcPart_60_69.h"
#include "funcPart_70_79.h"
#include "funcPart_80_89.h"
#include "funcPart_90_99.h"


void doAllFuncPart(void (**f)(), int count)
{
	for (int i = 0; i < count; ++i)
	{
		f[i]();
	}
}


int main(int argc, char* argv[]) {

	/*函數時間測量代碼*/
	auto start_time = std::chrono::high_resolution_clock::now();

	/*執行所有函數代碼*/
	void (*funcPart[])() = {
		funcPart00, funcPart01, funcPart02, funcPart03, funcPart04, funcPart05, funcPart06, funcPart07, funcPart08, funcPart09, 
		funcPart10, funcPart11, funcPart12, funcPart13, funcPart14, funcPart15, funcPart16, funcPart17, funcPart18, funcPart19,
		funcPart20, funcPart21, funcPart22, funcPart23, funcPart24, funcPart25, funcPart26, funcPart27, funcPart28, funcPart29,
		funcPart30, funcPart31, funcPart32, funcPart33, funcPart34, funcPart35, funcPart36, funcPart37, funcPart38, funcPart39,
		funcPart40, funcPart41, funcPart42, funcPart43, funcPart44, funcPart45, funcPart46, funcPart47, funcPart48, funcPart49,
		funcPart50, funcPart51, funcPart52, funcPart53, funcPart54, funcPart55, funcPart56, funcPart57, funcPart58, funcPart59,
		funcPart60, funcPart61, funcPart62, funcPart63, funcPart64, funcPart65, funcPart66, funcPart67, funcPart68, funcPart69,
		funcPart70, funcPart71, funcPart72, funcPart73, funcPart74, funcPart75, funcPart76, funcPart77, funcPart78, funcPart79,
		funcPart80, funcPart81, funcPart82, funcPart83, funcPart84, funcPart85, funcPart86, funcPart87, funcPart88, funcPart89,
		funcPart90, funcPart91, funcPart92, funcPart93, funcPart94, funcPart95, funcPart96, funcPart97, funcPart98, funcPart99,
	};
	int funcCount = sizeof(funcPart) / sizeof(funcPart[0]);
	doAllFuncPart(funcPart, funcCount);


	/*函數時間測量代碼*/
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "\nTime taken at Total : " << duration.count() / 1000.0 << " milliseconds" << std::endl;

	return 0;
}