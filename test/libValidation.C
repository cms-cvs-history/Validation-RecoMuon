TLegend* gLegend;
int gNHist;

void ConnectLines(TH1F* hist, TString name)
{
  if ( hist->GetEntries() == 0 ) return;
  const int nBin = hist->GetNbinsX();
  TGraph* grp = new TGraph(nBin);
  for(int i=0; i<nBin; i++) {
    grp->SetPoint(i, hist->GetBinCenter(i+1), hist->GetBinContent(i+1));
  }
  grp->SetLineWidth(1);
  grp->SetLineColor(gNHist);
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

