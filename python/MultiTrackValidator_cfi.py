import FWCore.ParameterSet.Config as cms

from Validation.RecoMuon.selectors_cff import *
from Validation.RecoMuon.associators_cff import *

import Validation.RecoTrack.MultiTrackValidator_cfi

RMmultiTrackValidator = Validation.RecoTrack.MultiTrackValidator_cfi.multiTrackValidator.clone()
RMmultiTrackValidator.dirName = 'RecoMuonV/MultiTrack/'
RMmultiTrackValidator.pdgIdTP = (13,-13)

RMmultiTrackValidator.useFabsEta = False
RMmultiTrackValidator.nint = cms.int32(25)
RMmultiTrackValidator.min = cms.double(0)
RMmultiTrackValidator.max = cms.double(2.5)

RMmultiTrackValidator.nintPhi = cms.int32(36)
RMmultiTrackValidator.minPhi = cms.double(-3.15)
RMmultiTrackValidator.maxPhi = cms.double(3.15)

RMmultiTrackValidator.nintpT = cms.int32(25)
RMmultiTrackValidator.minpT = cms.double(0.0)
RMmultiTrackValidator.maxpT = cms.double(1100.0)

RMmultiTrackValidator.nintHit = cms.int32(75)
RMmultiTrackValidator.minHit = cms.double(-0.5)
RMmultiTrackValidator.maxHit = cms.double(74.5)

RMmultiTrackValidator.phiRes_rangeMin = cms.double(-0.1)
RMmultiTrackValidator.phiRes_rangeMax = cms.double(0.1)
 
RMmultiTrackValidator.UseAssociators = False





