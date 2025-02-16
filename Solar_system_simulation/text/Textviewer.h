#pragma once
#include <iostream>
#include "SupportADessin.h"

class TextViewer : public SupportADessin {
	
	public:
	
    TextViewer(std::ostream& s = std::cout):
        sortie(s){}
	
	
    void dessine(Astre const& p) override;
    void dessine(std::string s) override;


	
	private:
	std::ostream& sortie;
	
};
