#include "Calculations.h"

std::mutex m;
std::once_flag flag;
std::exception_ptr GlobalException = nullptr;
HANDLE h;

void Corrupted::Add(std::thread::id id) {
	v.push_back(id);
}

void Corrupted::Print() {
	for (const auto& id : v) {
		std::cout << "Id: " << id << " ";
	}
	std::cout << std::endl;
}

Corrupted c;

int RandNumLarge() {
	std::srand(std::time(0));
	std::vector<int> vec(100);
	for (auto& v : vec) {
		v = 5000 + std::rand() % 20000;
	}
	return vec[std::rand() % 100];
}

bool RussianRoulette() {
	std::srand(std::time(0));
	int bang = 1 + std::rand() % 20;
	if (bang == 8) {
		return true;
	}
	else {
		return false;
	}
}


void VerySlowSort_in_parallel(int num) {
	Timer t;
	char Loaded = 219;
	t.Start();

	int load = 0;

	std::call_once(flag, []() {
		std::cout << "# id\t   bar\t\t time";
		});

	{
		std::lock_guard<std::mutex> l(m);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
			{
				static_cast<SHORT>(0), static_cast<SHORT>(num + 1)
			});
		std::cout << num << " " << std::this_thread::get_id();
	}

	for (int i = 0; i < 10; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * (num + 1)));
		{
			std::lock_guard<std::mutex> l(m);

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
				{
					static_cast<SHORT>(i + 10), static_cast<SHORT>(num + 1)
				});

			try
			{
				if (RussianRoulette()) {
					std::this_thread::sleep_for(1000ms);
					c.Add(std::this_thread::get_id());
					throw std::exception{ "Following threads wasn't complited:" };
				}
			}
			catch (const std::exception&)
			{
				h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, 04);
				GlobalException = std::current_exception();
				for (int i = load; i < 10; i++) {
					std::cout << Loaded;
				}
				std::cout << "\t Corrupted!";
				SetConsoleTextAttribute(h, 07);
				return;
				break;
			}

			std::cout << Loaded;
			load++;
		}
	}
	{
		std::lock_guard<std::mutex> l(m);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
			{
				static_cast<SHORT>(25), static_cast<SHORT>(num + 1)
			});
		t.End();
	}
}

void StartCalculation_in_parallel() {
	int ThreadAmout = 4;
	std::vector<std::thread> vt;
	for (int i = 0; i < ThreadAmout; i++) {
		vt.push_back(std::thread(VerySlowSort_in_parallel, i));
	}
	for (auto& v : vt) {
		v.join();
	}

	std::cout << std::endl << std::endl;

	if (GlobalException) {
		try
		{
			std::rethrow_exception(GlobalException);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			c.Print();
		}
	}
}

//void VerySlowSort(int num) {
//	std::lock_guard<std::mutex> grd(m);
//
//	Timer time;
//
//	std::vector<int> vec(RandNumLarge());
//	int temp;
//	for (auto& v : vec) {
//		v = 500 + std::rand() % 2500;
//	}
//
//	int percent = 0;
//	size_t OnePercent = vec.size() / 10;
//
//	char Loaded = 219;
//
//	std::call_once(flag, []() {
//		std::cout << "#\tid\tbar\t\ttime\n";
//		});
//	std::cout << num << "\t" << std::this_thread::get_id() << "\t";
//
//	time.Start();
//	for (size_t i = 0; i < vec.size(); i++) {
//		for (size_t j = 0; j < vec.size(); j++) {
//			if (vec[i] < vec[j]) {
//				temp = vec[i];
//				vec[i] = vec[j];
//				vec[j] = temp;
//			}
//		}
//		if (i >= OnePercent * percent && percent < 13) {
//			std::cout << Loaded;
//			percent++;
//		}
//		try
//		{
//			if (RussianRoulette()) {
//				std::this_thread::sleep_for(5000ms);
//				c.Add(std::this_thread::get_id());
//				throw std::exception{ "Following threads wasn't complited:" };
//
//			}
//		}
//		catch (const std::exception&)
//		{
//			h = GetStdHandle(STD_OUTPUT_HANDLE);
//			SetConsoleTextAttribute(h, 04);
//			GlobalException = std::current_exception();
//			for (int i = percent; i < 11; i++) {
//				std::cout << Loaded;
//			}
//			std::cout << "\tCorrupted!\n";
//			SetConsoleTextAttribute(h, 07);
//			return;
//			break;
//		}
//	}
//	if (percent < 11) { // Костыль чтобы всегда выводилось 12 делений, в 114 строке percent < 13 за этим же, уже закипел и не знаю как сделать правильно 
//		std::cout << Loaded;
//	}
//	std::cout << "\t";
//	time.End();
//}
//
//void StartCalculation() {
//	int ThreadAmout = 4;
//	std::vector<std::thread> vt;
//	for (int i = 0; i < ThreadAmout; i++) {
//		vt.push_back(std::thread(VerySlowSort, i));
//	}
//	for (auto& v : vt) {
//		v.join();
//	}
//
//	std::cout << std::endl;
//
//	if (GlobalException) {
//		try
//		{
//			std::rethrow_exception(GlobalException);
//		}
//		catch (const std::exception& e)
//		{
//			std::cout << e.what() << std::endl;
//			c.Print();
//		}
//	}
//}