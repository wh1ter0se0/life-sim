#include <fstream>

std::vector<std::string> generate_vector(std::string filename){
    std::vector<std::string> gen_vector;
    std::ifstream file(filename);
    std::string str;
    while(std::getline(file, str)){
        gen_vector.push_back(str);
    }
    file.close();
    return gen_vector;
}
std::vector<int> generate_vector_temp1(){
    std::vector<int> gen_vector;
    gen_vector.push_back(20); gen_vector.push_back(30); gen_vector.push_back(100);
    return gen_vector;
}
std::vector<int> generate_vector_temp2(){
    std::vector<int> gen_vector;
    gen_vector.push_back(30); gen_vector.push_back(90); gen_vector.push_back(300);
    return gen_vector;
}
