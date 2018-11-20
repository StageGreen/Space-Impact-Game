#ifndef GUNUPGRADE_H_INCLUDED
#define GUNUPGRADE_H_INCLUDED

#include "PowerUp.h"

const size_t gunUpgradeWidth = 7;
const size_t gunUpgradeHeight = 1;
const char gunUpgradeImage[gunUpgradeHeight][gunUpgradeWidth] = {
	{ '[', 'G', ' ', 'U', ' ', 'N', ']' }
};

class GunUpgrade : public PowerUp
{
public:
	GunUpgrade(short X, short Y);
	GunUpgrade(const GunUpgrade& other);
	GunUpgrade& operator=(const GunUpgrade& other);
	virtual ~GunUpgrade();

	virtual size_t getType() const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

private:

};

#endif