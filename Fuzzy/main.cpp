#include <iostream>
#include "fuzzycmeans.h"
#include <fstream>
#include <string>
#include <regex>



void parseFile(char * fileName ,cv::Mat & data)
{
    std::ifstream file("iris.data");
    std::string line;
    std::regex re("(\"([^\"]*)\"|([^,]*))(,|$)");
    data = cv::Mat::zeros(0 , 4 , CV_64F);
    cv::Mat temp = cv::Mat::zeros(1 , 4 , CV_32F);
    float * t = temp.ptr<float>();
    if(file.is_open())
    {
        while(getline(file , line))
        {
            std::sregex_iterator next(line.begin() , line.end() , re);
            std::sregex_iterator end;
            int i = 0;
            while(next != end)
            {
                if(i == 4) break;
                std::smatch match = *next;
                //std::cout << match.str() <<'\n';
                std::string m = match.str();
                double tp = std::stod(m , nullptr);
                t[i] = tp;

                //std::cout << tp << ',';
                next++;
                i++;
            }
            data.push_back(temp);
            std::cout << '\n';
        }
    }
    else{

        std::cout << "here" << '\n';
    }

    file.close();

}



int main()
{

    cv::Mat Data;

    parseFile("~/iris.data" , Data);
    FuzzyCmeans f(Data.rows , Data.cols , 3);

    f.Cluster(Data , 2 ,  .01);

    cv::Mat &U = f.getU();
    std::cout << U << std::endl;



}


