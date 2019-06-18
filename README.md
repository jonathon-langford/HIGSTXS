STXS support measurements
====

Normalization uncertainties in STXS bins

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





    