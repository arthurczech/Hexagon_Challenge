/******************************************************************************************************************/
/*           Code developed for the Control Analist position in the R&D division in Hexagon Agriculture           */
/*                                          Candidate: Arthur Schmietke Czech                                     */
/*                                              Date: April 15th, 2023                                            */
/*           This code was developed in order to implement an algorithm capable of opening a data file            */
/*           containing the X, Y and Z accelerations from a MMA8451 accelerometer test, parsing said data,        */
/*           estimate the roll and pitch angles and save the reults in an output file. For conducting this        */
/*           activity an application note (provided by Hexagon Agriculture) was used. The equations used          */
/*           from this document are disclosed in the comments below. The rotation sequence used was xyz.          */
/******************************************************************************************************************/


// Lybraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// Auxiliary functions

// Input file reading function
void r_input(std::string name_arq, std::vector<std::vector<std::string>>& data) {
    std::ifstream arq(name_arq);

    if (arq.is_open()) {
        std::string rows;

        while (getline(arq, rows)) {
            std::vector<std::string> values;
            std::stringstream line(rows);
            std::string val;

            while (getline(line, val, ';')) {
                values.push_back(val);
            }

            data.push_back(values);
        }

        arq.close();
    } else {
        std::cout << "Unable to open " << name_arq << std::endl;
    }
}

// Type casting function
void convert(const std::vector<std::vector<std::string>>& data, std::vector<std::vector<float>>& converted) {
    converted.resize(data.size());
float val = 0;
    for (size_t i = 0; i < data.size(); i++) {
        converted[i].resize(data[i].size());

        for (size_t j = 0; j < data[i].size(); j++) {
            converted[i][j] = std::stof(data[i][j]);
        }
    }

}

// Output file generating function
void generate_output(std::string name_arq, std::vector<float> col0, std::vector<float> theta, std::vector<float> phi) {
    std::ofstream arq(name_arq);

    if (arq.is_open()) {

        for (int i = 0; i < col0.size(); i++){
          arq << col0[i] << ";" << phi[i] << ";" << theta[i] << std::endl;
        }

        arq.close();
    } else {
        std::cout << "Unable to create " << name_arq << std::endl;
    }
}

// Data manipulation function
void parse_data(const std::vector<std::vector<float>>& converted, std::vector<float>& col0, std::vector<float>& col1, std::vector<float>& col2, std::vector<float>& col3, std::vector<float>& theta, std::vector<float>& phi){

  for (const auto& row : converted){
    col0.push_back(row[0]);           // this vector (col0) contais the timestamp
    col1.push_back(row[1]);           // this vector (col1) contains the X axis coordinates
    col2.push_back(row[2]);           // this vector (col2) contains the Y axis coordinates
    col3.push_back(row[3]);           // this vector (col3) contains the Z axis coordinates
  }

  theta.resize(col0.size());
  phi.resize(col0.size());

  for (size_t i = 0; i < col0.size(); i++){

    phi[i] = (atan(col2[i]/col3[i])*180)/M_PI;                                            // equation 25 of application note (roll)

    theta[i] = (atan((-col1[i])/(sqrt(col2[i]*col2[i] + col3[i]*col3[i])))*180)/M_PI;     // equation 26 of application note (pitch)
  }

}

// Main function
int main() {
    std::string input = "attitude_exam.log";
    std::string output = "output.log";

    // Raw data matrix
    std::vector<std::vector<std::string>> data;

    r_input(input, data);

    // Auxiliary Vectors and float matrix
    std::vector<std::vector<float>> converted;
    std::vector<float> col0, col1, col2, col3, theta, phi;

    convert(data, converted);

    parse_data(converted, col0, col1, col2, col3, theta, phi);

    generate_output(output, col0, theta, phi);

    return 0;
}
