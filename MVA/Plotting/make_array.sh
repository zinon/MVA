# ls | sort -n -k1.6 | sed 's/png/png \\/g'
# ls | wc

output=preselection_12x12_correlation_array.pdf

convert \
plot_1_dijet_dEta_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_2_dijet_dEta_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_3_dijet_dEta_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_4_dijet_dEta_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_5_dijet_dEta_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_6_dijet_dEta_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_7_dijet_dEta_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_8_dijet_dEta_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_9_dijet_dEta_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_10_dijet_dEta_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_11_dijet_dEta_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_12_dijet_dEta_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_13_dijet_eta1_x_eta2_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_14_dijet_eta1_x_eta2_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_15_dijet_eta1_x_eta2_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_16_dijet_eta1_x_eta2_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_17_dijet_eta1_x_eta2_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_18_dijet_eta1_x_eta2_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_19_dijet_eta1_x_eta2_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_20_dijet_eta1_x_eta2_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_21_dijet_eta1_x_eta2_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_22_dijet_eta1_x_eta2_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_23_dijet_eta1_x_eta2_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_24_dijet_eta1_x_eta2_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_25_dijet_mass_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_26_dijet_mass_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_27_dijet_mass_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_28_dijet_mass_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_29_dijet_mass_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_30_dijet_mass_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_31_dijet_mass_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_32_dijet_mass_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_33_dijet_mass_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_34_dijet_mass_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_35_dijet_mass_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_36_dijet_mass_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_37_ditau_dijet_met_VecSumPt_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_38_ditau_dijet_met_VecSumPt_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_39_ditau_dijet_met_VecSumPt_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_40_ditau_dijet_met_VecSumPt_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_41_ditau_dijet_met_VecSumPt_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_42_ditau_dijet_met_VecSumPt_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_43_ditau_dijet_met_VecSumPt_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_44_ditau_dijet_met_VecSumPt_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_45_ditau_dijet_met_VecSumPt_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_46_ditau_dijet_met_VecSumPt_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_47_ditau_dijet_met_VecSumPt_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_48_ditau_dijet_met_VecSumPt_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_49_ditau_dR_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_50_ditau_dR_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_51_ditau_dR_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_52_ditau_dR_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_53_ditau_dR_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_54_ditau_dR_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_55_ditau_dR_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_56_ditau_dR_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_57_ditau_dR_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_58_ditau_dR_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_59_ditau_dR_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_60_ditau_dR_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_61_ditau_mass_mmc_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_62_ditau_mass_mmc_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_63_ditau_mass_mmc_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_64_ditau_mass_mmc_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_65_ditau_mass_mmc_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_66_ditau_mass_mmc_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_67_ditau_mass_mmc_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_68_ditau_mass_mmc_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_69_ditau_mass_mmc_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_70_ditau_mass_mmc_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_71_ditau_mass_mmc_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_72_ditau_mass_mmc_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_73_ditau_pT_0_over_pT_1_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_74_ditau_pT_0_over_pT_1_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_75_ditau_pT_0_over_pT_1_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_76_ditau_pT_0_over_pT_1_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_77_ditau_pT_0_over_pT_1_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_78_ditau_pT_0_over_pT_1_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_79_ditau_pT_0_over_pT_1_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_80_ditau_pT_0_over_pT_1_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_81_ditau_pT_0_over_pT_1_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_82_ditau_pT_0_over_pT_1_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_83_ditau_pT_0_over_pT_1_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_84_ditau_pT_0_over_pT_1_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_85_HT_jets_taus_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_86_HT_jets_taus_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_87_HT_jets_taus_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_88_HT_jets_taus_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_89_HT_jets_taus_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_90_HT_jets_taus_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_91_HT_jets_taus_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_92_HT_jets_taus_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_93_HT_jets_taus_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_94_HT_jets_taus_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_95_HT_jets_taus_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_96_HT_jets_taus_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_97_MMC_resonance_x0_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_98_MMC_resonance_x0_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_99_MMC_resonance_x0_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_100_MMC_resonance_x0_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_101_MMC_resonance_x0_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_102_MMC_resonance_x0_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_103_MMC_resonance_x0_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_104_MMC_resonance_x0_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_105_MMC_resonance_x0_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_106_MMC_resonance_x0_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_107_MMC_resonance_x0_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_108_MMC_resonance_x0_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_109_MMC_resonance_x1_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_110_MMC_resonance_x1_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_111_MMC_resonance_x1_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_112_MMC_resonance_x1_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_113_MMC_resonance_x1_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_114_MMC_resonance_x1_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_115_MMC_resonance_x1_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_116_MMC_resonance_x1_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_117_MMC_resonance_x1_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_118_MMC_resonance_x1_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_119_MMC_resonance_x1_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_120_MMC_resonance_x1_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_121_tau_0_dijet_eta_centr_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_122_tau_0_dijet_eta_centr_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_123_tau_0_dijet_eta_centr_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_124_tau_0_dijet_eta_centr_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_125_tau_0_dijet_eta_centr_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_126_tau_0_dijet_eta_centr_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_127_tau_0_dijet_eta_centr_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_128_tau_0_dijet_eta_centr_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_129_tau_0_dijet_eta_centr_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_130_tau_0_dijet_eta_centr_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_131_tau_0_dijet_eta_centr_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_132_tau_0_dijet_eta_centr_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_133_tau_1_dijet_eta_centr_Vs_dijet_dEta_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_134_tau_1_dijet_eta_centr_Vs_dijet_eta1_x_eta2_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_135_tau_1_dijet_eta_centr_Vs_dijet_mass_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_136_tau_1_dijet_eta_centr_Vs_ditau_dijet_met_VecSumPt_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_137_tau_1_dijet_eta_centr_Vs_ditau_dR_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_138_tau_1_dijet_eta_centr_Vs_ditau_mass_mmc_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_139_tau_1_dijet_eta_centr_Vs_ditau_pT_0_over_pT_1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_140_tau_1_dijet_eta_centr_Vs_HT_jets_taus_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_141_tau_1_dijet_eta_centr_Vs_MMC_resonance_x0_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_142_tau_1_dijet_eta_centr_Vs_MMC_resonance_x1_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_143_tau_1_dijet_eta_centr_Vs_tau_0_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
plot_144_tau_1_dijet_eta_centr_Vs_tau_1_dijet_eta_centr_preselection_125_CR_preselection_notOS_TrkFit_v12.png \
$output
