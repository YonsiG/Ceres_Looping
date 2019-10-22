cd ..
./ZZZAna.exe ../table/4l_channel_list/signal16.txt signal16 2016
./ZZZAna.exe ../table/4l_channel_list/signal17.txt signal17 2017
./ZZZAna.exe ../table/4l_channel_list/signal18.txt signal18 2018
./ZZZAna.exe ../table/4l_channel_list/signal16_h.txt signal16_h 2016
./ZZZAna.exe ../table/4l_channel_list/signal17_h.txt signal17_h 2017
./ZZZAna.exe ../table/4l_channel_list/signal18_h.txt signal18_h 2018

cd ../outfiles

rm signal_selected.root
hadd signal_selected.root signal16_selected.root signal17_selected.root signal18_selected.root
mv signal_selected.root 4l1F/

rm signal_h_selected.root
hadd signal_h_selected.root signal16_h_selected.root signal17_h_selected.root signal18_h_selected.root
mv signal_h_selected.root 4l1F/
