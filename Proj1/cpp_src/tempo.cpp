#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <utility>
#include <regex>

using namespace std;

int main()
{
  ifstream inputFile("tempo2.txt");
  list<pair<int, double>> times;
  string line;
  string out;
  pair<int, double> time;
  int extractedNumber;
  while (getline(inputFile, line))
  {
    istringstream iss(line);
    if (line.find("teste") != string::npos)
    {
      stringstream number;

      for (char ch : line)
      {
        if (isdigit(ch))
        {
          number << ch;
        }
      }

      int extractedNumber;
      number >> extractedNumber;
      time.first = stoi(number.str());
    }
    else if (line.find("real") != string::npos)
    {
      std::regex number_regex("[0-9]+[.]?[0-9]*"); // Matches decimal numbers

      std::sregex_iterator it(line.begin(), line.end(), number_regex);
      std::sregex_iterator end;
      int i = 0;
      double sum = 0;
      while (it != end)
      {
        std::smatch match = *it;
        if (i == 0)
        {
          sum += (stod(match.str()) * 60);
        }
        else
        {
          sum += (stod(match.str()));
        }
        ++it;
        i++;
      }
      time.second = sum;
      times.push_back(time);
      time.first = 0;
      time.second = 0;
    }
  }
  times.sort();
  inputFile.close(); // Close the file
  std::ofstream dataFile("TempoPlot.txt");
  std::ofstream dataFile3("N3.txt");
  std::ofstream dataFile2("N2.txt");

  
  for (const auto &pair : times)
  {
    double TestNumber = pair.first;
    double time = pair.second;
    dataFile << TestNumber << " " << time << "\n";
    
    dataFile3 << TestNumber*TestNumber*TestNumber << " " << time << "\n";
    dataFile2 << TestNumber*TestNumber << " " << time << "\n";    
  }

  dataFile.close();
  dataFile2.close();
  dataFile3.close();

  // Open a pipe to gnuplot
  FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
  if (!gnuplotPipe)
  {
    std::cerr << "Error opening gnuplot pipe!" << std::endl;
    return 1;
  }

  // Send commands to gnuplot
  fprintf(gnuplotPipe, "set multiplot layout 2,1 title 'Time Plot' font 'JetBrainsMono Nerd Font, 12'\n"); // Set up a 3x1 grid of plots

  // Plot 'TempoPlot.txt' with x-range [0:1000000]
  
  fprintf(gnuplotPipe, "set xlabel \"N\" \n");
  fprintf(gnuplotPipe, "set ylabel \"Time\" \n");
  fprintf(gnuplotPipe, "set xrange[0:1500]\n");
  fprintf(gnuplotPipe, "plot 'TempoPlot.txt' with lines title 'Time Plot'\n");

  fprintf(gnuplotPipe, "set xrange[0:3375000000]\n");
  fprintf(gnuplotPipe, "set xlabel \"N³\" \n");
  fprintf(gnuplotPipe, "plot 'N3.txt' with lines title 'Time Plot of N³'\n");
  
  // Plot 'N3.txt' with x-range [0:3000000]
  
  fprintf(gnuplotPipe, "unset multiplot\n"); // End multiplot mode

  // Close gnuplot pipe
  pclose(gnuplotPipe);
}
