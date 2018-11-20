#ifndef POWERUPCOLLECTION_H_INCLUDED
#define POWERUPCOLLECTION_H_INCLUDED

#include "PowerUp.h"

#include "ExtraLife.h" 
#include "GunUpgrade.h"
#include "Nuke.h"

class PowerUpCollection
{
public:
	PowerUpCollection();
	~PowerUpCollection();

	PowerUp * operator[](short index) const;

	void addPowerUp(PowerUp * newPowerUp);
	void removePowerUp(short index);
	size_t getSize() const;

	void save(std::ostream& out);
	void load(std::istream& in);

private:
	PowerUpCollection(const PowerUpCollection& other) = delete;
	PowerUpCollection& operator=(const PowerUpCollection& other) = delete;

	void resize();
	void clean();

	size_t size;
	size_t capacity;
	PowerUp ** powerUpArray;
};


#endif
