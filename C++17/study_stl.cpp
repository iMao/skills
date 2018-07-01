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
	iv.shrink_to_fit();
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

//-------------------------------------тестирование контейнера std::deque<>------------------------------------------------
void test_deque()
{

	//методы создания контейнера std::deque<>
	std::deque<string> dq0;									//пустой контейнер
	std::deque<string> dq1(3);								//контейнер на 3 элемента инициализированных своими конструкторами по умолчанию
	std::deque<string> dq2(3, string("simple"));			//контейнер на 3 элемента типа string инициализированных значением "simple"
	std::deque<string> dq3{"Hello", "world", "!!!", "OK"};	//контейнер на основе списка инициализации {}

	std::deque<string> dq4(dq2);							//создание контейнера с помощью конструктора копирования
	std::deque<string> dq5(std::move(dq3));					//создание контейнера при помощи перемещающего конструктора

	std::deque<string> dq6((++dq5.cbegin()), dq5.cend());	//создание контейнера на основе диапазоне значений другого контейнера


	std::initializer_list<string> text{"BMW","Audi","Opel","Toyota","Volvo","Mercedes","Porshe"};
	std::deque<string> dq7 = text;							//создание контейнера на основе присвоения списка инициализации	{}

	std::deque<string> dq8 = dq2;							//создание контейнера на основе оператора копирующего присваивания
	std::deque<string> dq9 = std::move(dq5);				//создание контейнера на оснопе оператора перемещающего присваивания


	//запрос информации о контейнере
	print_deque_info(dq7);
	print_deque(dq7);


	//модифицирование контейнера std::deque<>
	dq7.push_back(string("Pegot"));
	dq7.push_front(string("Citroen"));
	
	dq7.emplace_back("AlfaRomeo");
	dq7.emplace_front("Shevrole");

	dq7.insert(++dq7.cbegin(), string("Mustang"));
	dq7.emplace(++dq7.cbegin(), "Volga");

	print_deque(dq7);
	
	dq7.pop_back();
	dq7.pop_front();
	
	print_deque(dq7);

	dq7.assign(10, string("Bently"));

	print_deque(dq7);

	dq7.assign(text.begin(), text.end());

	print_deque(dq7);

	dq7.erase(--dq7.end());
	
	print_deque(dq7);
	
	dq7.erase(++dq7.begin(), --dq7.end());

	print_deque(dq7);

	dq7.insert(++dq7.begin(), { "Audi","Opel","Toyota","Volvo" } );
	
	print_deque(dq7);

	dq7.clear();

	print_deque(dq7);

	dq7.resize(5, string("some string"));
	print_deque(dq7);

	dq7.resize(7, string("something else"));
	print_deque(dq7);

	dq7.resize(3);
	print_deque(dq7);


	//итераторы для обхода контейнера std::deque<>
	std::deque<string>::const_iterator ci          = dq7.begin();
	std::deque<string>::iterator it                = dq7.begin();
	std::deque<string>::const_reverse_iterator cri = dq7.crbegin();
	std::deque<string>::reverse_iterator ri        = dq7.rbegin();

	cout << endl;
	for (; ci != dq7.end(); ++ci)
		cout << "e - " << (*ci) << endl;

	cout << endl;
	for (; it != dq7.end(); ++it) 
		cout << "e - " << (*it).append("-") << endl;

	cout << endl;
	for (; cri != dq7.crend(); ++cri)
		cout << "e <- " << (*cri) << endl;

	cout << endl;
	for (; ri != dq7.rend(); ++ri)
	{
		(*ri).at((*ri).size() - 1) = '+';
		cout << "e <- " << (*ri) << endl;
	}

}


bool rmbig(int a)
{
	return (a > 1000 ? true : false);
}

//-------------------------------------тестирование контейнера std::list<>-------------------------------------------------
void test_list()
{
	//методы создание контейнера std::list<>
	std::list<int> lst0;							//пустой список
	std::list<int> lst1(5);							//список из 5-ти элементов созданных конструктором их типа по умолчанию
	std::list<int> lst2(5, 5);						//список из 5-ти элементов 5
	std::list<int> lst3{ 1,9,3,7,0,10,24,12 };		//список на основе списка инициализации
	std::list<int> lst4({ 2,4,5,6,1,0 });			//

	std::list<int> lst5(lst3);						//список создан путем вызова конструктора копирования
	std::list<int> lst6(std::move(lst2));			//список создан путем вызова конструктора перемещения
	std::list<int> lst7(lst3.begin(), lst3.end());	//список создан на основе интервала заданного итераторами (begin, end)

	std::initializer_list<int> ini_list{ 9,8,7,6,5,4,3,2,1,0 };
	std::list<int> lst8 = ini_list;					//список создан на основе списка инициализации
	std::list<int> lst9 = lst8;						//неявный вызов конструктора копирования		
	std::list<int> lst10 = std::move(lst9);			//неявный вызов конструктора перемещения


	print_list(lst0);
	print_list(lst8);
	print_list_info(lst8);

	//операции присваивания
	lst0.assign(ini_list);
	lst1.assign(4, 9990);
	lst2.assign(++lst3.begin(), --lst3.end());

	print_list(lst0);
	print_list(lst1);
	print_list(lst2);

	lst9.assign(ini_list);
	lst1.swap(lst9);

	print_list(lst9);
	print_list(lst1);


	//доступ к элементам
	cout << "first element - " << lst1.front() << endl;
	cout << "last  element - " << lst1.back()  << endl;

	//доступ спомощью итераторов
	std::list<int>::const_iterator ci;
	std::list<int>::iterator i;
	std::list<int>::reverse_iterator ri;
	std::list<int>::const_reverse_iterator cri;

	for (ci = lst9.cbegin(); ci != lst9.cend(); ++ci)
		cout << (*ci) << " ";

	cout << endl;
	for (i = lst9.begin(); i != lst9.end(); ++i)
		cout << ((*i) /= 2)<<" ";

	cout << endl;
	for (ri = lst1.rbegin(); ri != lst1.rend(); ++ri)
		cout << ((*ri) *= 2) << " ";

	cout << endl;
	for (cri = lst1.crbegin(); cri != lst1.crend(); ++cri)
		cout << (*cri) << " ";

	cout << endl;

	//модификация списка
	std::initializer_list<int> numbers{ 7,7,7,5,5,5 };
	std::initializer_list<int> big_numbers{ 1000,2000,3000 };
	
	std::list<int> l = numbers;

	l.push_back(10);
	l.push_front(10);
	l.emplace_back(9);
	l.emplace_front(9);

	auto pos = l.begin();
	
	size_t k = l.size();
	size_t half = k / 2;
	while (k > half)
	{
		--k;
		++pos;
	}

	l.insert(pos, 5000);				//вставка элемента в середину списка
	print_list(l);

	l.insert(l.begin(), big_numbers);
	l.insert(l.end(), big_numbers.begin(), big_numbers.end() );
	print_list(l);


	cout << endl << "remove all numbers 9 " << endl;
	l.remove(9);						//удаляем все числа 9
	print_list(l);						

	cout << endl << "remove all numbers >1000 " << endl;
	l.remove_if(rmbig);
	print_list(l);

	cout << endl << "remove all even numbers " << endl;
	l.remove_if(Rm());
	print_list(l);

	cout << endl << " remove all numbers that can be divided / 5 " << endl;
	l.remove_if([](int a)->bool {
		if ((a % 5) == 0)
			return true;
		else
			return false;
	});
	
	print_list(l);

	cout << endl << "resize to 10 elements" << endl;
	l.resize(10, 3);
	print_list(l);

	cout << endl << "reverse list" << endl;
	l.reverse();
	print_list(l);

	cout << endl << "erase core" << endl;
	l.erase(++l.begin(), --l.end());
	print_list(l);


	cout << endl << "erase first element" << endl;
	l.erase(l.begin());
	print_list(l);

	l.clear();

}

//функция предикат для выявления одинаковой целой части вещественных чисел
bool same_integral_part(double & first, double & second)
{
	return (static_cast<int>(first) == static_cast<int>(second));
}

bool compare_pairs(std::pair<int, int>& p1, std::pair<int, int>& p2)
{
	return (p1.second < p2.second);
}

void test_list_special()
{
	//специальные модифицирующие операции над списками
	std::list<int> l{ 9,9,4,2,1,3,3,0,4,6,5,0,0 };
	print_list(l);
	
	l.unique();												//удаляет дубликаты последовательных элементов
	print_list(l);

	std::list<double>ld{ 9.3, 9.1, 4.9, 5.0, 6.1, 5.95, 6.0, 6.5, 7.2, 8.11, 8.21, 9.25 };
	print_list(ld);

	ld.unique(same_integral_part);							//удаление элементов у которых равные целые части (предикат-функция)
	print_list(ld);

	ld.unique(Near());										//удаление элементов для которых /разность/ < 0.5 (предикат-функтор)
	print_list(ld);

	ld.unique([](const double a, const double b)->bool {    //удаление элементов у которых дробная часть отличается менее чем на 0.1
	
		double a_ = a - static_cast<int>(a);
		double b_ = b - static_cast<int>(b);

		return (fabs(a_ - b_) < 0.1);
	});


	print_list(ld);

	//модификация списков с1 и с2
	std::list<int> a{ 9, 8, 7, 6, 5 };
	std::list<int> b{ 5, 5, 6, 6 };

	cout << endl << "lists modifications" << endl;
	print_list(a);
	print_list(b);

	a.splice(a.begin(), b);									//перемещаем список b все элементы в список a
	print_list(a);
	print_list(b);

	b.splice(b.begin(), a, a.begin());						//в список b вставляем один элемент	из списка а
	print_list(b);

	b.splice(++b.begin(), a, ++a.begin(), a.end());			//перемещаем все элементы кроме первого из списка а в список b
	print_list(a);
	print_list(b);

	b.sort();												//сортировка списка с помощью оператора <
	print_list(b);

	std::list<std::pair<int, int>> lp;						//создаем список пар std::pair<int,int>
	std::list<std::pair<int, int>> lp2;
	for (int i = 0; i < 5; i++)
	{
		lp.push_back(std::make_pair(5-i, i));
		lp2.push_back(std::make_pair(i, 7 - i));
	}

	lp.push_back(std::make_pair(4, 4));
	lp.push_back(std::make_pair(4, 4));

	print_list(lp);

	lp.sort();
	print_list(lp);

	lp.sort(compare_pairs);									//сортируем при помощи предиката
	print_list(lp);

	lp2.sort(compare_pairs);								
	print_list(lp2);										

	lp.merge(lp2, compare_pairs);							//объединяю два отсортированных списка на основе функции-предиката
	print_list(lp);
}



//------------------------------------------тестирование контейнера std::forward_list<>----------------------------------------------
bool compare_strings_lower(string s1, string s2)
{
	std::transform(s1.begin(), s1.end(), s1.begin(), tolower);
	std::transform(s2.begin(), s2.end(), s2.begin(), tolower);

	if (0 == s1.compare(s2))
		return true;
	else
		return false;
}

bool cmp_abs(int a, int b)
{
	return (abs(a) < abs(b));
}



void test_forward_list()
{
	//методы создания контейнера std::forward_list<>
	std::forward_list<int> frwd0;
	std::forward_list<int> frwd1(5);
	std::forward_list<int> frwd2(5, 5);
	std::forward_list<int> frwd3{ 5,6,7,8,9 };
	std::forward_list<int> frwd4(frwd3);
	std::forward_list<int> frwd5(std::move(frwd3));
	
	std::initializer_list<int> init_list{ 1,1,2,2,3,3,4,4,5,5 };
	std::forward_list<int> frwd6(init_list);
	std::forward_list<int> frwd7({ 55,66,77,88,99 });

	std::forward_list<int> frwd8 = frwd2;
	std::forward_list<int> frwd9 = std::move(frwd7);
	std::forward_list<int> frwd10 = init_list;

	std::forward_list<int> frwd11(frwd9.begin(), frwd9.end());

	print_forward_list(frwd6);
	print_forward_list(frwd11);


	//немодифицирующие операци 
	print_forward_list_info(frwd6);
	print_forward_list_info(frwd11);


	//операции присваивания
	std::initializer_list<string> str_list{"Ivan", "Lena", "Ksenia"};

	std::forward_list<string> frwds0{ "Maria", "Nico", "Pico" };
	std::forward_list<string> frwds1 = frwds0;

	std::forward_list<string> frwds2 = std::move(frwds1);
	std::forward_list<string> frwds3 = { "Jack", "Bruce", "Andrew" };

	print_forward_list(frwds2);
	print_forward_list(frwds3);


	frwds2.assign(5, "jambo");
	frwds3.assign(++frwds0.begin(), frwds0.end());
	frwds0.assign(str_list);

	print_forward_list(frwds2);
	print_forward_list(frwds3);
	print_forward_list(frwds0);

	//вставка и удаление элементов
	std::forward_list<double> fd0{ 9.1,9.6, 9.8, 9.9, 2.3, 2.4 };
	fd0.push_front(0.3);
	fd0.emplace_front(0.5);

	print_forward_list(fd0);

	std::forward_list<double>fd1{ 5.5, 6.6, 7.7 };

	fd0.insert_after(fd0.before_begin(), 100.01);
	fd0.insert_after(fd0.before_begin(), fd1.begin(), fd1.end());
	fd0.insert_after(fd0.before_begin(), 3, 500.05);

	fd0.emplace_after(fd0.before_begin(), 99.9);

	print_forward_list(fd0);

	//нахождение позиции итератора
	auto pos_before = fd0.before_begin();
	for (auto pos = fd0.begin(); pos != fd0.end(); ++pos, ++pos_before)
	{
		if ((*pos) < 3.0)		//находим первое число, которое меньше 3
			break;
	}

	fd0.erase_after(pos_before);						//удаляем элемент стоящий после позиции на которую указывает pos_before

	print_forward_list(fd0);

	fd0.remove_if([](double & a)->bool {
					return (a - static_cast<int>(a) > 0.4);
	});

	print_forward_list(fd0);

	fd0.erase_after(fd0.begin(), fd0.end());			//удаляем все элементы из интервала (beg, end) не включая границы

	print_forward_list(fd0);


	//нахождение позиции итератора при помощи функции next()
	std::forward_list<int>f{1,3,5,6,7,8,9,10 };
	print_forward_list(f);

	auto posBefore = f.before_begin();
	for (; next(posBefore) != f.end(); ++posBefore)
	{
		if ((*next(posBefore)) % 2 == 0)
			break;
	}

	f.erase_after(posBefore);							//хотим удалить первый четный элемент

	print_forward_list(f);


	auto position = findBefore(f.begin(), f.end(), 8);	//ищем итератор указывающий на позицию элемента предшествующего искомому 
	f.erase_after(position);

	print_forward_list(f);

	auto pos_insertion = findBefore_if(f.begin(), f.end(), [](int a)->bool { return ((a % 2) == 0); });
	f.insert_after(pos_insertion, 1000);

	print_forward_list(f);


	//модификация списков
	std::forward_list<string> strlist{ "hello", "HELLO", "BAY-BAY", "bay-bay", "good morning", "GOOD MORNING" };
	print_forward_list(strlist);

	cout << endl << "unique(op)" << endl;
	strlist.unique(compare_strings_lower);
	print_forward_list(strlist);

	std::forward_list<string> strlist2{ "hello", "HELLO", "BAY-BAY", "bay-bay", "good morning", "GOOD MORNING" };
	print_forward_list(strlist2);

	strlist2.unique(CompUpper());
	print_forward_list(strlist2);

	std::forward_list<string> additional{ "1234","9876" };

	strlist.splice_after(strlist.before_begin(), additional);
	print_forward_list(strlist);

	strlist.splice_after(strlist.before_begin(), strlist2, strlist2.before_begin());
	print_forward_list(strlist);
	
	cout << endl << "Payment cards" << endl;
	std::forward_list<string> cards{ "Visa", "Mastercard" };
	std::forward_list<string> vip_cards{ "Visa Gold","Visa Classic", "Visa Platinum", "Mastercard Black" };

	cards.splice_after(findBefore(cards.begin(), cards.end(), "Mastercard"), vip_cards, vip_cards.before_begin(), findIterator(vip_cards.begin(), vip_cards.end(), "Mastercard Black") );
	print_forward_list(cards);


	cout << endl << "sort() with abs() " << endl;
	std::forward_list<int> digits{ 5, 6,-4, -5, -6, 3, 0, -1, 2, 1, 10, -9 };
	digits.sort(cmp_abs);
	print_forward_list(digits);

	std::forward_list<int> digits_{ 2, 3, 1, -2, -7, -11, -34, 23, -6, 8 };
	digits_.sort(cmp_abs);
	print_forward_list(digits_);

	cout << endl << "merge forward_lists" << endl;
	digits.merge(digits_, cmp_abs);
	digits.reverse();            
	
	print_forward_list(digits);

}




//--------------------------------тестирование множеств std::set<>-----------------------------------------------------------------

std::ostream & operator<<(std::ostream & os, Num & num)
{
	return os << "[ 0x" <<std::hex << num.get_a() << " ]";
}


void test_sets()
{
	//методы создания и инициализации
	std::set<int> set1;									//пустое множество элементов типа int, с критерием сортировки заданным по умолчанию std::less<>
	std::set<int, std::less<int>> set2;					//пустое множество элементов типа int, с явно заданным критерием сортировки 
	std::set<int, std::greater<int>> set3;				//пустое множество элементов типа int, с явно заданным критерием сортировки 

//	std::set<int> set4(std::less<int>());				//пустое множество элементов типа int, но критерий сортировки задан как параметр в конструкторе				

	std::initializer_list<int> ilst{ 9,3,10,2,5,1,0,7 };

	std::set<int, std::less<int>> set5(ilst);			//множество элементов типа int c заданным критерием сортровки, инициализированное списком инициализации
	std::set<int> set6(set5);							//множество созданное конструктором копирования
	std::set<int> set7(std::move(set5));				//множество созданное конструктором перемещения


	std::list<int> list0{ 8,5,6,1,4,2,9,0 };
	std::set<int> set8(list0.begin(), list0.end());		//множество элементов созданное на основе элементов из интервала заданного итераторами, с критерием сортировки по умолчанию

	std::set<int, std::greater<int>> set9(set8.begin(), set8.end(), std::greater<int>() );//множество созданное на основе элементов из интервала другого множества но с другим критерием сортировки


	//методы присваивания
	std::set<int> set10 = set8;
	std::set<int> set11 = std::move(set8);
	std::set<int> set12 = { 9,7,1,3,2,5,6 };
	std::set<int> set13 = ilst;


	print_set(set7);
	print_set_info(set7);
	print_cmp_criteria(set7);

	print_set(set9);
	print_set_info(set9);
	print_cmp_criteria(set9);

	//специальные операции поиска элемента во множестве std::set<>
	std::set<int, std::less<int>> set01{ 3,5,7,0,1,10,8,6 };
	cout << endl << "set.count(7) = " << set01.count(7) << endl;
	
	std::set<int,std::less<int>>::const_iterator pos1 = set01.find(7);
	std::set<int, std::less<int>>::const_iterator pos2 = set01.find(8);
	
	print_set_beg_end(pos1, pos2, set01);

	print_set(set01);
	bounds(set01, 4);
	bounds(set01, 7);


	//вставка и удаление элементов
	auto result = set01.insert(9);
	if (result.second)
		print_set(set01);

	auto result2 = set01.insert( set01.find(10) ,11);
	print_set(set01);

	std::list<int> l{ -5,2,15,25 };
	std::initializer_list<int>intlist{ -6, -7 ,-8, -9};

	set01.insert(l.begin(), l.end());
	set01.insert(intlist);
	print_set(set01);

	
	
	std::set<Num, NumLess<Num>> numbers{ Num(8), Num(10), Num(11), Num(7) };
	print_set(numbers);


	numbers.emplace(15);
	numbers.emplace_hint(numbers.find(Num(7)), 3);
	print_set(numbers);

	numbers.erase(Num(7));
	print_set(numbers);

	numbers.erase(numbers.find(Num(0xF)));
	print_set(numbers);

	numbers.erase(++numbers.begin(), --numbers.end());
	print_set(numbers);

	numbers.clear();
	print_set_info(numbers);
}




//-----------------------------------тестирование мультимножеств std::multiset<>-----------------------------------------------
void test_multisets()
{
	//методы создания
	std::multiset<int> mset0;
	std::multiset<int, std::greater<int>> mset1;
	//std::multiset<int, std::greater<int>> mset3(std::greater<int>);
	std::multiset<int> mset4{ 5,6,1,0,2,5 };

	std::initializer_list<int> ls{ 9,2,1,7,5,3,4,7 };
	std::multiset<int, std::greater<int>> mset5(ls);
	std::multiset<int, std::greater<int>> mset6(mset5);
	std::multiset<int> mset7(std::move(mset4));
	
	std::vector<int> vec{ 0,5,3,2,7,8,8,9,9 };
	std::multiset<int> mset8(vec.begin(), vec.end());
	std::multiset<int, std::greater<int>> mset9(vec.begin(), vec.end(), std::greater<int>());

	//методы присваивания
	std::multiset<int> mset10{ 9,3,3,3,4,4,4,5,5,5 };

	std::multiset<int> mset11 = mset10;
	std::multiset<int> mset12 = std::move(mset11);
	std::multiset<int> mset13 = ls;
	std::multiset<int> mset14 = { 4,3,1,8,7,7,7,8,8,8 };

	//поиск элементов
	cout << endl << "number 7    - " << mset14.count(7) <<" times"<< endl;
	cout << endl << "number 1    - " << *mset14.find(1) << endl;
	cout << endl << "lower_bound(7) - " << *mset14.lower_bound(7) << endl;
	cout << endl << "upper_bound(7) - " << *mset14.upper_bound(7) << endl;
	cout << endl << "equal_range(7) - " << *mset14.equal_range(7).first << " - " << *mset14.equal_range(7).second << endl;


	//методы модификации множества
	mset14.insert(1);
	cout <<endl<< "insert 1 " << endl;
	print_multiset(mset14);

	mset14.insert(mset14.find(4), 5);
	cout << endl << "insert 5 " << endl;
	print_multiset(mset14);

	mset14.insert(mset12.begin(), mset12.end());
	cout << endl << "insert [beg, end) " << endl;
	print_multiset(mset14);

	mset14.insert(ls);
	cout << endl << "insert (initlist) " << endl;
	print_multiset(mset14);

	mset14.emplace(-1);
	mset14.emplace_hint(mset14.find(-1), 0);
	print_multiset(mset14);


	cout << endl << "erase all numbers 7 " << endl;
	mset14.erase(7);
	print_multiset(mset14);

	mset14.erase(mset14.find(8));
	print_multiset(mset14);

	mset14.erase(++mset14.begin(), --mset14.end());
	print_multiset(mset14);
}



//------------------------------------------тестирование отображений std::map<>------------------------------------------------
void test_maps()
{
	//методы создания
	std::map<int, string> mp0;										//пустое отображение с элементами std::pair<int, string> и критерием упорядочивания по умолчанию std::less<>
	std::map<int, string, std::greater<int>> mp1;

	std::map<int, string> mp2{ std::make_pair(5,"Tom"), std::make_pair(8,"Jack"), std::make_pair(1,"Kate"), std::make_pair(7,"Tim") };
	std::map<int, string> mp02{ {22,"Pico"},{55, "Sergo"},{90,"Siri"} };
	std::map<int, string> mp3(mp2);
	std::map<int, string> mp4(std::move(mp2));


	std::initializer_list<std::pair<const int, string>> ilp{ std::make_pair(4,string("Andrew")), std::make_pair(9,string("Timur")), std::make_pair(2,string("Nico")), std::make_pair(6,string("Peter")) };
	std::initializer_list<std::pair<const int, string> > ls{ { 77,"Valio" },{ 97, "Julio" } };

	std::map<int, string> mp7(ls);
	std::map<int, string> mp8(ilp);


	std::deque<std::pair<int, string>> dq{ std::make_pair(0,"Andrew"), std::make_pair(10,"Timur"), std::make_pair(3,"Nico"), std::make_pair(11,"Peter") };

	std::map<int, string> mp5(dq.begin(), dq.end());
	std::map<int, string, std::greater<int>> mp6(dq.begin(), dq.end(), std::greater<int>());
	

	print_map(mp3);
	print_map(mp02);
	print_map(mp4);

	print_map(mp7);
	print_map(mp8);
	print_map(mp5);
	print_map(mp6);

	//операции присваивания
	std::map<int, string> mp9 = mp5;
	std::map<int, string> mp10 = std::move(mp7);
	std::map<int, string> mp11 = ls;
	std::map<int, string> mp12 = { {3,"Hello"},{9,"Bay"},{5,"Afternoon"} };


	cout << endl << "maps after operation = " << endl;
	print_map(mp9);
	print_map(mp10);
	print_map(mp11);
	print_map(mp12);

	//операции поиска 
	mapbounds(mp12, 5);

	cout << endl << "Number elements with key 3 = " << mp12.count(3) << endl;
	cout << endl << "Find element wih key 3, val = " << (*mp12.find(3)).second << endl;

	//итераторы
	std::map<int, string>::iterator i;
	std::map<int, string>::const_iterator ci;
	std::map<int, string>::reverse_iterator ri;
	std::map<int, string>::const_reverse_iterator cri;

	for (i = mp12.begin(); i != mp12.end(); ++i)
		i->second = i->second.append(" word");

	print_map(mp12);

	cout << endl;
	for (ci = mp12.cbegin(); ci != mp12.cend(); ++ci)
		cout << (*ci).first<<" , "<<(*ci).second<<endl;


	for (ri = mp12.rbegin(); ri != mp12.rend(); ++ri)
		 ri->second.insert(ri->second.begin(), '-');

	print_map(mp12);


	for (cri = mp12.crbegin(); cri != mp12.crend(); ++cri)
		cout << (*cri).first << endl;


	//модифицирующие операции
	std::map<string, string> dictionary{ {"black","черный"},{"white","белый"} };
	
	dictionary.insert(std::make_pair("red", "красный"));
	
	dictionary.insert(std::map<string, string>::value_type("blue", "синий"));
	
	dictionary.insert(std::pair<string, string>("green", "зеленый"));
	
	dictionary.insert(std::pair<const string, string>("green", "зеленый"));
	
	print_map(dictionary);


	dictionary.insert(dictionary.find("black"), std::make_pair("be", "быть"));


	std::vector<std::pair<string, string> > vec{ {"do","делать"},{"make","производить"},{"get","получить"},{"go","идти"} };
	std::initializer_list<std::pair<const string, string>> words{ {"word","слово"},{"world","мир"},{"hello","привет"} };


	dictionary.insert(vec.begin(), vec.end());
	dictionary.insert(words);

	print_map(dictionary);


	dictionary.emplace("house", "дом");
	dictionary.emplace_hint(dictionary.find("green"),  "good","хороший" );
	
	print_map(dictionary);

	dictionary.erase("hello");
	print_map(dictionary);

	//dictionary.erase(dictionary.find("green"));
	//print_map(dictionary);

	//dictionary.erase(dictionary.find("get"), dictionary.find("word"));
	//print_map(dictionary);


	//использование отображений как ассоциативных массивов

	dictionary["name"] = "имя";
	dictionary["sex"] = "пол";
	dictionary["family"] = "семья";

	print_map(dictionary);

	cout << endl << dictionary.at("sex") << endl;
	cout << endl << dictionary.at("name") << endl;
	cout << endl << dictionary.at("family") << endl;


	replace_key(dictionary, string("make"), string("produce") );
	print_map(dictionary);

	//применение алгоритмов

	std::map<string, float> pp;
	pp["BASF"]  = 70.3f;
	pp["TSL"]   = 90.9f;
	pp["NVDIA"] = 100.0f;
	pp["UBS"]   = 78.2f;
	pp["VW"] = 45.7f;


	std::for_each(pp.begin(), pp.end(), [](std::map<string, float>::value_type & e) { e.second *= 2.0; });

	cout << endl;
	std::for_each(pp.begin(), pp.end(), [](const std::map<string,float>::value_type & e) { cout <<"("<< e.first <<","<<e.second<<")"<<endl; });

	pp["Volkswagen"] = pp["VW"];
	pp.erase("VW");

	cout << endl;
	std::for_each(pp.begin(), pp.end(), [](const std::map<string, float>::value_type & e) { cout << "(" << e.first << "," << e.second << ")" << endl; });


	//поиск по значению

	cout << endl;
	auto pos = std::find_if(pp.begin(), pp.end(), [](std::pair<const string, float> & p) { return abs(p.second - (90.9 * 2)) < 0.1; });

	if (pos != pp.end())
		cout << "(" << pos->first << " , " << pos->second << ")" << endl;




	//динамическое изменение критерия сравнения
	std::map<string, int, RealTimeCmp> currencies;
	currencies["DOL"] = 100;
	currencies["EUR"] = 50;
	currencies["CHF"] = 150;
	currencies["RUB"] = 20;
	currencies["YUP"] = 100;
	currencies["BPS"] = 150;
	currencies["UAN"] = 20;
	currencies["dollar"] = 100;
	currencies["euro"] = 50;
	currencies["swichss"] = 150;
	currencies["rubles"] = 20;




	print_map(currencies);

	RealTimeCmp nocase_cmp(RealTimeCmp::nocase);
	
	std::map<string, int, RealTimeCmp> dng(nocase_cmp);				//создание контейнера с тем же типом но другим критерием сравнения
	dng["DOL"] = 100;
	dng["EUR"] = 50;
	dng["CHF"] = 150;
	dng["RUB"] = 20;
	dng["YUP"] = 100;
	dng["BPS"] = 150;
	dng["UAN"] = 20;
	dng["dollar"] = 100;
	dng["euro"] = 50;
	dng["swichss"] = 150;
	dng["rubles"] = 20;


	print_map(dng);



}



//---------------тестирование неупорядоченных множеств и мультимножеств std::unordered_set<> and std::unordered_multiset<>--------
std::ostream & operator<<(std::ostream & ostr, const Customer & c)
{
	return ostr << "Customer: [" <<std::setw(10)<<std::left<< c.get_name() << " - " << c.get_check_sum()<<"]";
}




void test_unordered_sets()
{
	//методы создания и инициализации
	std::unordered_set<int> uset0;										//создание пустой hash таблицы для элементов типа int, с hash функцией std::hash() и критерием эквивалентности equal_to()
	std::unordered_set<int> uset1(10);									//создание пустой hash таблицы для элементов типа int, и с заданным количеством сегментов
	std::unordered_set<int, std::size_t(*)(int)> uset01 (10, hashf<int>);

	std::initializer_list<int> intlist{ 9,3,1,7,5,4,2,8 };

	std::unordered_set<int> uset2{ 7,4,1,8,9 };			//создание неупорядоченного контейнера на основе списка инициализации
	std::unordered_set<int> uset3(intlist);				//
	
	std::unordered_set<int> uset4(uset2);				//с помощью конструктора копирования
	std::unordered_set<int> uset5(std::move(uset2));	//использование конструктора перемещения

	std::unordered_set<int, std::hash<int>, std::equal_to<int>> uset6{ 8,12,4,5 };	//явное указание функции хеширования и проверки на эквивалентность

	std::forward_list<int> flist{ 89,34,12,35,56,78,87 };

	std::unordered_set<int> uset7( flist.begin(), flist.end() );
	std::unordered_set<int> uset8(flist.begin(), flist.end(), 10);

	print_unordered_set(uset4);
	print_unordered_set_info(uset4);

	print_unordered_set(uset8);
	print_unordered_set_info(uset8);

	std::unordered_set<int, std::size_t(*)(int)> uset9( flist.begin(), flist.end(), 10, hashf<int>);
	print_unordered_set(uset9);
	print_unordered_set_info(uset9);


	std::unordered_set<Customer, CustomerHash, CustomerEqual> restoran{ Customer("Jack", 50), Customer("Jon",70), Customer("Tim", 89), Customer() };
	print_unordered_set(restoran);
	print_unordered_set_info(restoran);

	std::unordered_set<Customer, CustomerHash> bar{ Customer("Nico", 50), Customer("Linda",70), Customer("Jim", 89), Customer("Silver",90) };
	print_unordered_set(bar);


	//операторы присваивания
	uset0 = uset3;
	uset1 = std::move(uset3);

	std::unordered_set<int> uset10 = intlist;
	std::unordered_set<int> uset11 = {45,12,46};


	//специальные операции поиска
	print_unordered_set(uset1);
	cout << endl << "Сколько элементов со значением " << 8 << "  " << uset1.count(8) << endl;
	cout << endl << "Элемент 8 " << *(uset1.find(8)) << endl;
	cout << endl << "Находим интервал для элемента 1 " << *(uset1.equal_range(1).first) << " - " << *(uset1.equal_range(1).second) << endl;
	
	std::unordered_set<int> uset12(intlist);
	
	std::unordered_set<int>::const_iterator pos1, pos2;

	std::tie(pos1, pos2) = uset12.equal_range(8);

	if (pos1 == uset12.end())
		cout << "pos1 is bad" << endl;

	if (pos2 == uset12.end())
		cout << "pos2 is bad" << endl;

	//итераторы существуют только однонаправленные, модифицировать значения НЕЛЬЗЯ
	std::unordered_set<int>::const_iterator ci;
	std::unordered_set<int>::iterator i;
	
	for (i = uset12.begin(); i != uset12.end(); ++i)
		cout << (*i) << " ";


	//модифицирующие операции
	uset12.insert(100);
	print_unordered_set(uset12);

	uset12.insert(uset12.find(100), 101);
	print_unordered_set(uset12);

	uset12.insert(uset11.begin(), uset11.end());
	print_unordered_set(uset12);

	uset12.insert({ 200,230 });
	print_unordered_set(uset12);



	bar.emplace("Edvard", 345);
	print_unordered_set(bar);

	bar.emplace_hint(bar.find(Customer("Edvard", 345)), "Donn Diego", 300);
	print_unordered_set(bar);


	bar.erase(Customer("Edvard", 345));
	print_unordered_set(bar);

	bar.erase(bar.find(Customer("Nico", 50)));
	print_unordered_set(bar);

	bar.erase(++bar.begin(), bar.end());
	print_unordered_set(bar);

	bar.clear();
	print_unordered_set(bar);
}





//-------------------------------------тестирование потоков ввода вывода------------------------------------------------------------

void cin_properties(std::istream & cin_)
{
	std::ios::iostate cin_state = cin_.rdstate();						//запрос флагов состояния потока

	cout << "-------------------------------------------------------";
	cout <<endl << "прверка битов состояния потока cin " << endl;

	//проверка отдельных флагов
	if (cin_state & std::ios::goodbit)
		cout << "cin has \'goodbit\' " << endl;
	else
		cout << "cin does not has  \'goodbit\' " << endl;

	if (cin_state & std::ios::eofbit)
		cout << "cin has \'eofbit\' " << endl;
	else
		cout << "cin does not has  \'eofbit\' " << endl;

	if(cin_state & std::ios::failbit)
		cout << "cin has \'failbit\' " << endl;
	else
		cout << "cin does not has  \'failbit\' " << endl;

	if(cin_state & std::ios::badbit)
		cout << "cin has \'badbit\' " << endl;
	else
		cout << "cin does not has  \'badbit\' " << endl;


	cout <<endl<< "проверка битов состояния с помощью функций good(), eof(), fail(), bad() " << endl;
	

	//проверка отдельных битов с помощью функций
	if(cin_.good())
		cout << "cin has \'goodbit\' " << endl;
	else
		cout << "cin does not has  \'goodbit\' " << endl;

	if(cin_.eof())
		cout << "cin has \'eofbit\' " << endl;
	else
		cout << "cin does not has  \'eofbit\' " << endl;

	if(cin_.fail())
		cout << "cin has \'failbit\' " << endl;
	else
		cout << "cin does not has  \'failbit\' " << endl;

	if(cin_.bad())
		cout << "cin has \'badbit\' " << endl;
	else
		cout << "cin does not has  \'badbit\' " << endl;


	//проверка битов состояний которые генерируют исключения
	cout << endl << "Проверка битов состояний которые генерируют исключения" << endl;

	int flags = cin_.exceptions();									//получаем флаги установка которых вызывает исключения

	if (flags & std::ios::goodbit)
		cout << "cin не генерирует исключений" << endl;

	if (flags & std::ios::eofbit)
		cout << "cin генерирует исключения при достижении конца файла EOF" << endl;

	if (flags & std::ios::failbit)
		cout << "cin генерирует исключения при ошибке ввода failbit" << endl;

	if (flags & std::ios::badbit)
		cout << "cin генерирует исключения при ошибке ввода badbit" << endl;
}


void set_locale(LANG lang)
{
	switch (lang)
	{
		case C:			setlocale(LC_ALL, "C");
			break;
		case ENG:		setlocale(LC_ALL, "en-US");
			break;
		case ENG_UTF8:	setlocale(LC_ALL, "en_US.UTF-8");
			break;
		case RUS:		setlocale(LC_ALL, "Russian");
			break;
		case RUS_UTF8:	setlocale(LC_ALL, "ru_RU.utf8");
			break;
		case DE:		setlocale(LC_ALL, "de_DE");
			break;
		case DE_UTF8:	setlocale(LC_ALL, "de_DE.utf8");
			break;
		case FR:		setlocale(LC_ALL, "fr-FR");
			break;
		default: cout << "You chosed wrong language. Reset locale." << endl;
			break;
	}

	std::cout << "User preffered local:" << std::locale().name() << endl;					
}



void test_ithreads()
{
	//проверка свойств потока ввода std:cin 
	//cin_properties(cin);
	//cin.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);					//установка бит состояний в которых будут генерироваться исключения

	//cin_properties(cin);
	//cin.exceptions(std::ios::goodbit);															//сброс всех флагов		

	//cin_properties(cin);

	//ввод данных с консоли
	char c;
	wchar_t wc;

	//cout << "input char - ";
	//cin.get(c);																					//функция istream & istream::get(char & c) срабатывает по событию ввода <Enter>
	//cout <<endl<< "You input " << c << endl;

	//cout << "input char - ";
	//c = cin.get();																				//функция int istream::get() просто возвращает следующий символ из потока ввода								
	//cout << "char - " << c << endl;


	//нужно использовать либо cin либо wcin

	//wcout << "input wchar_t - ";
	//wcin.get(wc);																					//
	//wcout <<endl <<"You input " << wc << endl;

	//wcout << "input wchar_t - ";
	//wc = wcin.get();																				//
	//wcout << "wchar - " << wc << endl;													

	const int N{ 10 };
	char buffer[N]{'\0'};
	char buffer2[N]{ '\0' };
	char buffer3[N]{ '\0' };
	char buffer4[N]{ '\0' };




	//cout << endl << "input string - ";
	//cin.get(buffer, 10);												//функция istream & istream::get(char*, streamsize n) считывает n-1 символов, \n - оставляет в потоке
	//cout << endl << "You input: " << buffer << endl;

	//cout << endl << "input string - ";
	//cin.get(buffer, 9, '-');											//функция istream & istream::get(char*, streamsize n, char delim)
	//cout << endl << "You input: " << buffer << endl;


	//memset(buffer, '\0', N);
	//cout << endl << "Input string - ";
	//cin.getline(buffer, 6);												//функция istream& istream::getline(char*, streamsize n) символ \n - извлекается из потока но не вставляется в буфер			
	//cout << endl << "You input: " << buffer << endl;

	//memset(buffer, '\0', N);
	//cout << endl << "Input string - ";
	//cin.getline(buffer, 6, '\\');										//функция istream& istream::getline(char*, streamsize n, char delim)
	//cout << endl << "You input: " << buffer << endl;

	//memset(buffer, '\0', N);
	//cout << endl << "Input string - ";
	//cin.read(buffer, 9);												//считывает указанное колличество не добавляя \0 в конце		
	//cout << "You input: " << buffer << endl;
	
	//memset(buffer, '\0', N);
	//cout << endl << "Input string - ";
	//cin.get(c);
	//int countchar = cin.readsome(buffer, 5);							//считывает указанное колличество не добавляя \0 в конце, возвращает количество прочитанных символов	
	//cout << "You input: " <<countchar<<" chars "<< buffer << endl;
	//
	//int gc = cin.gcount();												//возвращает количество символов считанных в последнии раз		
	//cout << "gcount() = " << gc << endl;


	//игнорирование символов с извлечением из потока cin.ignore()
	//123456789123*5678
	//memset(buffer, '\0', N);
	//cin.get(buffer, 4);														//считываем 123	
	//cin.ignore();															//игнорируем 4
	//cin.ignore(6);															//игнорируем 567891	
	//cin.ignore(4, '*');														//игнорируем 4 пока не встретится '*'		
	//cin.get(c);																//потом считываем один символ			
	//char next_char = cin.peek();											//возвращаем следующий символ без его извлечения	

	//cout << "You input: " << buffer << " " << c << " nextchar - "<<next_char<<endl;

	//cin.unget();
	//cin.get(c);
	//cout << "Last readed char: " << c << endl;
	//
	//cin_properties(cin.putback('9'));										//пытаемся вернуть назад в поток символ, который не считывали	
	//
	//cin.get(c);
	//cout << "Last returned char: " << c << endl;



	//манипуляторы ввода-вывода
	//memset(buffer, '\0', N);
	//
	//cout << "Input char chain with \' \'" << std::ends;						//добавляем символ \0 в конец вывода
	//cin >> std::noskipws;													//отключаем игнорирование пробельных символов при вводе >>123 234 356 ->123 234 356 
	//cin.get(buffer, 10);
	//cout << "You input: " << buffer << std::endl;

	//cout << "Input char chain with \' \'" << std::ends;						//добавляем символ \0 в конец вывода
	//cin >> std::ws;															//включаем игнорирование пробельных символов
	//cin.get(buffer2, 10);
	//cout << "You input: " << buffer2 << std::endl;


	//манипуляторы для вывода вещественных чисел
	double num = 90.34567;
	//cout << '|' << std::setw(15) << std::showpos << std::left << num 
	//	 << '|' <<std::setw(15) << std::noshowpos << std::left << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << num 
	//	 << '|' << std::setw(15) << std::noshowpos << std::right << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::internal << num
 //		 << '|' << std::setw(15) << std::noshowpos << std::right << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << std::setfill('_') << num
	//	 << '|' << std::setw(15) << std::showpos << std::right << std::setfill('*') << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << std::setfill(' ') << num
	//	 << '|' << std::setw(15) << std::showpos << std::right << std::setfill(' ') << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << std::scientific << num
 //		 << '|' << std::setw(15) << std::showpos << std::right << std::scientific << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << std::defaultfloat << num
	//	 << '|' << std::setw(15) << std::showpos << std::right << std::defaultfloat << num << '|' << endl;

	//cout << '|' << std::setw(15) << std::showpos << std::right << std::hexfloat << num
 //		 << '|' << std::setw(15) << std::showpos << std::right << std::hexfloat << num << '|' << endl;

	////std::setprecision(n) совместно с std::defaultfloat задает общее количество знаков числа
	//cout << '|' << std::setw(15) <<std::setprecision(3) << std::defaultfloat << std::showpos << std::right << num
	//	<< '|' << std::setw(15) << std::setprecision(4) << std::defaultfloat << std::showpos << std::right  << num << '|' << endl;


	////std::setprecision(n) совместно с std::fixed задает количество знаков после запятой
	//cout << '|' << std::setw(15) << std::setprecision(6) << std::fixed << std::showpos << std::right << num
	//	<< '|' << std::setw(15) << std::setprecision(7) << std::fixed << std::showpos << std::right << num << '|' << endl;


	//манипуляторы для вывода целых чисел
	int intnum = 255;
	//cout << endl;
	//cout << '|' << std::setw(17) << std::dec << std::showpos << std::right << intnum << '|' << endl;
	//cout << '|' << std::setw(17) << std::hex << std::showpos << std::right << intnum << '|' << endl;
	//cout << '|' << std::setw(17) << std::uppercase<< std::hex << std::showpos << std::right << intnum << '|' << endl;
	//cout << '|' << std::setw(17) << std::oct << std::showpos << std::right << intnum << '|' << endl;
	//cout << '|' << std::setw(17) << std::dec <<std::showbase<< std::showpos << std::right << intnum << '|' << endl;


	//установка кодировки символов
	set_locale(RUS);

	cout << myendl;
	cout << "Hello ostream" << myendl << "I am glad to see You again" << myendl << "I am happy" << myendl;
	cout << "Привет ostream" << myendl << "Я рад видеть тебя снова" << myendl << "Я счастлив" << myendl;
	
	//игнорирование строк при вводе
	string instr;

	cout << "Input n - strings:" << endl;
	cin >> ignoreLine(3) >> instr;
	cout << "You have input: " << instr << endl;

	
}


//--------------------------------------тестирование файловых потоков---------------------------------------------------
void test_fstreams()
{
	set_locale(RUS);

	cout << "Работа с файловыми потоками вывода" << endl;

	//тестирование простого вывода ASCI кодов в файл
	cout << "вывод таблицы кодов ASCI" << endl;

	std::ofstream ofs;
	ofs.open("asci.txt", std::ios::out | std::ios::trunc);
	
	for (int i = 0; i < 256; i++)
	{
		ofs << static_cast<char>(i);
	}
	ofs.close();

	//вывод текста в файл
	cout << "вывод текста в файл" << endl;

	char text[]{"hello C++11, \n I am glad to see new C++ standart* - \n I hope that \n + I can find new excelent job with big salary, "};

	ofs.open("text.txt", std::ios::out | std::ios::trunc);
	ofs <<text;
	ofs.close();

	//вывод чисел в файл
	ofs.open("numbers.txt", std::ios::out | std::ios::trunc);
	
	for (int i = 0; i < 16; i++)
	{
		ofs.width(5);
		ofs.setf(std::ios::uppercase | std::ios::showpos | std::ios::showbase);
		ofs.setf(std::ios::hex, std::ios::basefield);
		ofs.fill('_');
		ofs << i <<endl;
	}
	
	for (int j = 0; j < 10; j++)
	{
		ofs << "|" << std::setw(10) << std::setprecision(5) << static_cast<double>(j)*3.14 << "|" << std::setw(10) << j << "|" << endl;
	}
	ofs.close();


	//комбинированный вывод
	std::ofstream cmb_ofs("cmb.txt", std::ios::out | std::ios::trunc);
	cmb_ofs.write(text, strlen(text));
	cmb_ofs.put('\n');
	
	std::array<int, 10> M{34,-12,45,67,-14,59,23,-18,13,90};

	for (auto i = M.begin(); i != M.end(); ++i)
	{
		cmb_ofs.width(4);
		cmb_ofs.setf(std::ios::showpos);
		cmb_ofs.setf(std::ios::internal, std::ios::adjustfield);
		cmb_ofs << (*i) << "<-"<<endl;
	}

	cmb_ofs.close();



	//тестирование файлового ввода посимвольное чтение
	cout << endl << "Чтение данных из файла" << endl;
	
	std::ifstream ifs("cmb.txt", std::ios::in);
	
	while (!ifs.eof())
	{
		char c = ifs.get();
		cout << c;
	}
	ifs.close();


	//чтение из файла с помощью разных функций ввода
	char strbuffer[512];
	memset(strbuffer, '\0', 512);
	int len = strlen(text);

	cout << endl << "length of text: " << len <<endl;

	std::ifstream strm("cmb.txt", std::ios::in);
	strm.get(strbuffer, len);											//читаем (len-1) символов до символа '\n'		
	cout << endl << "Прочитано из файла: " << strbuffer;

	memset(strbuffer, '\0', 512);
	strm.get(strbuffer, len, '*');										//читаем (len-1) символов до символа '*'	
	cout << endl << "Прочитано из файла: " << strbuffer;
	
	strm.getline(strbuffer, len);
	cout << endl << "Прочитано из файла: " << strbuffer;

	strm.getline(strbuffer, len, '+');
	cout << endl << "Прочитано из файла: " << strbuffer;

	memset(strbuffer, '\0', 512);
	strm.read(strbuffer, 11);
	cout << endl << "Прочитано из файла функцией read(): " << strbuffer;

	memset(strbuffer, '\0', 512);
	std::streamsize s = strm.readsome(strbuffer, 35);
	cout << endl << "Прочитано из файла функцией readsome(): "<<s<<" символов:" << strbuffer;

	strm.close();
	

	//работа с позициями
	std::ifstream ifstrm("numbers.txt", std::ios::in);
	ifstrm.seekg(0, std::ios::beg);
	
	char num[3];
	do {
		switch (ifstrm.peek())
		{
			case '_':
			case '0':
			case 'X':
				ifstrm.ignore();
				break;
			default: 
			{
				ifstrm.getline(num, 3);
				int a = atoi(num);
				cout << endl << "a = " << a;
			}
				 break;
		}
	} while (ifstrm.peek() != '|');



	ifstrm.seekg(-25, std::ios::end);
	ifstrm.getline(strbuffer, 25);

	cout << endl << "Last row: " << strbuffer;

	ifstrm.close();



	//создание потока для чтения и записи в файл
	cout << endl;
	cout << endl << "work with std::fstream class" << endl;
	
	std::fstream fs("text.txt", std::ios::in | std::ios::out);
	fs.seekp(0, std::ios::end);
	
	fs << "I like big salary CHF 5000-10000 or US dollar $";
	
	fs.seekg(0, std::ios::beg);
	fs.getline(strbuffer, 512, '$');
	
	cout << "Text from file text.txt: " << strbuffer<<endl;
	fs.close();

}




//--------------------------------------тестирование строковыых потоков------------------------------------------------------
void test_string_streams()
{
	//вывод в строковой поток
	std::ostringstream oss;
	oss << std::setw(5) << std::right << std::showpos << 53;
	oss << std::setw(5) << std::right << std::showpos << 7 << '\n';

	cout << endl;
	cout <<"String from std::ostringstream: " <<oss.str();

	//форматированый вывод чисел в строковый поток
	std::ostringstream os;
	int i = 10;
	while (--i)
	{
		os.width(7);
		os.fill('_');
		os.setf(std::ios::hex, std::ios::basefield);
		os.setf(std::ios::uppercase | std::ios::showbase);
		os << i << " ";
	}

	cout << endl <<"String from string stream: "<< os.str();


	//ввод данных из строкового потока
	string s("6   7 8 9.2");
	int a, b, c;
	float d;

	std::istringstream ist;
	ist.str(s);
	ist >> a >> b >> c >> d;

	cout << endl << "a = " << a << " b = " << b << " c = " << c <<" d = " << d << endl;

	//ввод данных в кортеж
	string str{"Hello 5 6.5 $"};

	string hello;
	int num;
	float f;
	char ch;

	std::istringstream is(str);
	is >> hello >> num >> f >> ch;

	std::tuple<string &, int&, float&, char&> tp = std::tie(hello, num, f, ch);

	cout << endl;
	cout <<"Tuple<>: "<< std::get<0>(tp) << " " << std::get<1>(tp) << " " << std::get<2>(tp)<<" " << std::get<3>(tp) <<endl;

}












