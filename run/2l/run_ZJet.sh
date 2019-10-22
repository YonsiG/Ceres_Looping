cd ..
for iloop in {0..4}
do
nohup ./ZZZAna.exe ../table/2l_channel_list/Z+Jetlist/Z+Jet_filelist${iloop}.txt Z+Jet${iloop} 9999 &
done
wait 
rm ../outfiles/Z+Jet_selected.root
hadd Z+Jet_selected.root ../outfiles/Z+Jet*_selected.root
rm ../outfiles/Z+Jet*_selected.root
mv Z+Jet_selected.root ../outfiles/Z+Jet_selected.root
