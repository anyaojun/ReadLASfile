/*
* 读取LAS文件
% LAS格式参考Las Specification Version 1.2
% $Revision: 1.0
% $Date: 2017/10/28
% $Author: 药菌
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//file Public Header Block
struct public_Header_Block
{
	char file_signature[4];
	unsigned short file_source_id;
	unsigned short global_encoding;

	unsigned long project_id_guid_data1;
	unsigned short project_id_guid_data2;
	unsigned short project_id_guid_data3;
	unsigned char project_id_guid_data4[8];

	unsigned char version_major;
	unsigned char version_minor;

	char systemID[32];
	char generatingSoftware[32];
	unsigned short fileCreationDay;
	unsigned short fileCreationYear;
	unsigned short headerSize;
	unsigned long  pointDataOffset;
	unsigned long  numberOfVariableRecords;
	unsigned char  pointDataFormatID;
	unsigned short pointDataRecordLength;
	unsigned long  numberOfPointRecords;
	unsigned long  numberOfPointsByReturn[5];

	double x_scale;
	double y_scale;
	double z_scale;

	double x_offset;
	double y_offset;
	double z_offset;

	double x_max;
	double x_min;
	double y_max;
	double y_min;
	double z_max;
	double z_min;
};

//variable length records
struct variable_Length_Record_Header
{
	unsigned short  reserved;
	char  user_ID[16];
	unsigned short record_ID;
	unsigned short record_Length_After_Header;
	char  description[32];

};

//point_Data_Record(case 1： 28 bytes)
struct point_Data_Record
{
	long x;
	long y;
	long z;
	unsigned short intensity;
	unsigned char return_Number;//返回相关
	unsigned char classification;//分类相关
	unsigned char scanAngleRank;
	unsigned char userData;
	unsigned short pointSourceID;

	double time; //GPS Time
	unsigned short r;
	unsigned short g;
	unsigned short b;
};



class ReadLas 
{
public:
	void read_Header();
	void out_Header();
	void read_var_Length_Record();
	void out_var_Length_Record();
	void read_Point_Data_Record();
	void output_PointData(string outname);


	public_Header_Block  header;
	vector<variable_Length_Record_Header> variableRecord;
	vector<point_Data_Record>    pointdataRecord;
	string filename;
};