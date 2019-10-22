cd ..
nohup ./ZZZAna.exe ../table/4l_channel_list/ZZ16.txt ZZ16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/WZ16.txt WZ16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/tWZ16.txt tWZ16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/h16.txt h16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/ttZ16.txt ttZ16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/others16.txt others16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/stt16.txt stt16 2016 &
nohup ./ZZZAna.exe ../table/4l_channel_list/ZZ17.txt ZZ17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/WZ17.txt WZ17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/tWZ17.txt tWZ17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/h17.txt h17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/ttZ17.txt ttZ17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/others17.txt others17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/stt17.txt stt17 2017 &
nohup ./ZZZAna.exe ../table/4l_channel_list/ZZ18.txt ZZ18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/WZ18.txt WZ18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/tWZ18.txt tWZ18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/h18.txt h18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/ttZ18.txt ttZ18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/others18.txt others18 2018 &
nohup ./ZZZAna.exe ../table/4l_channel_list/stt18.txt stt18 2018 &
wait

cd ../outfiles
rm bkg_selected.root WZ_selected.root ZZ_selected.root h_selected.root others_selected.root stt_selected.root tWZ_selected.root ttZ_selected.root
hadd WZ_selected.root WZ16_selected.root WZ17_selected.root WZ18_selected.root
hadd ZZ_selected.root ZZ16_selected.root ZZ17_selected.root ZZ18_selected.root
hadd h_selected.root h16_selected.root h17_selected.root h18_selected.root
hadd others_selected.root others16_selected.root others17_selected.root others18_selected.root
hadd stt_selected.root stt16_selected.root stt17_selected.root stt18_selected.root
hadd tWZ_selected.root tWZ16_selected.root tWZ17_selected.root tWZ18_selected.root
hadd ttZ_selected.root ttZ16_selected.root ttZ17_selected.root ttZ18_selected.root
hadd bkg_selected.root WZ_selected.root ZZ_selected.root h_selected.root others_selected.root stt_selected.root tWZ_selected.root ttZ_selected.root
mv *.root 4l1F
