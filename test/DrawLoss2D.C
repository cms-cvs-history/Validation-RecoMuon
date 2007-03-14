void DrawLoss2D()
{
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  TCanvas* c;

  c = new TCanvas("cSeedLoss2D", "SeedMuon Loss2D rates", 1024, 768);
  c->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Seed", "Sim", c->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Seed", "Sim", c->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Seed", "Sim", c->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Seed", "Sim", c->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Seed", "Sim", c->cd( 5));
  
  DrawLoss2D("Mu+Pt10"  , "Seed", "Sim", c->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Seed", "Sim", c->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Seed", "Sim", c->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Seed", "Sim", c->cd( 9)); 
  DrawLoss2D("Mu+Pt1000", "Seed", "Sim", c->cd(10));
  
  c->Print("plots/Eff2DSeed.gif");

  c = new TCanvas("c", "StaMuon Loss2D rates", 1024, 768); 
  c->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Sta", "Sim", c->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Sta", "Sim", c->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Sta", "Sim", c->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Sta", "Sim", c->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Sta", "Sim", c->cd( 5));

  DrawLoss2D("Mu+Pt10"  , "Sta", "Sim", c->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Sta", "Sim", c->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Sta", "Sim", c->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Sta", "Sim", c->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Sta", "Sim", c->cd(10));

  c->Print("plots/Eff2DSta.gif");

  c = new TCanvas("c", "GlbMuon Loss2D rates", 1024, 768); 
  c->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Glb", "Sim", c->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Glb", "Sim", c->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Glb", "Sim", c->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Glb", "Sim", c->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Glb", "Sim", c->cd( 5));
                                               
  DrawLoss2D("Mu+Pt10"  , "Glb", "Sim", c->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Glb", "Sim", c->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Glb", "Sim", c->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Glb", "Sim", c->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Glb", "Sim", c->cd(10));

  c->Print("plots/Eff2DGlb.gif");

  c = new TCanvas("c", "GlbMuon/StaMuon Loss2D rates", 1024, 768); 
  c->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Glb", "Sta", c->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Glb", "Sta", c->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Glb", "Sta", c->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Glb", "Sta", c->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Glb", "Sta", c->cd( 5));
                                                  
  DrawLoss2D("Mu+Pt10"  , "Glb", "Sta", c->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Glb", "Sta", c->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Glb", "Sta", c->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Glb", "Sta", c->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Glb", "Sta", c->cd(10));

  c->Print("plots/Eff2DGlbSta.gif");
  
}

void DrawLoss2D(TString sampleName, TString muonType1, TString muonType2, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(sampleName+".root"); file.cd();

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
