hed /msu/data/t3work9/voetberg/bdt_tmva_outputs/reader_results/TrainingResult16_pt150.root\
  -o /home/voetberg/programs/TMVA/BDT_n_ANN/tmva_16feat/reader/ReaderResults/h_TrainingResults_pt150_sb.pdf\
  -e 's/^(Background|Signal)$//'\
     'nl/^(Signal|Background)$.*/\1/'\
     't///'\
     'n/^Signal$/scale 0.00000290578 width'\
     'n/^Background$/scale 0.00001313922 width'\
  -g 'leg tr'\
  --colors=600 632 800


hed /msu/data/t3work9/voetberg/bdt_tmva_outputs/reader_results/TrainingResult16_pt150.root\
  -o /home/voetberg/programs/TMVA/BDT_n_ANN/tmva_16feat/reader/ReaderResults/h_TrainingResults_pt150_sbs.pdf\
  -e 's/^(Signal|Background|Res_Signal)$//'\
     'nl/(Signal|Background|Res_Signal)$.*/\1/'\
     't//Response from Signal/'\
     'n/^Signal$/scale 0.00000290578 width'\
     'n/^Background$/scale 0.00001313922 width'\
     'n/^Res_Signal$/scale 0.00000291037 width'\
  -g 'leg tr'\
  --colors=600 632 800


hed /msu/data/t3work9/voetberg/bdt_tmva_outputs/reader_results/TrainingResult16_pt150.root\
  -o /home/voetberg/programs/TMVA/BDT_n_ANN/tmva_16feat/reader/ReaderResults/h_TrainingResults_pt150_sbb.pdf\
  -e 's/^(Signal|Background|Res_Background)$//'\
     'nl/^(Signal|Background|Res_Background)$.*/\1/'\
     't//Response from MC Background/' \
     'n/^Signal$/scale 0.00000290578 width'\
     'n/^Background$/scale 0.00001313922 width'\
     'n/^Res_Background$/scale 0.00003316199 width'\
  -g 'leg tr'\
  --colors=600 632 800


hed /msu/data/t3work9/voetberg/bdt_tmva_outputs/reader_results/TrainingResult16_pt150.root\
  -o /home/voetberg/programs/TMVA/BDT_n_ANN/tmva_16feat/reader/ReaderResults/h_TrainingResults_pt150_sbd.pdf\
  -e 's/^(Signal|Background|Res_Data)$//'\
     'nl/^(Signal|Background|Res_Data)$.*/\1/'\
     't//Response from Data/' \
     'n/^Signal$/scale 0.00000290578 width'\
     'n/^Background$/scale 0.00001313922 width'\
     'n/^Res_Data$/scale 0.00065659881 width'\
  -g 'leg tr'\
  --colors=600 632 800
     

     # 'n/Signal/scale 0.0000058017 width'\
     # 'n/Background/scale 0.0000652103 width'\
     # 'n/Res_Signal/scale 0.00000290223 width'\
     # 'n/Res_Background/scale 0.00003316199 width'\
     # 'n/Res_Data/scale 0.00065659881 width'\


