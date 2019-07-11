if (dv_pos.perp() > 150){
    passMaterialVeto_v3 = ( m_materialMap_v3_Outer->GetBinContent(m_materialMap_v3_Outer->FindBin( dv_pos.perp() ,
												   dv_pos.phi() ,
												   dv_pos.z() ) ) == 0);
}
else {
    for (Int_t i=0;i<5;i++){
        if (dv_pos.perp() < (*m_materialMap_v32_Matrix)[i][0]){
	    float test_x = dv_pos.x() + (*m_materialMap_v32_Matrix)[i][1];
	    float test_y = dv_pos.y() + (*m_materialMap_v32_Matrix)[i][2];
	    double calc_phi = fmod( TMath::ATan2(test_y,test_x),TMath::Pi()/(*m_materialMap_v32_Matrix)[i][3] );
	    if (calc_phi <0) calc_phi = calc_phi + TMath::Pi()/(*m_materialMap_v32_Matrix)[i][3];
	    
	    passMaterialVeto_v3 = ( m_materialMap_v32_Inner->GetBinContent(m_materialMap_v32_Inner->FindBin( sqrt(test_x*test_x + test_y*test_y ) ,
													     calc_phi , 
													     dv_pos.z() ) ) == 0);
	    break;
	}
    }
}
