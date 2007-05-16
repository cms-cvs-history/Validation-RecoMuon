TString gSampleLoc;

void DrawLoss2D(TString sampleLoc)
{
  gSampleLoc = sampleLoc;

  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  DrawEff("Seed","Sim");
  DrawEff("Sta","Sim");
  DrawEff("Glb","Sim");
  DrawEff("Glb","Sta");
 
}

void DrawLoss2D(TString sampleName, TString muonType1, TString muonType2, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(gSampleLoc+sampleName+".root"); 
  if(file.IsZombie()) return;
  file.cd();

  TH2F* hRec = (TH2F*)file.Get(muonType1+"EtaVsPhi");
  TH2F* hSim = (TH2F*)file.Get(muonType2+"EtaVsPhi");

//  hRec->RebinX(2); 
//  hSim->RebinX(2);

  gROOT->cd();
  TH2F* his  = new TH2F(sampleName+muonType1+muonType2+"his", sampleName+muonType1+muonType2, 
                        hRec->GetNbinsX(), hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax(), 
                        hRec->GetNbinsY(), hRec->GetYaxis()->GetXmin(), hRec->GetYaxis()->GetXmax());
  his->SetMinimum(0); his->SetMaximum(1);
  his->Divide(hRec, hSim, 1, -1);

  TF1 f1("f1", "1", hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax());
  his->Add(&f1);

  his->SetTitle(sampleName+muonType1+muonType2+" Muon loss rate");
  his->GetXaxis()->SetTitle("Angle #phi"); 
  his->GetYaxis()->SetTitle("Psuedorapidity #eta");
  his->Draw("COLZ");

  file.Close();
}


void DrawEff(TString muonStep2, TString muonStep1){

  TCanvas* c;

  c = new TCanvas("c"+muonStep2+muonStep1+"Loss2D",muonStep2+muonStep1+" Loss2D rates", 1024, 768);

  c->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , muonStep2, muonStep1, c->cd( 1));
  DrawLoss2D("Mu-Pt50"  , muonStep2, muonStep1, c->cd( 2));
  DrawLoss2D("Mu-Pt100" , muonStep2, muonStep1, c->cd( 3));
  DrawLoss2D("Mu-Pt500" , muonStep2, muonStep1, c->cd( 4));
  DrawLoss2D("Mu-Pt1000", muonStep2, muonStep1, c->cd( 5));
  
  DrawLoss2D("Mu+Pt10"  , muonStep2, muonStep1, c->cd( 6));
  DrawLoss2D("Mu+Pt50"  , muonStep2, muonStep1, c->cd( 7));
  DrawLoss2D("Mu+Pt100" , muonStep2, muonStep1, c->cd( 8));
  DrawLoss2D("Mu+Pt500" , muonStep2, muonStep1, c->cd( 9)); 
  DrawLoss2D("Mu+Pt1000", muonStep2, muonStep1, c->cd(10));
  
  c->Print("plots/Eff2D"+muonStep2+muonStep1+".gif");
}
