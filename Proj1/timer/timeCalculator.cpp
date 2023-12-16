#include <chrono>
#include <ctime>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>


using namespace std;

// Readd all files from a function
std::vector<std::string> getFilesInDirectory(const std::string& directoryPath) {
  std::vector<std::string> filesIn;
  std::vector<std::string> filesOut;
  for (const auto & entry : std::filesystem::directory_iterator(directoryPath)) {
    if(entry.path().extension() == ".in"){
      filesIn.push_back(entry.path().string());
    }else if(entry.path().extension() == ".out"){
      filesOut.push_back(entry.path().string());
    }
  }
  return (filesIn,filesOut);
}

// Read File
void readFile(string fileName){
  ifstream file(fileName);
  string line;
  if(file.is_open()){
    while(getline(file,line)){
      cout << line << endl;
      // Dps de ler o ficheiro preciso de mandar para a função principal

    }
    file.close();
  }
}


int main()
{
  chrono::time_point<chrono::system_clock> start, end;
  

  start = chrono::system_clock::now();
  end = chrono::system_clock::now();

  chrono::duration<double> Deviation = end - start;

  start = chrono::system_clock::now();

  Proj1() < Input; 
  

  end = chrono::system_clock::now();

  chrono::duration<double> elapsed_seconds = (end - start)-Deviation;
  
  

  cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


