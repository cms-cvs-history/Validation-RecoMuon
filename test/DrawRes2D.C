void DrawRes2D()
{
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  DrawResQHists("Pt10"  );
  DrawResQHists("Pt50"  );
  DrawResQHists("Pt100" );
  DrawResQHists("Pt500" );
  DrawResQHists("Pt1000");
}

void DrawResQHists(TString sample)
{
  TCanvas* c = new TCanvas(sample+"Canvas", sample+" sigma(q/pT)", 1024, 768);
  c->Divide(2,3);

  DrawResVsEta(TString("Mu+")+sample, "Seed", c->cd(1));
  DrawResVsEta(TString("Mu-")+sample, "Seed", c->cd(2));
  DrawResVsEta(TString("Mu+")+sample, "Sta" , c->cd(3));
  DrawResVsEta(TString("Mu-")+sample, "Sta" , c->cd(4));
  DrawResVsEta(TString("Mu+")+sample, "Glb" , c->cd(5));
  DrawResVsEta(TString("Mu-")+sample, "Glb" , c->cd(6));

  c->Print(TString("plots/Res2DMu")+sample+".gif");
}

void DrawResVsEta(TString sampleName, TString muonType, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(sampleName+".root"); file.cd();

  gROOT->cd();
  TH2F* his = (TH2F*)(file.Get(muonType+"EtaVsErrQPt")->Clone());
  his->Rebin2D(1,2);

  his->SetTitle(sampleName+muonType+" Muon #eta vs #sigma(q/p_{T})");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("PTDR #sigma(q/p_{T})");
  his->Draw("COLZ");

  file.Close();
}
