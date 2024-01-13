#include <iostream>
#include <fstream>
#include "Graph.hh"
#include "Histo.hh"

int main() {
std::ifstream infile("channel1_old.bin3", std::ifstream::binary);

infile.seekg(0, infile.end);
long size = infile.tellg();
infile.seekg(0);

std::cout<<"File size is: " << size << " Bytes" << std::endl;

std::istream& read (char* s, std::streamsize n);

double val;
long numberOfPoints = size / 24;
Histo histo("FileHistoOne",500, 0, 10);
Histo histo2("FileHistoTwo",500, 0, 10);

Graph graph("FileGraph");
double startTime;
infile.read((char*)& startTime, sizeof(double));

infile.seekg(0);
double x,y,yerr;
for(int i = 0; i < numberOfPoints; i++){
    infile.read((char*)& val, sizeof(double));
    x = val - startTime;

    infile.read((char*)& val, sizeof(double));
    y = (val - 30) * 1000;
    if(x > 3000 && y > 2 && y < 10){
        histo.Fill(y);
    }
    if(x > 12000 && x < 13000 && y > 2 && y < 10){
        histo2.Fill(y);
    }
    infile.read((char*)& yerr, sizeof(double));

    graph.AddPoint(x,y,yerr);
}

graph.draw();

histo.draw();
histo2.draw();

std::cout <<"first RMS is: "<< histo.GetRMS() << std::endl;
std::cout <<"second RMS is: "<< histo2.GetRMS() << std::endl;

}
