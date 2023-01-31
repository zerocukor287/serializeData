#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
constexpr char delimiter = '\0';
constexpr uint32_t maxStringSize = 1024;

struct Data {
    double d;
    int i;
    std::string s1;
    uint32_t u;
    std::string s2;
    bool b;
};

int main()
{
    std::string filename = "Test.b";
     
    // make some test data
    std::vector<Data> data {{3.14, 5, "String", 9, "Pear", true}, {0.5, 42, "Another string", 6, "Peach", false}};

    // prepare a file to read
    std::ofstream outStream(filename, std::ios::binary);
    for(auto structure : data) {
        outStream.write(reinterpret_cast<char*>(&structure.d), sizeof structure.d)
            << structure.i << structure.s1 << delimiter << structure.u << structure.s2 << delimiter << structure.b;
    }
    outStream.close();

    // open file for reading
    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';
    else
    {
        while(!istrm.eof()) {
            Data dataRead;

            // binary input
            istrm.read(reinterpret_cast<char*>(&dataRead.d), sizeof dataRead.d);
            
            // number input
            istrm >> dataRead.i;
            
            // buffer for string reading
            char* buf = new char[maxStringSize];

            // string input
            istrm.getline(buf, maxStringSize, delimiter);
            dataRead.s1 = std::string(buf);

            // another number input
            istrm >> dataRead.u;

             // string input reusing the buffer
            istrm.getline(buf, maxStringSize, delimiter);
            dataRead.s2 = std::string(buf);

            // bool input
            istrm >> dataRead.b;

            std::cout << "read back from file: " << dataRead.d << ' ' << dataRead.i << ' '
                << dataRead.s1 << ' ' << dataRead.u << ' ' << dataRead.s2 << ' ' << (dataRead.b ? "true" : "false") << '\n';

            delete[] buf;
        }
    }
}