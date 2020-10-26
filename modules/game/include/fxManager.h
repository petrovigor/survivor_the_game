#pragma once

#include <list>
#include "fx.h"
#include "shell.h"

class FX_MANAGER {
private:
	std::list<FX_FLASH> flashes;
	std::list<FX_BLOOD> bloods;
	std::list<SHELL> shells;
	
public:
	std::list<SHELL>* getShellsList(void) {return &shells;}

	void addFlash(double _x, double _y, double newPower, double _lifeTime, const int newVisualType) {
		if(DEBUGVAR_INCLUDE_FXS) flashes.push_back(FX_FLASH(_x, _y, newPower, _lifeTime, newVisualType));
	}

	void setCameraOffset(double X,double Y) {
		for(std::list<FX_BLOOD>::iterator i=bloods.begin(); i!=bloods.end(); ++i) {
			i->setCameraOffset(X,Y);
		}
		for(std::list<FX_FLASH>::iterator i=flashes.begin(); i!=flashes.end(); ++i) {
			i->setCameraOffset(X,Y);
		}
		for(std::list<SHELL>::iterator i=shells.begin(); i!=shells.end(); ++i) {
			i->setCameraOffset(X,Y);
		}
	}

	void depose(double X, double Y) {
		for(std::list<FX_BLOOD>::iterator i=bloods.begin(); i!=bloods.end(); ++i) {
			i->depose(X,Y);
		}
		for(std::list<SHELL>::iterator i=shells.begin(); i!=shells.end(); ++i) {
			i->depose(X,Y);
		}
	}

	void addShell(double newX, double newY, double newAngle) {
		if(DEBUGVAR_INCLUDE_SHELLS) {
			double newSpeed = rand()%100+30;
			double newSize = 1.0;
			double newDecreaseSpeed = newSpeed /1.2;
			double newAngleRate = 90.0 * DEGTORAD;
			double precision = 15 * DEGTORAD;

			if(rand()%2==0) {
				newAngle += ((double)(rand()%(int)(precision*100))/100);
			} else {
				newAngle -= ((double)(rand()%(int)(precision*100))/100);
			}

			shells.push_back(SHELL(newX, newY, newAngle, newSize, newSpeed, newDecreaseSpeed, newAngleRate));
		}
	}

	void addBlood(double newX, double newY, double newAngle, double newRadius, double newSpeed, const int newVisualType/*, PHYSICS_MANAGER *pptr*/) {
		if(DEBUGVAR_INCLUDE_FXS) {
			int offsetAngleMax = 20.0;
		
			int n=rand()%3+1;
			for(int i=0; i<n; i++) {
				double a = 0.0;

				if(rand()%2==0) {
					a=a+rand()% offsetAngleMax;
				} else {
					a=a-rand()% offsetAngleMax;
				}

				a*=DEGTORAD;

				bloods.push_back(FX_BLOOD(newX, newY, newAngle+a, newRadius, newSpeed, newVisualType));
			}
		}
	}

	void draw(HDC bhdc) {
		for(std::list<FX_FLASH>::iterator i=flashes.begin(); i!=flashes.end(); ++i) {
			i->draw(bhdc);
		}
		for(std::list<FX_BLOOD>::iterator i=bloods.begin(); i!=bloods.end(); ++i) {
			i->draw(bhdc);
		}
		for(std::list<SHELL>::iterator i=shells.begin(); i!=shells.end(); ++i) {
			i->draw(bhdc);
		}
	}

	void updateFXs(double deltaTime) {
		for(std::list<FX_FLASH>::iterator i=flashes.begin(); i!=flashes.end(); ++i) {
			i->update(deltaTime);
		}
		for(std::list<FX_BLOOD>::iterator i=bloods.begin(); i!=bloods.end(); ++i) {
			i->update(deltaTime);
		}
		for(std::list<SHELL>::iterator i=shells.begin(); i!=shells.end(); ++i) {
			i->process(deltaTime);
		}

		std::list<FX_FLASH>::iterator i=flashes.begin();
		while(i!=flashes.end()) {
			if(i->getFlag()) {
				flashes.erase(i);
				i=flashes.begin();
			} else {
				i++;
			}
		}

		std::list<FX_BLOOD>::iterator j=bloods.begin();
		while(j!=bloods.end()) {
			if(j->getFlag()) {
				bloods.erase(j);
				j=bloods.begin();
			} else {
				j++;
			}
		}

		std::list<SHELL>::iterator k=shells.begin();
		while(k!=shells.end()) {
			if(!k->is()) {
				shells.erase(k);
				k=shells.begin();
			} else {
				k++;
			}
		}
	}
};
