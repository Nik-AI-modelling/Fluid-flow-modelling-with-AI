

#include <vector>
#include <iostream>
#include <fstream>
#include "Print_2Dvector.h"
#include <string>



//Write variables into a file
Print_2Dvector::Print_2Dvector( const std::vector<std::vector<float>>& vec2D,const std::string& VecName) {
	
		//Create and open the file 
	std::ofstream outfile(VecName+".txt");
	//Check if the file is open
	if (outfile.is_open()) {
		//Write 2D vector into a file
		for (const auto& row : vec2D) {
			outfile << "[";
				for (int  i = 0; i < row.size(); ++i) {
					outfile << row[i];

					if (i != row.size() - 1) {
						outfile << " , ";
					}
				}
				outfile << "]," << std::endl;//Move to the next line after each row
		}

		//Close file
		outfile.close();
		std::cout << "2D vector written to file succsefully." << VecName  << std::endl;
	} 	else {
		std::cerr << "Failed to open the file" << std::endl;
	}
}
