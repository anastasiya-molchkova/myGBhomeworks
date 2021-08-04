#include <iostream>
#include <string>    // для std::string
#include <clocale>   // для вывода сообщений на кириллице 
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> OOP3

using std::cout; using std::endl; using std::cin;
using std::string;

class Card
{
public:
	//перечисление мастей
	enum Suits
	{
		Diamonds, //буби
		Hearts,   //черви
		Spades,   //пики
		Clubs,    //крести
		suitsNumber //для обозначения количества мастей
	};

	//перечисление достоинств карт
	enum CardRanks
	{
<<<<<<< HEAD
		Ace = 1,
=======
>>>>>>> OOP3
		rank2,
		rank3,
		rank4,
		rank5,
		rank6,
		rank7,
		rank8,
		rank9,
		rank10,
		Jack,
		Queen,
		King,
<<<<<<< HEAD
=======
		Ace,
>>>>>>> OOP3
		//Jocker,
		ranksNumber //для обозначения количества достоинств
	};
private:
	//переменные для представления карты
	Suits m_suit;
	CardRanks m_rank;
	bool face;        // true, если карту видно
public:
	//конструктор класса Card с инициализацией карт (переменных-членов класса)
	Card(Suits suit = suitsNumber, CardRanks rank = ranksNumber, bool visible = false) : m_suit(suit), m_rank(rank), face(visible)
	{}

	//printCard функция возвращает принимаемую как параметр карту в виде строки типа ДостоинствоМасть
	string printCard() const
	{
		string cardCode{};

		//сначала разбираемся с достоинствами карты
		switch (m_rank)
		{
		case rank2:
<<<<<<< HEAD
		case rank3:
		case rank4:
		case rank5:
		case rank6:
		case rank7:
		case rank8:
		case rank9:
		case rank10:
			cardCode = m_rank;
=======
			cardCode = "2";
			break;
		case rank3:
			cardCode = "3";
			break;
		case rank4:
			cardCode = "4";
			break;
		case rank5:
			cardCode = "5";
			break;
		case rank6:
			cardCode = "6";
			break;
		case rank7:
			cardCode = "7";
			break;
		case rank8:
			cardCode = "8";
			break;
		case rank9:
			cardCode = "9";
			break;
		case rank10:
			cardCode = "10";
>>>>>>> OOP3
			break;
		case Jack:
			cardCode = "Валет";
			break;
		case Queen:
			cardCode = "Дама";
			break;
		case King:
			cardCode = "Kороль";
			break;
		case Ace:
			cardCode = "Туз";
			break;
		default:
			cardCode = "ErrorRank";
		}

		//теперь добавляем в строку масть
		switch (m_suit)
		{
		case Diamonds: //буби
			cardCode += "Буби";
			break;
		case Hearts:   //черви
			cardCode += "Черви";
			break;
		case Spades:   //пики
			cardCode += "Пики";
			break;
		case Clubs:    //крести
			cardCode += "Крести";
			break;
		default:
			cardCode += "ErrorSuit";
		}
		return cardCode;
	}

	//getCardValue возвращает значение карты (валет, королева или король — это 10, туз — это 11)
	unsigned short getCardValue() const
	{
		switch (m_rank)
		{
<<<<<<< HEAD
		case Ace:
=======
>>>>>>> OOP3
		case rank2:
		case rank3:
		case rank4:
		case rank5:
		case rank6:
		case rank7:
		case rank8:
		case rank9:
		case rank10:
<<<<<<< HEAD
			return m_rank;
=======
			return (m_rank + 2); // двойка имеет 0 индекс в перечислении, 3 - первый и т.д.
>>>>>>> OOP3
		case Jack:
		case Queen:
		case King:
			return 10;
<<<<<<< HEAD
=======
		case Ace:
			return 11;
>>>>>>> OOP3
		default:
			return 0;
		}
	}
	// переворачивает карту, т.е. если она была рубашкой вверх, то поворачивает лицом вверх, и наоборот
	void flip()
	{
		face = !face;
	}
<<<<<<< HEAD

	bool is_Ace()
	{
		return (m_rank == Ace) ? true : false;
	}
};

class Hand
{
protected:
	std::vector <Card*> cards_on_hand;
public:
	// добавляет в коллекцию карт новую карту
	void Add(Card* card)
	{
		cards_on_hand.push_back(card);
	}
	// очищает руку от карт
	void Clear()
	{
		/*
		for (auto card_ptr : cards_on_hand)
		{
			delete card_ptr;
			card_ptr = nullptr;
		}
		*/
		cards_on_hand.clear();
	}
	// возвращает сумму очков карт руки
	unsigned short GetValue()
	{
		unsigned short summ{ 0 };
		size_t aces_on_hand{ 0 };
		for (const auto& card_ptr : cards_on_hand)
		{
			summ += card_ptr->getCardValue();
			if (card_ptr->is_Ace())
				++aces_on_hand;
		}

		const int goal{ 21 };
		//считаем тузы как 11 вместо 1, если сумма меньше 11:
		while ((summ <= (goal-10)) && (aces_on_hand > 0))
		{
			summ += 10;
			--aces_on_hand;
		}

		return summ;
	}
=======
>>>>>>> OOP3
};

int main()
{
	// для вывода сообщений пользователю на кириллице
	setlocale(LC_CTYPE, "rus");

	Card c1(Card::Spades, Card::rank8, true);
	cout << c1.printCard() << endl;

	Card c2(Card::Clubs, Card::Queen);
	cout << c2.printCard() << endl;

<<<<<<< HEAD
	Card c3(Card::Clubs, Card::Ace);
	cout << c3.printCard() << endl;

	Card c4(Card::Spades, Card::Ace);
	cout << c4.printCard() << endl;

	Card c5(Card::Hearts, Card::Ace);
	cout << c5.printCard() << endl;

	Hand someHand;
	someHand.Add(&c1);
	someHand.Add(&c2);
	someHand.Add(&c3);
	someHand.Add(&c4);
	someHand.Add(&c5);
	std::cout << "Summ value on hand: " << someHand.GetValue() << std::endl;
	someHand.Clear();

	// main из методички:
	//cout << "\t\tWelcome to Blackjack!\n\n";

	//int numPlayers = 0;
	//while (numPlayers < 1 || numPlayers > 7)
	//{
	//	cout << "How many players? (1 - 7): ";
	//	cin >> numPlayers;
	//}

	//vector<string> names;
	//string name;
	//for (int i = 0; i < numPlayers; ++i)
	//{
	//	cout << "Enter player name: ";
	//	cin >> name;
	//	names.push_back(name);
	//}
	//cout << endl;

	//// игровой цикл
	//Game aGame(names);
	//char again = 'y';
	//while (again != 'n' && again != 'N')
	//{
	//	aGame.Play();
	//	cout << "\nDo you want to play again? (Y/N): ";
	//	cin >> again;
	//}

=======
>>>>>>> OOP3
	return 0;
}