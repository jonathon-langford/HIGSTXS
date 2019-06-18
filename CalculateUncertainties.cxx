

void CalculateUncertainties () {
  
  TFile *file = TFile::Open("nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125_1.root");
  TTree* Events = (TTree*) file->Get("Events");
  
  TH1F* histo = new TH1F ("histo", "", 500, 0, 500);

  TH1F* histo_scale[9];
  
  
  Events->Draw("HTXS_stage_1_pTjet30 >> histo", "1");
    
//   LHEWeight_originalXWGTUP
//   LHEScaleWeight  [9]          (and then LHEPdfWeight)  [103]
//   https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#HTXS
//   
//   LHEScaleWeight[4] --> always "1" ---> this is already the ratio!
//
  
  for (int i=0; i<9; i++) {
    
    TString name = Form ("histo_%d", i);
    histo_scale[i] = new TH1F (name.Data(), "", 500, 0, 500);
    
    TString weight = Form ("LHEScaleWeight[%d]", i);
    TString whattodraw = Form ("HTXS_stage_1_pTjet30 >> %s", name.Data());
    
    Events->Draw(whattodraw.Data(), weight.Data());
    
  }
  
  //---- now write
  
  for (int iBin=0; iBin<500; iBin++) {
    
    float integral_nominal = histo->GetBinContent (iBin+1);
    
    if (integral_nominal != 0) {
      
      std::cout << " [" << iBin << "] => " << integral_nominal << " ::: ";
      
      for (int i=0; i<9; i++) {
        float integral_varied = histo_scale[i]->GetBinContent (iBin+1);
        
        std::cout << " " << integral_varied << " , ";
      }
      
      std::cout << std::endl;
      
    }
    
  }
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  
  //---- normalized
  
  for (int iBin=0; iBin<500; iBin++) {
    
    float integral_nominal = histo->GetBinContent (iBin+1);
    
    if (integral_nominal != 0) {
      
      std::cout << " [" << iBin << "] =>  ::: ";
      
      for (int i=0; i<9; i++) {
        float integral_varied = histo_scale[i]->GetBinContent (iBin+1);
        
        std::cout << " " << (integral_varied-integral_nominal)/integral_nominal*100. << " % , ";
      }
      
      std::cout << std::endl;
      
    }
    
  }
  
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  
  // ---- 1001 = weights_LHE[0] ---> nominal
  //                                                         https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf
  //      [ 0 ] = 1001                                       <weight id="1001"> muR=0.10000E+01 muF=0.10000E+01 </weight>             Nominal
  //      [ 1 ] = 1002                                       <weight id="1002"> muR=0.10000E+01 muF=0.20000E+01 </weight>             NU
  //      [ 2 ] = 1003                                       <weight id="1003"> muR=0.10000E+01 muF=0.50000E+00 </weight>             ND
  //      [ 3 ] = 1004                                       <weight id="1004"> muR=0.20000E+01 muF=0.10000E+01 </weight>             UN
  //      [ 4 ] = 1005                                       <weight id="1005"> muR=0.20000E+01 muF=0.20000E+01 </weight>             UU
  //      [ 5 ] = 1006                                       <weight id="1006"> muR=0.20000E+01 muF=0.50000E+00 </weight>             UD   -> not used
  //      [ 6 ] = 1007                                       <weight id="1007"> muR=0.50000E+00 muF=0.10000E+01 </weight>             DN
  //      [ 7 ] = 1008                                       <weight id="1008"> muR=0.50000E+00 muF=0.20000E+01 </weight>             DU   -> not used
  //      [ 8 ] = 1009                                       <weight id="1009"> muR=0.50000E+00 muF=0.50000E+00 </weight>             DD
  
  
}





