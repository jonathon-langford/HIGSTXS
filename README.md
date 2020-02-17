STXS support measurements
====

Normalization uncertainties in STXS bins
~~~


Input:

    /GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8/RunIISummer16NanoAODv4-PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/NANOAODSIM

    xrdcp  root://cmsxrootd.fnal.gov///store/mc/RunIISummer16NanoAODv4/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8/NANOAODSIM/PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/50000/8E7B6585-5692-DE4B-B504-91C62A377AAB.root  /tmp/amassiro/
    
    scp amassiro@lxplus779.cern.ch:/tmp/amassiro/8E7B6585-5692-DE4B-B504-91C62A377AAB.root .
    
    --> missing STXS
    
    
    
    /GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/RunIIAutumn18NanoAODv4-Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/NANOAODSIM
    
    xrdcp  root://cmsxrootd.fnal.gov////store/mc/RunIIAutumn18NanoAODv4/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/NANOAODSIM/Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/120000/B126F357-D8B7-4E42-BB75-BF8C06584B39.root      /tmp/amassiro/
     
    scp amassiro@lxplus779.cern.ch:/tmp/amassiro/B126F357-D8B7-4E42-BB75-BF8C06584B39.root  .
    
    --> missing STXS
    
    
    
    
    /GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/RunIISummer16NanoAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/NANOAODSIM 
    
    xrdcp  root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv3/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/NANOAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/26E441C7-7B3F-E911-880B-0025905B8574.root     /tmp/amassiro/  
    
    scp amassiro@lxplus779.cern.ch:/tmp/amassiro/26E441C7-7B3F-E911-880B-0025905B8574.root    .
    
    --> missing STXS
     
    
    
    
    /GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/RunIISummer16NanoAODv4-PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/NANOAODSIM 
    
    xrdcp  root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv4/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/NANOAODSIM/PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/10000/2BB304AE-F385-9E43-8972-4D662517ED7F.root   /tmp/amassiro/

    
    Already STXS added:
    
    /eos/cms/store/group/phys_higgs/cmshww/amassiro/NanoProd/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125/190124_220256/0000/nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125_1.root
    
    
    
Variables:

    https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
    
    https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#HTXS
    
    HTXS_stage_0
    HTXS_stage_1_pTjet30
    
    
Run:

    r99t CalculateUncertainties.cxx


    

Normalization in each STXS bin 
~~~

Provide the inputs needed by analyzers to rescale the weights in each STXS bin, or to perform a a-posteriori splitting of the nuisance.
See the slides for the explanation of the method.

Current baseline is powheg re-weightted to minlo.

Input:
    
    Already STXS added:
    
    /eos/cms/store/group/phys_higgs/cmshww/amassiro/NanoProd/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125/190124_220256/0000/nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125_1.root

Official production:

    /store/mc/RunIISummer16NanoAODv6/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/NANOAODSIM/PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1/100000/1DBC2A44-BB36-2B4D-B4F9-16C95A4197F3.root
    xrdcp  root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv6/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/NANOAODSIM/PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1/100000/1DBC2A44-BB36-2B4D-B4F9-16C95A4197F3.root   /tmp/amassiro/  
    
    nano_HJNNLOPS.root
    
    Events->Draw("HTXS_stage_1_pTjet30")
    --> stxs 700/201 -> bbh??  https://gitlab.cern.ch/LHCHIGGSXS/LHCHXSWG2/STXS/Classification/blob/master/HiggsTemplateCrossSections.h
    
    
    
    /store/group/phys_higgs/cmshww/amassiro/NanoProd/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_minloHJ_NNLOPS_JHUGenV702_pythia8/nanoAOD__Summer16_102X_nAODv5_Full2016v6_NNLOPS__GluGluHToWWTo2L2NuPowhegNNLOPS_M125_private/200115_155222/0000/
    
    data/nanoAOD__Summer16_102X_nAODv5_Full2016v6_NNLOPS__GluGluHToWWTo2L2NuPowhegNNLOPS_M125_private_1.root
    data/nanoAOD__Summer16_102X_nAODv5_Full2016v6_NNLOPS__GluGluHToWWTo2L2NuPowhegNNLOPS_M125_private_2.root
    
    
    
    
    
    /GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1/NANOAODSIM
    /store/mc/RunIISummer16NanoAODv6/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/NANOAODSIM/PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1/280000/C832E8FC-6BE7-FA44-88F8-22F7BE1833E3.root
    xrdcp  root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv6/GluGluHToZZTo4L_M125_13TeV_powheg2_minloHJ_NNLOPS_JHUgenV702_pythia8/NANOAODSIM/PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1/280000/C832E8FC-6BE7-FA44-88F8-22F7BE1833E3.root   /tmp/amassiro/  
    
    data/nano_HJNNLOPS_HZZ.root

    Events->Draw("HTXS_stage_1_pTjet30")
    --> stxs 700/201 -> bbh??  https://gitlab.cern.ch/LHCHIGGSXS/LHCHXSWG2/STXS/Classification/blob/master/HiggsTemplateCrossSections.h
     
     
    

Run:

    r99t CalculateNormalizations.cxx
    r99t CalculateNormalizations.cxx\(\"data/nano_HJNNLOPS_HZZ.root\"\)
    
    r99t CalculateNormalizations.cxx\(\"data/nanoAOD__Summer16_102X_nAODv5_Full2016v6_NNLOPS__GluGluHToWWTo2L2NuPowhegNNLOPS_M125_private_1.root\"\)
    

    
    
Check X to MINLO reweighting
~~~

Check the pt distribution of the Higgs and the reweighting from powheg to MINLO currently used.


    r99t CheckReweight.cxx
    
    


    