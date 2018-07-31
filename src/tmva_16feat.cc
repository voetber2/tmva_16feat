#include <iostream>                                                             
#include <cstdlib>                                                              
#include <map>                                                                  
#include <string>                                                               
                                                                                
#include <TChain.h>                                                             
#include <TFile.h>                                                              
#include <TTree.h>                                                         
#include <TString.h>                                                            
#include <TObjString.h>                                                         
#include <TSystem.h>                                                            
                                                                                
#include <TMVA/Factory.h>                                                       
#include <TMVA/DataLoader.h>                                                    
#include <TMVA/Tools.h>                                                         
                                                                                
using namespace std;                                                            
                                                                                
int main(){                                                                     
  TMVA::Tools::Instance();                                                      
  map<string, int> Use;

  TFile* out = TFile::Open("tmva_bdt16_ptcuts.root", "RECREATE"); 
  TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", out, 
    "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification");

  //=========================================================================
  //Data with cut at 50
  TFile* in_50 = TFile::Open("$TMPDIR/data16_pt50.root"); 
  TMVA:: DataLoader* data_50 = new TMVA::DataLoader("data_pt50"); 
  
  //Adding every variable                                                       
  data_50->AddVariable("s",'F');                                           
  data_50->AddVariable("yydr",'F');                                          
  data_50->AddVariable("y1dr",'F');                                           
  data_50->AddVariable("y2dr",'F');                                           
  data_50->AddVariable("ptratio",'F');                                             
  data_50->AddVariable("y1y",'F');                                             
  data_50->AddVariable("y2y",'F');                                             
  data_50->AddVariable("jety",'F');                                              
  data_50->AddVariable("yydy",'F');                                              
                                                                                
  data_50->AddVariable("y1E",'F');                                            
  data_50->AddVariable("y1pt",'F');                                           
                                                                                
  data_50->AddVariable("y2E",'F');                                            
  data_50->AddVariable("y2pt",'F');                                           
                                                                                
  data_50->AddVariable("yyE",'F');                                           
  data_50->AddVariable("yypt",'F');                                          
                                                                                
  data_50->AddVariable("jetE",'F');                                                
    
  //Load in data from the input                                                 
  TTree* sigTrain_50 = (TTree*)in_50->Get("sigTrain");                             
  TTree* bgTrain_50 = (TTree*)in_50->Get("bgTrain");                               
  TTree* sigTest_50 = (TTree*)in_50->Get("sigTest");                               
  TTree* bgTest_50 = (TTree*)in_50->Get("bgTest"); 
  
  Float_t sig_w_50 = 1./(sigTrain_50->GetEntries() + sigTest_50->GetEntries());  
  Float_t bg_w_50 = 1./(bgTrain_50->GetEntries() + bgTest_50->GetEntries());   
  
  data_50->AddSignalTree(sigTrain_50, sig_w_50, "Training"); 
  data_50->AddSignalTree(sigTest_50, sig_w_50, "Testing"); 
  data_50->AddBackgroundTree(bgTrain_50, bg_w_50, "Training"); 
  data_50->AddBackgroundTree(bgTest_50, bg_w_50, "Testing"); 
  
  //Add weights 
  //Loading in weights 
  TMVA::DataLoader* weight_data_50 = new TMVA::DataLoader("weight_data"); 
  weight_data_50->AddVariable("weights", 'F'); 
  
  weight_data_50->AddSignalTree(sigTrain_50, sig_w_50, "Training"); 
  weight_data_50->AddSignalTree(sigTest_50, sig_w_50, "Testing"); 
  weight_data_50->AddBackgroundTree(bgTrain_50, bg_w_50, "Training"); 
  weight_data_50->AddBackgroundTree(bgTest_50, bg_w_50, "Testing"); 
  
  data_50->SetWeightExpression("weights"); 
  //=============================================================================
  //Data with pt100 cut 
  TFile* in_100 = TFile::Open("$TMPDIR/data16_pt100.root"); 
  TMVA:: DataLoader* data_100 = new TMVA::DataLoader("data_pt100"); 
  
  //Adding every variable                                                       
  data_100->AddVariable("s",'F');                                           
  data_100->AddVariable("yydr",'F');                                          
  data_100->AddVariable("y1dr",'F');                                           
  data_100->AddVariable("y2dr",'F');                                           
  data_100->AddVariable("ptratio",'F');                                             
  data_100->AddVariable("y1y",'F');                                             
  data_100->AddVariable("y2y",'F');                                             
  data_100->AddVariable("jety",'F');                                              
  data_100->AddVariable("yydy",'F');                                              
                                                                                
  data_100->AddVariable("y1E",'F');                                            
  data_100->AddVariable("y1pt",'F');                                           
                                                                                
  data_100->AddVariable("y2E",'F');                                            
  data_100->AddVariable("y2pt",'F');                                           
                                                                                
  data_100->AddVariable("yyE",'F');                                           
  data_100->AddVariable("yypt",'F');                                          
                                                                                
  data_100->AddVariable("jetE",'F');                                                
    
  //Load in data from the input                                                 
  TTree* sigTrain_100 = (TTree*)in_100->Get("sigTrain");                             
  TTree* bgTrain_100 = (TTree*)in_100->Get("bgTrain");                               
  TTree* sigTest_100 = (TTree*)in_100->Get("sigTest");                               
  TTree* bgTest_100 = (TTree*)in_100->Get("bgTest"); 
  
  Float_t sig_w_100 = 1./(sigTrain_100->GetEntries() + sigTest_100->GetEntries());  
  Float_t bg_w_100 = 1./(bgTrain_100->GetEntries() + bgTest_100->GetEntries());   
  
  data_100->AddSignalTree(sigTrain_100, sig_w_100, "Training"); 
  data_100->AddSignalTree(sigTest_100, sig_w_100, "Testing"); 
  data_100->AddBackgroundTree(bgTrain_100, bg_w_100, "Training"); 
  data_100->AddBackgroundTree(bgTest_100, bg_w_100, "Testing"); 
  
  //Add weights 
  //Loading in weights 
  TMVA::DataLoader* weight_data_100 = new TMVA::DataLoader("weight_data"); 
  weight_data_100->AddVariable("weights", 'F'); 
  
  weight_data_100->AddSignalTree(sigTrain_100, sig_w_100, "Training"); 
  weight_data_100->AddSignalTree(sigTest_100, sig_w_100, "Testing"); 
  weight_data_100->AddBackgroundTree(bgTrain_100, bg_w_100, "Training"); 
  weight_data_100->AddBackgroundTree(bgTest_100, bg_w_100, "Testing"); 
  
  data_100->SetWeightExpression("weights"); 
  //=============================================================================
  //Data with pt150 cut 
  TFile* in_150 = TFile::Open("$TMPDIR/data16_pt150.root"); 
  TMVA:: DataLoader* data_150 = new TMVA::DataLoader("data_pt150"); 
  
  //Adding every variable                                                       
  data_150->AddVariable("s",'F');                                           
  data_150->AddVariable("yydr",'F');                                          
  data_150->AddVariable("y1dr",'F');                                           
  data_150->AddVariable("y2dr",'F');                                           
  data_150->AddVariable("ptratio",'F');                                             
  data_150->AddVariable("y1y",'F');                                             
  data_150->AddVariable("y2y",'F');                                             
  data_150->AddVariable("jety",'F');                                              
  data_150->AddVariable("yydy",'F');                                              
                                                                                
  data_150->AddVariable("y1E",'F');                                            
  data_150->AddVariable("y1pt",'F');                                           
                                                                                
  data_150->AddVariable("y2E",'F');                                            
  data_150->AddVariable("y2pt",'F');                                           
                                                                                
  data_150->AddVariable("yyE",'F');                                           
  data_150->AddVariable("yypt",'F');                                          
                                                                                
  data_150->AddVariable("jetE",'F');                                                
    
  //Load in data from the input                                                 
  TTree* sigTrain_150 = (TTree*)in_150->Get("sigTrain");                             
  TTree* bgTrain_150 = (TTree*)in_150->Get("bgTrain");                               
  TTree* sigTest_150 = (TTree*)in_150->Get("sigTest");                               
  TTree* bgTest_150 = (TTree*)in_150->Get("bgTest"); 
  
  Float_t sig_w_150 = 1./(sigTrain_150->GetEntries() + sigTest_150->GetEntries());  
  Float_t bg_w_150 = 1./(bgTrain_150->GetEntries() + bgTest_150->GetEntries());   
  
  data_150->AddSignalTree(sigTrain_150, sig_w_150, "Training"); 
  data_150->AddSignalTree(sigTest_150, sig_w_150, "Testing"); 
  data_150->AddBackgroundTree(bgTrain_150, bg_w_150, "Training"); 
  data_150->AddBackgroundTree(bgTest_150, bg_w_150, "Testing"); 
  
  //Add weights 
  //Loading in weights 
  TMVA::DataLoader* weight_data_150 = new TMVA::DataLoader("weight_data"); 
  weight_data_150->AddVariable("weights", 'F'); 
  
  weight_data_150->AddSignalTree(sigTrain_150, sig_w_150, "Training"); 
  weight_data_150->AddSignalTree(sigTest_150, sig_w_150, "Testing"); 
  weight_data_150->AddBackgroundTree(bgTrain_150, bg_w_150, "Training"); 
  weight_data_150->AddBackgroundTree(bgTest_150, bg_w_150, "Testing"); 
  
  data_150->SetWeightExpression("weights"); 
  //=============================================================================
  //Data with pt200 cut 
  TFile* in_200 = TFile::Open("$TMPDIR/data16_pt200.root"); 
  TMVA:: DataLoader* data_200 = new TMVA::DataLoader("data_pt200"); 
  
  //Adding every variable                                                       
  data_200->AddVariable("s",'F');                                           
  data_200->AddVariable("yydr",'F');                                          
  data_200->AddVariable("y1dr",'F');                                           
  data_200->AddVariable("y2dr",'F');                                           
  data_200->AddVariable("ptratio",'F');                                             
  data_200->AddVariable("y1y",'F');                                             
  data_200->AddVariable("y2y",'F');                                             
  data_200->AddVariable("jety",'F');                                              
  data_200->AddVariable("yydy",'F');                                              
                                                                                
  data_200->AddVariable("y1E",'F');                                            
  data_200->AddVariable("y1pt",'F');                                           
                                                                                
  data_200->AddVariable("y2E",'F');                                            
  data_200->AddVariable("y2pt",'F');                                           
                                                                                
  data_200->AddVariable("yyE",'F');                                           
  data_200->AddVariable("yypt",'F');                                          
                                                                                
  data_200->AddVariable("jetE",'F');                                                
    
  //Load in data from the input                                                 
  TTree* sigTrain_200 = (TTree*)in_200->Get("sigTrain");                             
  TTree* bgTrain_200 = (TTree*)in_200->Get("bgTrain");                               
  TTree* sigTest_200 = (TTree*)in_200->Get("sigTest");                               
  TTree* bgTest_200 = (TTree*)in_200->Get("bgTest"); 
  
  Float_t sig_w_200 = 1./(sigTrain_200->GetEntries() + sigTest_200->GetEntries());  
  Float_t bg_w_200 = 1./(bgTrain_200->GetEntries() + bgTest_200->GetEntries());   
  
  data_200->AddSignalTree(sigTrain_200, sig_w_200, "Training"); 
  data_200->AddSignalTree(sigTest_200, sig_w_200, "Testing"); 
  data_200->AddBackgroundTree(bgTrain_200, bg_w_200, "Training"); 
  data_200->AddBackgroundTree(bgTest_200, bg_w_200, "Testing"); 
  
  //Add weights 
  //Loading in weights 
  TMVA::DataLoader* weight_data_200 = new TMVA::DataLoader("weight_data"); 
  weight_data_200->AddVariable("weights", 'F'); 
  
  weight_data_200->AddSignalTree(sigTrain_200, sig_w_200, "Training"); 
  weight_data_200->AddSignalTree(sigTest_200, sig_w_200, "Testing"); 
  weight_data_200->AddBackgroundTree(bgTrain_200, bg_w_200, "Training"); 
  weight_data_200->AddBackgroundTree(bgTest_200, bg_w_200, "Testing"); 
  
  data_200->SetWeightExpression("weights"); 
  //=============================================================================
  //Data with pt200+ cut 
  TFile* in_200p = TFile::Open("$TMPDIR/data16_pt200p.root");  
  TMVA:: DataLoader* data_200p = new TMVA::DataLoader("data_pt200p"); 
  
  //Adding every variable                                                       
  data_200p->AddVariable("s",'F');                                           
  data_200p->AddVariable("yydr",'F');                                          
  data_200p->AddVariable("y1dr",'F');                                           
  data_200p->AddVariable("y2dr",'F');                                           
  data_200p->AddVariable("ptratio",'F');                                             
  data_200p->AddVariable("y1y",'F');                                             
  data_200p->AddVariable("y2y",'F');                                             
  data_200p->AddVariable("jety",'F');                                              
  data_200p->AddVariable("yydy",'F');                                              
                                                                                
  data_200p->AddVariable("y1E",'F');                                            
  data_200p->AddVariable("y1pt",'F');                                           
                                                                                
  data_200p->AddVariable("y2E",'F');                                            
  data_200p->AddVariable("y2pt",'F');                                           
                                                                                
  data_200p->AddVariable("yyE",'F');                                           
  data_200p->AddVariable("yypt",'F');                                          
                                                                                
  data_200p->AddVariable("jetE",'F');                                                
    
  //Load in data from the input                                                 
  TTree* sigTrain_200p = (TTree*)in_200p->Get("sigTrain");                             
  TTree* bgTrain_200p = (TTree*)in_200p->Get("bgTrain");                               
  TTree* sigTest_200p = (TTree*)in_200p->Get("sigTest");                               
  TTree* bgTest_200p = (TTree*)in_200p->Get("bgTest"); 
  
  Float_t sig_w_200p = 1./(sigTrain_200p->GetEntries() + sigTest_200p->GetEntries());  
  Float_t bg_w_200p = 1./(bgTrain_200p->GetEntries() + bgTest_200p->GetEntries());   
  
  data_200p->AddSignalTree(sigTrain_200p, sig_w_200p, "Training"); 
  data_200p->AddSignalTree(sigTest_200p, sig_w_200p, "Testing"); 
  data_200p->AddBackgroundTree(bgTrain_200p, bg_w_200p, "Training"); 
  data_200p->AddBackgroundTree(bgTest_200p, bg_w_200p, "Testing"); 
  
  //Add weights 
  //Loading in weights 
  TMVA::DataLoader* weight_data_200p = new TMVA::DataLoader("weight_data"); 
  weight_data_200p->AddVariable("weights", 'F'); 
  
  weight_data_200p->AddSignalTree(sigTrain_200p, sig_w_200p, "Training"); 
  weight_data_200p->AddSignalTree(sigTest_200p, sig_w_200p, "Testing"); 
  weight_data_200p->AddBackgroundTree(bgTrain_200p, bg_w_200p, "Training"); 
  weight_data_200p->AddBackgroundTree(bgTest_200p, bg_w_200p, "Testing"); 
  
  data_200p->SetWeightExpression("weights"); 
  //============================================================================
  //Factories 
  TString settings = "NTrees=600:MaxDepth=3:nCuts=20:BoostType=AdaBoost:AdaBoostBeta=.5:!UseRandomisedTrees:UseYesNoLeaf";
  
  factory->BookMethod(data_50, TMVA::Types::kBDT, "BDT_50", settings);
  factory->BookMethod(data_100, TMVA::Types::kBDT, "BDT_100", settings);
  factory->BookMethod(data_150, TMVA::Types::kBDT, "BDT_150", settings);
  factory->BookMethod(data_200, TMVA::Types::kBDT, "BDT_200", settings);
  factory->BookMethod(data_200p, TMVA::Types::kBDT, "BDT_200p", settings);
  
  factory->TrainAllMethods(); 
  factory->TestAllMethods(); 
  factory->EvaluateAllMethods(); 
  
  out->Write(); 
  out->Close(); 
  
  delete factory; 
  
  delete data_50; 
  delete weight_data_50;   
  
  delete data_100; 
  delete weight_data_100;   
  
  delete data_150; 
  delete weight_data_150;   
  
  delete data_200; 
  delete weight_data_200;   
  
  delete data_200p; 
  delete weight_data_200p;   
}
