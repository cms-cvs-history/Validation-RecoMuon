#!/bin/bash 

export PKGDIR=$CMSSW_BASE/src/Validation/RecoMuon
export OUTDIR=$PKGDIR/data/RootHisto_`date +%Y%m%d%H%M`

[ -d $OUTDIR ] || mkdir $OUTDIR

QUEUE=1nh
RUNSCRIPT=run.sh

for i in Mu-Pt1000 Mu+Pt1000 \
         Mu-Pt500  Mu+Pt500  \
         Mu-Pt100  Mu+Pt100  \
         Mu-Pt50   Mu+Pt50   \
         Mu-Pt10   Mu+Pt10   
do
  bsub -q $QUEUE -oo /dev/null $RUNSCRIPT $i
done

