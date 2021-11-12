#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Имеется отсортированный массив целых чисел.Необходимо разработать функцию insert_sorted,
// которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе,
// чтобы упорядоченность контейнера сохранялась. Реализуйте шаблонную функцию insert_sorted,
// которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.

template<typename T>
void insert_sorted(std::vector<T>& sorted_vec, const T new_value, bool asc_order = true)
{
	if (asc_order) 
		sorted_vec.insert(std::upper_bound(sorted_vec.begin(), sorted_vec.end(), new_value), new_value);
	else
	{
		auto pos_to_ins = std::upper_bound(sorted_vec.rbegin(), sorted_vec.rend(), new_value);
		int shift = sorted_vec.rend() - pos_to_ins;
		sorted_vec.insert(sorted_vec.begin() + shift, new_value);
	}
}

void task1()
{
	std::cout << "TASK 1\n";
	const size_t count = 35;
	std::vector<int> numbers(count);
	std::generate(numbers.begin(), numbers.end(), []() {return (rand() % 100); });

	// тестируем для вектора, отсортированного по возрастанию:
	std::sort(numbers.begin(), numbers.end());
	std::cout << "Initial vector:\n";
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>{std::cout, " "});
	int value_to_insert = 72;
	std::cout << "\nResult vector after insertion " << value_to_insert << ":\n";
	insert_sorted(numbers, value_to_insert);
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>{std::cout, " "});

	// тестируем для вектора, отсортированного по убыванию:
	std::cout << "\n\nInitial vector with descending order to sort:\n";
	std::reverse(numbers.begin(), numbers.end());
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>{std::cout, " "});
	value_to_insert = 91;
	std::cout << "\nResult vector after insertion " << value_to_insert << ":\n";
	insert_sorted(numbers, value_to_insert, false);
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << "\n" << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Сгенерируйте вектор, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала.
// На основе этого массива чисел создайте другой вектор целых чисел, представляющий цифровой сигнал,
// в котором будут откинуты дробные части чисел. Выведите получившиеся массивы чисел.
// Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле :
// ∑_(i = 0) ^ (N - 1) 〖(a_i - b_i)〗 ^ 2,
// где :
//		N - количество элементов в векторе,
//		a - элемент вектора с дробными числами,
//		b - элемент вектора с целыми числами
// Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.

void task2()
{
	std::cout << "TASK 2\n";
	const size_t size = 100;
	std::vector<double> analog_signal(size);
	std::vector<int> digital_signal(size);

	std::cout << "Analog signal:\n";
	std::generate(analog_signal.begin(), analog_signal.end(), []() {return ((rand() % 1000) + (static_cast<double>(rand() % 1000)/ 1000)); });
	std::copy(analog_signal.begin(), analog_signal.end(), std::ostream_iterator<double>{std::cout, " "});
	
	std::cout << "\nDigital signal:\n";
	// идёт неявное преобразование из дробного в целочисленный тип:
	std::copy(analog_signal.begin(), analog_signal.end(), digital_signal.begin());
	std::copy(digital_signal.begin(), digital_signal.end(), std::ostream_iterator<int>{std::cout, " "});

	std::cout << "\nError = ";
	std::vector<double> error_vector(size);
	// !!! здесь не знаю, как сделать, чтобы в каждое значение вектора ошибки записывался результат функции над двумя векторами:
	std::transform(analog_signal.begin(), analog_signal.end(), error_vector.begin(), 
					[](double value) { return pow(value - static_cast<int>(value), 2); });
	std::cout << std::accumulate(error_vector.begin(), error_vector.end(), 0.0) << "\n" << std::endl;
}

int main()
{
	task1();
	task2();
	return 0;
}