#include <iostream>
#include <string>
#include <vector>

class AggressiveStrategy
{
public:
	void executeStrategy()
	{
		std::cout << "  [AGGRESSIVE] Launching full-scale attack!\n";
		std::cout << "  [AGGRESSIVE] Focus on dealing maximum damage!\n";
	}

	int calculateDamage(int baseDamage)
	{
		return baseDamage * 2;  // Удвоенный урон
	}

	int calculateDefense(int baseDefense)
	{
		return baseDefense / 2;  // Сниженная защита
	}
};

class DefensiveStrategy
{
public:
	void executeStrategy()
	{
		std::cout << "  [DEFENSIVE] Taking defensive stance!\n";
		std::cout << "  [DEFENSIVE] Minimizing damage taken!\n";
	}

	int calculateDamage(int baseDamage)
	{
		return baseDamage / 2;  // Сниженный урон
	}

	int calculateDefense(int baseDefense)
	{
		return baseDefense * 2;  // Удвоенная защита
	}
};

class BalancedStrategy
{
public:
	void executeStrategy()
	{
		std::cout << "  [BALANCED] Maintaining equilibrium!\n";
		std::cout << "  [BALANCED] Optimal balance between offense and defense!\n";
	}

	int calculateDamage(int baseDamage)
	{
		return baseDamage;  // Базовый урон
	}

	int calculateDefense(int baseDefense)
	{
		return baseDefense;  // Базовая защита
	}
};

// Хитрая стратегия
class CunningStrategy
{
public:
	void executeStrategy()
	{
		std::cout << "  [CUNNING] Using tactics and deception!\n";
		std::cout << "  [CUNNING] Striking at weak points!\n";
	}

	int calculateDamage(int baseDamage)
	{
		return baseDamage + baseDamage / 2;  // 150% урона
	}

	int calculateDefense(int baseDefense)
	{
		return baseDefense + baseDefense / 3;  // 133% защиты
	}
};

template<typename StrategyType>
class Entity : public StrategyType
{
public:
	Entity(std::string name, int health, int baseDamage, int baseDefense)
		: m_name(name), m_health(health), m_baseDamage(baseDamage), m_baseDefense(baseDefense)
	{}

	void performAction()
	{
		std::cout << "\n" << m_name << " is performing action:\n";
		
		this->executeStrategy();
		
		int effectiveDamage = this->calculateDamage(m_baseDamage);
		int effectiveDefense = this->calculateDefense(m_baseDefense);
		
		std::cout << "  Effective damage: " << effectiveDamage << "\n";
		std::cout << "  Effective defense: " << effectiveDefense << "\n";
	}

	void displayInfo() const
	{
		std::cout << "Entity: " << m_name 
		          << " (HP: " << m_health 
		          << ", Base DMG: " << m_baseDamage 
		          << ", Base DEF: " << m_baseDefense << ")\n";
	}

	std::string getName() const { return m_name; }
	int getHealth() const { return m_health; }

private:
	std::string m_name;
	int m_health;
	int m_baseDamage;
	int m_baseDefense;
};

int main()
{
	std::cout << "STRATEGY PATTERN WITH STATIC POLYMORPHISM\n";
	std::cout << "No Strategy base class, no constructor with Strategy, no Strategy reference\n\n";

	Entity<AggressiveStrategy> warrior("Warrior", 200, 50, 30);
	Entity<DefensiveStrategy> guardian("Guardian", 300, 30, 60);
	Entity<BalancedStrategy> knight("Knight", 250, 40, 40);
	Entity<CunningStrategy> rogue("Rogue", 150, 45, 25);

	std::cout << "ENTITIES\n";
	std::cout << std::string(60, '-') << "\n";
	warrior.displayInfo();
	guardian.displayInfo();
	knight.displayInfo();
	rogue.displayInfo();

	std::cout << "\nACTIONS\n";
	std::cout << std::string(60, '-') << "\n";

	warrior.performAction();
	guardian.performAction();
	knight.performAction();
	rogue.performAction();

	std::cout << "\nSTATIC POLYMORPHISM DEMONSTRATION\n";
	std::cout << std::string(60, '-') << "\n";
	std::cout << "\nEach entity type is determined at compile time.\n";
	std::cout << "No virtual functions, no vtables, no runtime overhead!\n";

	// Можно использовать в шаблонных функциях
	auto processEntity = [](auto& entity) {
		std::cout << "\nProcessing: " << entity.getName() << "\n";
		entity.performAction();
	};

	std::cout << "\nGENERIC PROCESSING\n";
	std::cout << std::string(60, '-') << "\n";

	processEntity(warrior);
	processEntity(guardian);

	// можно создавать контейнеры одинаковых типов
	std::cout << "\nCOLLECTION OF SAME STRATEGY TYPE\n";
	std::cout << std::string(60, '-') << "\n";

	std::vector<Entity<AggressiveStrategy>> aggressiveArmy;
	aggressiveArmy.emplace_back("Berserker 1", 180, 55, 25);
	aggressiveArmy.emplace_back("Berserker 2", 190, 52, 28);
	aggressiveArmy.emplace_back("Berserker 3", 185, 53, 27);

	std::cout << "\nAggressive Army (" << aggressiveArmy.size() << " units):\n";
	for (auto& unit : aggressiveArmy)
	{
		unit.displayInfo();
	}

	std::cout << "\nAll units perform coordinated attack:\n";
	for (auto& unit : aggressiveArmy)
	{
		unit.performAction();
	}

	// Преимущества статического полиморфизма
	std::cout << "\nADVANTAGES\n";
	std::cout << std::string(60, '-') << "\n";
	std::cout << "1. No virtual function overhead\n";
	std::cout << "2. No vtable pointer in objects\n";
	std::cout << "3. Better inlining opportunities\n";
	std::cout << "4. Type safety at compile time\n";
	std::cout << "5. Zero runtime cost for strategy selection\n";

	std::cout << "\nSIMULATION COMPLETE\n";

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////

