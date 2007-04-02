#!/usr/bin/env python

queue = '8nh'

import os, sys, datetime

usage = 'Usage : %s nFiles' % sys.argv[0]
args = sys.argv[1:]

if len(args) != 1:
	print usage
	sys.exit(2)

try:
	nFiles = int(args[0])
except:
	print 'Invaid input of number of Files'
	print usage
	sys.exit(3)

# Parameters for all samples
parameters = {
	'Mu-Pt1000':{'minPt':750, 'maxPt':1500, 'widthSeedErrQPt':100, 'widthStaErrQPt':10, 'widthGlbErrQPt':2   },
	'Mu+Pt1000':{'minPt':750, 'maxPt':1500, 'widthSeedErrQPt':100, 'widthStaErrQPt':10, 'widthGlbErrQPt':2   },
	'Mu-Pt500' :{'minPt':300, 'maxPt':750,  'widthSeedErrQPt':20,  'widthStaErrQPt':5,  'widthGlbErrQPt':1   },
	'Mu+Pt500' :{'minPt':300, 'maxPt':750,  'widthSeedErrQPt':20,  'widthStaErrQPt':5,  'widthGlbErrQPt':1   },
	'Mu-Pt100' :{'minPt':75,  'maxPt':300,  'widthSeedErrQPt':10,  'widthStaErrQPt':5,  'widthGlbErrQPt':0.5 },
	'Mu+Pt100' :{'minPt':75,  'maxPt':300,  'widthSeedErrQPt':10,  'widthStaErrQPt':5,  'widthGlbErrQPt':0.5 },
	'Mu-Pt50'  :{'minPt':30,  'maxPt':75,   'widthSeedErrQPt':7,   'widthStaErrQPt':3,  'widthGlbErrQPt':0.2 },
	'Mu+Pt50'  :{'minPt':30,  'maxPt':75,   'widthSeedErrQPt':7,   'widthStaErrQPt':3,  'widthGlbErrQPt':0.2 },
	'Mu-Pt10'  :{'minPt':0,   'maxPt':30,   'widthSeedErrQPt':5,   'widthStaErrQPt':2,  'widthGlbErrQPt':0.2 },
	'Mu+Pt10'  :{'minPt':0,   'maxPt':30,   'widthSeedErrQPt':5,   'widthStaErrQPt':2,  'widthGlbErrQPt':0.2 }
}

# Dictionary of sample name - paths to files
samples = {
	'Mu-Pt1000':(
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/04E1C9EF-DD9B-DB11-A623-00096BB5C55E.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/1E55E5FC-E09B-DB11-8030-00096BB5C0EC.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/2280361B-DE9B-DB11-AD25-00096B003F59.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/2842E016-DF9B-DB11-A660-00096BB5C55E.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/2EC80C34-FA9B-DB11-84CF-00096BB5C54A.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/3A7DD75D-E09B-DB11-8517-00096BB5BEEA.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/3A8AD826-E19B-DB11-8202-00096BB5BECE.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/3C51E7B0-DE9B-DB11-8D5F-00096BB5C0EE.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/4629C1CC-DE9B-DB11-8E10-00096BB5BEE2.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/4685D71D-DF9B-DB11-908C-00096BB5C526.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/4E92C7CF-E19B-DB11-9041-00096BB5C484.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/54647BF6-DE9B-DB11-9EC5-00096BB5BFAC.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/586B1D65-E19B-DB11-A5AF-00096BB5BDAA.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/5E68EB3E-E19B-DB11-917A-00096BB5CC34.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/78A50C38-DE9B-DB11-963C-00096BB5C596.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/9C8CFA92-DF9B-DB11-B4F7-00096BB5C48C.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/B8A701A7-DD9B-DB11-A801-00096BB5BECE.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/CA016323-DF9B-DB11-B538-00096BB5C10E.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuMinus-Pt1000/0001/D21C72E3-DD9B-DB11-8B33-00096BB5BDAA.root'),
	'Mu+Pt1000':(
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/1A171A8C-429F-DB11-8F08-00304828FD0E.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/2E082FE6-3E9D-DB11-9474-003048597E7B.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/3AFB2807-C99E-DB11-83D8-00304875A901.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/5498D3A6-329D-DB11-9272-003048597ECB.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/5C34C262-B59E-DB11-BFC7-003048597D6B.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/74549B86-C3A1-DB11-896F-003048597D77.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/820A7727-CC9E-DB11-9487-003048597D6B.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/94C79376-329E-DB11-9A0B-00304828FDEA.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/9828550A-C89E-DB11-868A-003048597D6B.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/BA346D58-CA9E-DB11-BFBF-0030485318C7.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/BA6EC834-2C9E-DB11-BA2B-00304828FDEA.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0001/D0D19007-419D-DB11-83DE-00304875A863.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0003/B8ECA550-46A5-DB11-9AC9-003048597D65.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0004/10B1222D-5DA5-DB11-B6D0-00304853CC4B.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0004/D80B254B-D4A4-DB11-9040-003048597E95.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0004/DE7BA697-5DA5-DB11-B196-00304853CB19.root',
'/store/mc/2007/1/2/mc-physval-120-SingleMuPlus-Pt1000/0004/E87D8254-D2A4-DB11-BB06-00304853CACD.root'),
	'Mu-Pt500':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/0204155C-4A98-DB11-A370-00093D139F2B.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/0E085A75-4A98-DB11-AE0D-00E08158D36A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/100C385A-4A98-DB11-8CFB-00093D139C58.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/1021D7EA-2398-DB11-84F6-005045BBA244.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/10323866-4A98-DB11-8C5A-00E08158AE31.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/16F19B6A-4A98-DB11-AFC5-00E08158AE51.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/3052E172-4A98-DB11-8C22-00E08158D320.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/44625459-4A98-DB11-B82F-00093D139C58.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/5ECD69A2-6297-DB11-8214-005045BBA20A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/64B25975-4A98-DB11-A927-00E08158D36A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/682CF678-4A98-DB11-8F27-00E081585AD8.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/8E489D8F-4A98-DB11-879F-00E08158EE94.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/92B9B8A6-6297-DB11-A98E-005045010EDE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/9C4441A7-6297-DB11-8EF2-005045010F38.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/A0A7BF74-4A98-DB11-A405-00E081585AD8.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/A86F9D8F-4A98-DB11-820F-00E08158EE94.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/B49BB15C-4A98-DB11-BB6D-00E08158AE31.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/DAA6F26C-4A98-DB11-A3F2-00E08158AE51.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/E81BEB9C-9F97-DB11-92BE-00E08158AE31.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt500/0000/F678839F-E997-DB11-AE9B-00093D139EE5.root'),
	'Mu+Pt500':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/0655EBDD-E897-DB11-82DF-00093D139C58.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/5A561627-A995-DB11-8C77-00093D139FC1.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/7057B752-4A98-DB11-8EB6-00093D139EE5.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/7C862B58-E395-DB11-8BC2-00E08158AE31.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/9C680723-A995-DB11-9569-00093D139F2B.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/B0502B81-A895-DB11-A4F6-00093D139F2B.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/BCCFF336-A995-DB11-9BD3-00093D139C58.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/C8041CE2-A895-DB11-9391-00E08158D320.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/CEE8643B-A995-DB11-8981-00E08158CFA6.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt500/0000/E2126CE2-A895-DB11-93BE-005045010E7A.root'),
	'Mu-Pt100':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/0490CFD6-6695-DB11-AB1D-00145E1D63A2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/04D46AB6-6695-DB11-82A9-00145E1D6432.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/0E8AB8E1-6495-DB11-8F98-00145E1D64B6.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/1C05EAC2-6495-DB11-932C-00145E1DB4D8.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/72EA9BB3-5E95-DB11-AFC3-00C09FD9499A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/762CDBBE-6495-DB11-97D3-00145E1D63A2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/7C49BCB3-6695-DB11-8A54-00145E1DB4EA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/8A38336B-5E95-DB11-84DB-00C09FD94A50.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/987A6BED-6295-DB11-8314-00145E1D6432.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/9E2FB989-5E95-DB11-A945-00145E1D647A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/A87E8A18-5F95-DB11-966C-00145E1D65D0.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/BE4B30D6-6895-DB11-A0CA-00145E1DB4EA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/C008A886-5E95-DB11-A882-00145E1D6432.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/C27A5D6C-5E95-DB11-92E0-00C09FBD3FEE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt100/0000/F0D454C3-6495-DB11-8A7F-00145E1D644A.root'),
	'Mu+Pt100':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/04B074BD-B496-DB11-B4BF-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/064C3D23-AC96-DB11-A216-00096B005334.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/0AC496C2-B496-DB11-86FB-00096B005334.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/0EEEEFD0-AB96-DB11-B940-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/1445A004-B696-DB11-8899-00096B00531C.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/16C04DD5-B596-DB11-802F-00096B005334.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/1C1966C8-B496-DB11-8AB4-00096BB5BFAC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/32F0F7D5-B496-DB11-8166-00096B0032C5.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/426E707E-A696-DB11-B3E7-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/4E92EAD9-B496-DB11-9E2A-00096B0043E8.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/5A3B5AD8-B496-DB11-89DD-00096B0053C2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/6045B2C0-B496-DB11-8152-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/628BB2C8-B496-DB11-B507-00096B0053F0.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/62F609D8-B596-DB11-8D3C-00096B0053F0.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/784EF4C6-A596-DB11-8216-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/78D178BA-B496-DB11-AA19-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/8A20FBF3-AB96-DB11-8CB1-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/8CDE58D7-B496-DB11-B862-00096B00531C.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/8EB6A919-B696-DB11-925F-00096B0043E8.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/92BFEBC1-A596-DB11-B369-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/94F4F5AC-B596-DB11-9BCA-00096BB5BFAC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/A62A15FA-AB96-DB11-ADFA-00096BB5BFAC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/AAAD7E22-AC96-DB11-A269-00096B0053F0.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/AEB649D2-AB96-DB11-88E6-00096BB5BFAC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/AED44B1B-B696-DB11-A62C-00096B0053C2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/D4136BFB-AB96-DB11-B7EF-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/D461B3C0-B496-DB11-8F67-00096BB5BFFA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/E6AECE1C-AC96-DB11-9C8C-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/E6DF3CA6-B596-DB11-B149-00096BB5BFFA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt100/0000/F276B31D-B696-DB11-87A7-001560EDC951.root'),
	'Mu-Pt50':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/3EB62571-D896-DB11-ACFD-0016353E0E6F.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/40E61446-D896-DB11-A148-0015605F3463.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/46087D2B-E596-DB11-8CFA-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/5859A17D-DE96-DB11-9604-00096BB5BFFA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/728FB31E-E596-DB11-BBC7-00096BB5BFFA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/7AE20D19-E596-DB11-B029-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/92370E0B-E596-DB11-A47C-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/A2652CE0-EA96-DB11-A38F-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/A64AD2E2-EA96-DB11-9FB9-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/B617D215-E596-DB11-AD78-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/CE5C037F-DE96-DB11-947F-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/DE8C1D53-D896-DB11-ABA5-00096BB5C0EE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/F8CE0A15-EB96-DB11-965D-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt50/0000/FAB5E15D-D896-DB11-A602-001560EDC951.root'),
	'Mu+Pt50':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/1C5FCDD6-A396-DB11-8066-00096BB5C598.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/26462EC6-A396-DB11-9A91-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/32BC03D8-A396-DB11-8D5D-00096BB5C006.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/34943DCE-A396-DB11-A677-00096BB5BDD6.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/367ACCF1-A496-DB11-9415-00096BB5C006.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/3E74D09A-A596-DB11-B548-001560EDC951.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/5ADB42E7-A496-DB11-97DB-00096BB5C3FC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/62CABECF-A396-DB11-ACD1-00096BB5C3FC.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/7C7872DB-A396-DB11-98D3-00096BB5C08A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/964073D0-A396-DB11-8597-00096BB5C08A.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/A89F1EC7-A496-DB11-8A3E-00096BB5BFD2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/B87D09CC-A396-DB11-83E6-00096BB5C0E2.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/DCB9D9DC-A396-DB11-B734-0016353E0E6F.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt50/0000/E2941BCE-A396-DB11-A738-00096BB5C094.root'),
	'Mu-Pt10':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/0293C1AE-5A95-DB11-A46C-00E081348C93.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/0A645686-5B95-DB11-BB7A-00E081348D25.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/5A70BBA6-5B95-DB11-B3C4-00E081348CEB.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/5AFFBD92-6095-DB11-BE08-00E081348D25.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/7695DD59-5995-DB11-B6F4-00E0813493CD.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/86C0941A-5B95-DB11-A862-00E08104DA95.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/9CBE1C08-5E95-DB11-9EE9-00E081348C93.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/9E88D3FB-5A95-DB11-88A8-00E081348CEB.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/B8825D77-5A95-DB11-9BB1-00E081348D25.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/C22A11E3-6095-DB11-9A4C-00E081348C93.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/DA71DEC1-5A95-DB11-8937-00E0813493CD.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/E016F182-5995-DB11-AC5A-0030487276ED.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/E04A222D-5E95-DB11-9048-00E081348CC5.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/F2486429-5B95-DB11-9987-00E081349B33.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuMinus-Pt10/0000/F2C61D4E-5E95-DB11-9D42-00E0813493CD.root'),
	'Mu+Pt10':(
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/229F994B-4898-DB11-B0B2-00E081053FCD.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/2CF3CA43-4898-DB11-A516-003048724753.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/327C43C9-4798-DB11-95E7-0030487277AE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/424029C4-4798-DB11-B485-003048727708.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/4E4962B1-4D98-DB11-8927-003048724771.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/704B24C2-4798-DB11-BEF5-003048724752.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/724A63B3-4D98-DB11-94F7-00E0812040E6.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/766A2064-4898-DB11-A3A8-00E081203FBA.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/80E06337-4898-DB11-BAB4-0030487276BE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/862BEC21-4898-DB11-A8D2-0030487247A3.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/8876ACD8-4798-DB11-8CF0-00304872476C.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/8EDB7BB6-4D98-DB11-8691-00304872474B.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/B202C806-4898-DB11-A802-003048723EBE.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/DAC143BC-4D98-DB11-864D-00304872474F.root',
'/store/mc/2006/12/21/mc-physval-120-SingleMuPlus-Pt10/0000/F47CBF66-4898-DB11-B4D1-0030487276F7.root'),
}

# Create working directory
pkgdir = '%s/src/Validation/RecoMuon' % os.environ['CMSSW_BASE']
date = datetime.datetime.now().strftime('%Y%m%d-%H%M')
outdir = '%s/data/%s' % (pkgdir, date)
os.mkdir(outdir)

# Read templates
recoTm = open('template_reco.cfg').read()
validTm = open('template_validation.cfg').read()

# Generate cfgs for all samples
for sampleName, sampleFiles in samples.items():
	for i in range(1,len(sampleFiles), nFiles):
		section = i/nFiles
		recoCfgFileName = '%s/reco_%s_%d.cfg' % (outdir, sampleName, section)
		validCfgFileName = '%s/%s_%d.cfg' % (outdir, sampleName, section)

		# Generate cfg for re-reconstruction
		filePath = str(sampleFiles[i:i+nFiles]).replace('(','{').replace(')','}')
		recoCfg = recoTm.replace('@FILEPATH@', filePath)
		open(recoCfgFileName, 'w').write(recoCfg)

		# Generate cfg for Validator
		validCfg = validTm.replace('@OUTPUT@', '%s_%d.root' % (sampleName, section))
		for parKey, parVal in parameters[sampleName].items():
			validCfg = validCfg.replace('@%s@'%parKey, str(parVal))
		open(validCfgFileName, 'w').write(validCfg)

		# submit to batch server
		os.putenv('OUTDIR', outdir)
		os.system("bsub -q %s -oo /dev/null run.sh %s_%d" % (queue, sampleName, section))

