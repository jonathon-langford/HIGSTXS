

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
      
      std::cout << " [" << iBin << "] => " << integral_nominal ;
      std::cout << std::endl;
      
    }
    
  }
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  
  
  for (int iBin=0; iBin<500; iBin++) {
    
    float integral_nominal = histo->GetBinContent (iBin+1);
    
    if (integral_nominal != 0) {
      
      std::cout << " [" << iBin << "] => " << integral_nominal << " ::: ";
      
      for (int i=0; i<9; i++) {
        if (i==2 || i==6) continue;
        
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
        if (i==2 || i==6) continue;
        
        float integral_varied = histo_scale[i]->GetBinContent (iBin+1);
        
        std::cout << " " << (integral_varied-integral_nominal)/integral_nominal*100. << " % , ";
      }
      
      std::cout << std::endl;
      
    }
    
  }
  
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  
  
//   # Gluon fusion
//   'GG2H_FWDH' : 100,                             |   |eta_h| > 2.5
//   'GG2H_VBFTOPO_JET3VETO' : 101,                 |    2 jet
//   'GG2H_VBFTOPO_JET3' : 102,                     |    3 jet
//   'GG2H_0J'   : 103,                             |    0 jet
//   'GG2H_1J_PTH_0_60' : 104,                      |    1 jet
//   'GG2H_1J_PTH_60_120' : 105,                    |    1 jet
//   'GG2H_1J_PTH_120_200' : 106,                   |    1 jet
//   'GG2H_1J_PTH_GT200' : 107,                     |    1 jet
//   'GG2H_GE2J_PTH_0_60' : 108,                    |    2 jet
//   'GG2H_GE2J_PTH_60_120' : 109,                  |    2 jet
//   'GG2H_GE2J_PTH_120_200' : 110,                 |    2 jet
//   'GG2H_GE2J_PTH_GT200' : 111,                   |    2 jet
//   
  
//   
//   N = nominal, U = up, D = down
// 
//   DU and UD not considered later
//   
  std::map< int, float > integral_DD;
  std::map< int, float > integral_DN;
  std::map< int, float > integral_DU; // *
  std::map< int, float > integral_ND;
  std::map< int, float > integral_NN;
  std::map< int, float > integral_NU;
  std::map< int, float > integral_UD; // *
  std::map< int, float > integral_UN;
  std::map< int, float > integral_UU;
  
  std::vector< std::map< int, float > >  integrals;
  integrals.push_back(integral_DD);
  integrals.push_back(integral_DN);
  integrals.push_back(integral_DU); // *
  integrals.push_back(integral_ND);
  integrals.push_back(integral_NN);
  integrals.push_back(integral_NU);
  integrals.push_back(integral_UD); // *
  integrals.push_back(integral_UN);
  integrals.push_back(integral_UU);
  
  
  //   
  //   LHEScaleWeight      
  //   
  //   https://cms-nanoaod-integration.web.cern.ch/integration/master-94X/mc94Xv2_doc.html#LHEScaleWeight
  //   
  //   Float_t LHE scale variation weights (w_var / w_nominal);
  //   [0] is renscfact=0.5d0 facscfact=0.5d0 ;                    DD
  //   [1] is renscfact=0.5d0 facscfact=1d0 ;                      DN
  //   [2] is renscfact=0.5d0 facscfact=2d0 ;                      DU  *
  //   [3] is renscfact=1d0 facscfact=0.5d0 ;                      ND
  //   [4] is renscfact=1d0 facscfact=1d0 ;                        NN
  //   [5] is renscfact=1d0 facscfact=2d0 ;                        NU
  //   [6] is renscfact=2d0 facscfact=0.5d0 ;                      UD  *
  //   [7] is renscfact=2d0 facscfact=1d0 ;                        UN
  //   [8] is renscfact=2d0 facscfact=2d0                          UU
  //   
  
  
  for (int iBin=0; iBin<500; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      for (int i=0; i<9; i++) {
        (integrals.at(i))[iBin] = histo_scale[i]->GetBinContent (iBin+1);
        }
    }
  }

  
//   
//   ---- bins to add for njets
//   
//   
//   103  ->  == 0 jets                             ---> 0 index
//   104, 105, 106, 107   -> == 1 jet               ---> 1 index
//   108, 109, 110, 111, 101, 102 --> >= 2 jets     ---> 2 index
//   
  
  
  for (int i=0; i<9; i++) {
  
    (integrals.at(i))[0]  = (integrals.at(i))[103];
   
    (integrals.at(i))[1]  = (integrals.at(i))[104];
    (integrals.at(i))[1] += (integrals.at(i))[105];
    (integrals.at(i))[1] += (integrals.at(i))[106];
    (integrals.at(i))[1] += (integrals.at(i))[107];
 
    (integrals.at(i))[2]  = (integrals.at(i))[108];
    (integrals.at(i))[2] += (integrals.at(i))[109];
    (integrals.at(i))[2] += (integrals.at(i))[110];
    (integrals.at(i))[2] += (integrals.at(i))[111];
    (integrals.at(i))[2] += (integrals.at(i))[101];
    (integrals.at(i))[2] += (integrals.at(i))[102];
    
  }
  
  
  //---- [4]  =  NN
  // scale each bin by nominal / value in the corresponding jet bin
  //   
  
  for (int iBin=0; iBin<500; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      std::cout << " [" << iBin << "] =>  scale factors ::: ";
      for (int i=0; i<9; i++) {
        
        if (i==2 || i==6) continue;
        
        if ( (iBin) == 103)  std::cout << " " << ( (integrals.at(4))[0] / (integrals.at(i))[0] ) << " , ";

        if ( (iBin) == 104)  std::cout << " " << ( (integrals.at(4))[1] / (integrals.at(i))[1] ) << " , ";
        if ( (iBin) == 105)  std::cout << " " << ( (integrals.at(4))[1] / (integrals.at(i))[1] ) << " , ";
        if ( (iBin) == 106)  std::cout << " " << ( (integrals.at(4))[1] / (integrals.at(i))[1] ) << " , ";
        if ( (iBin) == 107)  std::cout << " " << ( (integrals.at(4))[1] / (integrals.at(i))[1] ) << " , ";

        if ( (iBin) == 108)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        if ( (iBin) == 109)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        if ( (iBin) == 110)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        if ( (iBin) == 111)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        if ( (iBin) == 101)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        if ( (iBin) == 102)  std::cout << " " << ( (integrals.at(4))[2] / (integrals.at(i))[2] ) << " , ";
        
      }
      std::cout << std::endl;
    }
  }
  
  
  std::cout << std::endl;
  
  for (int i=0; i<9; i++) {
    
    (integrals.at(i))[103] *= ( (integrals.at(4))[0] / (integrals.at(i))[0] ) ;
                                                                              
    (integrals.at(i))[104] *= ( (integrals.at(4))[1] / (integrals.at(i))[1] ) ;
    (integrals.at(i))[105] *= ( (integrals.at(4))[1] / (integrals.at(i))[1] ) ;
    (integrals.at(i))[106] *= ( (integrals.at(4))[1] / (integrals.at(i))[1] ) ;
    (integrals.at(i))[107] *= ( (integrals.at(4))[1] / (integrals.at(i))[1] ) ;
                                                                               
    (integrals.at(i))[108] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    (integrals.at(i))[109] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    (integrals.at(i))[110] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    (integrals.at(i))[111] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    (integrals.at(i))[101] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    (integrals.at(i))[102] *= ( (integrals.at(4))[2] / (integrals.at(i))[2] ) ;
    
  }  
  
  //---- now write:
  
  for (int iBin=0; iBin<500; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      std::cout << " [" << iBin << "] =>  ::: " << integral_nominal << "     ";
      for (int i=0; i<9; i++) {
        if (i==2 || i==6) continue;
        std::cout << " " << ( (integrals.at(i))[iBin] - (integrals.at(4))[iBin] ) / (integrals.at(4))[iBin] << " % , ";
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





