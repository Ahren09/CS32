#include <string>
#include <iostream>
using namespace std;

// ORDER OF CONSTRUCTION
// 1. The arguments to the constructor
// 2. Any private member variables (initializer list)
// 3. The body of the constructor

class Pokemon {
public:

	Pokemon(string name, int HP, int attack, int defense)
	{
		m_name = name;
		m_HP = HP;
		m_attack = attack;
		m_defense = defense;

		cout << name << " has " << HP << " HP " << attack << 
			" attack " << " and " << defense << " defense." << endl;
	}

	Pokemon() {
		cout << "    There's a spot for a pokemon here!" << endl;
	}

	~Pokemon() {
		cout << "A pokemon was destructed" << endl;
	}

	string getName() const {
		return m_name;
	}

	void attackEnemy(Pokemon &other) {
		other.doDamage(m_attack);
	}

	void doDamage(int attack) {
		m_HP -= attack - (.25 * m_defense);

		if (m_HP < 0) {
			cout << m_name << " fainted!!" << endl;
		}
	}

private:
	string m_name;
	int m_HP, m_attack, m_defense;
};


class Trainer {
public:
	Trainer(string name, Pokemon& starter)
	{
		m_name = name;
		m_pokemon[0] = starter;
		m_numPokemon = 1;

		cout << name << " started with " << starter.getName() << endl;
	}

	~Trainer() {
		cout << m_name << " fought hard with " << m_pokemon[0].getName() << endl;
		cout << "Game over for " << m_name << "!!!" << endl;
	}

private:
	string m_name;
	Pokemon m_pokemon[3];
	int m_numPokemon;
};



int main() {

	Pokemon pikachu("Pikachu", 20, 16, 12);
	Pokemon squirtle("Squirtle", 30, 10, 18);

	Trainer ash("Ash", pikachu);
	Trainer misty("Misty", squirtle);

	pikachu.attackEnemy(squirtle);
	squirtle.attackEnemy(pikachu);
	pikachu.attackEnemy(squirtle);
	squirtle.attackEnemy(pikachu);
	pikachu.attackEnemy(squirtle);

	return 0;
}