#pragma once
#include<iostream>
#include<string>
#include<memory> 
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>

enum class StudentType {
	BACHELOR,
	MASTER,
	PHD,
	EXTRAMURAL,
	INTERNATIONAL
};

static std::string studentTypeToString(const StudentType type) {
	switch (type)
	{
	case StudentType::BACHELOR: return "БАКАЛАВР";
	case StudentType::MASTER: return "МАГИСТР";
	case StudentType::PHD: return "АСПИРАНТ";
	case StudentType::EXTRAMURAL: return "ЗАОЧНИК";
	case StudentType::INTERNATIONAL: return "ИНОСТРАННЫЙ";
	default:
		return "UNKNOWN";
	}
}
static StudentType stringToStudentType(const std::string& typeStr) {
	if (typeStr == "BACHELOR" || typeStr == "БАКАЛАВР") return StudentType::BACHELOR;
	if (typeStr == "MASTER" || typeStr == "МАГИСТР") return StudentType::MASTER;
	if (typeStr == "PHD" || typeStr == "АСПИРАНТ") return StudentType::PHD;
	if (typeStr == "EXTRAMURAL" || typeStr == "ЗАОЧНИК") return StudentType::EXTRAMURAL;
	if (typeStr == "INTERNATIONAL" || typeStr == "ИНОСТРАННЫЙ") return StudentType::INTERNATIONAL;
	throw std::invalid_argument("Unknown student type");
}

class Student {
protected:
	std::string name;
	int age;
	std::string university;
	static size_t id_count;
	size_t id;
public:
	Student() : name("unknown"), age(0), university("unknown"), id(id_count++) {}
	Student(const std::string& name, int age, const std::string& university)
			 : name(name), age(age), university(university), id(id_count++) {}
	virtual ~Student() = 0;

	virtual std::string getName() const { return name; }
	virtual int getAge() const { return age; }
	virtual std::string getUniversity() const { return university; }
	virtual size_t getId() const { return id; }
	virtual void setName(const std::string& name) { this->name = name; }
	virtual void setAge(int age) { this->age = age; }
	virtual void setUniversity(const std::string& university) { this->university = university; }
	virtual void setId(size_t newId) { this->id = newId; }

	virtual void showInfo() const = 0;
	virtual StudentType getType() const = 0;
	virtual std::unique_ptr<Student> clone() const = 0;

};
size_t Student::id_count = 0;
Student::~Student(){}

class BachelorStudent :public Student {
	int course;
public:
	BachelorStudent(const std::string& name, int age, const std::string& university, int course)
					: Student(name, age, university), course(course) {}
	BachelorStudent(const BachelorStudent& other)
					: Student(other.name, other.age, other.university), course(other.course) {
					id = other.id;
	}
	~BachelorStudent(){}

	int getCourse() const { return course; }
	void setCourse(int course) { this->course = course; }

	void showInfo() const override{
		std::cout << "БАКАЛАВР [ID: " << id << "]\n"
			<< "Имя: " << name << "\n"
			<< "Возраст: " << age << "\n"
			<< "ВУЗ: " << university << "\n"
			<< "Курс: " << course << "\n" << std::endl;
	}
	StudentType getType() const override {
		return StudentType::BACHELOR;
	}
	std::unique_ptr<Student> clone() const override {
		return std::make_unique<BachelorStudent>(*this);
	}
};

class MasterStudent :public Student {
	std::string researchTopic;
public:
	MasterStudent(const std::string& name, int age, const std::string& university, const std::string& researchTopic)
				   : Student(name, age, university), researchTopic(researchTopic) {}
	MasterStudent(const MasterStudent& other) 
				   : Student(other.name, other.age, other.university), researchTopic(other.researchTopic) {
				   id = other.id;
	}
	~MasterStudent(){}

	std::string getResearchTopic() const { return researchTopic; }
	void setResearchTopic(const std::string& researchTopic) { this->researchTopic = researchTopic; }

	void showInfo() const override {
		std::cout << "МАГИСТР [ID: " << id << "]\n"
			<< "Имя: " << name << "\n"
			<< "Возраст: " << age << "\n"
			<< "ВУЗ: " << university << "\n"
		    << "Тема исследования: " << researchTopic << "\n" << std::endl;

	}
	StudentType getType() const override {
		return StudentType::MASTER;
	}
	std::unique_ptr<Student> clone() const override {
		return std::make_unique<MasterStudent>(*this);
	}
};
class PhDStudent :public Student {
	std::string dissertationTopic;
public:
	PhDStudent(const std::string& name, int age, const std::string& university, const std::string& dissertationTopic)
			    : Student(name, age, university), dissertationTopic(dissertationTopic) {}
	PhDStudent(const PhDStudent& other) 
				: Student(other.name, other.age, other.university), dissertationTopic(other.dissertationTopic) {
				id = other.id;
	}
	~PhDStudent(){}

	std::string getDissertationTopic() const { return dissertationTopic; }
	void setDissertationTopic(const std::string& dissertationTopic) { this->dissertationTopic = dissertationTopic; }

	void showInfo() const override {
		std::cout << "АСПИРАНТ [ID: " << id << "]\n"
			<< "Имя: " << name << "\n"
			<< "Возраст: " << age << "\n"
			<< "ВУЗ: " << university << "\n"
			<< "Тема диссертации: " << dissertationTopic << "\n" << std::endl;

	}
	StudentType getType() const override {
		return StudentType::PHD;
	}
	std::unique_ptr<Student> clone() const override {
		return std::make_unique<PhDStudent>(*this);
	}
};
class ExtramuralStudent :public Student {
	std::string workplace;
public:
	ExtramuralStudent(const std::string& name, int age, const std::string& university, const std::string& workplace)
			           : Student(name, age, university), workplace(workplace) {}
	ExtramuralStudent(const ExtramuralStudent& other) 
					   : Student(other.name, other.age, other.university), workplace(other.workplace) {
					   id = other.id;
	}
	~ExtramuralStudent(){}

	std::string getWorkplace() const { return workplace; }
	void setWorkplace(const std::string& workplace) { this->workplace = workplace; }

	void showInfo() const override {
		std::cout << "ЗАОЧНИК [ID: " << id << "]\n"
			<< "Имя: " << name << "\n"
			<< "Возраст: " << age << "\n"
			<< "ВУЗ: " << university << "\n"
			<< "Место работы: " << workplace << "\n" << std::endl;

	}
	StudentType getType() const override {
		return StudentType::EXTRAMURAL;
	}
	std::unique_ptr<Student> clone() const override {
		return std::make_unique<ExtramuralStudent>(*this);
	}
};
class InternationalStudent :public Student {
	std::string country;
public:
	InternationalStudent(const std::string& name, int age, const std::string& university, const std::string& country)
						  : Student(name, age, university), country(country) {}
	InternationalStudent(const InternationalStudent& other) 
						  : Student(other.name, other.age, other.university), country(other.country) {
					   	  id = other.id;
	}
	~InternationalStudent(){}

	std::string getCountry() const { return country; }
	void setCountry(const std::string& country) { this->country = country; }

	void showInfo() const override {
		std::cout << "ИНОСТРАННЫЙ СТУДЕНТ [ID: " << id << "]\n"
			<< "Имя: " << name << "\n"
			<< "Возраст: " << age << "\n"
			<< "ВУЗ: " << university << "\n"
			<< "Прибыл из: " << country << "\n" << std::endl;

	}
	StudentType getType() const override {
		return StudentType::INTERNATIONAL;
	}
	std::unique_ptr<Student> clone() const override {
		return std::make_unique<InternationalStudent>(*this);
	}
};


//file StudentFactory
class StudentFactory {
public:
	virtual ~StudentFactory() = default;
	virtual std::unique_ptr<Student> createStudent() const = 0;
};

class BachelorStudentFactory : public StudentFactory {
public:
	std::unique_ptr<Student> createStudent() const override {
		return std::make_unique<BachelorStudent>("Иван", 20, "бгуир", 1);
	}
};
class MasterStudentFactory : public StudentFactory {
public:
	std::unique_ptr<Student> createStudent() const override {
		return std::make_unique<MasterStudent>("Роман", 25, "бгу", "Разработка мобильных приложений");
	}
};
class PhDStudentFactory : public StudentFactory {
public:
	std::unique_ptr<Student> createStudent() const override {
		return std::make_unique<PhDStudent>("Алексей", 29, "бгуир", "Исследование нейросетей");
	}
};
class ExtramuralStudentFactory : public StudentFactory {
public:
	std::unique_ptr<Student> createStudent() const override {
		return std::make_unique<ExtramuralStudent>("Леонид", 45, "бнту", "Старший Менеджер по продажам");
	}
};
class InternationalStudentFactory : public StudentFactory {
public:
	std::unique_ptr<Student> createStudent() const override {
		return std::make_unique<InternationalStudent>("Хасан", 19, "бгуир", "Грузия");
	}
};

//file StudentFactoryWithArgs
//class StudentFactoryWithArgs {
//public:
//	virtual ~StudentFactoryWithArgs() = default;
//	virtual std::unique_ptr<Student> createStudent(const std::string& name, int age, const std::string& university) const = 0;
//};

//class PhDStudentFactoryWithArgs : public StudentFactoryWithArgs {
//public:
//	std::unique_ptr<Student> createStudent(const std::string& name, int age, const std::string& university) const override {
//		return std::make_unique<PhDStudent>(name, age, university);
//	}
//};
//class InternationalStudentFactoryWithArgs : public StudentFactoryWithArgs {
//public:
//	std::unique_ptr<Student> createStudent(const std::string& name, int age, const std::string& university) const override {
//		return std::make_unique<InternationalStudent>(name, age, university);
//	}
//};

//FactoryConstructor
class StudentFactoryConstructor {
public:
	static std::unique_ptr<Student> createBachelorStudent(const std::string& name, int age, const std::string& university, int course) {
		return std::make_unique<BachelorStudent>(name, age, university, course);
	}
	static std::unique_ptr<Student> createMasterStudent(const std::string& name, int age, const std::string& university, const std::string& researchTopic) {
		return std::make_unique<MasterStudent>(name, age, university, researchTopic);
	}
	static std::unique_ptr<Student> createPhDStudent(const std::string& name, int age, const std::string& university, const std::string& dissertationTopic) {
		return std::make_unique<PhDStudent>(name, age, university, dissertationTopic);
	}
	static std::unique_ptr<Student> createExtramuralStudent(const std::string& name, int age, const std::string& university, const std::string& workplace) {
		return std::make_unique<ExtramuralStudent>(name, age, university, workplace);
	}
	static std::unique_ptr<Student> createInternationalStudent(const std::string& name, int age, const std::string& university, const std::string& country) {
		return std::make_unique<InternationalStudent>(name, age, university, country);
	}
};

//PolymorphicFactory
class PolymorphicStudentFactory {
	std::map<StudentType, std::unique_ptr<StudentFactory>> factories;
	void registerFactory(StudentType type, std::unique_ptr<StudentFactory> factory) {
		factories[type] = std::move(factory);
	}
public:
	PolymorphicStudentFactory() {
		registerFactory(StudentType::BACHELOR, std::make_unique<BachelorStudentFactory>());
		registerFactory(StudentType::MASTER, std::make_unique<MasterStudentFactory>());
		registerFactory(StudentType::PHD, std::make_unique<PhDStudentFactory>());
		registerFactory(StudentType::EXTRAMURAL, std::make_unique<ExtramuralStudentFactory>());
		registerFactory(StudentType::INTERNATIONAL, std::make_unique<InternationalStudentFactory>());
	}
	std::unique_ptr<Student> createStudent(StudentType type) const {
		auto it = factories.find(type);
		if (it != factories.end()) {
			return it->second->createStudent();
		}
		return nullptr;
	}
	void addFactory(StudentType type, std::unique_ptr<StudentFactory> factory) {
		factories[type] = std::move(factory);
	}
};

//PrototypeRegistry
class StudentPrototypeRegistry {
private:
	std::map<StudentType, std::unique_ptr<Student>> prototypes;

	void registerPrototype(StudentType type, std::unique_ptr<Student> prototype) {
		prototypes[type] = std::move(prototype);
	}

public:
	StudentPrototypeRegistry() {
		registerPrototype(StudentType::BACHELOR, std::make_unique<BachelorStudent>("Прототип Бакалавра", 19, "БГУИР", 1));
	}
	std::unique_ptr<Student> createStudent(StudentType type) const {
		auto it = prototypes.find(type);
		if (it != prototypes.end()) {
			return it->second->clone();
		}
		return nullptr;
	}
	void addPrototype(StudentType type, std::unique_ptr<Student> prototype) {
		prototypes[type] = std::move(prototype);
	}
};

class StudentManager {
	std::vector<std::unique_ptr<Student>> students;
	PolymorphicStudentFactory polyFactory;
	StudentPrototypeRegistry prototypeRegistry;
public:
	void addStudentWithPolyFactory(const std::string& type) {
		try {
			StudentType studentType = stringToStudentType(type);
			auto student = polyFactory.createStudent(studentType);
			if (student) {
				students.push_back(std::move(student));
				std::cout << "Студент типа '" << studentTypeToString(studentType)
					      << "' добавлен через PolymorphicFactory\n";
			}
		}
		catch(const std::exception& e){
			std::cout << "Ошибка: " << e.what() << std::endl;
		}
	}
	void addStudentWithPrototype(const std::string& type) {
		try {
			StudentType studentType = stringToStudentType(type);
			auto student = prototypeRegistry.createStudent(studentType);
			if (student) {
				students.push_back(std::move(student));
				std::cout << "Студент типа '" << studentTypeToString(studentType)
					      << "' добавлен через PrototypeRegistry\n";
			}
		}
		catch (const std::exception& e) {
			std::cout << "Ошибка: " << e.what() << std::endl;
		}
	}

	void addStudentWithConstructor(const std::string& type,
		const std::string& name,
		int age,
		const std::string& university,
		const std::string& additionalInfo = "") {
		try {
			StudentType studentType = stringToStudentType(type);
			std::unique_ptr<Student> student;

			switch (studentType) {
			case StudentType::BACHELOR:
				student = StudentFactoryConstructor::createBachelorStudent(
					name, age, university, std::stoi(additionalInfo));
				break;
			case StudentType::MASTER:
				student = StudentFactoryConstructor::createMasterStudent(
					name, age, university, additionalInfo);
				break;
			case StudentType::PHD:
				student = StudentFactoryConstructor::createPhDStudent(
					name, age, university, additionalInfo);
				break;
			case StudentType::EXTRAMURAL:
				student = StudentFactoryConstructor::createExtramuralStudent(
					name, age, university, additionalInfo);
				break;
			case StudentType::INTERNATIONAL:
				student = StudentFactoryConstructor::createInternationalStudent(
					name, age, university, additionalInfo);
				break;
			default:
				throw std::invalid_argument("Unsupported student type");
			}

			students.push_back(std::move(student));
			std::cout << "Студент типа '" << studentTypeToString(studentType)
				      << "' добавлен через FactoryConstructor\n";

		}
		catch (const std::exception& e) {
			std::cout << "Ошибка: " << e.what() << std::endl;
		}
	}

	bool removeStudentById(size_t id) {
		auto it = std::find_if(students.begin(), students.end(),
			[id](const std::unique_ptr<Student>& student) {
				return student->getId() == id;
			});

		if (it != students.end()) {
			std::cout << "Студент с ID " << id << " удален\n";
			students.erase(it);
			return true;
		}
		std::cout << "Студент с ID " << id << " не найден\n";
		return false;
	}

	std::vector<Student*> findStudentsByType(const std::string& type) {
		std::vector<Student*> result;
		try {
			StudentType studentType = stringToStudentType(type);

			for (const auto& student : students) {
				if (student->getType() == studentType) {
					result.push_back(student.get());
				}
			}

			std::cout << "Найдено " << result.size() << " студентов типа '"
				<< studentTypeToString(studentType) << "'\n";

		}
		catch (const std::exception& e) {
			std::cout << "Ошибка: " << e.what() << std::endl;
		}
		return result;
	}

	void showAllStudents() const {
		if (students.empty()) {
			std::cout << "Нет студентов в системе\n";
			system("pause");
			return;
		}

		std::cout << "\n=== ВСЕ СТУДЕНТЫ ===\n";
		for (const auto& student : students) {
			student->showInfo();
		}
	}

	size_t getStudentCount() const {
		return students.size();
	}
	bool isEmpty() const {
		return students.empty();
	}
	void addFileInfo() {
		std::ofstream os("MyFILE.txt", std::ios::trunc);

		if (!os.is_open()) {
			std::cout << "Ошибка: не удалось открыть файл для записи!\n";
			return;
		}
		if (students.empty()) {
			std::cout << "Нет студентов в системе\n";
			system("pause");
			return;
		}

		std::cout << "Добавляем в файл";
		loadingImitation();

		os << "=== СПИСОК СТУДЕНТОВ ===\n\n";

		for (const auto& student : students) {
			switch (student->getType()) {
			case StudentType::BACHELOR: {
				auto* bachelor = dynamic_cast<BachelorStudent*>(student.get());
				if (bachelor) {
					os << "БАКАЛАВР [ID: " << student->getId() << "]\n"
						<< "Имя: " << student->getName() << "\n"
						<< "Возраст: " << student->getAge() << "\n"
						<< "ВУЗ: " << student->getUniversity() << "\n"
						<< "Курс: " << bachelor->getCourse() << "\n\n";
				}
				break;
			}
			case StudentType::MASTER: {
				auto* master = dynamic_cast<MasterStudent*>(student.get());
				if (master) {
					os << "МАГИСТР [ID: " << student->getId() << "]\n"
						<< "Имя: " << student->getName() << "\n"
						<< "Возраст: " << student->getAge() << "\n"
						<< "ВУЗ: " << student->getUniversity() << "\n"
						<< "Тема исследования: " << master->getResearchTopic() << "\n\n";
				}
				break;
			}
			case StudentType::PHD: {
				auto* phd = dynamic_cast<PhDStudent*>(student.get());
				if (phd) {
					os << "АСПИРАНТ [ID: " << student->getId() << "]\n"
						<< "Имя: " << student->getName() << "\n"
						<< "Возраст: " << student->getAge() << "\n"
						<< "ВУЗ: " << student->getUniversity() << "\n"
						<< "Тема диссертации: " << phd->getDissertationTopic() << "\n\n";
				}
				break;
			}
			case StudentType::EXTRAMURAL: {
				auto* extramural = dynamic_cast<ExtramuralStudent*>(student.get());
				if (extramural) {
					os << "ЗАОЧНИК [ID: " << student->getId() << "]\n"
						<< "Имя: " << student->getName() << "\n"
						<< "Возраст: " << student->getAge() << "\n"
						<< "ВУЗ: " << student->getUniversity() << "\n"
						<< "Место работы: " << extramural->getWorkplace() << "\n\n";
				}
				break;
			}
			case StudentType::INTERNATIONAL: {
				auto* international = dynamic_cast<InternationalStudent*>(student.get());
				if (international) {
					os << "ИНОСТРАННЫЙ СТУДЕНТ [ID: " << student->getId() << "]\n"
						<< "Имя: " << student->getName() << "\n"
						<< "Возраст: " << student->getAge() << "\n"
						<< "ВУЗ: " << student->getUniversity() << "\n"
						<< "Прибыл из: " << international->getCountry() << "\n\n";
				}
				break;
			}
			}
		}

	}
	bool studentExists(size_t id) const {
		for (const auto& student : students) {
			if (student->getId() == id) return true;
		}
		return false;
	}

	Student* getStudentById(size_t id) const {
		for (const auto& student : students) {
			if (student->getId() == id) return student.get();
		}
		return nullptr;
	}

	bool changeStudentData(size_t id) {
		auto* student = getStudentById(id);
		if (!student) {
			std::cout << "Студент с ID " << id << " не найден\n";
			return false;
		}

		std::cout << "\n=== РЕДАКТИРОВАНИЕ СТУДЕНТА ID: " << id << " ===\n";
		student->showInfo();

		std::string input;
		int numInput;

		std::cout << "\nТекущее имя: " << student->getName() << "\nНовое имя: ";
		std::getline(std::cin, input);
		if (!input.empty()) student->setName(input);

		std::cout << "Текущий возраст: " << student->getAge() << "\nНовый возраст: ";
		std::cin >> numInput;
		std::cin.ignore();
		if (numInput > 0) student->setAge(numInput);

		std::cout << "Текущий ВУЗ: " << student->getUniversity() << "\nНовый ВУЗ: ";
		std::getline(std::cin, input);
		if (!input.empty()) student->setUniversity(input);

		switch (student->getType()) {
		case StudentType::BACHELOR: {
			auto* bachelor = dynamic_cast<BachelorStudent*>(student);
			std::cout << "Текущий курс: " << bachelor->getCourse() << "\nНовый курс: ";
			std::cin >> numInput;
			std::cin.ignore();
			if (numInput > 0) bachelor->setCourse(numInput);
			break;
		}
		case StudentType::MASTER: {
			auto* master = dynamic_cast<MasterStudent*>(student);
			std::cout << "Текущая тема: " << master->getResearchTopic() << "\nНовая тема: ";
			std::getline(std::cin, input);
			if (!input.empty()) master->setResearchTopic(input);
			break;
		}
		case StudentType::PHD: {
			auto* phd = dynamic_cast<PhDStudent*>(student);
			std::cout << "Текущая тема: " << phd->getDissertationTopic() << "\nНовая тема: ";
			std::getline(std::cin, input);
			if (!input.empty()) phd->setDissertationTopic(input);
			break;
		}
		case StudentType::EXTRAMURAL: {
			auto* extramural = dynamic_cast<ExtramuralStudent*>(student);
			std::cout << "Текущее место работы: " << extramural->getWorkplace() << "\nНовое место: ";
			std::getline(std::cin, input);
			if (!input.empty()) extramural->setWorkplace(input);
			break;
		}
		case StudentType::INTERNATIONAL: {
			auto* international = dynamic_cast<InternationalStudent*>(student);
			std::cout << "Текущая страна: " << international->getCountry() << "\nНовая страна: ";
			std::getline(std::cin, input);
			if (!input.empty()) international->setCountry(input);
			break;
		}
		}

		std::cout << "Данные студента с ID " << id << " успешно обновлены\n";
		return true;
	}
};