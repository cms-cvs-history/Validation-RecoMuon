TLegend* gLegend;
int gLineColor;

void ConnectLines(TH1F* hist, TString name)
{
  if ( hist->GetEntries() == 0 ) return;
  const int nBin = hist->GetNbinsX();
  TGraph* grp = new TGraph(nBin);
  for(int i=0; i<nBin; i++) {
    grp->SetPoint(i, hist->GetBinCenter(i+1), hist->GetBinContent(i+1));
  }
  grp->SetLineWidth(1);
  grp->SetLineColor(gLineColor);
  grp->Draw("LPSame");
  gLegend->AddEntry(grp, name, "L");
}

TH1F* FoldH1(TH1F* hist)
{
  if ( hist->GetNbinsX()%2 != 0 ) cerr << "Warning : nBin of original histo is not even!\n";
  const int nBins = hist->GetNbinsX()/2;
  const double xMin = hist->GetXaxis()->GetXmin();
  const double xMax = hist->GetXaxis()->GetXmax();
  if ( xMin != -xMax ) cerr << "Warning : Folding a histogram with asymmetric x range\n";
  double newXMax = TMath::Max(-xMin, xMax);
  TH1F* newHist = new TH1F(TString(hist->GetName())+"fold", hist->GetTitle(), nBins, 0, newXMax);

  for(int i=0; i<nBins; i++) {
    newHist->SetBinContent(i, hist->GetBinContent(nBins+i)+hist->GetBinContent(nBins-i-1));
  }

  //delete hist;
  return newHist;
}

double gMeanMax, gWidthMin, gWidthMax, gChi2Max;
void DrawFitSlice(TString dataName, TString muonType, TString histoName,
                  TCanvas* cMean, TCanvas* cWidth, TCanvas* cChi2)
{
  gROOT->cd();
  TFile file(dataName+".root"); 
  if(file.IsZombie()) return;
  file.cd();
  TH2F* resHist = (TH2F*)file.Get(muonType+histoName);
  const double yMin = TMath::Max(resHist->GetYaxis()->GetXmin(), -gMeanMax);
  const double yMax = TMath::Min(resHist->GetYaxis()->GetXmax(), gMeanMax);

  TF1 gaus("gaus", "gaus");
  gaus.SetParameters(1.0, 0.0, gWidthMax);
  gaus.SetRange(yMin, yMax);

  gROOT->cd(); TDirectory dir("dir", "dir"); dir.cd();
  resHist->FitSlicesY(&gaus);

  gROOT->cd();
  TH1F* hMean  = (TH1F*)dir.Get(muonType+histoName+"_1")->Clone();
  TH1F* hWidth = (TH1F*)dir.Get(muonType+histoName+"_2")->Clone();
  TH1F* hChi2  = (TH1F*)dir.Get(muonType+histoName+"_chi2")->Clone();

  hMean ->SetTitle(muonType+"Muon "+histoName+" gaussian mean");
  hWidth->SetTitle(muonType+"Muon "+histoName+" gaussian width");
  hChi2 ->SetTitle(muonType+"Muon "+histoName+" gaussian fit chi2");

  hMean ->GetYaxis()->SetTitle("Gaussian mean");
  hWidth->GetYaxis()->SetTitle("Gaussian width");
  hChi2 ->GetYaxis()->SetTitle("Gaussian #Chi^2");

  hMean ->SetMinimum(-gMeanMax);
  hMean ->SetMaximum(gMeanMax);
  hWidth->SetMinimum(gWidthMin);
  hWidth->SetMaximum(gWidthMax);
  hChi2 ->SetMinimum(0); 
  hChi2 ->SetMaximum(gChi2Max);

  hMean ->SetLineColor(gLineColor);
  hWidth->SetLineColor(gLineColor);
  hChi2 ->SetLineColor(gLineColor);

  TString optColor(gLineColor==1 ? "" : "same");
  TString optErr = "E1X0" + optColor;

  cMean ->cd(); 
  hMean ->Draw(optErr);

  cWidth->cd(); 
  hWidth->Draw(optErr);
  ConnectLines(hWidth, muonType+dataName);

  cChi2 ->cd(); 
  hChi2 ->Draw(optColor);

  if ( ++gLineColor==kYellow ) ++gLineColor;

  file.Close();
}

