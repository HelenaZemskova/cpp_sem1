#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class GameObject
{
public:
	virtual void display() const = 0;
	virtual int getHealth() const = 0;
	virtual int getAttackPower() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual bool isAlive() const = 0;
	virtual ~GameObject() = default;
};

// конкретная реализация игрового объекта
class Unit : public GameObject
{
public:
	Unit(std::string name, int health, int attack, int defense, std::string type)
		: m_name(name), m_health(health), m_maxHealth(health), 
		  m_attack(attack), m_defense(defense), m_type(type)
	{}

	void display() const override
	{
		std::cout << "[" << m_type << "] " << m_name 
		          << " (HP: " << m_health << "/" << m_maxHealth 
		          << ", ATK: " << m_attack << ", DEF: " << m_defense << ")";
	}

	int getHealth() const override { return m_health; }
	int getAttackPower() const override { return m_attack; }
	bool isAlive() const override { return m_health > 0; }

	void takeDamage(int damage) override
	{
		int actualDamage = std::max(0, damage - m_defense);
		m_health = std::max(0, m_health - actualDamage);
	}

	std::string getName() const { return m_name; }
	std::string getType() const { return m_type; }

private:
	std::string m_name;
	int m_health;
	int m_maxHealth;
	int m_attack;
	int m_defense;
	std::string m_type;
};

class UnitBuilder
{
public:
	UnitBuilder() : m_name("Unknown"), m_health(100), m_attack(10), m_defense(5), m_type("Generic") {}

	UnitBuilder& setName(const std::string& name)
	{
		m_name = name;
		return *this;
	}

	UnitBuilder& setHealth(int health)
	{
		m_health = health;
		return *this;
	}

	UnitBuilder& setAttack(int attack)
	{
		m_attack = attack;
		return *this;
	}

	UnitBuilder& setDefense(int defense)
	{
		m_defense = defense;
		return *this;
	}

	UnitBuilder& setType(const std::string& type)
	{
		m_type = type;
		return *this;
	}

	std::unique_ptr<Unit> build()
	{
		return std::make_unique<Unit>(m_name, m_health, m_attack, m_defense, m_type);
	}

private:
	std::string m_name;
	int m_health;
	int m_attack;
	int m_defense;
	std::string m_type;
};

// для организации в группы
class Army : public GameObject
{
public:
	explicit Army(std::string name) : m_name(name) {}

	void addUnit(std::unique_ptr<Unit> unit)
	{
		m_units.push_back(std::move(unit));
	}

	void display() const override
	{
		std::cout << "\nArmy: " << m_name << "\n";
		std::cout << "Total units: " << m_units.size() << "\n";
		for (const auto& unit : m_units)
		{
			if (unit->isAlive())
			{
				std::cout << "  ";
				unit->display();
				std::cout << "\n";
			}
		}
	}

	int getHealth() const override
	{
		int totalHealth = 0;
		for (const auto& unit : m_units)
		{
			totalHealth += unit->getHealth();
		}
		return totalHealth;
	}

	int getAttackPower() const override
	{
		int totalAttack = 0;
		for (const auto& unit : m_units)
		{
			if (unit->isAlive())
			{
				totalAttack += unit->getAttackPower();
			}
		}
		return totalAttack;
	}

	void takeDamage(int damage) override
	{
		// Распределяем урон между живыми юнитами
		std::vector<Unit*> aliveUnits;
		for (auto& unit : m_units)
		{
			if (unit->isAlive())
			{
				aliveUnits.push_back(unit.get());
			}
		}

		if (!aliveUnits.empty())
		{
			int damagePerUnit = damage / aliveUnits.size();
			for (auto* unit : aliveUnits)
			{
				unit->takeDamage(damagePerUnit);
			}
		}
	}

	bool isAlive() const override
	{
		for (const auto& unit : m_units)
		{
			if (unit->isAlive())
			{
				return true;
			}
		}
		return false;
	}

	size_t getAliveCount() const
	{
		size_t count = 0;
		for (const auto& unit : m_units)
		{
			if (unit->isAlive())
			{
				++count;
			}
		}
		return count;
	}

private:
	std::string m_name;
	std::vector<std::unique_ptr<Unit>> m_units;
};

// класс для боевых действий
class BattleTemplate
{
public:
	virtual ~BattleTemplate() = default;

	// определяем общий алгоритм боя
	void executeBattle(GameObject& attacker, GameObject& defender)
	{
		std::cout << "\n" << std::string(60, '-') << "\n";
		std::cout << "BATTLE COMMENCED!\n";
		std::cout << std::string(60, '-') << "\n";

		preparation(attacker, defender);
		
		int round = 1;
		while (attacker.isAlive() && defender.isAlive() && round <= 5)
		{
			std::cout << "\n--- Round " << round << " ---\n";
			
			performAttack(attacker, defender);
			
			if (defender.isAlive())
			{
				performCounterAttack(defender, attacker);
			}
			
			displayStatus(attacker, defender);
			
			++round;
		}

		conclusion(attacker, defender);
	}

protected:
	// Хуки
	virtual void preparation(GameObject& attacker, GameObject& defender)
	{
		std::cout << "\nAttacker status:\n  ";
		attacker.display();
		std::cout << "\n\nDefender status:\n  ";
		defender.display();
		std::cout << "\n";
	}

	virtual void performAttack(GameObject& attacker, GameObject& defender)
	{
		int damage = attacker.getAttackPower();
		std::cout << "Attacker deals " << damage << " damage!\n";
		defender.takeDamage(damage);
	}

	virtual void performCounterAttack(GameObject& defender, GameObject& attacker)
	{
		int damage = defender.getAttackPower() / 2;  // Контратака слабее
		std::cout << "Defender counter-attacks for " << damage << " damage!\n";
		attacker.takeDamage(damage);
	}

	virtual void displayStatus(GameObject& attacker, GameObject& defender)
	{
		std::cout << "Attacker HP: " << attacker.getHealth() << "\n";
		std::cout << "Defender HP: " << defender.getHealth() << "\n";
	}

	virtual void conclusion(GameObject& attacker, GameObject& defender)
	{
		std::cout << "\n" << std::string(60, '-') << "\n";
		std::cout << "BATTLE RESULT:\n";
		std::cout << std::string(60, '-') << "\n";
		
		if (attacker.isAlive() && !defender.isAlive())
		{
			std::cout << "ATTACKER WINS!\n";
		}
		else if (!attacker.isAlive() && defender.isAlive())
		{
			std::cout << "DEFENDER WINS!\n";
		}
		else if (attacker.isAlive() && defender.isAlive())
		{
			std::cout << "DRAW - BOTH SIDES STILL STANDING!\n";
		}
		else
		{
			std::cout << "MUTUAL DESTRUCTION!\n";
		}
		
		std::cout << std::string(60, '-') << "\n";
	}
};

class StandardBattle : public BattleTemplate
{
	// Использует стандартную реализацию
};

int main()
{
	std::cout << "STRATEGY GAME FRAMEWORK\n\n";

	// ДЕМОНСТРАЦИЯ BUILDER
	std::cout << "1. CREATING UNITS WITH BUILDER PATTERN\n";
	std::cout << std::string(60, '-') << "\n";

	UnitBuilder builder;
	
	auto warrior1 = builder.setName("Warrior Alpha")
	                       .setHealth(150)
	                       .setAttack(25)
	                       .setDefense(10)
	                       .setType("Warrior")
	                       .build();

	auto warrior2 = builder.setName("Warrior Beta")
	                       .setHealth(140)
	                       .setAttack(23)
	                       .setDefense(12)
	                       .setType("Warrior")
	                       .build();

	auto archer1 = builder.setName("Archer Gamma")
	                      .setHealth(100)
	                      .setAttack(30)
	                      .setDefense(5)
	                      .setType("Archer")
	                      .build();

	auto archer2 = builder.setName("Archer Delta")
	                      .setHealth(95)
	                      .setAttack(32)
	                      .setDefense(4)
	                      .setType("Archer")
	                      .build();

	std::cout << "Units created successfully!\n\n";

	// ДЕМОНСТРАЦИЯ COMPOSITE
	std::cout << "2. ORGANIZING UNITS WITH COMPOSITE PATTERN\n";
	std::cout << std::string(60, '-') << "\n";

	Army attackingArmy("Northern Legion");
	attackingArmy.addUnit(std::move(warrior1));
	attackingArmy.addUnit(std::move(archer1));

	Army defendingArmy("Southern Guard");
	defendingArmy.addUnit(std::move(warrior2));
	defendingArmy.addUnit(std::move(archer2));

	attackingArmy.display();
	defendingArmy.display();

	// ДЕМОНСТРАЦИЯ TEMPLATE METHOD
	std::cout << "\n3. BATTLE SIMULATION\n";
	std::cout << std::string(60, '-') << "\n";

	StandardBattle battle;
	battle.executeBattle(attackingArmy, defendingArmy);

	// Финальчик
	std::cout << "\n4. FINAL\n";
	std::cout << std::string(60, '-') << "\n";
	
	std::cout << "\nAttacking Army:\n";
	std::cout << "  Alive units: " << attackingArmy.getAliveCount() << "\n";
	std::cout << "  Total health: " << attackingArmy.getHealth() << "\n";

	std::cout << "\nDefending Army:\n";
	std::cout << "  Alive units: " << defendingArmy.getAliveCount() << "\n";
	std::cout << "  Total health: " << defendingArmy.getHealth() << "\n";

	std::cout << "\n SIMULATION COMPLETE \n";

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////

