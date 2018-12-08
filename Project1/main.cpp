#include "ReadLas.h"
#include "ReadTrj.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{

	ReadLas las;
	las.filename = "A01";
	//Read Public Header Block
	las.read_Header();
	//display Public Header Block
	las.out_Header();
	//read in variable length records
	las.read_var_Length_Record();
	//dispaly variable length records
	las.out_var_Length_Record();
	//read in point data record
	las.read_Point_Data_Record();
	//write point data to txt
	string outname = "A01.txt";
	las.output_PointData(outname);


	system("pause");
	return 0;
}
