#include "study_stl.h"


//----------------------------------------------тестирование массива array<>-------------------------------------------------------
void test_array()
{
	//простой тест массива array<>
	std::array<char, 12> word{};
	strcpy(word.data(), "Hello world");

	word.at(11) = '\0';

	cout << endl << word.data() << endl;

	
	//тестирование конструкторов
	std::array<int, 10> a{ 0,1,2,3,4,5,6,7,8,9 };				//инициализация при объявлении списком инициализации

	std::array<int, 10> b{};									//инициализация всех элементов нулем 	
		
	std::array<int, 10> c(a);									//вызов неявного конструктора копирования

	std::array<int, 10> d = std::move(b);						//вызов конструктора перемещения

	b.fill(5);													//заполняем все элементы массива значением 5	

	print_array(b);
	print_array(c);
	print_array(word);

	std::array<int, 3> zero;									//содержит мусор		
	print_array(zero);

	std::array<int, 5> half_zero{ 1,2 };						//0-й и 1-й содержат 1 и 2 остальные - 0
	print_array(half_zero);


	std::array<int, 10> a_{ 0,1,2,3,4,5,6,7,8,9 };				//копия массива а
	compare_arrays(a, a_);

	std::array<int, 10> b_{ 1,2,3,4,5,6,7,8,9,10 };				//
	compare_arrays(b, b_);


	//обработка исключения при выходе за границы массива
	try {
		for (int i = 0; i < 12; i++)
			cout << endl << "a[" << i << "] = " << a.at(i);
	}
	catch (std::exception& e)
	{
		std::cerr <<endl<< "EXCEPTION " << e.what() << endl;
	}


	//тестирование семантики перемещения
	std::array<int, 5> s{ 9,9,9,9,9 };
	std::array<int, 5> h = std::move(s);							//происходит простое копирование исходного массива

	s[0] = 0;
	s[1] = 1;

	print_array(s);
	print_array(h);

	

	//массив с объектами
	std::array<Object<int, 5>, 5> matrix;
	for (auto& ar : matrix)
		ar.print();


	//использование списоков инициализации std::initializer_list<> невозможно
	std::initializer_list<int> lst{2,5,7,1,8,9};


	//применение алгоритмов STL
	std::array<float, 5> flt{ 3.0f, 3.1f, 3.2f };
	
	std::array<float, 5> transform_flt{};

	float sum = std::accumulate(flt.begin(), flt.end(), static_cast<float>(0));
	cout << endl << "sum = " << sum << endl;

	std::transform(flt.begin(), flt.end(), transform_flt.begin(), std::negate<float>());					//результаты положим в другой массив
	print_array(flt);
	print_array(transform_flt);

	std::transform(flt.begin(), flt.end(), flt.begin(), [](float& a)->float { return a *= 2.0f; } );			//результаты положим в тот же массив
	print_array(flt);


	//запрос информации о массиве

	cout << endl << ( (flt.empty() == true) ? " array is empty" : " array full") << endl;
	cout << endl << " flt array max size = " << flt.max_size() << endl;
	cout << endl << " half_zero array max size = " << half_zero.max_size() << endl;


	cout << endl << "get front element = " << flt.front() << endl;
	cout << endl << "get back element = " << flt.back() << endl;
}

//---------------------------------------------тестирование std::pair<T1,T2>p------------------------------------------------------
void test_pairs()
{
	//создание пар
	std::pair<int, string> p1;														//пустая пара
	cout << endl <<"p1 = "<< p1 << endl;

	std::pair<int, string>  p2 = std::make_pair(0, string("Pair"));					//использование std::make_pair()
	cout << endl << "p2 = " << p2 << endl;

	std::pair<int, string> p3(p2);													//использование копирующего конструктора
	cout << endl << "p3 = " << p3 << endl;

	std::pair<int, string> p4{ 5, "five" };											//использование списка инициализации
	cout << endl << "p4 = " << p4 << endl;

	std::pair<int, string> p5 = std::move(p4);										//использование перемещающего конструктора
	cout << endl << "p5 = std::move(p4) "<< p5 << endl;
	cout << endl << "p4 = " << p4 << endl;

	std::pair<int, string> p6{};													//пустой список инициализации
	cout << endl << "p6 = " << p6 << endl;
	
	auto p7 = std::make_pair('Q', '@');												//создание пары std::pair<char, char>		
	cout << endl << "p7 = " << p7 << endl;

	auto p8 = std::make_pair("D", "S");												//создание пары std::pair<const char*, const char*>			
	cout << endl << "p8 = " << p8 << endl;

	std::pair<int, float> p9(3, 2.71f);
	cout << endl << "p9 = " << p9 << endl;




	//обмен парами
	cout << endl << "exchange pairs" << endl;

	std::pair<int, char> a1(9, 'Y');
	std::pair<int, char> a2(3, 'R');

	cout << endl << "a1 = " << a1 << endl;
	cout << endl << "a2 = " << a2 << endl;

	std::swap(a1, a2);																//обмен парами	

	cout << endl << "a1 = " << a1 << endl;
	cout << endl << "a2 = " << a2 << endl;


	string f{ "first" };
	string s{ "second" };
	
	std::pair<string, string> a3 = std::make_pair(std::move(f), std::move(s));		//использование семантики перемещения в std::make_pair( std::move(), std::move() )

	cout << endl << "a3 = " << a3 << endl;
	cout << endl << "f = " << f << endl;
	cout << endl << "s = " << s << endl;

	int i = 0;

	auto a4 = std::make_pair(std::ref(i), std::ref(i));								//использование семантики ссылок std::ref()		
	cout << endl << "a4 = " << a4 << endl;

	++a4.first;
	++a4.second;

	cout << endl << "a4 = " << a4 << endl;

	std::pair<char, double> a5{ 'Z', 4.789 };

	cout << endl <<"std::get<0>(a5) = "<<std::get<0>(a5)<<endl;
	cout << endl <<"std::get<1>(a5) = "<<std::get<1>(a5)<<endl;


	auto res = solve_equation(1.4f, 7.0f, 2.0f);
	cout << endl << "  result " << res << endl;


}

//---------------------------------------------тестирование кортежей std::tuple<T1,T2,...Tn> t-------------------------------------
void test_tuples()
{
	auto lam = [&](std::tuple<int, float, string>& t) {

		cout << endl << "tuple<int, float, string> t -> " << "[" << std::get<0>(t) <<","<< std::get<1>(t) << "," << std::get<2>(t) << "]";

	};

	//создание кортежа
	std::tuple<int, float, string> t0;									//кортеж из 3-х элементов с инициализацией конструкторами по умолчанию												
	std::tuple<int, float, string> t1(5, 4.2f, "string");				//кортеж из 3-х элементов с инициализацией заданными значениями
	std::tuple<int, float, string> t2{ 3,2.71f,"Hello" };				//кортеж из 3-х элементов с инициализацией списком инициализации
	std::tuple<int, float, string> t3(t1);								//кортеж из 3-х элементов с инициализацией конструктором копирования
	auto t4 = std::make_tuple(0, 0.1f, string("auto"));					//создание кортежа с выводом типов из инициализирующих значений

	lam(t0);
	lam(t1);
	lam(t2);
	lam(t3);
	lam(t4);

	int i = 33;	
	float f = 0.9f;
	string s("*******");

	auto t5 = std::make_tuple(std::ref(i), std::ref(f), std::ref(s));		//создание кортежа ссылок с помощью std::make_tuple()
	auto t6 = std::tie(i, f, s);											//создание кортежа ссылок с помощью std::tie()


	cout << endl << "tuple<int&, float&, string&> t5 -> " << "[" << std::get<0>(t5) << "," << std::get<1>(t5) << "," << std::get<2>(t5) << "]";
	cout << endl << "tuple<int&, float&, string&> t6 -> " << "[" << std::get<0>(t6) << "," << std::get<1>(t6) << "," << std::get<2>(t6) << "]";


	auto t7 = std::tuple_cat(t1, t2);										//создание кортежа склейкой из двух других

	cout << endl << "tuple<int, float, string, int, float, string> t7 -> " << "[" << std::get<0>(t7) << "," << std::get<1>(t7) << "," << std::get<2>(t7) << ","
	<< std::get<3>(t7) << "," << std::get<4>(t7) << "," << std::get<5>(t7) << "]"<<endl;

	std::pair<int, string> p0{ 9, std::string("pair") };
	std::tuple<int, string>t8(p0);											//создание кортежа путем вызова конструктора копирования для объекта std::pair<>

	//получение характеристик кортежа
	typedef std::tuple<string, int, char, double, short, bool, long> long_tuple;

	cout << endl << "std::tuple_size<decltype(t2)>::value = " << std::tuple_size<decltype(t2)>::value << endl;
	cout << endl << "std::tuple<string, int, char, double, short, bool, long> " << std::tuple_size<long_tuple>::value << endl;
	cout << endl << "std::tuple<int,char> t " << std::tuple_size<std::tuple<int, char>>::value << endl;

	//получить тип элемента кортежа
	std::tuple_element<0, long_tuple>::type str("same element");
	cout << endl << str << endl;

	//интерфейс кортежа для std::array<>
	cout << "std::tuple_size<std::array<string,5>>::value = " << std::tuple_size<std::array<string, 5>>::value << endl;
	
	std::tuple_element<0, std::array<int, 10>>::type a = 10;
	cout << "a = " << a << endl;

	std::array<string, 10> ar{"Nico","pico"};
	cout <<endl<<"std::get<0>(ar) = "<<std::get<0>(ar)<<endl;


	//std::pair<> как элементы внутри кортежа
	std::tuple<std::pair<int, string>, std::pair<char, float>> complex_t(std::make_pair(8,string("++++++++")), std::make_pair(1,1.12f));

	cout << endl << "internal pairs " << std::get<0>(complex_t) << "     " << std::get<1>(complex_t) << endl;

}

std::ostream & operator<<(std::ostream & ostr, Some& s)
{
	return ostr << "Some { " << s.getA() << ", " << s.getS() << " }" << endl;
}


//частичная специализация шаблона для типа bool
template<>
void print_vector<bool>(std::vector<bool>& v)
{
	cout << endl;
	for (auto & e : v)
		cout << "bit = " << std::boolalpha << e << endl;
}



//---------------------------------------------тестирование контейнера std::vector<>---------------------------------------
void test_vector()
{
	//способы создания контейнера std::vector<>
	std::vector<int> vec0;										//создание пустого вектора для элементов типа int
	std::vector<int> vec1(3);									//создание вектора из 3-х элементов инициализированных конструкторами по умолчанию
	std::vector<int> vec2(3, 777);								//создание вектора из 3-х элементов со значениями 777, 777, 777
	std::vector<int> vec3{1,0,35,89};							//создание вектора при помощи списка инициализации {3,4,5,6,7}

	std::vector<int> vec4(vec2);								//создание вектора при помощи конструктора копирования		
	std::vector<int> vec5(std::move(vec3));						//создание вектора при помощи перемещающего конструктора

	std::vector<int> vec6(vec2.begin(), vec2.end());            //создание вектора на основе диапазона другого вектора 

	std::initializer_list<int> initList{1,2,3,4,5,6,7,8,9};		//список инициализации
	std::vector<int> vec7 = initList;							//создание вектора путем присвоения списка инициализации								

	std::vector<int> vec8 = vec7;								//создание вектора путем копирующего присваивания
	std::vector<int> vec9 = std::move(vec8);					//создание вектора путем перемещающего присваивания


	//вывод статистики о векторе
	print_vector_info(vec5);

	vec5.reserve(10);											//увеличиваем размер памяти для вектора для хранения 10 элементов

	print_vector_info(vec5);

	vec5.shrink_to_fit();										//уменьшаем емкость до количества элементов	

	print_vector_info(vec5);

	vector_empty_info(vec3);									//применение конструктора перемещения оставило вектор vec3 - пустым

	//присваивание элементов
	std::vector<int> vec10 = initList;
	print_vector(vec10);

	vec10.assign({ 0,0,0 });									//assign - это просто присвоение, при этом удаляются все прежние элементы вектора	
	print_vector(vec10);

	vec10.assign(5, 7);
	print_vector(vec10);

	vec10.assign(vec2.begin(), vec2.end());
	print_vector(vec10);

	std::initializer_list<int> ilist{ 9,8,7,6,5,4,3,2,1 };
	vec10.assign(ilist);
	print_vector(vec10);


	//доступ к элементам вектора
	vec10[0] = 0;												//доступ к элементу при помощи [i]		
	vec10[8] = 0;
	print_vector(vec10);

	vec10.at(0) = -1;											//доступ к элементу при помощи функции at(i)	
	
	try {
		vec10.at(9) = -1;										//выход за границы диапазона
	}
	catch (std::exception& e)
	{
		std::cerr << "EXCEPTION " << e.what() << endl;
	}
	print_vector(vec10);

	cout << endl << "front e = " << vec10.front() << " back e = " << vec10.back() << endl;

	//тестирование итераторов
	std::vector<int> ivec{7,5,3};
	test_iterators(ivec);


	//операции вставки и удаления элементов вектора
	std::vector<int> int_vec;
	for (int i = 0; i < 5; ++i)
		int_vec.push_back(i);									//добавляем в конец вектора элементы

	print_vector(int_vec);
	
	int_vec.pop_back();											//удаляем с конца вектора элемент
	int_vec.pop_back();											//еще

	print_vector(int_vec);

	std::vector<int>::iterator i = int_vec.begin();
	++i;
	int_vec.insert(i, 100);										//вставляем один элемент	
	print_vector(int_vec);

	i = int_vec.begin();
	++i;
	int_vec.insert(i, 2, 90);									//вставляем 2 элемента 90
	print_vector(int_vec);

	int_vec.insert(int_vec.begin(), ivec.begin(), ivec.end());	//вставляем диапазон значений из другого вектора
	print_vector(int_vec);

	i = int_vec.begin();
	int_vec.insert(i, {0,1,0,1});
	print_vector(int_vec);


	//операция emplace()
	std::vector<Some> vec_some;
	vec_some.push_back(Some(3,"Hello "));
	vec_some.push_back(Some(5,"Jack "));

	vec_some.emplace_back(5, "Nico ");
	vec_some.emplace(vec_some.begin() + 1, 0, "Pico");

	cout << endl;
	print_vector(vec_some);

	//операция erase()
	vec_some.emplace_back(9, "Hero");
	vec_some.emplace_back(10, "Niger");
	vec_some.emplace_back(12, "Bigger");

	cout << endl;
	print_vector(vec_some);

	vec_some.erase(vec_some.end() - 1);
	
	cout << endl;
	print_vector(vec_some);

	vec_some.erase(vec_some.begin() + 1, vec_some.end());
	print_vector_info(vec_some);
	
	cout << endl;
	print_vector(vec_some);

	//операция resize()
	std::vector<int> iv{ 9,9,9,9,9,9,9 };
	print_vector(iv);

	iv.resize(4);
	print_vector(iv);

	iv.resize(8);
	print_vector(iv);

	iv.resize(10, 5);
	print_vector(iv);

	iv.clear();
	print_vector_info(iv);


	//специализация контейнера std::vector<bool>
	std::vector<bool> flags;
	flags.push_back(true);
	flags.push_back(true);
	flags.push_back(false);
	flags.push_back(false);

	print_vector(flags);

	flags.flip();

	print_vector(flags);
	print_vector_info(flags);

	flags[0].flip();
	flags[1] = true;
	print_vector(flags);

	flags.pop_back();
	flags.insert(flags.begin(), 5, true);

	print_vector(flags);

}















