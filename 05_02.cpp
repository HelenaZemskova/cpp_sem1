#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>

class Entity
{
public:
	virtual void action() = 0;
	virtual ~Entity() = default;
};

class BasicEntity : public virtual Entity
{
public:
	void action() override
	{
		std::cout << "[BasicEntity] Performing basic action" << std::endl;
	}
};

class AdvancedEntity : public virtual Entity
{
public:
	void action() override
	{
		std::cout << "[AdvancedEntity] Performing advanced action" << std::endl;
	}
};

template<typename T>
class Decorator : public virtual Entity, public T
{
public:
	void action() override
	{
		std::cout << "[Decorator] >>> START >>>" << std::endl;
		T::action();  // Вызываем действие базового класса T
		std::cout << "[Decorator] <<< END <<<" << std::endl;
	}
};

template<typename T>
class LoggingDecorator : public virtual Entity, public T
{
public:
	void action() override
	{
		// Получаем текущее время
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		auto local_time = *std::localtime(&time);
		
		std::cout << "[LOG] ========================================" << std::endl;
		std::cout << "[LOG] Action started at timestamp: " 
		          << std::put_time(&local_time, "%H:%M:%S") << std::endl;
		std::cout << "[LOG] ========================================" << std::endl;
		
		T::action();
		
		// Получаем время окончания
		now = std::chrono::system_clock::now();
		time = std::chrono::system_clock::to_time_t(now);
		local_time = *std::localtime(&time);
		
		std::cout << "[LOG] ========================================" << std::endl;
		std::cout << "[LOG] Action finished at timestamp: " 
		          << std::put_time(&local_time, "%H:%M:%S") << std::endl;
		std::cout << "[LOG] Action finished successfully" << std::endl;
		std::cout << "[LOG] ========================================" << std::endl;
	}
};

template<typename T>
class TimingDecorator : public virtual Entity, public T
{
public:
	void action() override
	{
		std::cout << "[TIMING] Start measuring..." << std::endl;
		
		auto start = std::chrono::high_resolution_clock::now();
		
		T::action();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		
		std::cout << "[TIMING] Execution time: " << duration.count() << " microseconds" << std::endl;
	}
};

template<typename T>
class ValidationDecorator : public virtual Entity, public T
{
public:
	void action() override
	{
		std::cout << "[VALIDATION] Checking preconditions..." << std::endl;
		std::cout << "[VALIDATION] All preconditions satisfied" << std::endl;
		
		T::action();
		
		std::cout << "[VALIDATION] Checking postconditions..." << std::endl;
		std::cout << "[VALIDATION] All postconditions satisfied" << std::endl;
	}
};

int main()
{
	std::cout << "1. Basic Entity (no decorators)" << std::endl;
	BasicEntity basic;
	basic.action();
	
	std::cout << "\n 2. BasicEntity with Decorator" << std::endl;
	Decorator<BasicEntity> decorated;
	decorated.action();
	
	std::cout << "\n 3. BasicEntity with LoggingDecorator" << std::endl;
	LoggingDecorator<BasicEntity> logged;
	logged.action();
	
	std::cout << "\n 4. BasicEntity with TimingDecorator" << std::endl;
	TimingDecorator<BasicEntity> timed;
	timed.action();
	
	std::cout << "\n 5. BasicEntity with ValidationDecorator" << std::endl;
	ValidationDecorator<BasicEntity> validated;
	validated.action();
	
	std::cout << "\n 6. Chain: Logging + Timing" << std::endl;
	LoggingDecorator<TimingDecorator<BasicEntity>> chain1;
	chain1.action();
	
	std::cout << "\n 7. Chain: Validation + Logging + Timing" << std::endl;
	ValidationDecorator<LoggingDecorator<TimingDecorator<BasicEntity>>> chain2;
	chain2.action();
	
	std::cout << "\n 8. AdvancedEntity with multiple decorators" << std::endl;
	Decorator<LoggingDecorator<AdvancedEntity>> advancedDecorated;
	advancedDecorated.action();
	
	std::cout << "\n 9. Polymorphism test" << std::endl;
	// Можно использовать через указатель на базовый класс
	Entity* entity1 = new BasicEntity();
	Entity* entity2 = new Decorator<BasicEntity>();
	Entity* entity3 = new LoggingDecorator<TimingDecorator<BasicEntity>>();
	
	std::cout << "\nEntity 1:" << std::endl;
	entity1->action();
	
	std::cout << "\nEntity 2:" << std::endl;
	entity2->action();
	
	std::cout << "\nEntity 3:" << std::endl;
	entity3->action();
	
	delete entity1;
	delete entity2;
	delete entity3;
	
	std::cout << "\n All tests completed successfully!" << std::endl;
}

