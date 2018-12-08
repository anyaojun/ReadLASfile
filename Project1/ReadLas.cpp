#include "ReadLas.h"


//Read Public Header Block
void ReadLas::read_Header()
{
	string str = filename + ".las";
	//读取： 
	ifstream infname(str, ios::binary | ios::in);
    infname.seekg(0, ios::beg);

	infname.read((char*)header.file_signature, sizeof(header.file_signature));
	infname.read((char*)&header.file_source_id, sizeof(header.file_source_id));
	infname.read((char*)&header.global_encoding, sizeof(header.global_encoding));

	infname.read((char*)&header.project_id_guid_data1, sizeof(header.project_id_guid_data1));
	infname.read((char*)&header.project_id_guid_data2, sizeof(header.project_id_guid_data2));
	infname.read((char*)&header.project_id_guid_data3, sizeof(header.project_id_guid_data3));
	infname.read((char*)header.project_id_guid_data4, sizeof(header.project_id_guid_data4));
	string project_id_guid_data4 = (char*)header.project_id_guid_data4;

	infname.read((char*)&header.version_major, sizeof(header.version_major));
	infname.read((char*)&header.version_minor, sizeof(header.version_minor));

	infname.read((char*)header.systemID, sizeof(header.systemID));
	infname.read((char*)header.generatingSoftware, sizeof(header.generatingSoftware));
	infname.read((char*)&header.fileCreationDay, sizeof(header.fileCreationDay));
	infname.read((char*)&header.fileCreationYear, sizeof(header.fileCreationYear));
	infname.read((char*)&header.headerSize, sizeof(header.headerSize));
	infname.read((char*)&header.pointDataOffset, sizeof(header.pointDataOffset));
	infname.read((char*)&header.numberOfVariableRecords, sizeof(header.numberOfVariableRecords));
	infname.read((char*)&header.pointDataFormatID, sizeof(header.pointDataFormatID));
	infname.read((char*)&header.pointDataRecordLength, sizeof(header.pointDataRecordLength));
	infname.read((char*)&header.numberOfPointRecords, sizeof(header.numberOfPointRecords));
	infname.read((char*)header.numberOfPointsByReturn, sizeof(header.numberOfPointsByReturn));

	infname.read((char*)&header.x_scale, sizeof(header.x_scale));
	infname.read((char*)&header.y_scale, sizeof(header.y_scale));
	infname.read((char*)&header.z_scale, sizeof(header.z_scale));

	infname.read((char*)&header.x_offset, sizeof(header.x_offset));
	infname.read((char*)&header.y_offset, sizeof(header.y_offset));
	infname.read((char*)&header.z_offset, sizeof(header.z_offset));

	infname.read((char*)&header.x_max, sizeof(header.x_max));
	infname.read((char*)&header.x_min, sizeof(header.x_min));
	infname.read((char*)&header.y_max, sizeof(header.y_max));
	infname.read((char*)&header.y_min, sizeof(header.y_min));
	infname.read((char*)&header.z_max, sizeof(header.z_max));
	infname.read((char*)&header.z_min, sizeof(header.z_min));

}

//display Public Header Block
void ReadLas::out_Header()
{
	cout << "file_signature :" << header.file_signature << endl;
	cout << "file_source_id: " << header.file_source_id << endl;
	cout << "global_encoding: " << header.global_encoding << endl;

	cout << "project_id_guid_data1: " << header.project_id_guid_data1 << endl;
	cout << "project_id_guid_data2: " << header.project_id_guid_data2 << endl;
	cout << "project_id_guid_data3: " << header.project_id_guid_data3 << endl;
	cout << "project_id_guid_data4: " << (int)header.project_id_guid_data4 << endl;

	cout << "version_major: " << (int)header.version_major << endl;
	cout << "version_minor: " << (int)header.version_minor << endl;

	cout << "systemID: " << header.systemID << endl;
	cout << "generatingSoftware: " << header.generatingSoftware << endl;
	cout << "fileCreationDay: " << header.fileCreationDay << endl;
	cout << "fileCreationYear: " << header.fileCreationYear << endl;
	cout << "headerSize: " << header.headerSize << endl;
	cout << "pointDataOffset: " << header.pointDataOffset << endl;
	cout << "numberOfVariableRecords: " << header.numberOfVariableRecords << endl;
	cout << "pointDataFormatID: " << (int)header.pointDataFormatID << endl;
	cout << "pointDataRecordLength: " << header.pointDataRecordLength << endl;
	cout << "numberOfPointRecords: " << header.numberOfPointRecords << endl;
	cout << "numberOfPointsByReturn: " << header.numberOfPointsByReturn << endl;

	cout << "x_scale: " << header.x_scale << endl;
	cout << "y_scale: " << header.y_scale << endl;
	cout << "z_scale: " << header.z_scale << endl;

	cout << "x_offset: " << header.x_offset << endl;
	cout << "y_offset: " << header.y_offset << endl;
	cout << "z_offset: " << header.z_offset << endl;

	cout << "x_max: " << header.x_max << endl;
	cout << "x_min: " << header.x_min << endl;
	cout << "y_max: " << header.y_max << endl;
	cout << "y_min: " << header.y_min << endl;
	cout << "z_max: " << header.z_max << endl;
	cout << "z_min: " << header.z_min << endl;

}

//read in variable length records
void ReadLas::read_var_Length_Record()
{
	string str = filename + ".las";
	ifstream infname(str, ios::binary | ios::in);
	infname.seekg(header.headerSize, ios::beg);

	//vector<variable_Length_Record_Header> var_Length_Record;
	int num = header.numberOfVariableRecords;
	for (int i = 0; i < num; i++)
	{
		variable_Length_Record_Header  var_Len_Record;

		infname.read((char*)&var_Len_Record.reserved, sizeof(var_Len_Record.reserved));
		infname.read((char*)var_Len_Record.user_ID, sizeof(var_Len_Record.user_ID));
		infname.read((char*)&var_Len_Record.record_ID, sizeof(var_Len_Record.record_ID));
		infname.read((char*)&var_Len_Record.record_Length_After_Header, sizeof(var_Len_Record.record_Length_After_Header));
		infname.read((char*)var_Len_Record.description, sizeof(var_Len_Record.description));

		variableRecord.push_back(var_Len_Record);

		//指针从当前位置移动字节数
		infname.seekg(var_Len_Record.record_Length_After_Header, ios::cur);
	}

};

//dispaly variable length records
void ReadLas::out_var_Length_Record()
{
	for (int i = 0; i < variableRecord.size(); i++)
	{
		cout << "var_Length_Record.at(" << i << ").reserved : " << variableRecord.at(i).reserved << endl;
		cout << "var_Length_Record.at(" << i << ").user_ID  : " << variableRecord.at(i).user_ID << endl;
		cout << "var_Length_Record.at(" << i << ").record_ID : " << variableRecord.at(i).record_ID << endl;
		cout << "var_Length_Record.at(" << i << ").record_Length_After_Header : " << variableRecord.at(i).record_Length_After_Header << endl;
		cout << "var_Length_Record.at(" << i << ").description  : " << variableRecord.at(i).description << endl;
		cout << endl;
	}

}

void ReadLas::read_Point_Data_Record()
{
	int c = header.pointDataOffset;
	int n = header.numberOfPointRecords;
	int formatlength;

	switch (header.pointDataFormatID)
	{
	case 0:
		formatlength = 20;
		break;
	case 1:
		formatlength = 28;
		break;
	case 2:
		formatlength = 26;
		break;
	case 3:
		formatlength = 34;
		break;
	default:
		std::cout << "Data format not supported." << std::endl;
	}
	
	//start to read point data to Vector<point_Data_Record>
	string str = filename + ".las";
	ifstream infname(str, ios::binary | ios::in);
	infname.seekg(c + 0, ios::beg);//跳转指针到达点数据记录起始位置

	for (int j = 0; j < n; j++)
	{
		point_Data_Record point;
		//infname.seekg(c + 0, ios::beg);
		infname.read((char*)&point.x, sizeof(point.x));
		//infname.seekg(c + 4, ios::beg);
		infname.read((char*)&point.y, sizeof(point.y));
		//infname.seekg(c + 8, ios::beg);
		infname.read((char*)&point.z, sizeof(point.z));
		//infname.seekg(c + 12, ios::beg);
		infname.read((char*)&point.intensity, sizeof(point.intensity));
		//infname.seekg(c + 14, ios::beg);
		infname.read((char*)&point.return_Number, sizeof(point.return_Number));
		//infname.seekg(c + 15, ios::beg);
		infname.read((char*)&point.classification, sizeof(point.classification));
		//infname.seekg(c + 16, ios::beg);
		infname.read((char*)&point.scanAngleRank, sizeof(point.scanAngleRank));
		//infname.seekg(c + 17, ios::beg);
		infname.read((char*)&point.userData, sizeof(point.userData));
		//infname.seekg(c + 18, ios::beg);
		infname.read((char*)&point.pointSourceID, sizeof(point.pointSourceID));

		if (header.pointDataFormatID == 1)
		{
			//infname.seekg(c + 20, ios::beg);
			infname.read((char*)&point.time, sizeof(point.time));
		}


		if (header.pointDataFormatID == 2)
		{
			//infname.seekg(c + 20, ios::beg);
			infname.read((char*)&point.r, sizeof(point.r));
			infname.read((char*)&point.g, sizeof(point.g));
			infname.read((char*)&point.b, sizeof(point.b));

		}

		if (header.pointDataFormatID == 3)
		{
			//infname.seekg(c + 28, ios::beg);
			infname.read((char*)&point.r, sizeof(point.r));
			infname.read((char*)&point.g, sizeof(point.g));
			infname.read((char*)&point.b, sizeof(point.b));

		}
		//infname.read((char*)&point.temp, formatlength - 28 );
		pointdataRecord.push_back(point);

		/*if (j < 3)
		{
			cout << setprecision(12) << "x= " << (double)(point.x * header.x_scale) + header.x_offset << endl;
			cout << setprecision(12) << "y= " << (double)(point.y * header.y_scale) + header.y_offset << endl;
			cout << setprecision(12) << "z= " << (double)(point.z * header.z_scale) + header.z_offset << endl;
			cout << "point.intensity= " << point.intensity << endl;
			cout << "point.time= " << point.time << endl;
			cout << "point.pointSourceID= " << point.pointSourceID << endl;
			cout << endl;
		}*/
	}

}

void ReadLas::output_PointData(string outname)
{
	ofstream foutput;
	
	foutput.open(outname);
	cout << "start to write point data to txt......" << endl;
	
	for (int ii = 0; ii < pointdataRecord.size(); ii++)
	{
		foutput << ii << " " << setprecision(13)
			<< (double)(pointdataRecord.at(ii).x * header.x_scale) + header.x_offset << " "
			<< (double)(pointdataRecord.at(ii).y * header.y_scale) + header.y_offset << " "
			<< (double)(pointdataRecord.at(ii).z * header.z_scale) + header.z_offset << " "
			<< pointdataRecord.at(ii).intensity << endl;

	}
	cout << "write point data to txt finished" << endl;
	foutput.close();

}