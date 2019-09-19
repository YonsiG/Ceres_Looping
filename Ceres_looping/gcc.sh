g++ -g -std=c++17 Controll.C makeHists.C ZZZAna.C -I$ROOTSYS/include `root-config --libs ` -lMinuit -lGenVector -o ZZZAna.exe
