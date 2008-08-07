import FWCore.ParameterSet.Config as cms

from Validation.RecoMuon.TrackingParticleSelectionForMuonEfficiency_cfi import *
multiStaTrackValidatorPos = cms.EDFilter("MultiTrackValidator",
    TrackingParticleSelectionForMuonEfficiency,
    useFabsEta = cms.bool(False),
    minpT = cms.double(0.0),
    nintHit = cms.int32(75),
    associatormap = cms.InputTag("tpToStaTrackAssociationPos"),
    label_tp_fake = cms.InputTag("mergedtruth","MergedTrackTruth"),
    out = cms.string('validationPlots.root'),
    min = cms.double(-2.5),
    maxPhi = cms.double(3.15),
    nintpT = cms.int32(300),
    label = cms.VInputTag(cms.InputTag("standAloneMuons","UpdatedAtVtx")),
    maxHit = cms.double(75.0),
    label_tp_effic = cms.InputTag("mergedtruth","MergedTrackTruth"),
    useInvPt = cms.bool(False),
    dirName = cms.string('RecoMuonV/MultiTrack/'),
    minHit = cms.double(0.0),
    sim = cms.string('g4SimHits'),
    associators = cms.vstring('TrackAssociatorByPosition'),
    max = cms.double(2.5),
    maxpT = cms.double(3100.0),
    nint = cms.int32(50),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    nintPhi = cms.int32(63),
    UseAssociators = cms.bool(False),
    minPhi = cms.double(-3.15)
)


