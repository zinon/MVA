
categories=(
#    	vbf
# 	boosted
#  	1jet
# 	0jet
  	preselection
	)

variables=(
#        BDT_Weight
#
#  	averageIntPerXing
# 	
#   	dijet_dEta
#  	dijet_dPhi
#  	dijet_eta1_x_eta2
#  	dijet_mass
#  	ditau_colapprox_x0
#  	ditau_colapprox_x1
#  	ditau_cosTheta
# #    	ditau_dEta
# 	ditau_dijet_met_VecSumPt
#    	ditau_dR
#   	ditau_mass_col
    ditau_mass_mmc
#  	ditau_mass_vis
# 	ditau_met_VecSumPt
#   	ditau_pT_0_over_pT_1
# 	
#  	esv_all_objects_aplanarity
#  	esv_all_objects_FoxWolfram_R1
#  	esv_all_objects_FoxWolfram_R2
#  	esv_all_objects_planarity
#  	esv_all_objects_sphericity
# 	
#  	HT_jets
# 	HT_jets_taus
#  	HT_jets_taus_met
#  	
#   	jet_0_eta
#   	jet_0_pt
#  	jet_1_eta
#    	jet_1_pt
#  		
#  	met_centrality
#  	met_et
#  	met_phi
# 	
#  	MMC_met_et
#  	MMC_resonance_dijet_DeltaPhi
#  	MMC_resonance_dijet_DeltaPt
#  	MMC_resonance_dijet_vecSumPt
#  	MMC_resonance_jets_min_dEta
#  	MMC_resonance_jets_min_dR
#  	MMC_resonance_pt
#  	MMC_resonance_x0
#  	MMC_resonance_x1
#  		
#  	tau_0_BDT_score
#  	tau_0_dijet_eta_centr
#   	tau_0_eta
#  	tau_0_pt
# 	tau_0_phi
#    tau_0_tracks
#  	tau_1_BDT_score
#  	tau_1_dijet_eta_centr
#   	tau_1_eta
#   tau_1_pt
# 	tau_1_phi
#    	tau_1_tracks	
	)

i=${#categories[@]}
j=${#variables[@]}
ij=$(($i * $j))
c=1
for iCat in "${categories[@]}"
do
	for iVar in "${variables[@]}"
	do
        echo $c "/" $ij
		root -x -l -b RunMultiPlots.C\(\"$iCat\",\"$iVar\"\)
        echo ""
		c=$((c+1))
	done
	
done
