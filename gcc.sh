cd source_code
g++ -g -std=c++17 Controll.C makeHists.C ZZZAna.C -I$ROOTSYS/include `root-config --libs ` -lMinuit -lGenVector -o ../run/ZZZAna.exe
cd ../run/4l
